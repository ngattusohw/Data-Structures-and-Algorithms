#include "linkedlist.h"
#include <stdio.h>


int main(int argc, char const *argv[]){
	linkedlist List;
	List.insertLast(1);
	printf("%s\n", "Gay!");
	List.insertLast(2);
	List.insertLast(3);
	List.insertLast(4);

	List.printElements();
	printf("%s\n", "Really after");
	/* code */
	return 0;
}