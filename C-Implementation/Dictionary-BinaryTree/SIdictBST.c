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
    char key[MAXKEYCHARS];
    int val;
    Tnode left;
    Tnode right;
};

struct si_dict{
    Tnode root;
};

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
    strcpy(temp->key, key);
    temp->val = val;

    if(d->root == NULL){
        d->root = temp;
        return 0;
    }


    printf("%s\n" , d->root->key);
    printf("%s\n", temp->key);

    int r = insert(d->root,temp);

    printf("%s\n", "Out of insert..");

    if(r==1){
        free(temp);
    }

    printf("%s\n", "Hello");

    return 0;
    
    //if it doesnt, make a new node
    

    
}

int lookup(SIdict d, char* key){
    // nodePtr curr = d->head;
    // while(curr != NULL){
    //     if(strcmp(key, curr->key) == 0){
    //         return curr->val;
    //     }
    //     curr = curr->next;
    // }

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
     return 1;
}

int insert(Tnode root, Tnode new_node) {
   printf("%s\n"," IN insert");
   printf("%s\n", root->key);
   printf("%s\n", new_node->key);
    if(strcmp(root->key, new_node->key) == 0){
        root->val = new_node->val;
        printf("%s\n", "equal");
        return 1;
    }

    if (new_node->val < root->val) {
        if (root->left == NULL){
            root->left = new_node;
            printf("%s\n", "left making new node");
            return 0;
        }
        else{
            printf("%s\n", "Left, contuning down");
            insert(root->left, new_node);
        }
    }

    if (new_node->val > root->val) {
        if (root->right == NULL){
            root->right = new_node;
            printf("%s\n", "Right making new node");
            return 0;
        }
        else{
            printf("%s\n", "Right, contuning down");
            insert(root->right, new_node);
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

