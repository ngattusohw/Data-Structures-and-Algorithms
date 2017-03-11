#include <stdlib.h>
#include <stdio.h>
#include "dfs.h"

void dfsvisit(Graph g, int y);
// struct stack{
//     int* theStack; // the array for the stack
//     int top; //the top most index of the stack
//     int bottom; // the bottom most index of the stack
// };

// typedef struct stack* StackP;

// StackP makeStack(int how_many);
// void pushStack(StackP s, int push);
// int popStack(StackP s);
// void printStack(StackP s);


// StackP makeStack(int how_many){
// 	StackP return_stack = (Stack) malloc(sizeof(struct stack));
// 	return_stack->theStack = (int*) malloc(sizeof(int) * how_many);
// 	return_stack->top = 0;
// 	for(int x=0;x<how_many;x++){
// 		return_stack->theStack[x] = -1;
// 	}
// 	return return_stack;
// }

// void pushStack(StackP s, int push){
// 	int x;
// 	for(x=0;s->theStack[x]!=-1;x++)
// 		//test to see if it does it with the conditional bc idk
// 	s->theStack[x] = push;
// 	s->top = x;
// }

// int popStack(StackP s){
// 	int x,returnpop;
// 	if(s->top == 0){
// 		return -1;
// 	}
// 	for(x=0;s->theStack[x]!=-1;x++)

// 	if(s->theStack[x]==-1){
// 		x--;
// 	}

// 	returnpop = s->theStack[x];
// 	s->theStack[x] = -1;
// 	s->top--;
// }

// void printStack(StackP s){
// 	if(s->top==0){
// 		return;
// 	}

// 	for(int x=0;x<s->top;x++){
// 		printf("%i\n", s->theStack[x]);
// 	}

// }
int fcounter=0;
int counter;
int* color;
DFSinfo theDFS;

DFSinfo DFS(Graph g){

	theDFS = (DFSinfo) malloc(sizeof(struct dfsinfo));
	theDFS->discover = (int*) malloc(sizeof(int) * numVerts(g));
	theDFS->finish = (int*) malloc(sizeof(int) * numVerts(g));
	theDFS->parent = (int*) malloc(sizeof(int) * numVerts(g));
	theDFS->finorder = (int*) malloc(sizeof(int) * numVerts(g));
	color = (int*) malloc(sizeof(int) * numVerts(g));

	theDFS->graph = g;

	for(int x=0;x<numVerts(g);x++){
		theDFS->discover[x] = 0;
		theDFS->finish[x] = 0;
		theDFS->parent[x] = -1;
		theDFS->finorder[x] = 0;
		color[x] = 0;
	}

	counter=0;
	for(int y=0;y<numVerts(g);y++){
		if(color[y]==0){
			dfsvisit(g,y);
		}
	}
	return theDFS;
}

void dfsvisit(Graph g, int y){
	color[y] = 1;
	counter++;
	theDFS->discover[y] = counter;
	int* succ = successors(g,y);
	for(int x=0;succ[x]!=-1;x++){
		if(color[succ[x]]==0){
			theDFS->parent[succ[x]] = y;
			dfsvisit(g,succ[x]);
		}
	}
	color[y]=2;
	theDFS->finorder[fcounter] = y; //add to finorder
	fcounter++;
	counter++;
	theDFS->finish[y] = counter;
	//return;
}


