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

//Sorry for this really long crazy function :(
int remKey(SIdict d, char* key){
    if(hasKey(d,key)==0){
        return 0;
    }

    Tnode curr = d->root;
    Tnode prev = curr;

    while(curr != NULL) {
        if(strcmp(key, curr->key) == 0){
            //first case, both children null
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
                //second case, one child is null
                if(strcmp(curr->key,prev->key) < 0){
                    prev->left = curr->right;
                    free(curr);
                    curr = NULL;
                    return 1;
                }else if(strcmp(curr->key,prev->key) > 0){
                    prev->right = curr->right;
                    free(curr);
                    curr = NULL;
                    return 1;
                }else{
                    //if they are equal then you are trying to
                    //remove the root when it has 1 subtree
                    d->root = curr->right;
                    free(curr);
                    curr = NULL;
                    return 1;
                }
            }else if(curr->right == NULL){
                //second child is still null
                if(strcmp(curr->key,prev->key) < 0){
                    prev->left = curr->left;
                    free(curr);
                    curr = NULL;
                    return 1;
                }else if(strcmp(curr->key,prev->key) > 0){
                    prev->right = curr->left;
                    free(curr);
                    curr = NULL;
                    return 1;
                }else{
                    //if they are equal then you are trying to
                    //remove the root when it has 1 subtree
                    d->root = curr->left;
                    free(curr);
                    curr = NULL;
                    return 1;
                }
            }else{
                //Third case, when both children are non null
                if(strcmp(curr->key,d->root->key) == 0){
                    if(curr->right->left == NULL && 
                        curr->right->right == NULL && 
                        curr->left->left == NULL && 
                        curr->left->right == NULL){
                        if(strcmp(curr->right->key,curr->left->key) < 0){
                            d->root = curr->right;
                            curr->right->left = curr->left;
                            curr = NULL;
                            free(curr);
                            return 1;
                        }else if(strcmp(curr->right->key,curr->left->key) > 0){
                            d->root = curr->left;
                            curr->left->right = curr->right;
                            curr = NULL;
                            free(curr);
                            return 1;
                        }
                    }
                }
                //swap rightmost of left tree VALUES
                Tnode right_most = curr->right;
                Tnode save_left;
                Tnode save_right;
                //swap if the rightmost is the only right
                //  element after curr
                if(right_most->right == NULL){
                    if(right_most->left == NULL){
                        if(strcmp(prev->right->key,curr->key) == 0){
                            prev->right = right_most;
                            right_most->left = curr->left;
                            free(curr);
                            curr = NULL; 
                            return 1;
                        }else if(strcmp(prev->left->key,curr->key) == 0){
                            prev->left = right_most;
                            right_most->left = curr->left;
                            free(curr);
                            curr = NULL;
                            return 1;
                        }
                    }else{
                        curr->val = right_most->left->val;
                        strcpy(curr->key,right_most->left->key);
                        right_most->left = NULL;
                        free(right_most->left);
                    }
                    return 1;
                }
                while(right_most->right != NULL){
                    //do general stuff..
                    if(right_most->left != NULL){
                        save_left = right_most->left;
                        save_right = right_most;
                    }
                    right_most = right_most->right;
                }

                //if a minimum cannot be found..
                if(save_left == NULL){
                    right_most = curr->right;
                    if(strcmp(prev->right->key,curr->key) == 0){
                        prev->right = right_most;
                        right_most->left = curr->left;
                        free(curr);
                        curr = NULL; 
                        return 1;
                    }else if(strcmp(prev->left->key,curr->key) == 0){
                        prev->left = right_most;
                        right_most->left = curr->left;
                        free(curr);
                        curr = NULL;
                        return 1;
                    }
                }

                //if a minimum can be found..
                curr->val = save_left->val;
                strcpy(curr->key,save_left->key);
                save_right->left = NULL;
                free(save_right->left);

                return 1;
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
    return 0;
}

int insertNode(Tnode root, Tnode new_node) {
    if(strcmp(root->key, new_node->key) == 0){
        root->val = new_node->val;
        return 1;
    }

    if (strcmp(new_node->key, root->key) < 0) {
        if (root->left == NULL){
            root->left = new_node;
            return 0;
        }
        else{
            insertNode(root->left, new_node);
        }
    }

    if (strcmp(new_node->key, root->key) > 0) {
        if (root->right == NULL){
            root->right = new_node;
            return 0;
        }
        else{
            insertNode(root->right, new_node);
        }
    }

    return 0;
}


