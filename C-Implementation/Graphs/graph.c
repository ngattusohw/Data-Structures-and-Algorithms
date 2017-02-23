#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "graph.h"

typedef struct node* NodePtr;
typedef float** Matrix;
typedef NodePtr* List;

struct node{
  unsigned int verts;
  float weight;
  NodePtr next;
};

struct graph{
	int representation;
	unsigned int numVert;
	List list;
	Matrix mat;
};

Matrix makeMatrix(int n);
List makeList(int n);
/* Make an empty graph with n vertices, using either adjacency matrix 
   or adjacency lists depending on whether rep==MATRIX or rep==LIST.
   Precondition: n>=1 and rep is MATRIX or LIST.
*/
Graph makeGraph(int n, int rep){
  Graph theGraph = (Graph) malloc(sizeof(struct graph));
	theGraph->numVert = n;
	theGraph->representation = rep;

	if(rep == 0){
   theGraph->mat = makeMatrix(n);
	}else if(rep == 1){
    theGraph->list = makeList(n);
  }

}


/* make a copy of g, but using the representation
   specified by rep (which is assumed to be MATRIX or LIST) 
*/
Graph cloneGraph(Graph G, int rep){
  Graph testGraph = (Graph) malloc(sizeof(struct graph));
  testGraph->numVert = G->numVert;
  

  if(rep == 0){
    if(G->representation == 0){
      //if its matrix and we have a matrix
      testGraph->representation = 0;
      testGraph->mat = makeMatrix(G->numVert);
      int x,y;
      for(x=0;x<G->numVert;x++){
        for(y=0;y<G->numVert;y++){
          testGraph->mat[x][y]=G->mat[x][y];
        }
      }
      return testGraph;
    }else{
      testGraph->representation = 1;
      testGraph->mat = makeMatrix(G->numVert);
      //if its matrix and we have a list
      int x;
      for(x=0;x<G->numVert;x++){
        NodePtr curr = G->list[x];
        while(curr!=NULL){
          testGraph->mat[x][curr->verts] = curr->weight;
          curr = curr->next;
        }
      }
      return testGraph;
    }
  }else{
    if(G->representation == 1){
      //if its list and we have a list
      testGraph->representation = 1;
      testGraph->list = makeList(G->numVert);

      
      for(x=0;x<G->numVert;x++){
        NodePtr curr = G->list[x];
      }
    }else{
      testGraph->representation = 0;
      //if its a list and we have a matrix
    }
  }
}


/* free the graph object and all its resources.
   Postcondition: g is no longer a valid pointer. 
*/
void disposeGraph(Graph G){

}


/* number of vertices */
int numVerts(Graph G){
	return G->numVert;
}


/* add edge from source to target with weight w, and return
   OK, if source and target are valid vertex numbers and
   there was no edge from source to target initially.
   Otherwise, make no change and return ERROR. 
*/
int addEdge(Graph G, int source, int target, float w){

}


/* delete edge from source to target, and return
   OK, if there was an edge from source.
   Otherwise, make no change and return ERROR. 
*/
int delEdge(Graph G, int source, int target){

}


/* return weight of the edge from source to target,
   if there is one; otherwise return INFINITY.
   Return -1.0 if source or target are out of range.
*/
float edge(Graph G, int source, int target){

}


/* a freshly allocated array with the successor
   vertices of source, if any, followed by an entry with -1
   to indicate end of sequence.
   Precondition: source is in range.
   Ownersip: the caller is responsible for freeing the array.
*/
int* successors(Graph G, int source){

}


/* a freshly allocated array with the predecessor
   vertices of target, if any, followed by an entry with -1
   to indicate end of sequence.
   Precondition: target is in range.
   Ownersip: the caller is responsible for freeing the array.
*/
int* predecessors(Graph G, int target){

}

Matrix makeMatrix(int n){
  float **temp = (float **)malloc(n * sizeof(float *));
   int i=0;
    for (i=0; i<n; i++)
      temp[i] = (float *)malloc(n * sizeof(float));
    return temp;
}

List makeList(int n){
  return (NodePtr*)malloc(n * sizeof(NodePtr*));
}
