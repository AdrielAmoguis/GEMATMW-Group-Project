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
		- Modular System
		- Two header files are required:
			1. SHORTESTPATH.h
			2. TRANSPO.h
*/
#include <stdio.h>
#include <stdlib.h>

// DETERMINE OPERATING SYSTEM
#if _WIN32 || _WIN64
	#define OS_CLEAR() system("cls")
	#define OS_PAUSE() system("PAUSE")
#else
	#define OS_CLEAR() system("clear")
	#define OS_PAUSE() system("read -n1 -r -p \"Press any key to continue...\" key")
#endif

// MODULE IMPORTS
#include "SHORTESTPATH.h"
#include "TRANSPO.h"

/* This function takes safe integer input. 
	Stores the input in the address of param1.
	Returns 0 when invalid, 1 when valid. */
int safeIntInput(int *x) {
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

/* *** MAIN FUNCTION ***/
int main() {
	// Variable Declarations
	int nChoice, doExit = 0;
	
	// MAIN MENU
	printf("DE LA SALLE UNIVERSITY\n"
		   "MATHEMATICS & STATISTICS DEPARTMENT\n"
		   "MATH IN THE MODERN WORLD\n"
		   "GROUP PROJECT\n"
		   "\nSUBMITTED TO: DR. APRIL SAY-AWEN\n"
		   "\nDEVELOPED BY:\n"
		   "ADRIEL ISAIAH V. AMOGUIS\n"
		   "BENEDICT SUN\n"
		   "GIANCARLO T. TEE\n"
		   "KYLE FRANCIS LIM\n"
		   "======================================\n");
	OS_PAUSE();
	OS_CLEAR();
	
	do {
		printf("ADI'S MINIGAMES - Choose One:\n"
		       "1. Lakwatsa sa Maynila!\n" // Definitely need a better title. HAHAHAHAHAHA
			   "2. Transportation Problem\n"
			   "3. Exit Program\n");
		printf("Your Choice: ");
		if(safeIntInput(&nChoice)) {
			switch(nChoice) {
				case 1:
					shortestPath();
					OS_PAUSE();
					break;
				case 2:
					transpoProblem();
					OS_PAUSE();
					break;
				case 3:
					doExit = 1;
					break;
				default:
					printf("Invalid Input!\n");
			}
		}
		else 
			printf("Invalid Input! Input must be an integer.\n");
		
		OS_CLEAR();
	} while(!doExit);
	
	return 0;
}

