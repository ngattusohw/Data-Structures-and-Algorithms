/* some tests illustrating the use of thestack.c */

#include <stdlib.h>
#include <stdio.h>

#include "thestack.h"

int main() {
    Stack p = makeStack(10); 
    //showing that popping works
    pushStack(p, 1);
    pushStack(p, 2);
    pushStack(p, 3);
    pushStack(p, 4);
    pushStack(p, 5);
    pushStack(p, 6);

    //showing that printing works
    printStack(p);

    //showing that getting the result from the pop works
    printf("%s %i\n" , "Result of the pop is :: " , popStack(p));

    //printing after the first pop
    printStack(p);

    //popping everything but the last one
    popStack(p);
    popStack(p);
    popStack(p);
    popStack(p);

    printStack(p);

    //showing that the program doesnt break if you pop with nothing in the stack
    popStack(p);
    printStack(p);
    popStack(p);
    printStack(p);

    //showing that the program wont break if you try to push into an empty stack
    pushStack(p, 100);
    printStack(p);
    popStack(p);
    printStack(p);


    return 0; 
}
