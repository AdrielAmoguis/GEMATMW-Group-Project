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
	int row, col, min = MIN_PRICE, max = MAX_PRICE;
	
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
	
	sum_stocks = rand() % (max - min + 1) + min;		// 1. Generate a number
	
	generateThree(supply, sum_stocks);			// 2. Generate 3 numbers that will add up to that number
	generateThree(demand, sum_stocks);			// 3. Do the same for demand

}
// ======================= END OF RNG FUNCTIONS ========================

//==============================DISPLAY FUNCTIONS====================================
/*
	MAIN FUNCTIONS FOR DISPLAYING TABLES
*/
//displays the top part of the table including the first row labels
void topTable(String28 labels[]){
	int i;
	
	printf("%c", UL_COR);
	for(i=0; i<15;i++){
		printf("%c", HORI);
	}
	printf("%c", U_MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", U_MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", U_MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", U_MID);
	for(i=0; i<7;i++){
			printf("%c", HORI);
		}
	printf("%c", UR_COR);
	printf("\n");
	printf("%c%-15s%c%-14s%c%-14s%c%-14s%c%-7s%c\n", VERT, " ", VERT, labels[0], VERT, labels[1], VERT, labels[2], VERT, " ", VERT);
}
//prints only the lines in between the middle rows of the table
void midTable(){
	int i;
	printf("%c", L_EDGE);
	for(i=0; i<15;i++){
		printf("%c", HORI);
	}
	printf("%c", MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", MID);
	
	for(i=0; i<7;i++){
		printf("%c", HORI);
  }
	printf("%c", R_EDGE);
	printf("\n");
}
//displays the bottom line of the table including the labels in the last wrow
void botTable(int demand[],int ogDemand[]){
	int i;
	printf("%c%-15s%c%7d/%-6d%c%7d/%-6d%c%7d/%-6d%c%-7s%c\n", VERT, " ", VERT, demand[0], ogDemand[0], VERT, demand[1], ogDemand[1], VERT, demand[2], ogDemand[2], VERT, " ", VERT);
	printf("%c", LL_COR);
	for(i=0; i<15;i++){
		printf("%c", HORI);
	}
	printf("%c", L_MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", L_MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", L_MID);
	for(i=0; i<14;i++){
		printf("%c", HORI);
	}
	printf("%c", L_MID);

	for(i=0; i<7;i++){
		printf("%c", HORI);
	}
	printf("%c", LR_COR);
}
//main function for displaying the table
void displayTable(int supply[], int demand[], Detail details[][3], String28 labels[], int ogSupply[], int ogDemand[]){
	int i, h=3;
	

	topTable(labels);
	for(i=0;i<3;i++){
		midTable();
		printf("%c%-15s%c%c%d%c%4d|%6.2f%c%c%d%c%4d|%6.2f%c%c%d%c%4d|%6.2f%c%3d/%3d%c\n", VERT, labels[h], VERT, '[', 1+3*i,']', details[i][0].quantity , details[i][0].price, VERT, '[', 2+3*i,']', details[i][1].quantity, details[i][1].price, VERT, '[', 3+3*i,']', details[i][2].quantity, details[i][2].price, VERT, supply[i], ogSupply[i], VERT);
		h++;
	}
	midTable();
	botTable(demand, ogDemand);
}

// ========================== END OF DISPLAY FUNCTIONS ===============================
void initializePlayers(Detail details[3][3], Detail player1[3][3], Detail player2[3][3]){
	int row, col;
	for (row=0; row<3; row++){
		for (col=0; col<3; col++){
			player1[row][col].price = details[row][col].price;
			player1[row][col].quantity = 0;
			player2[row][col] = player1[row][col];
			details[row][col] = player1[row][col];
		}
	}
}

void copySupplyDemand(int ogSupply[3], int ogDemand[3], int supply[3], int demand[3])
{
	int i;
	for (i=0; i<3; i++){
		supply[i] = ogSupply[i];
		demand[i] = ogDemand[i];
	}
}
void startMenu(int *nOption){
	int exit=0;
	while(exit!=1){
	printf("[1] Start Game\n");
	printf("[2] Back to Main Menu\n\n");
	printf("Enter option number: ");
	scanf("%d", nOption);
	
	if(*nOption==2||*nOption==1)
		exit=1;
	else{
		printf("\n[INVALID INPUT]\n");
		//system pause
		//system clear
	}
	}
}

void tutorial(){
	printf("\n\nInsert Tutorial Text Here\n\n");
	system("pause");
	system("cls");
}
// ================================== Turn Function ================================
//ERROR DETECTOR FUNCTIONS===================================================================
int checkSupply(int supply, int stored, int quant)	// quant <= supply + current
{
	if (quant <= stored + supply)
		return 1;
	else 
		return 0;
}

int checkDemand(int demand, int stored, int quant)
{
	if (quant <= stored + demand)
		return 1;
	else 
		return 0;
}

int getPos(int pos){
	int exit=0;
	while(exit!=1){
		printf("\n\nPick a position: ");
		scanf("%d", &pos);
		//getIndex(pos, &col, &row);
	
		if(pos<=0 || pos>9){
			printf("\n[INVALID POSITION!]\n");
		}
		else
			exit=1;
	}
	//systempause; <====put OSPAUSE here
	return pos;
}
//END OF ERROR FUNCTIONS==================================================================
/*
	row = supply
	col = demand
*/
void fillTable(int supply[3], int demand[3], Detail player[3][3], int pos){
	int row, col, tempQuant, invalid, *storedQuant;
	pos -= 1;
	getIndex(pos, &row, &col);
	storedQuant = &player[row][col].quantity;
	do{
		invalid = 0;
		printf("Enter quantity to allocate: ");
		scanf("%d", &tempQuant);
		if (checkSupply(supply[row], *storedQuant, tempQuant)) 	//quant = less than or equal to supply
		{
			if (checkDemand(demand[col], *storedQuant, tempQuant)) //quant = less than or equal to demand
			{
				//store tempQuant to player[row][col].quantity; reduce supply, might have to make another supply variable
				supply[row] += *storedQuant - tempQuant;
				demand[col] += *storedQuant - tempQuant;
				*storedQuant = tempQuant;
			}
			else{
				printf("Quantity exceeds demand of [%d], please allocate a lesser quantity...\n\n",  demand[col]);
				invalid = 1;
				OS_PAUSE();
				OS_CLEAR();
			}
		}
		else{
			printf("Quantity exceeds supply [%d]: please allocate a lesser quantity...\n\n", supply[row]);
			invalid = 1;
			OS_PAUSE();
			OS_CLEAR();
		}
			
	}while(invalid == 1);
}

/*
	1. Checks if all supply and demand have been properly allocated
	2. returns 1 if all are filled, 0 if not
*/
int isComplete(int supply[3], int demand[3]){
	int i, nComplete = 1;		// sensor to determine if all supplies and demands are 0
	for (i=0; i<3 && nComplete == 1; i++)
		if (supply[i] != 0 || demand[i] != 0)		//if any supply/demand is left, 
			nComplete = 0;
	return nComplete; 
}
// ========================= End of Turn Functions ===================
/* HEADER MAIN FUNCTION */
int transpoProblem() {
	// ================== Variable Declarations =================
  	//Gian's Variables
	String28 labels[6]={"LUZON","VISAYAS", "MINDANAO", "DHL AIRMAIL", "LBC LAND" , "PARCEL SHIPPING"};
  	//Ben's variables
  	Detail details[3][3], player1[3][3], player2[3][3];
  	int ogSupply[3], int ogDemand[3], supply[3], demand[3];
	int sum_stocks, nOption, over = 0, pos;
	char cOption;
	time_t t;
  	// ================== End of Variable Declarations ============
  
  	srand( (unsigned) time(&t));
	startMenu(&nOption);
	if (nOption == 1){
		system("cls");
		generatePrice(details);
		generateSupply_Demand(ogSupply, ogDemand);
		initializePlayers(details, player1, player2);
		copySupplyDemand(ogSupply, ogDemand, supply, demand);
		
		displayTable(supply, demand, details, labels, ogSupply, ogDemand);		// have to change to display player only	
		tutorial();
		
		do{
			printf("\t\tPlayer 1's Table\n");
			displayTable(supply, demand, player1, labels, ogSupply, ogDemand);
			pos=getPos(pos); 
			fillTable(supply, demand, player1, pos);
			if (isComplete(supply, demand)){
				printf("\nAll allocations completed... End your turn? [Y/N]: ");
				scanf(" %c", &cOption);
				if (cOption == 'Y' || cOption == 'y')
					over = 1;
				else if (cOption == 'N' || cOption == 'n'){
					printf("\n\nEdit the quantities that you wish to change\n\n");
					OS_PAUSE();
					OS_CLEAR();
				}
			}
			//check if all information is filled
			//if all is filled, prompt user to confirm		
		}while(!over);	// calculate for total cost, then repeat for player 2
		
	}
  return 0;
}
