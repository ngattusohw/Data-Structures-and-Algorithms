#include <string.h>
#include "minprio.h"
#include <stdio.h>
#include <stdlib.h>
#include "graphio.h"
#include "dijkstra.h"

int main(){
	GraphInfo gi = readGraphMakeSymm("ass.txt",MATRIX);
	Graph g = gi->graph;

	//gi->graph = 
	shortestPaths(gi,7);

	//writeGraph(gi);

}