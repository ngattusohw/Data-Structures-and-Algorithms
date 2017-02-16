#ifndef GRAPH_H
#define GRAPH_H

#define MATRIX 0
#define LIST 1

#define OK 0
#define ERROR 1

struct graph;
typedef struct graph* Graph;


/*Make an empty graph with n vertices, using adjacecy matrix or adjaceny
lists depending on whether rep==MATRIX or rep==LIST
Pre: n>=1 */

Graph makeGraph(int n, int rep);

/* make a copy of g, but using the repesentation specified by rep (which
is assumed to be MATRIX or LIST)

