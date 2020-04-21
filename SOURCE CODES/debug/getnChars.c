// Get nChars
#include <stdio.h>
#include <stdlib.h>

#include "SHORTESTPATH.h"

int main() {

    // Declare and initialize nodes & paths
	spNode SPNodes[MAX_MUNICIPAL][MAX_CITIES];
	spPath SPPaths[MAX_PATH];
	setShortestPathNodes(SPNodes);
    setShortestPathPaths(SPPaths, 1, 100);
    displaySPGrid(SPNodes, SPPaths, 0);

    // Open text file and count how many characters
    FILE *fp = fopen("playingGrid.txt", "r");
    if(fp==NULL) {
        fprintf(stderr, "playingGrid.txt does not exist!\n");
        printf("playingGrid.txt does not exist!\n");
        exit(1);
    }

    char dump;
    int nChars = 0;

    while(!feof(fp)) {
        fscanf(fp, "%c", &dump);
        nChars++;
        printf("%c", dump);
    }

    printf("Total # of characters: %d\n", nChars);
    fclose(fp);

    return 0;
}