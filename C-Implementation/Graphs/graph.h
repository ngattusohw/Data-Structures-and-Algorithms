#ifndef GRAPH_H
#define GRAPH_H

#define MATRIX 0
#define LIST 1

#define OK 0
#define ERROR 1

struct graph; //need a numVents, struct needs to account for matrix and list
typedef struct graph* Graph; 

/*Make an empty graph with n vertices, using adjacecy matrix or adjaceny
lists depending on whether rep==MATRIX or rep==LIST
Pre: n>=1 */

Graph makeGraph(int n, int rep);

/* make a copy of g, but using the repesentation specified by rep (which
is assumed to be MATRIX or LIST) */

Graph cloneGraph(Graph G, int rep);

/*free the graph object and all its recources. Post condition: g is
no longer a valid pointer. Alert: the caller should set their variable
to null */

void disposeGraph(Graph G);

/* num of vertices */

int numVerts(Graph G);

/* add edge from source to target with weight w, and return OK,
if source and target are alid vertex numbers and there was no edge ..
*/

int addEdge(Graph G, int source, int target, float w);

/* delete edge from source to target, and return OK, if there was an
edge from source. Otherwise, make not change and return ERROR */

int delEdge(Graph G, int source, int target);

/* return weight of the edge from souce to target, if there is one:
otherwise return INFINITY. Return -1.0 if source or target are out-of
-range */

float edge(Graph G, int source, int target);

/* a freshly allocated array with the successor vertices of source
if any, followed by an entry with -1 to indicate end ..
Pre: source is in range. 
Returns: Poiner to int array? */

int* successors(Graph G, int source);

int* predecessors(Graph G, int source);
