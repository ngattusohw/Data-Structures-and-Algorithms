#include "graphio.h"
#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"
/* Determine whether the graph has a cycle.  
   If so, print "Has a cycle:" followed by the vertices of a cycle (using the 
   vertex names, not their numbers).
   Just print one cycle, even if there are several.

   If not cyclic, print all the vertex names, in a topologically sorted order.

   For this purpose, we use Levitin's definition of a cycle, which does not include 
   self-loops, and which includes the starting vertex also at the end of the path.
   So the shortest cycle has three vertices: A B A where there are edges A->B and B->A.
*/
void topocycle(GraphInfo gi){
	DFSinfo returned = DFS(gi->graph);
	int cycle[numVerts(gi->graph)];

	for(int i = 0; i < numVerts(gi->graph); i++){
	    for(int x = 0; x<numVerts(gi->graph); x++){
			if(returned->discover[i] < returned->discover[x] && returned->discover[x] < returned->finish[x] && returned->finish[x] < returned->finish[i]&& returned->parent[i] == x){
				printf("%s", "Has Cycle: ");
				cycle[0] = i;
				int hold=0;
				int index = 0;
				while(returned->parent[hold]!= cycle[0]){
					cycle[index+1] = returned->parent[hold];
					hold = returned->parent[hold];
					index ++;
				}
				index ++;
				cycle[index] = i;
				

				int reverseIndex = index;
				int temp[index];

				for(int a = 0; a <=index ; a++){
					temp[a] = cycle[reverseIndex];
					reverseIndex--;
				}

				for(int a = 0; a <= index; a++){
					printf("%s ", gi->vertnames[temp[a]]);
				}
				printf("\n");

				return; //return to close out of the function
			}
		}
	}

	int* topoSORT = (int*)malloc(numVerts(gi->graph) * sizeof(int*));
	for (int i = 0; i < numVerts(gi->graph); ++i){
		topoSORT[i] = 0;
	}
	int y=0;

	for(int x=numVerts(gi->graph)-1;x>=0;x--){
		topoSORT[y] = returned->finorder[x];
		y++;
	}

	for (int i = 0; i < numVerts(gi->graph); ++i){
		printf("%s\n", gi->vertnames[topoSORT[i]]);
	}
	return;
}
