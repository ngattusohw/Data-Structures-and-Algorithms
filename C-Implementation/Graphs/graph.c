#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "graph.h"


/*
  I pledge my honor that I have abided by the stevens honor system
  Nick Gattuso


  ex1 :: x(1) + 5 * (n-1) = 5(n-1)
    b) 3^(n-1)x(1)=4 * 3^(n-1)
    c)(n(n+1))/2
    d) 2n-1
    e) 1+log(base3)n
  ex4 :: q(n-1) + 2n -1 = n^2
    b) M(n) = n-1
    c) C(n) = 3(n-1)

    Most of my time complexities will be O(n^2) , because I need to traverse through
    the matrix will 2 for loops, or a for loop and a while loop for List
*/

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
    int x,y;
    for(x=0;x<n;x++){
      for(y=0;y<n;y++){
        theGraph->mat[x][y]=-1;
      }
    }
	}else if(rep == 1){
    theGraph->list = makeList(n);
  }

  return theGraph;
}


/* make a copy of g, but using the representation
   specified by rep (which is assumed to be MATRIX or LIST) 
*/
Graph cloneGraph(Graph G, int rep){
  Graph clone = makeGraph(G->numVert,rep);
  if(G->list == NULL){
    int x,y;
    for(x=0;x<G->numVert;x++){
      for(y=0;y<G->numVert;y++){
        if(G->mat[x][y] != -1){
          addEdge(clone,x,y,G->mat[x][y]);
        }
      }
    }
  }else{
    int x;
    for(x=0;x<G->numVert;x++){
      NodePtr curr=G->list[x];
      while(curr!=NULL){
        addEdge(clone, x, curr->verts, curr->weight);
        curr = curr->next;
      }
    }
  }
  return clone;
}


/* free the graph object and all its resources.
   Postcondition: g is no longer a valid pointer. 
*/
void disposeGraph(Graph G){
  if(G->representation==MATRIX){
    //i dont have time for thisss
  }else if(G->representation==LIST){

  }
  free(G);
  return;
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
  if(source < G->numVert && target < G->numVert){

    if(G->representation==0){
      //if its a matrix
      if(G->mat[source][target]==-1){
        G->mat[source][target] = w;
        return OK;
      }else{
        return ERROR;
      }
    }else if(G->representation==1){
      //if its a list
      int x;
      
      NodePtr firstcurr = G->list[source];
      NodePtr prev;
      while(firstcurr!=NULL){
        if(firstcurr->verts == target){
          return ERROR;
        }
        prev = firstcurr;
        firstcurr = firstcurr->next;
      }
      

      NodePtr curr = G->list[source];
      if(curr == NULL){
        G->list[source] = (NodePtr) malloc(sizeof(struct node));
        G->list[source]->weight = w;
        G->list[source]->verts = target;
        G->list[source]->next = NULL;
        return OK;
      }

      while(curr->next!=NULL){
        curr = curr->next;
      }

      NodePtr new_node = (NodePtr) malloc(sizeof(struct node));
      new_node->weight = w;
      new_node->verts = target;
      curr->next = new_node;

      return OK;

    }
  }else{
    return ERROR;
  }
}


/* delete edge from source to target, and return
   OK, if there was an edge from source.
   Otherwise, make no change and return ERROR. 
*/
int delEdge(Graph G, int source, int target){
  if(G->representation==0){
    //if its a matrix
    if(G->mat[source][target]!=-1){
      G->mat[source][target]=-1;
      return OK;
    }else{
      return ERROR;
    }
  }else if(G->representation==1){
    //if its a list
    NodePtr curr = G->list[source];
    NodePtr prev = curr;
    if(curr==NULL){
      return ERROR;
    }
    if(curr->verts==target){
      G->list[source] = G->list[source]->next;
      prev->verts=0;
      prev->weight=0;
      prev=NULL;
      free(prev);
      return OK;
    }
    while(curr->next!=NULL){
      if(curr->next->verts==target){
        curr->next = curr->next->next;
        return OK;
      }
      curr = curr->next;
    }
    return ERROR;
  }
}


/* return weight of the edge from source to target,
   if there is one; otherwise return INFINITY.
   Return -1.0 if source or target are out of range.
*/
float edge(Graph G, int source, int target){
  if(source < G->numVert && target < G->numVert){
    if(G->representation==0){
      if(G->mat[source][target]!=-1){
        return G->mat[source][target];
      }else{
        return INFINITY;
      }
    }else if(G->representation==1){
      //printf("%s\n", "HERE");
      NodePtr curr = G->list[source];
      if(curr == NULL){

      }
      while(curr!=NULL){
        if(curr->verts == target){
          return curr->weight;
        }else{
          curr = curr->next;
        }
      }

      return INFINITY;
    }
  }else{
    return -1.0;
  }

}


/* a freshly allocated array with the successor
   vertices of source, if any, followed by an entry with -1
   to indicate end of sequence.
   Precondition: source is in range.
   Ownersip: the caller is responsible for freeing the array.
*/
int* successors(Graph G, int source){
  int* err = (int*) malloc(sizeof(int));
  err[0]=-1;

  int* succ = (int*) malloc(G->numVert+1 * sizeof(int));
  int counter = 0;
  if(G->representation==MATRIX){
    int x;
    for(x=0;x<G->numVert;x++){
      if(G->mat[source][x]!=-1){
        succ[counter] = G->mat[source][x];
        counter++;
      }
    }

    succ[counter] = -1;
    return succ;

  }else if(G->representation==LIST){
    NodePtr curr = G->list[source];
    while(curr!=NULL){
      succ[counter] = curr->verts;
      counter++;
      curr = curr->next;
    }
    succ[counter] = -1;
    return succ;
  }
  return err;
}


/* a freshly allocated array with the predecessor
   vertices of target, if any, followed by an entry with -1
   to indicate end of sequence.
   Precondition: target is in range.
   Ownersip: the caller is responsible for freeing the array.
*/
int* predecessors(Graph G, int target){
  int* err = (int*) malloc(sizeof(int));
  err[0]=-1;

  int* pre_succ = malloc( G->numVert+1 * sizeof(int));
  int counter = 0;

  if(G->representation==MATRIX){
    int x;
    for(x=0;x<G->numVert;x++){
      if(G->mat[x][target]!=-1){
        pre_succ[counter] = G->mat[x][target];
        counter++;
      }
    }

    pre_succ[counter] = -1;
    return pre_succ;

  }else if(G->representation==LIST){
    int x;
    for(x=0;x<G->numVert;x++){
      NodePtr curr = G->list[x];

      while(curr!=NULL){
        if(curr->verts == target){
          pre_succ[counter] = x;
          counter++;
          curr = curr->next;
        }
      }
    }

    pre_succ[counter] = -1;
    return pre_succ;

  }
  return err;
}

Matrix makeMatrix(int n){
  float **temp = (float **)malloc(n * sizeof(float *));
   int i=0;
    for (i=0; i<n; i++)
      temp[i] = (float *)malloc(n * sizeof(float));
    return temp;
}

List makeList(int n){
  List temp = (NodePtr*)malloc(n * sizeof(struct node));
  int x;
  for(x=0;x<n;x++){
    temp[x] = NULL;
  }

  return temp;
}
