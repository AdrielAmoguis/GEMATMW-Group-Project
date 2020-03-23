/*
	AMOGUIS, ADRIEL ISAIAH V.
	SUN, BENEDICT C.
	TEE, GIANCARLO
	LIM, KYLE FRANCIS
	
	GEMATMW - S15 : Dr. April Say-Awen
	Group Project
	
	Source Code Created On: March 15, 2020
	Source Code Last Edited On: March 24, 2020
	
	SOURCE NOTES:
		- [Adi - 03/15/2020] Let's get this rollin'!
*/

// Library Imports
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

// Header Imports


// Macro Definitions
#define NODENAME_LEN 31
#define MAX_MUNICIPAL 5
#define MAX_CITIES 7
#define MAX_NODES (MAX_MUNICIPAL * MAX_CITIES)


// Structure Definitions
struct spNeighborTag {
	int top;
	int right;
	int bottom;
	int left;
};

// Type Definitions
typedef struct spNodeTag {
	char name[NODENAME_LEN];
	char cityName[NODENAME_LEN];
	struct spNeighborTag distance;
} spNode;

// Functions
/* This function initializes all values of the node array for shortest path.
	This function is called by the setShortestPathNodes function. */
void initShortestPathNodes(spNode nodes[][MAX_CITIES]) {
	int i, j;
	
	for(i=0; i<MAX_CITIES; i++) {
		for(j=0; j<MAX_MUNICIPAL; j++) {
			strcpy(nodes[j][i].name, "NULL");
			strcpy(nodes[j][i].cityName, "NULL");
			nodes[j][i].distance.top = -1;
			nodes[j][i].distance.right = -1;
			nodes[j][i].distance.bottom = -1;
			nodes[j][i].distance.left = -1;
		}
	}
}

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

void displaySPGrid(spNode nodes[][MAX_CITIES]) {
	int i,j;
	printf("===================================================================================================================================================================================================================\n");
	printf("|%-29s|%-29s|%-29s|%-29s|%-29s|%-29s|%-29s|\n", nodes[0][0].cityName, nodes[0][1].cityName, nodes[0][2].cityName, nodes[0][3].cityName,
		nodes[0][4].cityName, nodes[0][5].cityName, nodes[0][6].cityName);
	printf("===================================================================================================================================================================================================================\n");
	for(i=0; i<MAX_MUNICIPAL; i++) {
		printf("|");
		for(j=0; j<MAX_CITIES; j++) {
			printf("%-29s|", nodes[i][j].name);
		} 
		printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		printf("\n");
	}	
}


/* *** MAIN FUNCTION ***/
int main() {
	spNode SPNodes[MAX_MUNICIPAL][MAX_CITIES];
	setShortestPathNodes(SPNodes);
	displaySPGrid(SPNodes);
	
	
	return 0;
}
