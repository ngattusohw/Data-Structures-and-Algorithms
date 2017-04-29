#include <string.h>
#include "minprio.h"
#include <stdio.h>
#include <stdlib.h>
#include "graphio.h"
#include "primmst.h"

int main(){
	GraphInfo gi = readGraphMakeSymm("tits.txt",LIST);
	Graph g = gi->graph;

	gi->graph = minSpanTree(g);

	writeGraph(gi);

}