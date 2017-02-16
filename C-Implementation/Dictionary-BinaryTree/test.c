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
      printf("%s\n", "In inorder");
      inorder(temp->left);
      printf("%d\n", temp->val);
      inorder(temp->right);
   }
}

int main(){
	SIdict dict = makeSIdict();
    addOrUpdate(dict, "Hello", 2);
    printf("%s\n", "FIRST ADD COMPLETE");
    addOrUpdate(dict, "Ass", 300);
    printf("%s\n", "SECOND ADD COMPLETE");
    addOrUpdate(dict, "Meow", 20);
    printf("%s\n", "Third ADD COMPLETE");
    //inorder(dict->root);
    //addOrUpdate(dict, "Meow", 600);
    addOrUpdate(dict, "Ass", 100);
    //inorder(dict->root);
    //printf("%i\n", hasKey(dict, "Ass"));
    inorder(dict->root);

}