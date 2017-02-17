/*
	I pledge my honor that I have abided by the stevens honor system
	Nick Gattuso
*/

#include <stdio.h>
#include "SIdictBST.c"

void inorder(Tnode temp) {
   if (temp != NULL) {
     // printf("%s\n", "In inorder");
      inorder(temp->left);
      printf("%s\n", temp->key);
      inorder(temp->right);
   }
}

int main(){
	SIdict dict = makeSIdict();
    addOrUpdate(dict, "First", 10);
    addOrUpdate(dict, "Second", 20);
    addOrUpdate(dict, "Third", 30);
    addOrUpdate(dict, "Fourth" , 40);
    addOrUpdate(dict, "Fifth" , 50);

    inorder(dict->root);
    addOrUpdate(dict, "Fifth" , 500);

    inorder(dict->root);

    printf("%i\n", lookup(dict, "Fifth"));
    printf("%i\n", lookup(dict, "not here!"));
    printf("%i\n", hasKey(dict, "First"));

    printf("%i\n",remKey(dict, "First"));
    inorder(dict->root);
    printf("%i\n", remKey(dict, "Second"));
    inorder(dict->root);
    printf("%i\n", remKey(dict, "Fourth"));
    inorder(dict->root);
    printf("%i\n", remKey(dict, "Third"));
    inorder(dict->root);
    printf("%i\n", remKey(dict, "Fifth"));
    addOrUpdate(dict, "Fifth" , 20000);
    printf("%i\n", remKey(dict, "Fifth"));

    inorder(dict->root);



}