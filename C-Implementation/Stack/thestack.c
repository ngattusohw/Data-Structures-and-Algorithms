#include <stdlib.h>
#include <stdio.h>

#include "thestack.h"


struct stack{
    int* theStack; // the array for the stack
    int top; //the top most index of the stack
};


Stack makeStack(int how_many){
	Stack return_stack = (Stack) malloc(sizeof(struct stack));
	return_stack->theStack = (int*) malloc(sizeof(int) * how_many);
	return_stack->top = -1;
	for(int x=0;x<how_many;x++){
		return_stack->theStack[x] = -1;
	}
	return return_stack;
}

void pushStack(Stack s, int push){
	if(s->theStack[0]==-1){
		s->theStack[0] = push;
		s->top=0;
		return;
	}

	int x;
	for(x=0;s->theStack[x]!=-1;x++){
		//test to see if it does it with the conditional bc idk
	}
	s->theStack[x] = push;
	s->top = x;
	printf("%s %i\n", "In pushStack" , s->top);
}

int popStack(Stack s){
	int x,returnpop;
	if(s->top == -1){
		return -1;
	}
	for(x=0;s->theStack[x]!=-1;x++){

	}

	if(s->theStack[x]==-1){
		x--;
	}

	returnpop = s->theStack[x];
	s->theStack[x] = -1;
	s->top--;

	return returnpop;
}

void printStack(Stack s){
	if(s->top==-1){
		printf("%s\n", "The Stack is empty");
		return;
	}

	printf("%s\n", "Printing the Stack::");
	for(int x=0;x<=s->top;x++){
		printf("%i\n", s->theStack[x]);
	}

}