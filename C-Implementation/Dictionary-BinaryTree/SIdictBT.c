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
struct tnode {
    char key[MAXKEYCHARS];
    int val;
    Tnode left;
    Tnode right;
};

struct si_dict {
    Tnode root;
};

SIdict makeSIdict() {
    SIdict dict = (SIdict) malloc(sizeof(struct si_dict));
    dict->head = NULL;
    return dict;
}

int hasKey(SIdict d, char* key) {
    int index = 1;
    nodePtr curr = d->head;

    while(curr != NULL) {
        if(strcmp(key, curr->key) == 0)
            return index;
        curr = curr->next;
        ++index;
    }

    return 0;
}

int addOrUpdate(SIdict d, char* key, int val) {
    int i, index;
    nodePtr node = d->head;
    //if it has, update
    if((index = hasKey(d, key))) {
        for(i=1; i < index && node != NULL; ++i)
            node = node->next;
        node->val = val;
        //free mem
        return 1;
    }
    //if it doesnt, make a new node
    nodePtr temp = (nodePtr) malloc(sizeof(struct node));
    temp->key = key;
    temp->val = val;

    //if the list dict is initally empty
    if(d->head == NULL) {
        node = NULL;
    }
    else {
        node = d->head;
    }

    d->head = temp;
    temp->next = node;

    return 0;
}

int lookup(SIdict d, char* key){
    nodePtr curr = d->head;
    while(curr != NULL){
        if(strcmp(key, curr->key) == 0){
            return curr->val;
        }
        curr = curr->next;
    }

    return -1;
}

int remKey(SIdict d, char* key){
    nodePtr prev = d->head;
    nodePtr rem;

    if(hasKey(d,key)==0){
        return 0;
    }
    if(strcmp(key, d->head->key) == 0){
        rem = d->head;
        d->head = rem->next;
    }else{
        while(prev != NULL){
            if(strcmp(key, prev->next->key) == 0){
                //remove the node from the linked list
                rem = prev->next;
                prev->next = rem->next;
                break;   
            }else{
                prev = prev->next;
            }
        }
    }

    rem->next = NULL;
    rem->val = 0;
    free(rem);
    return 1;
}

