/*
	GEMATMW PROJECT
	SHORTEST PATH MODULE
	
	DEVELOPMENT NOTES [Last updated: 10:35 PM - 04/11/2020]:
		- Node structure systems have been implemented.
		- Path structure systems have been implemented.
		- Random distance generation has been implemented.
		- Gameplay system under implementation.
		- DisplayGrid under implementation.
			- Think of a proper algorithm to do the final print.
		- Dijkstra's algorithm to be implemented.
*/

// Library Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// DETERMINE OPERATING SYSTEM
#if _WIN32 || _WIN64
	#define OS_CLEAR() system("cls")
	#define OS_PAUSE() system("PAUSE")
#else
	#define OS_CLEAR() system("clear")
	#define OS_PAUSE() system("read -n1 -r -p "Press any key to continue..." key")
#endif

// Macro Definitions
#define NODENAME_LEN 31
#define MAX_MUNICIPAL 5
#define MAX_CITIES 7
#define MAX_NODES (MAX_MUNICIPAL * MAX_CITIES)
#define MAX_PATH (4*MAX_MUNICIPAL*MAX_CITIES - 3*MAX_MUNICIPAL - 3*MAX_CITIES + 2)

// Type Definitions
typedef struct spPathTag {
	int pathID;
	int distance;
	int node1;
	int node2;
} spPath;

typedef struct spNodeTag {
	int nodeID;
	char name[NODENAME_LEN];
	char cityName[NODENAME_LEN];
	int activePlayer;
} spNode;

typedef struct spMoveTag {
	int oldNode;
	int newNode;
	int distance;
	int totalDistance;
} spMove;
// User-Defined Functions

// SECONDARY FUNCTIONS
/* This function generates a random integer between min and max inclusive
	and returns its value.
*/
int getRandInt(int seed, int min, int max) {
	time_t t;
	// Seed the rand()
	if(seed==0)
		srand((unsigned) time(&t));
	else 
		srand(seed);
	int x = min;
	x += rand() % (max-min);
	return x;
}

// PRIMARY FUNCTIONS
/* This function initializes all values of the node array for shortest path.
	This function is called by the setShortestPathNodes function. */
void initShortestPathNodes(spNode nodes[][MAX_CITIES]) {
	int i, j, id=0;
	
	for(i=0; i<MAX_MUNICIPAL; i++) {
		for(j=0; j<MAX_CITIES; j++) {
			nodes[i][j].nodeID = id++;
			strcpy(nodes[i][j].name, "NULL");
			strcpy(nodes[i][j].cityName, "NULL");
			nodes[i][j].activePlayer = 0;
		}
	}
}

/* This function initializes the pathList.
*/
void initShortestPathPaths(spPath pathList[]) {
	int i;
	
	for(i=0; i<MAX_PATH; i++){
		pathList[i].pathID = i;
		pathList[i].distance = -1;
		pathList[i].node1 = -1;
		pathList[i].node2 = -1;
	}
}
/* This function sets the values for the map.
*/
void setShortestPathNodes(spNode nodes[][MAX_CITIES]) {
	// Initialize Node List
	initShortestPathNodes(nodes);
	
	// Variable Declarations
	int i;
	
	// Set Node Values
	// MUNTINLUPA
	strcpy(nodes[0][0].name, "New Bilibid Prison Cemetery");
	strcpy(nodes[1][0].name, "Starmall Alabang");
	strcpy(nodes[2][0].name, "Yexel's Toy Museum");
	strcpy(nodes[3][0].name, "Jamboree Lake");
	strcpy(nodes[4][0].name, "Muntinlupa Sports Complex");
		// Set city
	for(i=0; i<MAX_MUNICIPAL; i++) {
		strcpy(nodes[i][0].cityName, "Muntinlupa");
	}
	
	// Taguig
	strcpy(nodes[0][1].name, "SM Aura");
	strcpy(nodes[1][1].name, "Bonifacio Global Center");
	strcpy(nodes[2][1].name, "Mind Museum");
	strcpy(nodes[3][1].name, "Enderun University");
	strcpy(nodes[4][1].name, "Manila American Cemetery");
		// Set city
	for(i=0; i<MAX_MUNICIPAL; i++) {
		strcpy(nodes[i][1].cityName, "Taguig");
	}
	
	// Pasig
	strcpy(nodes[0][2].name, "Hampton Gardens");
	strcpy(nodes[1][2].name, "St. Paul College Pasig");
	strcpy(nodes[2][2].name, "Estancia");
	strcpy(nodes[3][2].name, "Medical City");
	strcpy(nodes[4][2].name, "C5 Road");
		// Set city
	for(i=0; i<MAX_MUNICIPAL; i++) {
		strcpy(nodes[i][2].cityName, "Pasig");
	}
	
	// Mandaluyong
	strcpy(nodes[0][3].name, "Lourdes School of Mandaluyong");
	strcpy(nodes[1][3].name, "Shaw Boulevard");
	strcpy(nodes[2][3].name, "EDSA");
	strcpy(nodes[3][3].name, "Meralco");
	strcpy(nodes[4][3].name, "La Salle Greenhills");
		// Set city
	for(i=0; i<MAX_MUNICIPAL; i++) {
		strcpy(nodes[i][3].cityName, "Mandaluyong");
	}
	
	// Manila
	strcpy(nodes[0][4].name, "SM Mall of Asia");
	strcpy(nodes[1][4].name, "De La Salle University");
	strcpy(nodes[2][4].name, "University of Sto Thomas");
	strcpy(nodes[3][4].name, "Rizal Park");
	strcpy(nodes[4][4].name, "Fort Santiago");
		// Set city
	for(i=0; i<MAX_MUNICIPAL; i++) {
		strcpy(nodes[i][4].cityName, "Manila");
	}
	
	// Quezon
	strcpy(nodes[0][5].name, "Ateneo de Manila University");
	strcpy(nodes[1][5].name, "Quezon Memorial Circle");
	strcpy(nodes[2][5].name, "Eastwood");
	strcpy(nodes[3][5].name, "Cubao");
	strcpy(nodes[4][5].name, "Araneta Coliseum");
		// Set city
	for(i=0; i<MAX_MUNICIPAL; i++) {
		strcpy(nodes[i][5].cityName, "Quezon");
	}
	
	// Caloocan
	strcpy(nodes[0][6].name, "Malabon Zoo");
	strcpy(nodes[1][6].name, "La Mesa Nature Reserve");
	strcpy(nodes[2][6].name, "Glorieta Park");
	strcpy(nodes[3][6].name, "San Bartolome Church");
	strcpy(nodes[4][6].name, "LRT Caloocan Mall");
		// Set city
	for(i=0; i<MAX_MUNICIPAL; i++) {
		strcpy(nodes[i][6].cityName, "Caloocan");
	}
}

/* This function randomly sets distance values to the paths
	and connects them to their respective nodes. */
void setShortestPathPaths(spPath pathList[], int min, int max) {
	// Initialize the pathList
	initShortestPathPaths(pathList);
	// Variable Declarations
	int i, j, k;
	int index;
	
	// Initialize horizontal first element
	pathList[0].distance = getRandInt(0, min, max);
	pathList[0].node1 = 0;
	pathList[0].node2 = 1;	
	
	// Asign to corresponding nodes and random distance
	// Horizontal Paths
	for(i=0; i<MAX_MUNICIPAL; i++) {
		for(j=0; j<MAX_CITIES-1; j++) {
			index = (i*(MAX_CITIES-1))+j;
			if(index != 0) {
				if(j!=0) {
					pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
					pathList[index].node1 = pathList[index-1].node2;
					pathList[index].node2 = pathList[index].node1 + 1;
				}
				else {
					pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
					pathList[index].node1 = pathList[index-1].node2 + 1;
					pathList[index].node2 = pathList[index].node1 + 1;
				}
				
			}
		}
	}
	index++;
	// Initialize Vertical first element
	pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
	pathList[index].node1 = 0;
	pathList[index].node2 = 7;
	k = index;
	
	// Vertical Paths
	for(i=0; i<MAX_CITIES; i++) {
		for(j=0; j<MAX_MUNICIPAL-1; j++) {
			index = k + j+(i*(MAX_MUNICIPAL-1));
			if(index != k) {
				if(j!=0) {
					pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
					pathList[index].node1 = pathList[index-1].node2;
					pathList[index].node2 = pathList[index].node1 + 7;
				}
				else {
					pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
					pathList[index].node1 = i;
					pathList[index].node2 = pathList[index].node1 + 7;
				}
			}
		}
	}
	
	index++;
	// Initialize Falling-Diagonal first element
	pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
	pathList[index].node1 = 0;
	pathList[index].node2 = 8;
	k = index;
	
	// Falling-Diagonal Paths
	for(i=0; i<MAX_MUNICIPAL-1; i++) {
		for(j=0; j<MAX_CITIES-1; j++) {
			index = k + (i*(MAX_CITIES-1))+j;
			if(index != k) {
				if(j!=0) {
					pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
					pathList[index].node1 = pathList[index-1].node1 + 1;
					pathList[index].node2 = pathList[index-1].node2 + 1;
				}
				else {
					pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
					pathList[index].node1 = i*7;
					pathList[index].node2 = pathList[index].node1 + 8;
				}
			}
		}
	}
	
	index++;
	// Initialize Rising-Diagonal first element
	pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
	pathList[index].node1 = 1;
	pathList[index].node2 = 7;
	k = index;
	
	// Rising-Diagonal Paths
	for(i=0; i<MAX_MUNICIPAL-1; i++) {
		for(j=0; j<MAX_CITIES-1; j++) {
			index = k + (i*(MAX_CITIES-1))+j;
			if(index != k) {
				if(j!=0) {
					pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
					pathList[index].node1 = pathList[index-1].node1 + 1;
					pathList[index].node2 = pathList[index-1].node2 + 1;
				}
				else {
					pathList[index].distance = getRandInt(pathList[index-1].distance, min, max);
					pathList[index].node1 = (i*7)+1;
					pathList[index].node2 = pathList[index].node1 + 6;
				}
			}
		}
	}
	
}

/* This function displays the grid. 
*/
void displaySPGrid(spNode nodeList[][MAX_CITIES], spPath pathList[]) {
	// Variable Declarations
	int i, j, k;

	// Declare & Initialize nodebox
	struct nodeBoxTag {
		char nodeBox[161];
		spNode node;
		int occupied;
	} sNodeBox;
	char nodeSample[161] =  "-------------------------------\0"
					  		"|              ID             |\0"
					  		"|                             |\0"
					  		"|         OCCPUPIED: 0        |\0"
					  		"-------------------------------\0";
	strcpy(sNodeBox.nodeBox, "");
	i = 0;
	for(j=0;j<5;j++) {
		while(nodeSample[i]!=0) {
			sNodeBox.nodeBox[i] = nodeSample[i];
			i++;
		}
		sNodeBox.nodeBox[i] = 0;
		i++;
	}
	sNodeBox.occupied = 0;
	
	// Create & initialize the displayNodes array
	struct nodeBoxTag *current;
	int nameStartIndex = 79;
	struct nodeBoxTag displayNodes[MAX_MUNICIPAL][MAX_CITIES];
	for(i=0;i<MAX_MUNICIPAL;i++) {
		for(j=0;j<MAX_CITIES;j++) {
			current = &displayNodes[i][j];
			*current = sNodeBox;
			current->node = nodeList[i][j];

			// Fill in box information
			// ID
			if(current->node.nodeID<10) {
				current->nodeBox[47] = '0';
				current->nodeBox[48] = (current->node).nodeID + 48;
			}
			else {
				current->nodeBox[47] = (((current->node).nodeID)/10) + 48;
				current->nodeBox[48] = (((current->node).nodeID)%10) + 48;
			}
			// NAME (CENTER:79-80)
				// Calculate ratio
			nameStartIndex = 79;
			nameStartIndex -= strlen(current->node.name)/2;
			k = 0;
			while(current->node.name[k]!=0) {
				current->nodeBox[nameStartIndex + k] = current->node.name[k];
				k++;
			}

			// Check if occupied (index:117)
			current->nodeBox[117] = current->node.activePlayer + 48;
		}
	}

	// Declare & Initialize PathLines
	struct pathLineTag {
		int pathID;
		char pathBox[71];
		spPath path;
	} sPathBoxHor, sPathBoxVer, sPathBoxDiag;
	const char * pathSample1 = "             \0"
					   "=============\0"
					   "     000     \0"
					   "=============\0"
					   "             \0";
	const char * pathSample2 = "    |   |    \0"
					   "    |   |    \0"
					   "    |000|    \0"
					   "    |   |    \0"
					   "    |   |    \0";
	const char * pathSample3 = "## ##   ## ##\0"
					   "  ## ### ##  \0"
					   "000/## ##\\000\0"
					   "  ## ### ##  \0"
					   "## ##   ## ##\0";
	
	strcpy(sPathBoxHor.pathBox, "");
	strcpy(sPathBoxVer.pathBox, "");
	strcpy(sPathBoxDiag.pathBox, "");
	i = 0;
	for(j=0;j<5;j++) {
		while(pathSample1[i]!=0) {
			sPathBoxHor.pathBox[i] = pathSample1[i];
			sPathBoxVer.pathBox[i] = pathSample2[i];
			sPathBoxDiag.pathBox[i] = pathSample3[i];
			i++;
		}
		sPathBoxHor.pathBox[i] = 0;
		sPathBoxVer.pathBox[i] = 0;
		sPathBoxDiag.pathBox[i] = 0;
		i++;
	}
	
	
	struct pathLineTag *currPath;
	spPath diag1, diag2;
	struct pathLineTag displayPaths[MAX_PATH];
	for(i=0;i<MAX_PATH-24;i++) {
		currPath = &displayPaths[i];
		if(i<30) {
			// Horizontal
			*currPath = sPathBoxHor;
			currPath->path = pathList[i];
			// Set distance (index: 34-36)
			if(currPath->path.distance < 10) {
				currPath->pathBox[33] = '0';
				currPath->pathBox[34] = '0';
				currPath->pathBox[35] = (currPath->path).distance + 48;
			}
			else if(currPath->path.distance < 100) {
				currPath->pathBox[33] = '0';
				currPath->pathBox[34] = ((currPath->path).distance / 10) + 48;
				currPath->pathBox[35] = ((currPath->path).distance % 10) + 48;
			}
			else if(currPath->path.distance < 1000) {
				currPath->pathBox[33] = ((currPath->path).distance / 100) + 48;
				currPath->pathBox[34] = ((currPath->path).distance / 10 % 10) + 48;
				currPath->pathBox[35] = ((currPath->path).distance % 10) + 48;
			}
		}
		else if(i<58) {
			// Vertical
			*currPath = sPathBoxVer;
			currPath->path = pathList[i];
			// Set distance (index: 34-36)
			if(currPath->path.distance < 10) {
				currPath->pathBox[33] = '0';
				currPath->pathBox[34] = '0';
				currPath->pathBox[35] = (currPath->path).distance + 48;
			}
			else if(currPath->path.distance < 100) {
				currPath->pathBox[33] = '0';
				currPath->pathBox[34] = ((currPath->path).distance / 10) + 48;
				currPath->pathBox[35] = ((currPath->path).distance % 10) + 48;
			}
			else if(currPath->path.distance < 1000) {
				currPath->pathBox[33] = ((currPath->path).distance / 100) + 48;
				currPath->pathBox[34] = ((currPath->path).distance / 10 % 10) + 48;
				currPath->pathBox[35] = ((currPath->path).distance % 10) + 48;
			}
		}
		else {
			// Diagonals
			*currPath = sPathBoxDiag;
			diag1 = pathList[i];
			diag2 = pathList[i+24];
			// Set distance 1 (index: 28-30)
			if(diag1.distance < 10) {
				currPath->pathBox[28] = '0';
				currPath->pathBox[29] = '0';
				currPath->pathBox[30] = diag1.distance + 48;
			}
			else if(diag1.distance < 100) {
				currPath->pathBox[28] = '0';
				currPath->pathBox[29] = (diag1.distance / 10) + 48;
				currPath->pathBox[30] = (diag1.distance % 10) + 48;
			}
			else if(diag1.distance < 1000) {
				currPath->pathBox[28] = (diag1.distance / 100) + 48;
				currPath->pathBox[29] = (diag1.distance / 10 % 10) + 48;
				currPath->pathBox[30] = (diag1.distance % 10) + 48;
			}
			// Set distance 2 (index: 38-40)
			if(diag2.distance < 10) {
				currPath->pathBox[38] = '0';
				currPath->pathBox[39] = '0';
				currPath->pathBox[40] = diag2.distance + 48;
			}
			else if(diag2.distance < 100) {
				currPath->pathBox[38] = '0';
				currPath->pathBox[39] = (diag2.distance / 10) + 48;
				currPath->pathBox[40] = (diag2.distance % 10) + 48;
			}
			else if(diag2.distance < 1000) {
				currPath->pathBox[38] = (diag2.distance / 100) + 48;
				currPath->pathBox[39] = (diag2.distance / 10 % 10) + 48;
				currPath->pathBox[40] = (diag2.distance % 10) + 48;
			}
		}
	}

	// Print the actual grid
	/*
		ALGORITHM:
		
	*/
	// Row-Wise Array
	char megaString[10000] = "";
	int nodeI = 0, nodeJ = 0;
	int pathI;
	int nodeK = 0, pathK = 0;
	// Main Row Loop
	for(i=0;i<9;i++) {
		printf("Row Loop\n");
		// Line-index loop
		for(j=0;j<5;j++) {
			printf("Line-index loop\n");
			printf("nodeK = %d; pathK = %d\n", nodeK, pathK);
			// Column Loop
			for(k=0;k<13;k++) {
				printf("Column loop\n");
				// Odd-Even system
				if(k%2==0) {
					// Even - print node
					printf("TEST OUTPUT %d %d NODE: %s\n", nodeI, nodeJ, &displayNodes[nodeI][nodeJ].nodeBox[nodeK]);
					strcat(megaString, &displayNodes[nodeI][nodeJ++].nodeBox[nodeK]);
					printf("After node cat\n");
				}
				else {
					// Odd - print path
					printf("TEST OUTPUT %d PATH: %s\n", pathI,&displayPaths[pathI].pathBox[pathK]);
					strcat(megaString, &displayPaths[pathI++].pathBox[pathK]);
					printf("After path cat\n");
				}
			}
			nodeK += 32;
			pathK += 14;
			nodeJ = 0;
			pathI = i*6;
			strcat(megaString, "\n");
		}
		pathI = i*6;
		nodeK = 0;
		pathK = 0;
		nodeI++;
		nodeJ = 0;
		strcat(megaString, "\n");
		printf("Concat newline\n");
		printf("%s", megaString);
		OS_PAUSE();
	}
	//printf("%s", megaString);
	
	OS_PAUSE();
}

/* This function checks if someone has won the game or not.
	Returns 0 for false, 1 for player 1, 2 for player 2.
*/
int isGameOver(spMove *p1, spMove *p2, int destNode) {
	
	return 0;
}

/* This function implements playermoves.
*/
void doPlayerMove(int turn, spNode nodeList[][MAX_CITIES], spPath pathList[], spMove *p1, spMove *p2) {
	
}

/* This function is the heart of all the gameplay. It calls all relevant functions
	and handles all the gameplay. 
*/
void spGameplay(spNode nodeList[][MAX_CITIES], spPath pathList[]) {
	// Declare applicable lists
	int initialMovesetSize = 30;
	struct spMoveTag *p1 = (struct spMoveTag *) malloc(sizeof(struct spMoveTag)*initialMovesetSize);
	struct spMoveTag *p2 = (struct spMoveTag *) malloc(sizeof(struct spMoveTag)*initialMovesetSize);
	
	// Variable Declarations
	int doExit = 0;
	int turn = 1;
	
	// Main-loop
	do {
		// DISPLAY GRID
		displaySPGrid(nodeList, pathList);
	} while(!doExit);
	
	free(p1);
	free(p2);
}

/* HEADER MAIN */
int shortestPath() {
	OS_CLEAR();
	// Declare and initialize nodes & paths
	spNode SPNodes[MAX_MUNICIPAL][MAX_CITIES];
	spPath SPPaths[MAX_PATH];
	setShortestPathNodes(SPNodes);
	setShortestPathPaths(SPPaths, 1, 999);
	
	// Variable Declarations
	char cChoice;
	do {
		// Display game rules & mechanics
		//OS_CLEAR();
		printf("Note: Too see the entire map, please keep the terminal window in its biggest possible size.\n"
			   "===========================================================================================\n"
			   "\nGAME MECHANICS:\n"
			   "\nThis game is about speed and smarts.\n"
			   "1. Both players shall pick their starting points.\n"
			   "\t- Starting points must be in the first city.\n"
			   "2. Both players will have the same destination point.\n"
			   "\t- Destination point must be in the last city, to be chosen by the players.\n"
			   "3. Players cannot be on the same place at the same time.\n"
			   "4. Whoever reaches the destination point with the least distance traveled wins the game.\n"
			   "\n"
			   "Note: Distances are randomized every game.\n"
			   "Ready to play? [Y/n]: ");
		scanf(" %c", &cChoice);
	} while(cChoice!='Y' && cChoice!='y' && cChoice!='N' && cChoice!='n');
	
	if(cChoice=='N' || cChoice=='n')
		return 0;
	
	printf("Once again, please set the window to the maximum size. If you haven't yet, do so now.\n");
	OS_PAUSE();
	
	spGameplay(SPNodes, SPPaths);
	
	return 0;
}

