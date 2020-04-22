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
	int nChoice;
	char cChoice;
	int over = 0;
	// Target # of points to win
	const int targetPoints = 20;
	// Point Values for Each Game
	const int pointsSP = 4;
	const int pointsTP = 2;
	// Players' Points Variables
	int player1 = 0;
	int player2 = 0;
	
	// MAIN MENU
	printf("DE LA SALLE UNIVERSITY\n"
		   "MATHEMATICS & STATISTICS DEPARTMENT\n"
		   "MATH IN THE MODERN WORLD\n"
		   "GROUP PROJECT\n"
		   "\nSUBMITTED TO: DR. APRIL SAY-AWEN\n"
		   "\nDEVELOPED BY:\n"
		   "ADRIEL ISAIAH V. AMOGUIS\n"
		   "BENEDICT C. SUN\n"
		   "GIANCARLO T. TEE\n"
		   "KYLE FRANCIS Y. LIM\n"
		   "======================================\n");
	OS_PAUSE();
	OS_CLEAR();
	
	// Display Game Mechanics
	printf("WELCOME TO ADI'S MINIGAMES!\n"
		   "Game Mechanics:\n"
		   "1. This is a two player sequential game.\n"
		   "2. It's a race to %d points. The first to reach it wins the game.\n"
		   "3. Think of strategies to choose which games to play and in what order.\n", targetPoints);
	OS_PAUSE();
	OS_CLEAR();

	do {
		printf("Target Number of Points to Win: %d\n", targetPoints);
		printf("Player 1: %d Points\n", player1);
		printf("Player 2: %d Points\n\n", player2);
		printf("ADI'S MINIGAMES - Choose One:\n"
		       "1. Lakwatsa sa Maynila! 	[%d Points]\n" // Definitely need a better title. HAHAHAHAHAHA
			   "2. Shoppe?				 	[%d Points]\n"
			   "3. Exit Program\n", pointsSP, pointsTP);
		printf("Your Choice: ");
		if(safeIntInput(&nChoice)) {
			switch(nChoice) {
				case 1:
					switch(shortestPath()) {
						case 0: // Tie
							player1 += pointsSP/2;
							player2 += pointsSP/2;
							printf("%d points awarded to both players.\n", pointsSP/2);
							OS_PAUSE();
							break;
						case 1: // Player 1
							player1 += pointsSP;
							printf("%d points awarded to player 1.\n", pointsSP);
							OS_PAUSE();
							break;
						case 2: // Player 2
							player2 += pointsSP;
							printf("%d points awarded to player 2.\n", pointsSP);
							OS_PAUSE();
							break;
					}
					break;
				case 2:
					switch(transpoProblem()) {
						case 0: // Tie
							player1 += pointsTP/2;
							player2 += pointsTP/2;
							printf("%d points awarded to both players.\n", pointsTP/2);
							OS_PAUSE();
							break;
						case 1: // Player 1
							player1 += pointsTP;
							printf("%d points awarded to player 1.\n", pointsTP);
							OS_PAUSE();
							break;
						case 2: // Player 2
							player2 += pointsTP;
							printf("%d points awarded to player 2.\n", pointsTP);
							OS_PAUSE();
							break;
					}
					break;
				case 3:
					// Ask for confirmation before exit
					OS_CLEAR();
					printf("Are you sure you want to exit?\nAll progress will be lost: [y/N]: ");
					scanf(" %c", &cChoice);
					if(cChoice == 'Y' || cChoice == 'y')
						return 0;
					break;
				default:
					printf("Invalid Input!\n");
			}

			// Check for game winner
			if(player1 >= targetPoints && player2 >= targetPoints && player1 == player2) {
				// Tie
				OS_CLEAR();
				printf("GAME OVER!\n"
					   "The game is tied and both have reached the required score.\n"
					   "It's a tie!\n"
					   "\nTied Score: %d\n\n", player1);
				over = 1;
				OS_PAUSE();
			}
			else if(player1 >= targetPoints) {
				// Player 1 Wins
				OS_CLEAR();
				printf("GAME OVER!\n"
					   "Player one has reached over the score to beat!\n"
					   "Player 1 wins and takes the gold!\n"
					   "\nPlayer 1 Score: %d\nPlayer 2 Score: %d\n\n", player1, player2);
				over = 1;
				OS_PAUSE();
			}
			else if(player2 >= targetPoints) {
				// Player 2 Wins
				OS_CLEAR();
				printf("GAME OVER!\n"
					   "Player two has reached over the score to beat!\n"
					   "Player 2 wins and brings back the juicy bacon!\n"
					   "\nPlayer 1 Score: %d\nPlayer 2 Score: %d\n\n", player1, player2);
				over = 1;
				OS_PAUSE();
			}

			// Check if Game over
			if(over) {
				printf("Thanks for playing, really! :>\n");
				printf("Have a nice day!");
				return 0;
			}
		}
		else 
			printf("Invalid Input! Input must be an integer.\n");
		
		OS_CLEAR();
	} while(1);
	
	return 0;
}