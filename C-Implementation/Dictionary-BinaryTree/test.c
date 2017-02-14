/*
	I pledge my honor that I have abided by the stevens honor system
	Nick Gattuso
*/

#include <stdio.h>
#include "SIdictBST.c"


// void print(SIdict d) {
//     nodePtr curr = d->head;

//     while(curr != NULL) {
//         printf("%s\t%d\n", curr->key, curr->val);
//         curr = curr->next;
//     }
// }

void inorder(Tnode temp) {
   if (temp != NULL) {
      inorder(temp->left);
      printf("%d\n", temp->val);
      inorder(temp->right);
   }
}

int main(){
	SIdict dict = makeSIdict();
    addOrUpdate(dict, "Hello", 2);
    addOrUpdate(dict, "Ass", 300);
    addOrUpdate(dict, "Meow", 20);
    inorder(dict->root);
    addOrUpdate(dict, "Meow", 600);
    inorder(dict->root);
    //printf("%i\n", hasKey(dict, "Ass"));

}