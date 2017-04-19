#include <string.h>
#include "minprio.h"
#include <stdio.h>
#include <stdlib.h>

struct elements{
	int vertex;
	float weight;
};
typedef struct elements* Elements;

int test(void* temp, void* temp2){
	//printf("%i\n" , strcmp(temp,temp2));
	Elements item1 = (Elements) temp;
	Elements item2 = (Elements) temp2;
	if(item1->weight < item2->weight){
		return -1;
	}else if(item1->weight > item2->weight){
		return 1;
	}else{
		return 0;
	}
}

int test2 (void* temp, void* temp2){
	return strcmp(temp,temp2);
}


Elements makeElement(int i, float f){
	Elements elem = (Elements) malloc(sizeof(struct elements));
	elem->vertex = i;
	elem->weight = f;
	return elem;
}

void printArr(MinPrio qp);

int main(){
	MinPrio it = makeQueue(test2, 10);
	//printf("Non empty? %i\n", nonempty(it));

	//Elements e1 = makeElement(10,100.0);


	//Handle h = enqueue(it, e1);


	Handle h2 = enqueue(it, "5");
	Handle h3 = enqueue(it, "2");
	Handle h4 = enqueue(it, "7");
	Handle h5 = enqueue(it, "6");
	Handle h6 = enqueue(it, "4");
	Handle h7 = enqueue(it, "9");
	Handle h8 = enqueue(it, "3");

	//printf("FUCK ME %i\n", h4->pos);




	printArr(it);

	//printf("%s\n", "hi");
	void* shit = dequeueMin(it);
	void* balls = dequeueMin(it);
	void* fuck = dequeueMin(it);
	//printf("%s\n", "done");
	printArr(it);

	enqueue(it, "1");

	printArr(it);
	

	printf("Non empty? %i\n", nonempty(it));
	disposeQueue(it);
	printf("Non empty? %i\n", nonempty(it));

	return 0;
}