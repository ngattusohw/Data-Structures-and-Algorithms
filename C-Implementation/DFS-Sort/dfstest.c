#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "graphio.h"
#include "dfs.h"


/* test both toposort2 and topocycle */
int main() {
    char* filepath = "cycle3.txt";
    DFSinfo returned = DFS(readGraph(filepath, 0)->graph);
    
    for(int x=0;x<numVerts(returned->graph);x++){
        printf("%i\n", returned->finish[x]);
    }
}


