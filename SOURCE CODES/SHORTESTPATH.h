/*
	GEMATMW PROJECT
	SHORTEST PATH MODULE
	
	DEVELOPMENT NOTES [Last updated: 10:35 PM - 04/11/2020]:
		- Node structure systems have been implemented.
		- Path structure systems have been implemented.
		- Random distance generation has been implemented.
		- Gameplay system under implementation.
		- DisplayGrid under implementation [KYLE].
		- Dijkstra's algorithm to be implemented.
*/

// Library Imports
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

// DETERMINE OPERATING SYSTEM
#if _WIN32 || _WIN64
	#define OS_CLEAR() system("cls")
	#define OS_PAUSE() system("PAUSE")
#else
	#define OS_CLEAR() system("clear")
	#define OS_PAUSE() system("read -n1 -r -p \"Press any key to continue...\" key")
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
int getRandInt(int min, int max) {
	time_t t;
	// Seed the rand()
	srand((unsigned) time(&t));
	int x = min;
	x += rand() % (max-min);
	return x;
}

// PRIMARY FUNCTIONS
/* This function initializes all values of the node array for shortest path.
	This function is called by the setShortestPathNodes function. */
void initShortestPathNodes(spNode nodes[][MAX_CITIES]) {
	int i, j;
	
	for(i=0; i<MAX_CITIES; i++) {
		for(j=0; j<MAX_MUNICIPAL; j++) {
			nodes[j][i].nodeID = i+j;
			strcpy(nodes[j][i].name, "NULL");
			strcpy(nodes[j][i].cityName, "NULL");
			nodes[j][i].activePlayer = 0;
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
	pathList[0].distance = getRandInt(min, max);
	pathList[0].node1 = 0;
	pathList[0].node2 = 1;	
	
	// Asign to corresponding nodes and random distance
	// Horizontal Paths
	for(i=0; i<MAX_MUNICIPAL; i++) {
		for(j=0; j<MAX_CITIES-1; j++) {
			index = (i*(MAX_CITIES-1))+j;
			if(index != 0) {
				if(j!=0) {
					pathList[index].distance = getRandInt(min, max);
					pathList[index].node1 = pathList[index-1].node2;
					pathList[index].node2 = pathList[index].node1 + 1;
				}
				else {
					pathList[index].distance = getRandInt(min, max);
					pathList[index].node1 = pathList[index-1].node2 + 1;
					pathList[index].node2 = pathList[index].node1 + 1;
				}
				
			}
		}
	}
	index++;
	// Initialize Vertical first element
	pathList[index].distance = getRandInt(min, max);
	pathList[index].node1 = 0;
	pathList[index].node2 = 7;
	k = index;
	
	// Vertical Paths
	for(i=0; i<MAX_CITIES; i++) {
		for(j=0; j<MAX_MUNICIPAL-1; j++) {
			index = k + j+(i*(MAX_MUNICIPAL-1));
			if(index != k) {
				if(j!=0) {
					pathList[index].distance = getRandInt(min, max);
					pathList[index].node1 = pathList[index-1].node2;
					pathList[index].node2 = pathList[index].node1 + 7;
				}
				else {
					pathList[index].distance = getRandInt(min, max);
					pathList[index].node1 = i;
					pathList[index].node2 = pathList[index].node1 + 7;
				}
			}
		}
	}
	
	index++;
	// Initialize Falling-Diagonal first element
	pathList[index].distance = getRandInt(min, max);
	pathList[index].node1 = 0;
	pathList[index].node2 = 8;
	k = index;
	
	// Falling-Diagonal Paths
	for(i=0; i<MAX_MUNICIPAL-1; i++) {
		for(j=0; j<MAX_CITIES-1; j++) {
			index = k + (i*(MAX_CITIES-1))+j;
			if(index != k) {
				if(j!=0) {
					pathList[index].distance = getRandInt(min, max);
					pathList[index].node1 = pathList[index-1].node1 + 1;
					pathList[index].node2 = pathList[index-1].node2 + 1;
				}
				else {
					pathList[index].distance = getRandInt(min, max);
					pathList[index].node1 = i*7;
					pathList[index].node2 = pathList[index].node1 + 8;
				}
			}
		}
	}
	
	index++;
	// Initialize Rising-Diagonal first element
	pathList[index].distance = getRandInt(min, max);
	pathList[index].node1 = 1;
	pathList[index].node2 = 7;
	k = index;
	
	// Rising-Diagonal Paths
	for(i=0; i<MAX_MUNICIPAL-1; i++) {
		for(j=0; j<MAX_CITIES-1; j++) {
			index = k + (i*(MAX_CITIES-1))+j;
			if(index != k) {
				if(j!=0) {
					pathList[index].distance = getRandInt(min, max);
					pathList[index].node1 = pathList[index-1].node1 + 1;
					pathList[index].node2 = pathList[index-1].node2 + 1;
				}
				else {
					pathList[index].distance = getRandInt(min, max);
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
void spGameplay() {
	// Declare applicable lists
	int initialMovesetSize = 30;
	spMove *p1 = malloc(sizeof(struct spMoveTag)*initialMovesetSize);
	spMove *p2 = malloc(sizeof(struct spMoveTag)*initialMovesetSize);
	
	// Variable Declarations
	int doExit = 0;
	int turn = 1;
	
	// Main-loop
	do {
		
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
		OS_CLEAR();
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
	
	spGameplay();
	
	return 0;
}

