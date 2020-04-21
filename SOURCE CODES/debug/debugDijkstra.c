// Dijkstra's Algorithm Testing Script

#include <stdio.h>
#include <stdlib.h>

#include "SHORTESTPATH.h"

int main() {

    int i;
    int start, end;
    int mapSize;

    // Initializations
    spNode SPNodes[MAX_MUNICIPAL][MAX_CITIES];
	spPath SPPaths[MAX_PATH];
	setShortestPathNodes(SPNodes);

    printf("Enter maximum path distance: ");
    scanf("%d", &mapSize);

    setShortestPathPaths(SPPaths, 1, mapSize);

    printf("Enter starting node ID: ");
    scanf("%d", &start);
    printf("Enter destination node ID: ");
    scanf("%d", &end);

    spDijkstra spTest = dijkstra(start, end, SPNodes, SPPaths);

    printf("Total Distance: %d\n", spTest.distance);

    i = 0;
    while(spTest.path[i] != -1) {
        printf("%s\n", searchNodes(spTest.path[i++], SPNodes)->name);
    }

    return 0;
}