/*

Matt Poltorak and Nick Gattuso
Stevens!

 */



#include <string.h>
#include "minprio.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


/* Assume g is non-null pointer to non-empty graph.
 * Assume g is a symmetric graph, so it can be 
 * considered as an undirected graph.  
 * (In particular, the weight u->v must equal weight v->u
 * for every u,v.)
 * Assume the weights are not INFINITY and g is connected.
 * 
 * Return a minimum spanning tree, as a new graph.
 * (So it will have the same number of vertices, 
 * but only some of the edges.  Weights same as in g.)
 * 
 * Implement this using Prim's algorithm.  The implementation only
 * needs to access the input graph via the graph.h API, so 
 * it shouldn't matter which representation the input uses.
 * Since the tree will be a sparse graph, use LIST representation 
 * for the output graph.
 * 
 */

struct elements{
	int vertex; 
	float weight;
};
typedef struct elements* Elements;

Elements makeElement(int vertex, float weight){
	Elements el = (Elements) malloc(sizeof(struct elements));
	el->vertex = vertex;
	el->weight = weight;
	return el;
}

int comp(void* temp1, void* temp2){
	Elements Eltemp1 = (Elements)temp1;
	Elements Eltemp2 = (Elements)temp2;

	if(Eltemp1->weight < Eltemp2->weight){
		return -1;
	}else if(Eltemp1->weight > Eltemp2->weight){
		return 1;
	}else{
		return 0;
	}
}

Graph minSpanTree(Graph g){

	Graph newGraph = makeGraph(numVerts(g), 1);
	int root = 0;
	MinPrio minQueue = makeQueue(comp, numVerts(g));//Change max size if need be
	int link[numVerts(g)];
	Handle hold_handle[numVerts(g)];

	// for (int i = 0; i < numVerts(g); ++i)
	// {
	// 	link[i] = NULL;
	// }

	hold_handle[0] = enqueue(minQueue, (void*) makeElement(root,0));
	for (int i = 0; i < numVerts(g); ++i)
	{
		if(link[i] != root){
			hold_handle[i] = enqueue(minQueue, (void*) makeElement(i, INFINITY));
		}
	}

	int inArr[numVerts(g)];

	for (int i = 0; i < numVerts(g); ++i)
	{
		inArr[i] = 1; //all el in array
	}

	while(nonempty(minQueue) == 1){
		Elements minEl = makeElement(-1,-1);
		minEl = dequeueMin(minQueue);
		inArr[minEl->vertex] = 0;
		hold_handle[minEl->vertex] = NULL;

		int* succArray = successors(g, minEl->vertex);



		for (int i = 0; succArray[i] != -1; i++)
		{
			// void* hold = minQueue->the_handle[0]->content;
			// Elements el_hold = (Elements) hold;
							
			//check if the handle for that element is in the array
			
//&& edge(g, minEl->vertex, hold_handles[succArray[i]]) < el_hold->weight)


			if(inArr[succArray[i]] == 1){
				Handle w = hold_handle[succArray[i]];
				Elements e = (Elements) w->content;
				if(edge(g, minEl->vertex, e->vertex) < e->weight){
					link[succArray[i]] = minEl->vertex;
					e->weight = edge(g, minEl->vertex, e->vertex);

					decreasedKey(minQueue, w);
				}

				


				// Handle handy = (Handle) malloc(sizeof(struct handle));
				// handy->content = makeElement(succArray[i], el_hold->weight);
				
			}
			// if(edge(g, minEl->vertex, i) < minQueue->the_handle[i]->content->weight){
			// 	link[i] = minEl->vertex;
			// 	minQueue->the_handle[i]->content->weight = edge(g, minEl->vertex, i);
			// 	decreasedKey(minQueue, i);
			// }
		}

	}

	for(int i = 0; i < numVerts(g); i++){
		addEdge(newGraph, i, link[i], edge(g,i,link[i]));
		addEdge(newGraph, link[i],i , edge(g,i,link[i]));
	}

	return newGraph;
}



//use min prio to pop lowest weight edge