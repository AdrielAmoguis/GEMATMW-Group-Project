/*
	GEMATMW PROJECT
	SHORTEST PATH MODULE
	
	DEVELOPMENT NOTES [Last updated: 10:35 PM - 04/11/2020]:
		- Node structure systems have been implemented.
		- Path structure systems have been implemented.
		- Random distance generation has been implemented.
		- Gameplay systems have been implemented.
		- DisplayGrid has been implemented.
		- Dijkstra's under implementation.
*/

// Library Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

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

/* This function takes safe integer input. 
	Stores the input in the address of param1.
	Returns 0 when invalid, 1 when valid. */
int spSafeIntInput(int *x) {
	char buffer[50];
	int i, size;
	
	scanf("%s", buffer);
	size = strlen(buffer);
	
	if(size > 0) {
		// Check for non-integer
		for(i=0;i<size;i++) {
			if((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '-')
				return 0;
		}
		// Convert to integer
		*x = atoi(buffer);
		return 1;
	}
	
	return 0;
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

/* This function searches the nodeList for the element with the key id.
	Returns the address of the node found.
*/
spNode * searchNodes(int id, spNode nodeList[][MAX_CITIES]) {
	int i, j;
	for(i=0;i<MAX_MUNICIPAL;i++)
		for(j=0;j<MAX_CITIES;j++)
			if(nodeList[i][j].nodeID == id)
				return &nodeList[i][j];
	return NULL;
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
	const char * pathSample2 = "             \0"
					   "=============\0"
					   "     000     \0"
					   "=============\0"
					   "             \0";
	const char * pathSample1 = "    |   |    \0"
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
		The grid axes will be inverted.
		Prepare for spaghetti code
	*/

	// Variable Declarations
	char finalDisplay[20000] = "";
	int nodeI = 4;
	int nodeJ = 0;
	int pathI = 33, pathI2 = 24, pathI3 = 76;
	int nodeK = 0, pathK = 0;
	// Row-Loop
	for(i=0;i<13;i++) {
		// Line-index loop
		nodeK = 0;
		pathK = 0;
		for(k=0;k<5;k++) {
			// Odd-Even system
			if(i%2==0) {
				// Nodes & Paths Row
				// Column Loop
				pathI = 33 + 2*i;
				for(j=0;j<9;j++) {
					// Odd-Even System
					if(j%2==0) {
						// Even - print node
						strcat(finalDisplay, &displayNodes[nodeI--][nodeJ].nodeBox[nodeK]);
					}
					else {
						// Odd - print path
						strcat(finalDisplay, &displayPaths[pathI--].pathBox[pathK]);
					}
				}
			}
			else {
				// Paths Only
				// Odd-Even system, even hor, odd diag
				// Column Loop
				pathI2 = 24 + i/2;
				pathI3 = 76 + i/2;
				for(j=0;j<9;j++) {
					strcat(finalDisplay, "         ");
					if(j%2==0) {
						// Even - print horizontal
						strcat(finalDisplay, &displayPaths[pathI2].pathBox[pathK]);
						pathI2 -= 6;
					}
					else {
						// Odd - print diagonal
						strcat(finalDisplay, &displayPaths[pathI3].pathBox[pathK]);
						pathI3 -= 6;
					}
				}
			}
			nodeK += 32;
			pathK += 14;
			nodeI = 4; 
			strcat(finalDisplay, "\n");
		}
		if(i%2==0)
			nodeJ++;
	}

	// Finally, print the finished grid
	printf("%s\n", finalDisplay);

	// Print the grid to a file
	FILE *grid = fopen("playingGrid.txt", "w");
	fprintf(grid, "%s", finalDisplay);
	fclose(grid);
}

/* This function checks if the destination has been reached.
	Returns 0 for false, 1 for true.
*/
int isGameOver(int turn, spMove *p1, spMove *p2, int destNode) {
	// Variable Declarations
	int i;
	int nMove;

	if(turn) {
		// Player 1
		i = 0;
		while(p1[i++].distance != -1);
		nMove = i - 1;

		// Check if the last move is the destination node
		if(p1[nMove-1].newNode == destNode)
			return 1;
	}
	else {
		// Player 2
		i = 0;
		while(p2[i++].distance != -1);
		nMove = i - 1;

		// Check if the last move is the destination node
		if(p2[nMove-1].newNode == destNode)
			return 1;
	}
	return 0;
}

/* This function flips the player turn.
*/
void switchTurn(int *turn) {
	*turn = !(*turn);
}

/* This function searches for a specific path index where the path connects node1 & node2.
	Returns the index of that path.
*/
int searchPath(int node1, int node2, spPath pathList[]) {
	int i;
	for(i = 0; i < MAX_PATH; i++) {
		if(pathList[i].node1 == node1 && pathList[i].node2 == node2)
			return i;
		else if(pathList[i].node1 == node2 && pathList[i].node2 == node1)
			return i;
	}
	return -1;
}

/* This function returns the distance of the path indexed.
*/
int getPathDistance(int pathIndex, spPath pathList[]) {
	return pathList[pathIndex].distance;
}

/* This function asks for and implements playermoves. Returns totalDistance traveled if valid.
*/
int doPlayerMove(int turn, spNode nodeList[][MAX_CITIES], spPath pathList[], spMove p1[], spMove p2[], int *newNode) {
	// Variable Declarations
	int nMove, i;
	int currentMove, pathUsed;

	// Get current move index
	if(turn) {
		// Player 1 move index
		i = 0;
		while(p1[i++].distance != -1);
		nMove = i - 1;
	}
	else {
		// Player 2 move index
		i = 0;
		while(p2[i++].distance != -1);
		nMove = i - 1;
	}

	// Read Playermove
	if(spSafeIntInput(&currentMove)) {
		// Check player
		if(turn) {
			// Check if valid node [Player 1]
			if((pathUsed = searchPath(p1[nMove-1].newNode, currentMove, pathList))!=-1) {
				// Add new move to the moveset array & update node to be occupied
				searchNodes(currentMove, nodeList)->activePlayer = 1;
				searchNodes(p1[nMove-1].newNode, nodeList)->activePlayer = 0;
				p1[nMove].newNode = currentMove;
				p1[nMove].oldNode = p1[nMove-1].newNode;
				p1[nMove].distance = getPathDistance(pathUsed, pathList);
				p1[nMove].totalDistance = p1[nMove-1].totalDistance + p1[nMove].distance;
				*newNode = currentMove;
				return p1[nMove].totalDistance;
			}
			else {
				printf("Invalid Move. You may only move one node horizontally, vertically, or diagonally.\n");
				OS_PAUSE();
				return -1;
			}
		}
		else {
			// Check if valid node [Player 2]
			if((pathUsed = searchPath(p2[nMove-1].newNode, currentMove, pathList))!=-1) {
				searchNodes(currentMove, nodeList)->activePlayer = 2;
				searchNodes(p2[nMove-1].newNode, nodeList)->activePlayer = 0;
				p2[nMove].newNode = currentMove;
				p2[nMove].oldNode = p2[nMove-1].newNode;
				p2[nMove].distance = getPathDistance(pathUsed, pathList);
				p2[nMove].totalDistance = p2[nMove-1].totalDistance + p2[nMove].distance;
				*newNode = currentMove;
				return p2[nMove].totalDistance;
			}
			else {
				printf("Invalid Move. You may only move one node horizontally, vertically, or diagonally.\n");
				OS_PAUSE();
				return -1;
			}
		}

	}
	return -1;
}

const char * trivia(char pPlaces[]){

	//Muntinlupa
	if  (strcmp(pPlaces,"New Bilibid Prison Cemetery")==0) {
		return "A place where the dead lay to rest. It is near the New Bilibid Prison.";				
	}
	
	else if  (strcmp(pPlaces,"Starmall Alabang")==0) {
		return  "It is formerly called Metropolis Star Alabang. It is built in the 90's.";
	}
	
	else if  (strcmp(pPlaces,"Yexel's Toy Museum")==0) {
		return  "The museum has amassed over 7000 action figures and 100 life-sized figures. Yexel Sebastian was the owner of all the items in the museum.";
	}
	else if  (strcmp(pPlaces,"Jamboree Lake")==0) {
		return  "It is the smallest natural lake in the philippines. It is once served as a food production unit for the officials and inmates of the New Bilibid Prison.";
	}
	else if  (strcmp(pPlaces,"Muntinlupa Sports Complex")==0) {
		return  "It is used for a variety of activities such as concerts, conferences, reunions and graduation. It has a seating capacity of 3500 and has two seperate multipurpose rooms.";
	}
	
	//Taguig
	else if  (strcmp(pPlaces,"SM Aura")==0) {
		return "A large upscale shopping mall located along McKinley Parkway and C5 Road. It is the 13th SM Supermall in Metro Manila.";	
	}
	
	else if  (strcmp(pPlaces,"Bonifacio Global Center")==0) {
		return  "It is a financial and lifestyle district in Taguig, Metro Manila. It was once part of a multi-hectare portion of Taguig.";
	}
	
	else if  (strcmp(pPlaces,"Mind Museum")==0) {
		return  "The Mind Museum open its doors to the public on March 16, 2012. The Mind Museum's mission is to initiate and bolster science engagement in elevating aspects of individual, community and national life to inspire solutions to real-world problems.";
	}
	else if  (strcmp(pPlaces,"Enderun University")==0) {
		return  "It is a private non-sectarian undergraduate college. It was established in 2005.";
	}
	else if  (strcmp(pPlaces,"Manila American Cemetery")==0) {
		return  "A cemetery that honors the American and allied servicemen who died fighting the Japanese in World War 2. It offers repose to soldiers who died in the Pacific theater.";
	}
	
	//Pasig
	else if  (strcmp(pPlaces,"Hampton Gardens")==0) {
		return "It is a condominium complex that consits of low to medium rise complex towers. The construction of the condominium started in 2008.";	
	}
	
	else if  (strcmp(pPlaces,"St. Paul College Pasig")==0) {
		return  "A private,  Roman Catholic school exclusively for girls run by the Sisters of St. Paul of Chartres which was founded in France. It was established in 1970.";
	}
	
	else if  (strcmp(pPlaces,"Estancia")==0) {
		return  "It is located within the Capitol Commons. It  offers a distinctly affluent shopping, dining, and entertainment experience";
	}
	else if  (strcmp(pPlaces,"Medical City")==0) {
		return  "A tertiary care hospital in the Philippines where its health care complex serves some 40,000 in-patients and 400,000 out-patients annually. It was first named as ABM Sison Hospital which was later changed in 1975 to Medical City.";
	}
	else if  (strcmp(pPlaces,"C5 Road")==0) {
		return  "It begun its construction in 1986. It was legally known as President Carlos P. Garcia Avenue, honoring the eighth president of the Republic of the Philippines, Carlos P. Garcia.";
	}

	//Mandaluyong
	else if  (strcmp(pPlaces,"Lourdes School of Mandaluyong")==0) {
		return "It was established by the Capuchin Fathers of the Philippines in 1959. It is a private, Catholic educational institution.";	
	}
	
	else if  (strcmp(pPlaces,"Shaw Boulevard")==0) {
		return  "It is a highway that connects the cities of Mandaluyong and Pasig. It is named after William James Shaw.";
	}
	
	else if  (strcmp(pPlaces,"EDSA")==0) {
		return  "It is the longest and the most congested highway in the metropolis. It is named after Epifanio de los Santos.";
	}
	else if  (strcmp(pPlaces,"Meralco")==0) {
		return  "It is the Philippines' largest distributor of electrical power. It is led by Chairman and CEO Manuel M. Lopez, whose family, through direct and indirect holdings, retains control of some 25 percent of the company.";
	}
	else if  (strcmp(pPlaces,"La Salle Greenhills")==0) {
		return  "It is a private Catholic school exclusively for boys located on Ortigas Avenue, Mandaluyong City, Metro Manila. The school opened its door in July 1959.";
	}
	
	//Manila
	else if  (strcmp(pPlaces,"SM Mall of Asia")==0) {
		return "It is the fourth largest shooping mall in the Philippines. Owned and developed by SM Prime Holdings, the largest mall chain owner and developer in the Philippines.";	
	}
	
	else if  (strcmp(pPlaces,"De La Salle University")==0) {
		return  "It was established in 1911 by the Catholic teaching congregation Brothers of the Christian Schools. De La Salle College was granted university status on February 19, 1975.";
	}
	
	else if  (strcmp(pPlaces,"University of Sto Thomas")==0) {
		return  "The University of Santo Tomas is one of the oldest existing universities and holds the oldest extant university charter in the Philippines and in Asia. It was founded on April 28, 1611.";
	}
	else if  (strcmp(pPlaces,"Rizal Park")==0) {
		return  "It was officially named Rizal Park, after the name of Dr. Jose Rizal, our national hero, as an honor and tribute to him. It is also called Luneta Park because the area looks like a crescent (Lunette).";
	}
	else if  (strcmp(pPlaces,"Fort Santiago")==0) {
		return  "It is a citadel built by Spanish navigator and governor Miguel López de Legazpi for the new established city of Manila in the Philippines. It is built in 1593.";
	}

	
	//Quezon
	else if  (strcmp(pPlaces,"Ateneo de Manila University")==0) {
		return "It began in 1859 when Spanish Jesuits established the Escuela Municipal de Manila, a public primary school established in Intramuros for the city of Manila. The educational tradition of the Ateneo embraces the much older history of the Jesuits as a teaching order in the Philippines. ";	
	}
	else if  (strcmp(pPlaces,"Quezon Memorial Circle")==0) {
		return  "A national park and a national shrine located in Quezon City, which became the capital of the Philippines from 1948 to 1976. The park is located inside a large traffic circle in the shape of an ellipse and bounded by the Elliptical Road.";
	}
	else if  (strcmp(pPlaces,"Eastwood")==0) {
		return  "It was opened in 1969 with Sears, Strouss, Montgomery Ward, and Woolworth as anchors. It was the first mall to feature both Montgomery Ward and Sears. ";
	}
	else if  (strcmp(pPlaces,"Cubao")==0) {
		return  "The area of Cubao was once friar lands that were part of the District of Morong (now Rizal Province) during the Spanish Occupation (1565-1898). It was named Cubao because of the folk tales spotting hunchbacked (kuba) witches in the area.";
	}
	else if  (strcmp(pPlaces,"Araneta Coliseum")==0) {
		return  "It was constructed from 1957 to late 1959, and designed and built by Architect Dominador Lacson Lugtu and Engrineer Leonardo Onjunco Lugtu. The Coliseum received international recognition and was recognized as the largest covered coliseum in the world.";
	}
	
	//Caloocan
	else if  (strcmp(pPlaces,"Malabon Zoo")==0) {
		return "The zoo has a private collection of exotic and Philippine endemic animals. Mr. Manny Tangco collected these animals since 1960's.";	
	}
	else if  (strcmp(pPlaces,"La Mesa Nature Reserve")==0) {
		return  "It is surrounding the La Mesa Reservoir, which is the source of most of the drinking water of Manila. A place where you can go trekking, biking, trail running and bird watching.";
	}
	else if  (strcmp(pPlaces,"Glorieta Park")==0) {
		return  "It was built in the 1970s as part of the wider Makati Commercial Center complex. It was used as a location by Viva Films for its youth-oriented movie Hotshots.";
	}
	else if  (strcmp(pPlaces,"San Bartolome Church")==0) {
		return  "A Roman Catholic church located in Poblacion, Malabon. Established as a visita of Tondo, 21st of May 1599. Became a parish under the patronage of Saint Bartholomew in Tambobong (Malabon today), 17th of May 1614.";
	}
	else if  (strcmp(pPlaces,"LRT Caloocan Mall")==0) {
		return  "It is a home to hundred of stores and outlets that offer a variety of products and services. It is located along Rizal Avenue Extension. The mall entrance is directly adjacent to LRT Monumento Station.";
	}

}

/* This function initializes the moveset arrays
*/
void initMoveSet(int size, spMove moveset[]) {
	int i;
	for(i = 0; i < size; i++) {
		moveset[i].distance = -1;
		moveset[i].totalDistance = -1;
		moveset[i].newNode = -1;
		moveset[i].oldNode = -1;
	}
}

/*	This function checks the totalDistance and decides who won the game.
	Returns 0 for draw, 1 for Player 1, 2 for Player 2.
*/
int decideWinner(spMove p1[], spMove p2[]) {
	// Variable Declarations
	int i, nMove;
	int distance1, distance2;

	// Decide winner
	i = 0;
	while(p1[i++].distance != -1);
	nMove = i - 1;

	distance1 = p1[nMove-1].totalDistance;

	i = 0;
	while(p2[i++].distance != -1);
	nMove = i - 1;

	distance2 = p2[nMove-1].totalDistance;

	if(distance1 < distance2)
		return 1;
	else if(distance2 < distance1)
		return 2;

	return 0;
}

spMove * dijkstra(int startpoint, int endpoint, spNode nodeList[][MAX_CITIES], spPath pathList[]) {
	// Declare the return moveset - assume it will be freed by caller
	int initSPSize = MAX_NODES;
	spMove * moveset = (spMove *) malloc(sizeof(struct spMoveTag)*initSPSize);
	// Catch null memory
	if(moveset == NULL) {
		printf("Dijkstra's Algorithm: NOT ENOUGH MEMORY!\n");
		fprintf(stderr, "Dijkstra's Algorithm: Out of Memory Error!");
		exit(1);
	}

	// Matrix Declarations
	int costMatrix[MAX_MUNICIPAL*MAX_CITIES][MAX_MUNICIPAL*MAX_CITIES];


	// Variable Declarations
	

	// Operations:

	// 1. Calculate the elements of the cost matrix.
	

	return moveset;
}

/* This function is the heart of all the gameplay. It calls all relevant functions
	and handles all the gameplay. 
*/
void spGameplay(spNode nodeList[][MAX_CITIES], spPath pathList[]) {
	// Declare and initialize applicable lists
	int initialMovesetSize = 200;
	struct spMoveTag *p1 = (struct spMoveTag *) malloc(sizeof(struct spMoveTag)*initialMovesetSize);
	struct spMoveTag *p2 = (struct spMoveTag *) malloc(sizeof(struct spMoveTag)*initialMovesetSize);

	// Catch null memory
	if(p1 == NULL) {
		printf("Gameplay P1: NOT ENOUGH MEMORY!\n");
		fprintf(stderr, "Gameplay P1: Out of Memory Error!");
		exit(1);
	}
	else if(p2 == NULL) {
		printf("Gameplay P2: NOT ENOUGH MEMORY!\n");
		fprintf(stderr, "Gameplay P2: Out of Memory Error!");
		exit(1);
	}

	initMoveSet(initialMovesetSize, p1);
	initMoveSet(initialMovesetSize, p2);
	
	// Variable Declarations
	int doExit = 0, over = 0, totalDistance = 0, currDistance = 0;
	int turn = 1, activePlayer;
	int nChoice, i, j;
	int destPoint;
	char destName[20];
	int latestNode;
	
	// Loop for both players
	do {
		// Initialize Game / Select Starting Point
		do {
			OS_CLEAR();
			displaySPGrid(nodeList, pathList);
			printf("Alternatively, a text-file version of this grid has also been generated.\n"
				"========================================================================\n");

			// Let player select starting-point
			if(turn) activePlayer = 1;
			else activePlayer = 2;
			printf("Player %d:\n"
				"Enter your starting point. Your starting point must be in the first city on the grid (Muntinlupa).\n"
				"In other words, the first row of this grid.\n"
				"Your Choice [Enter Node ID]: ", activePlayer);
			if(spSafeIntInput(&nChoice)) {
				// Check if input is in the first city
				if(nChoice == 28 || nChoice == 21 || nChoice == 14 || nChoice == 7 || nChoice == 0) {
					if(turn) {
						// Player 1
						p1->newNode = nChoice;
						p1->distance = 0;
						p1->totalDistance = 0;
						latestNode = nChoice;
						// Update nodeList
						for(i=0; i<MAX_MUNICIPAL; i++) {
							for(j=0; j<MAX_CITIES; j++) {
								if(nodeList[i][j].nodeID == p1->newNode)
									nodeList[i][j].activePlayer = 1;
							}
						}
						doExit = 1;
					}
					else {
						// Player 2
						p2->newNode = nChoice;
						p2->distance = 0;
						p2->totalDistance = 0;
						latestNode = nChoice;
						// Update nodeList
						for(i=0; i<MAX_MUNICIPAL; i++) {
							for(j=0; j<MAX_CITIES; j++) {
								if(nodeList[i][j].nodeID == p1->newNode)
									nodeList[i][j].activePlayer = 2;
							}
						}
						doExit = 1;
					}
				}
				else {
					printf("Starting point must be in the first row (Muntinlupa).\n");
					OS_PAUSE();
				}
			}
			else {
				printf("Input must be a valid integer!\n");
				OS_PAUSE();
			} 
		} while(!doExit);
		
		doExit = 0;
		// Select destination point
		do {
			OS_CLEAR();
			// Let player select destination-point
			if(turn) {
				// Display Grid
				displaySPGrid(nodeList, pathList);
				printf("Destination Point:\n"
					"Enter your destination point. Your destination point must be in the last city on the grid (Caloocan).\n"
					"In other words, the last row of this grid.\nThe destination point will be the same for both players.\n"
					"Your Choice [Enter Node ID]: ");
				if(spSafeIntInput(&nChoice)) {
					// Check if input is in the first city
					if(nChoice == 34 || nChoice == 27 || nChoice == 20 || nChoice == 13 || nChoice == 6) {
						if(turn) {
							// Save Destination Point
							destPoint = nChoice;
							doExit = 1;
						}
					}
					else {
						printf("Destination point must be in the last row (Caloocan).\n");
						OS_PAUSE();
					}
				}
				else {
					printf("Input must be a valid integer!\n");
					OS_PAUSE();
				} 
			}
			else {
				// Search in nodes
				strcpy(destName, searchNodes(destPoint, nodeList)->name);
				printf("Same with player 1, the destination point is %s.\n", destName);
				doExit = 1;
			}	
		} while(!doExit);

		printf("You may now start the game!\n");
		OS_PAUSE();

		// Main-loop
		doExit = 0;
		totalDistance = 0;
		do {
			OS_CLEAR();
			// DISPLAY GRID
			displaySPGrid(nodeList, pathList);
			printf("Alternatively, a text-file version of this grid has also been re-generated.\n"
				"========================================================================\n");

			if(turn) {
				activePlayer = 1;
			}
			else {
				activePlayer = 2;
			}

			// Ask the player for the move
			do {
				printf("Current Node: %s\n", searchNodes(latestNode, nodeList)->name);
				printf("Fun fact!: %s\n", trivia(searchNodes(latestNode, nodeList)->name));
				printf("[Player %d | Total Distance: %d units] Enter your move: ", activePlayer, totalDistance);
				currDistance = doPlayerMove(turn, nodeList, pathList, p1, p2, &latestNode);
			} while(currDistance==-1);
			
			totalDistance = currDistance;

			// Check if destination reached.
			if(isGameOver(turn, p1, p2, destPoint))
				doExit = 1;

		} while(!doExit);

		if(turn) {
			// Switch turns
			switchTurn(&turn);
			OS_CLEAR();
			printf("Player 1, you have reached the destination with a total distance of %d units!\n"
					"Player 2, you're up!\n", totalDistance);
			OS_PAUSE();
		}
			
		else 
			// End Game
			over = 1;

	} while(!over);

	// Decide Winner
	OS_CLEAR();
	switch(decideWinner(p1,p2)) {
		case 0:
			printf("It's a draw! Congratulations to both players!\n");
			break;
		case 1:
			printf("Player 1 wins the game!\n");
			break;
		case 2:
			printf("Player 2 wins the game!\n");
	}	

	// Display Game Statistics

	i = 0;
	while(p1[i++].distance != -1);
	int nMove = i - 1;
	
	printf("Player 1 travled a total distance of: %d units.\n", p1[nMove-1].totalDistance);

	i = 0;
	while(p1[i++].distance != -1);
	nMove = i - 1;

	printf("Player 2 travled a total distance of: %d units.\n", p2[nMove-1].totalDistance);
	
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
	
	spMove * dijkstraPath = dijkstra(28,34,SPNodes,SPPaths);

	int i = 0;
	while(dijkstraPath[i].distance != -1) {
		printf("%d	%d\n", dijkstraPath[i].newNode, dijkstraPath[i].totalDistance);
		i++;
	}
	free(dijkstraPath);

	/* COMMENTING THE WHOLE MAIN OUT FOR TESTING PURPOSES FOR DIJKSTRA'S ALGORITHM
	// Variable Declarations
	char cChoice;
	do {
		// Display game rules & mechanics
		//OS_CLEAR();
		printf("Note: To see the entire map, please keep the terminal window in its biggest possible size.\n"
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
	*/
	return 0;
}
