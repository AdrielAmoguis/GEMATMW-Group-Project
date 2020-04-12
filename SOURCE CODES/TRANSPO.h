/*
	GEMATMW PROJECT
	TRANSPORTATION PROBLEM MODULE
*/
// Library Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// DETERMINE OPERATING SYSTEM
#if _WIN32 || _WIN64
	#define OS_CLEAR() system("cls")
	#define OS_PAUSE() system("PAUSE")
#else
	#define OS_CLEAR() system("clear")
	#define OS_PAUSE() system("read -n1 -r -p \"Press any key to continue...\" key")
#endif

// Typedefs
typedef struct detail{
	float price;
	int quantity;
}Detail;

// Constant Definitions
//Gian Constants
//TABLE VALUES-------------------------------------------
#define VERT   186   
#define HORI   205   
#define L_MID  202   
#define U_MID  203   
#define MID    206   
#define L_EDGE 204
#define R_EDGE 185
#define UL_COR 201
#define LL_COR 200
#define UR_COR 187
#define LR_COR 188

//Ben Constants
#define MIN_PRICE 25			// range for price
#define MAX_PRICE 35
#define MIN_STOCKS 500			// range for sum of three integers
#define MAX_STOCKS 800
#define MIN_SEED 150			// range for one out of three integers
#define MAX_SEED 300

// Function Definitions
// Secondary Functions
/*
  1. Generates 3 numbers that will add up to second parameter
  2. Stores those 3 numbers to first parameter
*/
void generateThree(int stocks[3], int sum_stocks){
	int i, nStock, min = MIN_SEED, max = MAX_SEED, sum = 0;
	
	for (i=0; i<3; i++){
		if (i != 2){
			nStock = rand() % (max - min + 1) + min;
			sum += nStock;
		}
		else
			nStock = (sum_stocks - sum);
		stocks[i] = nStock;
	}
}

// Primary Functions
// ==================== START OF RNG FUNCTIONS =======================
/*
    1. Generates 9 different prices for each
*/
void generatePrice(Detail details[3][3])
{
	float price;
	time_t t;
	int row, col, min = MIN_PRICE, max = MAX_PRICE;
	
	srand(time(&t));
	
	for (row=0; row < 3; row++){
		for (col = 0; col < 3; col++){
			price = rand() % (max - min + 1) + min; 
			details[row][col].price = price;
		}
	}
}

/*
	1. Generate a number
	2. Generate 3 numbers that will add up to that number
	3. Do the same for demand
*/
void generateSupply_Demand(int supply[3], int demand[3]){			
	int sum_stocks, min = MIN_STOCKS, max = MAX_STOCKS;
	time_t t;
	
	srand(time(&t));
	sum_stocks = rand() % (max - min + 1) + min;		// 1. Generate a number
	
	generateThree(supply, sum_stocks);			// 2. Generate 3 numbers that will add up to that number
	generateThree(demand, sum_stocks);			// 3. Do the same for demand

}
// ======================= END OF RNG FUNCTIONS ========================


/* HEADER MAIN FUNCTION */
int transpoProblem() {
	// ================== Variable Declarations =================
  	//Gian's Variables

  	//Ben's variables
  	Detail details[3][3];
  	int supply[3], demand[3];
  	// ================== End of Variable Declarations ============
  
  	printf("%c%c%c%c%c%c%c", UL_COR, HORI, HORI, HORI, HORI, HORI, UR_COR);
  	printf("%cgoma goma hindi%c\n", VERT, VERT);

	generatePrice(details);
	generateSupply_Demand(supply, demand);
	return 0;
}
