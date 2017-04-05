#include <string.h>
#include "SVdict.h"
#include <stdio.h>
#include <stdlib.h>


/* Interface for dictionaries that map strings to "void pointers".
 *
 * A key is a null-terminated string.  The associated value has 
 * type void*, so it can be any pointer type and is not dereferenced 
 * by the dictionary implementation code.
 * 
 * The implementation should use AVL trees as discussed in class and Levitin 6.3.
 */



typedef struct node* Node; 
struct node { void* val; 
    Node right; 
    Node left; 
    char* key; 
    Node parent; 
    int height; 
};

typedef struct sv_dict* SVdict;
struct sv_dict {
    Node node;
};



/* make an empty dictionary */
SVdict makeSVdict(){
	SVdict d = (SVdict) malloc(sizeof(struct sv_dict));
	d->node = NULL;
	return d;
}

/* SOME GENERAL HELPER METHODS */
int getMax(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

int height(Node n){
    if (n == NULL){
        return -1;
    }
    return n->height;
}

int getHeight(Node n){
    if(n->left != NULL && n->right != NULL){
        return 1 + getMax(getHeight(n->left), getHeight(n->right));
    }else if(n->left == NULL && n->right != NULL){
        return 1 + getHeight(n->right);
    }else if(n->left != NULL && n->right == NULL){
        return 1 + getHeight(n->left);
    }else{
        return 0;
    }
}

void preorderHeights(Node n){
    if(n==NULL){
        return;
    }else{
        n->height = getHeight(n);
        preorderHeights(n->left);
        preorderHeights(n->right);
    }
}

int getBalance(Node n){
    if (n == NULL){
        return 0;
    }
    return height(n->left) - height(n->right);
}


void rightRotate(Node node, SVdict d){
    node->left->right = node;
    node->left->parent = node->parent;
    
    if(node->parent!=NULL){
        node->parent->right = node->left;
    }

    node->parent = node->left;

    if(node->left->parent == NULL){
        d->node = node->left;
    }

    node->left = NULL;
}
 
void leftRotate(Node node, SVdict d){

    if(node->right->left!=NULL){
        Node temp = node->right->left;

        node->right->left = node;
        node->right->parent = node->parent;
   

        if(node->parent!=NULL){
            node->parent->left = node->right;
        }

        node->parent = node->right;


        if(node->right->parent == NULL){
            d->node = node->right;
        }

        node->right = NULL;

        d->node->left->right = temp;

    }else{
        node->right->left = node;
        node->right->parent = node->parent;

        if(node->parent!=NULL){
            node->parent->left = node->right;
        }

        node->parent = node->right;

        if(node->right->parent == NULL){
            d->node = node->right;
        }

        node->right = NULL;
    }
}

void postDispose(Node n){
    if(n==NULL){
        return;
    }
    postDispose(n->right);
    postDispose(n->left);
    free(n->key);
    n->key = NULL;
    free(n);
}


/* Free the dictionary object and all its resources.
 * Precondition: d is non-null and has been initialized by makeSVdict. 
 * Postcondition: d is no longer a valid pointer. 
 * Alert: the caller should set their variable to null.
 * The dictionary owns its copies of the keys, but does not own
 * the values so those are not freed. 
 */
void disposeSVdict(SVdict d){
    postDispose(d->node);
    free(d);
}


/* whether key is present 
 * Return 1 if present else 0.
 * Precondition: d and key are non-null. 
 */
int hasKey(SVdict d, char* key){
	Node temp = d->node;
	while(temp != NULL){
	  if(strcmp(key,temp->key)>0){
	  	temp = temp->right;
	  }else if(strcmp(key,temp->key) <0){
	  	temp = temp->left;
	  }else{
	    return 1;
	  }
	}
	return 0;
}

int insert(Node node, Node newNode, SVdict d){
    if(d->node == NULL){
        d->node = newNode;
        d->node->height = 1 + getMax(height(d->node->left), height(d->node->right));
        return 0;
    }

	if (strcmp(newNode->key, node->key) < 0){
        if(node->left == NULL){
            node->left = newNode;
            newNode->parent = node;
        }else{
            insert(node->left, newNode, d);
        }
	}else if (strcmp(newNode->key, node->key) > 0){
        if(node->right == NULL){
          node->right = newNode;
          newNode->parent = node;
        }else{
            insert(node->right, newNode, d);
        }
    }else{
        node->val = newNode->val;
        return 1;
    }

    preorderHeights(d->node);
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && strcmp(newNode->key, node->left->key) < 0){
        rightRotate(node,d);
        return 0;
    }
 
    // Right Right Case
    if (balance < -1 && strcmp(newNode->key, node->right->key) > 0){
        leftRotate(node,d);
        return 0;
    }
 
    // Left Right Case
    if (balance > 1 && strcmp(newNode->key, node->left->key) > 0){
        leftRotate(node->left,d);
        rightRotate(node,d);
        return 0;
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(newNode->key, node->right->key) < 0){
        rightRotate(node->right, d);
        leftRotate(node, d);
        return 0;
    }
    return 0;
}

/* map key to val; return 1 if key was already present else 0 
 * Precondition: d and key are non-null. 
 * Stores a copy of key, not the pointer itself.
*/
int addOrUpdate(SVdict d, char* key, void* val){
	Node theNode = (Node) malloc(sizeof(struct node));
	theNode->val = val;
	theNode->left = NULL;
	theNode->right = NULL;
    theNode->parent = NULL;
    
	theNode->key = (char*) malloc(sizeof(char) * MAXKEYLEN);
	strncpy(theNode->key,key,MAXKEYLEN);


    int toReturn = insert(d->node, theNode, d);
  	return toReturn;
}


/* get value associated with key, or NULL if key not in d.
 * Precondition: d and key are non-null.
 */
void* lookup(SVdict d, char* key){
	Node temp = d->node;
	while(temp != NULL){
        if(strcmp(key,temp->key)>0){
            temp = temp->right;
        }else if(strcmp(key,temp->key) <0){
            temp = temp->left;
        }else{
            return temp->val;
        }
	}
	return 0;
}

/* Remove key/val; return 1 if key was already present else 0
   Precondition: d and key are non-null. */
int remKey(SVdict d, char* key){
    printf("%s\n", "I didn't malloc enough time for this assignment to do this function");
    return 0;
}

void print(Node root, int x){
    for(int i = 0; i < x; i++){
        printf(" ");
    }

    if(root == NULL){
        printf("%s\n", EMPTY_PRINT);
        return;
    }

    printf("%s\n", root->key);
    print(root->left, x+1);
    print(root->right, x+1);
}


/* Print the keys, in pre-order, to standard output. 
 * Print each key, preceded by some spaces, and followed by \n.  
 * If a subtree is empty, print EMPTY_PRINT.  
 * Nothing else should be printed. 
 * The number of preceding spaces should indicate the depth of the
 * tree, INDENT spaces per level, with no spaces for the root. 
 * Precondition: d is non-null. 
 * Hint: write a recursive helper function that has an integer 
 * parameter for the depth.
 */
void preorderKeys(SVdict d){
    if(d->node == NULL){
        printf("%s\n", EMPTY_PRINT);
    }
    print(d->node, 0);
}

