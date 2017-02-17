/*
    I pledge my honor that I have abided by the stevens honor system
    Nick Gattuso
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "SIdict.h"

#define MAXKEYCHARS 32

void print(SIdict d);


typedef struct tnode* Tnode;
struct tnode{
    char* key;
    int val;
    Tnode left;
    Tnode right;
};

struct si_dict{
    Tnode root;
};

int insertNode(Tnode root, Tnode new_node);

SIdict makeSIdict() {
    SIdict dict = (SIdict) malloc(sizeof(struct si_dict));
    dict->root = NULL;
    return dict;
}

int hasKey(SIdict d, char* key) {
    int index = 1;
    Tnode curr = d->root;

    while(curr != NULL) {
        if(strcmp(key, curr->key) == 0)
            return index;
        else if(strcmp(key, curr->key)>0)
            curr = curr->right;
        else if(strcmp(key, curr->key)<0)
            curr = curr->left;
        ++index;
    }

    return 0;
}

//string copy
int addOrUpdate(SIdict d, char* key, int val) { 
    Tnode temp = (Tnode) malloc(sizeof(struct tnode));
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    
    temp->key = (char*) malloc(sizeof(char) * MAXKEYCHARS);
    strncpy(temp->key,key,MAXKEYCHARS);
    

    if(d->root == NULL){
        d->root = temp;
        return 0;
    }

    int r = insertNode(d->root,temp);

    // if(r==1){
    //     free(temp);
    // }

    //find a more efficent way

    return r;
    
   
    

    
}

int lookup(SIdict d, char* key){
    Tnode curr = d->root;

    while(curr != NULL) {
        if(strcmp(key, curr->key) == 0)
            return curr->val;
        else if(strcmp(key, curr->key)>0)
            curr = curr->right;
        else if(strcmp(key, curr->key)<0)
            curr = curr->left;
    }

     return -1;
 }

int remKey(SIdict d, char* key){
    // nodePtr prev = d->head;
    // nodePtr rem;

    // if(hasKey(d,key)==0){
    //     return 0;
    // }
    // if(strcmp(key, d->head->key) == 0){
    //     rem = d->head;
    //     d->head = rem->next;
    // }else{
    //     while(prev != NULL){
    //         if(strcmp(key, prev->next->key) == 0){
    //             //remove the node from the linked list
    //             rem = prev->next;
    //             prev->next = rem->next;
    //             break;   
    //         }else{
    //             prev = prev->next;
    //         }
    //     }
    // }

    // rem->next = NULL;
    // rem->val = 0;
    // free(rem);

    if(hasKey(d,key)==0){
        return 0;
    }

    Tnode curr = d->root;
    Tnode prev = curr;
    //three cases

    while(curr != NULL) {
        if(strcmp(key, curr->key) == 0){
            if(curr->left == NULL && curr->right == NULL){
                if(curr==d->root){
                    d->root = NULL;
                    return 1;
                }else{
                    if(strcmp(curr->key,prev->key) < 0){
                        free(prev->left);
                        prev->left = NULL;
                        return 1;
                    }else if(strcmp(curr->key,prev->key) > 0){
                        free(prev->right);
                        prev->right = NULL;
                        return 1;
                    }
                }
            }else if(curr->left == NULL){
                if(strcmp(curr->key,prev->key) < 0){
                    prev->left = curr->right;
                    free(curr);
                    curr = NULL;
                }else if(strcmp(curr->key,prev->key) > 0){
                    prev->right = curr->right;
                    free(curr);
                    curr = NULL;
                }
            }else if(curr->right == NULL){
                if(strcmp(curr->key,prev->key) < 0){
                    prev->left = curr->left;
                    free(curr);
                    curr = NULL;
                }else if(strcmp(curr->key,prev->key) > 0){
                    prev->right = curr->left;
                    free(curr);
                    curr = NULL;
                }
            }else{
                //swap rightmost of left tree
            }

        }
        //keep checking..
        else if(strcmp(key, curr->key)>0){
            prev = curr;
            curr = curr->right;
        }
        else if(strcmp(key, curr->key)<0){
            prev = curr;
            curr = curr->left;
        }
    }
     return 1;
}

int insertNode(Tnode root, Tnode new_node) {
   printf("%s\n"," IN insert");
   printf("%s\n", root->key);
   printf("%s\n", new_node->key);
    if(strcmp(root->key, new_node->key) == 0){
        root->val = new_node->val;
        printf("%s\n", "equal");
        return 1;
    }

    if (strcmp(new_node->key, root->key) < 0) {
        if (root->left == NULL){
            root->left = new_node;
            printf("%s\n", "left making new node");
            return 0;
        }
        else{
            printf("%s\n", "Left, contuning down");
            insertNode(root->left, new_node);
        }
    }

    if (strcmp(new_node->key, root->key) > 0) {
        if (root->right == NULL){
            root->right = new_node;
            printf("%s\n", "Right making new node");
            return 0;
        }
        else{
            printf("%s\n", "Right, contuning down");
            insertNode(root->right, new_node);
        }
    }

    return 0;
}



// int main(){
//     SIdict dict = makeSIdict();
//     addOrUpdate(dict, "Hello", 2);
//     addOrUpdate(dict, "Ass", 300);
//     addOrUpdate(dict, "Meow", 20);
//     printf("%i\n", hasKey(dict, "Ass"));

//     return 0;
// }

