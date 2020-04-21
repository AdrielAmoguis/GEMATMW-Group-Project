// Dijkstra's Algorithm Testing Script

#include <stdio.h>
#include <stdlib.h>

#include "SHORTESTPATH.h"

int main() {

    int i;

    // Initializations
    spNode SPNodes[MAX_MUNICIPAL][MAX_CITIES];
	spPath SPPaths[MAX_PATH];
	setShortestPathNodes(SPNodes);
    setShortestPathPaths(SPPaths, 1, 100);

    spDijkstra spTest = dijkstra(0, 20, SPNodes, SPPaths);

    printf("Total Distance: %d\n", spTest.distance);

    i = 0;
    while(spTest.path[i] != -1) {
        printf("%s\n", searchNodes(spTest.path[i++], SPNodes)->name);
    }

    return 0;
}