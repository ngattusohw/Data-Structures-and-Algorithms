#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "dlqueue.h"

Queue makeQueue(){
	Queue q = (Queue) malloc(sizeof(struct queue));
	q->front = q->back = NULL;
	return q;
}

void enqueue(Queue qp, int val){
	Dnode n = (Dnode) malloc(sizeof(struct dnode));
	n->val = val;
	n->next = qp->front;
	n->prev = NULL;
	if(qp->front != NULL)
		qp->front->prev = n;
	else
		qp->back = n;
	qp->front = n;
}

int nonempty(Queue qp){
	return qp->front != NULL;
}

int dequeue(Queue qp){
	assert(qp->front !=NULL);
	Dnode back = qp->back;
	int result = back->val;
	qp->back = back->prev;
	if(back->prev != NULL)
		back->prev->next = NULL;
	else
		qp->front = NULL;
	back->val =0;
	back->prev = NULL;
	back->next = NULL; //You want to zero out your vals, just in case..
	free(back);
	return result;
}

int main() {
	Queue q0, q1;
	q0 = makeQueue();
	enqueue(q0, 1);
	enqueue(q0, 2);
	enqueue(q0, 3);
	while( nonempty(q0))
		printf("%i ", dequeue(q0));
	printf("\n");
	q1 = makeQueue();
	int impossible = dequeue(q1);
}				


