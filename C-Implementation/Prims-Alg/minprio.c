#include <string.h>
#include "minprio.h"
#include <stdio.h>
#include <stdlib.h>



struct minprio{
	Handle* the_handle;
	int max;
	Comparator the_comp;
	int placement;
};

void printArr(MinPrio qp){
	printf("%s\n", "Printing the array");
	int x = 0;
	Handle hold = qp->the_handle[x];
	while(hold!=NULL){
		printf("%s\n", hold->content);
		x++;
		hold = qp->the_handle[x];
	}

	printf("%s\n", "Finish");

}


/* make an empty queue
 * Items will be compared using comp.
 *
 * It' the client's responsibility to ensure that
 * there are never more than maxsize elements in queue.
 */
MinPrio makeQueue(Comparator comp, int maxsize){
	MinPrio it = (MinPrio) malloc(sizeof(struct minprio));
	it->max = maxsize;
	it->the_handle = (Handle*) malloc(sizeof(struct handle) * maxsize);
	it->the_comp = comp;
	it->placement = 0;

	for(int x=0;x<maxsize;x++){
		it->the_handle[x] = NULL;
		//it->the_handle[x]->content = NULL;
	}

	return it;
}


/* dispose of memory owned by the queue
 * Namely: the queue object, the array, and the Handles.
 * The Handle contents are the responsibility of the client.
 */
void disposeQueue(MinPrio qp){
	if(qp!=NULL){
		int x = qp->placement - 1;
		Handle next = qp->the_handle[x];
		//printf("%s\n", qp->the_handle[x]->content);
		while(next!=NULL && x!=-1){ //new indexing at 1
			qp->the_handle[x] = NULL;
			free(qp->the_handle[x]);
			x--;
			next = qp->the_handle[x];
			//printf("%i\n", x);
		}
	}

	qp->placement = 0;
	free(qp->the_handle);
	free(qp);
	qp = NULL;
}


MinPrio reOrder(MinPrio qp, int i){
	MinPrio np = qp;
	int index = i;
	void* current = np->the_handle[index];
	void* temp;
	Comparator comp = np->the_comp;
	while(current!=np->the_handle[0]->content){
		if(np->the_handle[index]!=NULL && np->the_handle[index/2]!=NULL){
			if(comp(np->the_handle[index]->content,np->the_handle[index/2]->content)<=0){ //min so <=
				temp = np->the_handle[index/2]->content;
				//printf("Temp :: %s\n", temp);
				np->the_handle[index/2]->content = np->the_handle[index]->content;
				current = np->the_handle[index/2]->content;
				//printf("New Parent:: %s\n", np->the_handle[index/2]->content);
				np->the_handle[index]->content = temp;
				index/=2;
			}else{
				break;
			}
		}else{
			break;
		}
	}

	return np;
}

//swaps the contents of h1 and h2
void swapContents(Handle h1, Handle h2){
	void* temp = h1->content;
	h1->content = h2->content;
	h2->content = temp;
}


/* enqueue 
 * Assumes queue currently contains less than maxsize elements.
 * Assumes qp and item non-null. 
 * Returns a Handle containing the item, for use with decreaseKey.
 */
Handle enqueue(MinPrio qp, void* item){
	void* the_item = (void*) item;

	int index = qp->placement;
	if(index>qp->max){
		printf("%s\n", "Array is at maximum size");
		return NULL;
	}else if(index==0){
		qp->the_handle[index] = (Handle) malloc(sizeof(struct handle));
		qp->the_handle[index]->content = the_item;
		qp->the_handle[index]->pos = index;
		qp->placement++;
		//printf("%s\n" , qp->the_handle[index]->content);
		return qp->the_handle[index];
	}

	qp->the_handle[index] = (Handle) malloc(sizeof(struct handle));
	qp->the_handle[index]->content = the_item;
	qp->the_handle[index]->pos = index;
	Handle return_handle = (Handle) malloc(sizeof(struct handle));
	return_handle->content = qp->the_handle[index]->content;
	return_handle->pos = qp->the_handle[index]->pos;

	//printf("SHIT DICK 1 %s\n", return_handle->content);
	qp = reOrder(qp,index);
	//printf("SHIT DICK 2 %s\n", return_handle->content);
	qp->placement++;
	//printf("%s \n", qp->the_handle[index]->content);
	return return_handle;
}


/* 1 if queue has elements, else 0 (assuming qp non-null) */
int nonempty(MinPrio qp){
	if(qp->placement==0){
		return 0;
	}else{
		return 1;
	}
}


/* dequeue and return a minimum element according to the comparator.
 * Assumes qp non-null and queue nonempty.
 * Frees the handle, so client should no longer use handle.
 */
void* dequeueMin(MinPrio qp){
	void* the_return = qp->the_handle[0]->content; // this will be a problem i think
	if(qp->placement==1){
		//if theres only one
		qp->the_handle[0]->content = NULL;
		free(qp->the_handle[0]);
		qp->placement=0;
		return the_return;
	}else if(qp->placement==2){
		//if theres only two
		swapContents(qp->the_handle[0],qp->the_handle[1]);
		qp->the_handle[1]->content = NULL;
		free(qp->the_handle[1]);
		qp->placement=1;
	}else{
		//now general case..
		Comparator comp = qp->the_comp;
		Handle the_min = qp->the_handle[0];
		qp->the_handle[0]->content = qp->the_handle[(qp->placement)-1]->content;
		qp->the_handle[(qp->placement)-1] = NULL;
		//placement--?
		Handle hold = qp->the_handle[0];
		int index = 0;
		while(hold!=NULL){
			if(index==0){
				//if its the top
				if(qp->the_handle[2]!=NULL && qp->the_handle[1]!=NULL){
					if(comp(qp->the_handle[1]->content,qp->the_handle[2]->content)<0){
					swapContents(qp->the_handle[0],qp->the_handle[1]);
					index = 1;
					hold = qp->the_handle[index];
					}else{
						swapContents(qp->the_handle[0],qp->the_handle[2]);
						index = 2;
						hold = qp->the_handle[index];
					}
				}else{
					index = 2;
					hold = qp->the_handle[2];

					
					//break;
				}
			}else{
				//if its not the top
				if(qp->the_handle[index*2]!=NULL && qp->the_handle[(index*2)+1]!=NULL){
					if(comp(qp->the_handle[index*2]->content,qp->the_handle[(index*2) +1]->content)<0){
						swapContents(hold,qp->the_handle[index*2]);
						index*=2;
						hold = qp->the_handle[index];
					}else{
						swapContents(hold,qp->the_handle[(index*2) + 1]);
						index = (index * 2) + 1;
						hold = qp->the_handle[index];
					}
				}else{
					break;
				}
			}
		}
		qp->placement--;
	}
	return the_return;
}


/* decrease the item's key
 * Must be called whenever comparison value may have changed.
 * Must only decrease comparison value (i.e. raise priority).
 *
 * Assumes qp non-null and hand is in the queue. 
 */
void decreasedKey(MinPrio qp, Handle hand){
	int index = hand->pos;
	qp = reOrder(qp,index);
	//when called, goes throught the whole heap and makes sure that everything is all good
}

