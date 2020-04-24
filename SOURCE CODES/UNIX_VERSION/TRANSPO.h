/*
	GEMATMW PROJECT
	TRANSPORTATION PROBLEM MODULE

	DEVELOPED BY:
		- Giancarlo T. Tee
		- Benedict C. Sun

*/
// Library Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// SET UNIX-SPECIFIC MACROS
#define OS_CLEAR() system("clear")
#define OS_PAUSE() fflush(stdin); printf("Press any key to continue...\n"); getchar()

//Typedefs
typedef char String28[29];
typedef struct detail{
	float price;
	int quantity;
}Detail;
typedef struct{
	int Pathing[3][3];
	float sum;
}pathinfo;

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

//Ben's Definitions
#define MIN_PRICE 25			// range for price
#define MAX_PRICE 35
#define MIN_STOCKS 700			// range for sum of three integers
#define MAX_STOCKS 900
#define MIN_SEED 150			// range for one out of three integers
#define MAX_SEED 300

//User-defined functions

int tpSafeIntInput(int *x) {
	char buffer[15];
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
/*
	1. Checks if there exists same quantity for row n and column n
*/
int checkDegenerate(int ogSupply[3], int ogDemand[3]){
	int i, degenerate = 0;
	for (i=0; i<3 && !degenerate; i++)
		if (ogSupply[i] == ogDemand[i])
			degenerate = 1;

	return degenerate;
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
	printf("%c\n", LR_COR);
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
void initializePlayers(Detail details[3][3], Detail player1[3][3], Detail player2[3][3], Detail best[3][3]){
	int row, col;
	for (row=0; row<3; row++){
		for (col=0; col<3; col++){
			details[row][col].quantity = 0;
			player1[row][col] = details[row][col];
			player2[row][col] = details[row][col];
			best[row][col] = details[row][col];
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
		printf("=======================================\n      TRANSPORTATION PROBLEM GAME\n=======================================\n");
		printf("[Setting]:\n\n  During time of Covid-19 lockdown, online purchasing has been the highest it has ever been. However, this \nmeans that work in shopee management is more hectic than ever, the company needs more logistics managers! \nAs Shopee employees, you are both given the chance at a promotion but only one will get the position. So \nthe company decided to make this a competition between you two.\n\n  You are both given the task to manage distribution of toilet paper orders throughout Luzon, Visayas, and Mindanao.\nYou are given a choice to allocate the method of distribution through land, sea, and air with varying costs. Whoever\nis able to minimize the cost while distributing everyting will get the position. Who will prevail?\n\n");
		printf("[1] Start Game\n");
		printf("[2] Back to Main Menu\n\n");
		printf("Enter option number: ");
		if (tpSafeIntInput(nOption))
		{
			if(*nOption==2||*nOption==1)
				exit=1;
			else{
				printf("\n[INVALID INPUT]\n");
				OS_PAUSE();
				OS_CLEAR();
			}
		}
		else{
			printf("\n[INVALID INPUT]\n");
			OS_PAUSE();
			OS_CLEAR();
		}
				
	}
}

void tutorial(){
	printf("[Table Guide]\nSupply & demant info: number left/Original Number\nBox Format: [number]  Allocated supplies | Price\n\n");
	printf("\n\n[Tutorial]:\n\nIn this game, the goal is to try and allocate the supplies to fill in the demand on the bottom of the table.\nThe players will take turns exhausting all the supplies and filling all demand by filling the 3x3 grid. Use the information given.\n\n");
	printf("1. The program will ask to input a position you wish to fill, the position number is shown with the [number] icon\n");
	printf("2. Player 1 will allocate first, then once player 1 is done allocating, player 2 will allocate next.\n");
	printf("3. Once all players are done allocating, the program displays its calculation for the most optimal allocation.\n");
	printf("4. The one closest to the most optimal allocation wins.\n\n");
	
	OS_PAUSE();
	OS_CLEAR();
}

//======================================= Turn Function ========================================
/*
  Parameter/s Required: (a) int corresponding to position on the board (b) int* corresponding to the row index, (c) *int corresponding to column index 
  Return Type: N/A
  Description: (a) Converts the position into its corresponding row and column indices
*/
void getIndex(int pos, int *row, int *col)	
{
	*col = pos % 3;
	*row = pos / 3;
}

/*
	returns 1 if quantity is sufficient
*/
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
		if (tpSafeIntInput(&pos))
		{
			if(pos<=0 || pos>9)
				printf("\n[INVALID POSITION!]\n");
			else
				exit=1;
		}
		else
			printf("\n[INVALID POSITION!]\n");
		//getIndex(pos, &col, &row);
	
		
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
	int row, col, tempQuant, invalid, *storedQuant, isChar;
	pos -= 1;
	getIndex(pos, &row, &col);
	storedQuant = &player[row][col].quantity;
	do{
		invalid = 0;
		
		do{
			isChar = 0; // if user inputs a character
			printf("Enter quantity to allocate [ [-1] to cancel ]: ");
			if(tpSafeIntInput(&tempQuant)){
				if (tempQuant < 0)
					printf("Only non-negative integers allowed\n\n");
			}
			else{
				printf("Only non-negative integers allowed\n\n");
				isChar = 1;
			}
		}while(tempQuant < -1 || isChar);
	
		if (tempQuant != -1)
		{
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
					printf("Quantity exceeds demand of [%d], please allocate a lesser quantity...\n\n",  *storedQuant + demand[col]);
					invalid = 1;
					OS_PAUSE();
				}
			}
			else{
				printf("Quantity exceeds supply [%d]: please allocate a lesser quantity...\n\n", *storedQuant + supply[row]);
				invalid = 1;
				OS_PAUSE();
			}
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
/*
	1. Calculates a player's total price
	2. Returns a float representing the total price
*/
float calculateCost(Detail player[3][3]){
	float total = 0;
	int row, col;
	for (row = 0; row < 3; row++){
		for (col = 0; col < 3; col++)
			total += player[row][col].quantity * player[row][col].price;
	}
	return total;
}

//==================CHECKING ALGORITHMS==================================================================
/*
	1. Northwest Corner Rule
*/

void nwCornerRule(Detail best[3][3], int supply[3], int demand[3]){
	int row, col;
	for(row = 0; row < 3; row++){
		for (col = 0; col < 3; col++){
			if (supply[row] >= demand[col]){ 	// if supply is sufficient to fill demand
				best[row][col].quantity = demand[col];		// fill block with demand
				supply[row] -= demand[col];					// deduct supplies with total column's total demand
				demand[col] -= demand[col];					// set demand to 0
			}
			else if (supply[row] < demand[col] && supply[row] != 0){ // if supply is insufficient but can still allocate some
 				best[row][col].quantity = supply[row];		// fill block with remaining supplies
				demand[col] -= supply[row];					// reduce demand with remaining supplies
				supply[row] -= supply[row];					// set supplies to 0
			}
			else	// cannot allocate anything
				best[row][col].quantity = 0;				// fill block with 0 quantity
		}
	}
}
//==================================Stepping Stone Related Function=========================================================
//used to initialize 3x3 2d arrays
void init2dArray(int Array[][3]){
	int i, h;
	for(i=0;i<3;i++){
		for(h=0;h<3;h++)
			Array[i][h]=0;
		}
}
//used for initializing any arrays with pathinfo
void initPathresult(pathinfo Pathresult[]){
	int i, z, h;
	for(i=0;i<4;i++){
		Pathresult[i].sum=0;
		for(z=0;z<3;z++){
			for(h=0;h<3;h++){
				Pathresult[i].Pathing[z][h]=0;
			}
		}
	}
}
//Adjusts the table given the info on the new path with the highest amount saved.
void adjustTable(pathinfo Pathresult, Detail Best[][3]){
	int i, h;
	int quantity=-1000;
	//Finds the lowest quantity among the ones that you subtracted price in the initial stepping stone. (the ones below 0 in this case)
	for(i=0;i<3;i++){
		for(h=0;h<3;h++){
			if (Pathresult.Pathing[i][h]<0){
				if(quantity<Best[i][h].quantity*-1){
					quantity=Best[i][h].quantity*-1;
				}
			}
		}
	}
	//adds or subtracts the quantity by the lowest quantity we got from the loop above^ depending on the sign
	for(i=0;i<3;i++){
		for(h=0;h<3;h++){
			if (Pathresult.Pathing[i][h]!=0){
				if(Pathresult.Pathing[i][h]<0){
					Best[i][h].quantity+=quantity;
				}
				else if(Pathresult.Pathing[i][h]>0){
					Best[i][h].quantity-=quantity;
				}
			}
		}
	}
}
//This function determines the possible movements vertically and horizontaly based on the position in the 3x3 matrix
//-1=right/down, 0=both sides, 1=left/up
void posMovement(int nRow, int nCol, int* vert, int* hori){
	switch (nRow){
		case 0:
			*vert=-1;
		break;
		case 1:
			*vert=0;
		break;
		case 2:
			*vert=1;
		break;
	}
	switch (nCol){
		case 0:
			*hori=-1;
		break;
		case 1:
			*hori=0;
		break;
		case 2:
			*hori=1;
		break;
	}
}
//program checks the next next possible movements in advance to see if it will lead to a win or a dead end
int nextDest2(Detail Best[][3], int i, int h, int state, int Path[][3], int nRow, int nCol, int pNum){
	int vert, hori;
	posMovement(i, h, &vert, &hori);
	int noEnd=0;
	//HORIZONTAL MOVEMENT==============================================================================================
	pNum++;	
		
		if(state==0){
			if(pNum>=3){
				if(i==nRow && h+1==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i==nRow && h+2==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i==nRow && h-1==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i==nRow && h-2==nCol){
					return 1;
					noEnd=1;
				}		
			}
			if(noEnd==0){
			if(hori==-1 || hori==0){
				if(Best[i][h+1].quantity!=0 && Path[i][h+1]==0){// if quantity of coord is filled and has not been passed through or is the original position
						return 1;
						}
					}
			if(hori==-1){
					if(Best[i][h+2].quantity!=0 && Path[i][h+2]==0){
							return 1;
				}
			}
			if(hori==1 || hori==0){
				if(Best[i][h-1].quantity!=0 && Path[i][h-1]==0)
						return 1;
			}
			if(hori==1){
					if(Best[i][h-2].quantity!=0 && Path[i][h-2]==0){
							return 1;
				}
			}	
		}
		}
		//END OF HORIZONTAL====================================================================================
		//VERTICAL MOVEMENT======================================================================================
		if(state==1){
			if(pNum>=3){
				if(i+1==nRow && h==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i+2==nRow && h==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i-1==nRow && h==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i-2==nRow && h==nCol){
					return 1;
					noEnd=1;
				}		
			}
			if(noEnd==0){
			if(vert==-1 || vert==0){
				if(Best[i+1][h].quantity!=0 && Path[i+1][h]==0){// if quantity of coord is filled and has not been passed through or is the original position	
						return 1;
				}
			}
			if(vert==-1){
				if(Best[i+2][h].quantity!=0 && Path[i+2][h]==0){
					
						return 1;
				}
			}
			if(vert==1 || vert==0){
				if(Best[i-1][h].quantity!=0 && Path[i-1][h]==0){
						
						return 1;
				}
			}
			if(vert==1){
				if(Best[i-2][h].quantity!=0 && Path[i-2][h]==0){
						
						return 1;
				}
			}
		}
	}
		//END OF VERTICAL==================================================
	return 0;
}
//program checks future movement in advance to see if it will lead to a stalemate.
int nextDest(Detail Best[][3], int i, int h, int state, int Path[][3], int nRow, int nCol, int pNum){
	int vert, hori;
	posMovement(i, h, &vert, &hori);
	int noEnd=0;
	//HORIZONTAL MOVEMENT==============================================================================================
		pNum++;
		
		if(state==0){
			if(pNum>=3){
				if(i==nRow && h+1==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i==nRow && h+2==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i==nRow && h-1==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i==nRow && h-2==nCol){
					return 1;
					noEnd=1;
				}		
			}
			if(noEnd==0){
			if(hori==-1 || hori==0){
				if(Best[i][h+1].quantity!=0 && Path[i][h+1]==0){// if quantity of coord is filled and has not been passed through or is the original position
					if(nextDest2(Best, i, h+1, 1, Path, nRow, nCol, pNum))
							return 1;
						}
					}
			if(hori==-1){
					if(Best[i][h+2].quantity!=0 && Path[i][h+2]==0 ){
					if(nextDest2(Best, i, h+2, 1, Path, nRow, nCol, pNum))
							return 1;
				}
			}
			if(hori==1 || hori==0){
				if(Best[i][h-1].quantity!=0 && Path[i][h-1]==0 )
					if(nextDest2(Best, i, h-1, 1, Path, nRow, nCol, pNum))
						return 1;
			}
			if(hori==1){
					if(Best[i][h-2].quantity!=0 && Path[i][h-2]==0){
						if(nextDest2(Best, i, h-2, 1, Path, nRow, nCol, pNum))
							return 1;
				}
			}	
		}
		}
		//END OF HORIZONTAL====================================================================================
		//VERTICAL MOVEMENT======================================================================================
		if(state==1){
			if(pNum>=3){
				if(i+1==nRow && h==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i+2==nRow && h==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i-1==nRow && h==nCol){
					return 1;
					noEnd=1;
				}
						
				else if(i-2==nRow && h==nCol){
					return 1;
					noEnd=1;
				}		
			}
			if(noEnd==0){
			if(vert==-1 || vert==0){
				if(Best[i+1][h].quantity!=0 && Path[i+1][h]==0){// if quantity of coord is filled and has not been passed through or is the original position
					if(nextDest2(Best, i+1, h, 0, Path, nRow, nCol, pNum))	
						return 1;
				}
			}
			if(vert==-1){
				if(Best[i+2][h].quantity!=0 && Path[i+2][h]==0){
				if(nextDest2(Best, i+2, h, 0, Path, nRow, nCol, pNum))
						return 1;
				}
			}
			if(vert==1 || vert==0){
				if(Best[i-1][h].quantity!=0 && Path[i-1][h]==0){
					if(nextDest2(Best, i-1, h, 0, Path, nRow, nCol, pNum))	
						return 1;
				}
			}
			if(vert==1){
				if(Best[i-2][h].quantity!=0 && Path[i-2][h]==0){
					if(nextDest2(Best, i-2, h, 0, Path, nRow, nCol, pNum))	
						return 1;
				}
			}
			
		}
		}
		//END OF VERTICAL==================================================
	return 0;
}
//Main function for creating the closed loop path of each empty quantities
//stores the path in the Path array
void CreateLoop(int nRow, int nCol, Detail Best[][3], int Path[][3]){
	int i, h, pNum=1;//pNum is the number of the current path
	int state=0,vert, hori;//state=0 means horizontal movement, 1 is for vertical.
	int noEnd=0, moved=1, error=0, exit=0;
	i=nRow;
	h=nCol;
	//loop does not stop until i and h is equal to their original values
	do{
		error++;
		noEnd=0;
		if(moved){
		Path[i][h]=pNum;//turns the value of the current coords to 1
		pNum++;
		moved=0;
		}
		posMovement(i, h, &vert, &hori);
		//printf("\n%d %d\n", vert, hori);
		//printf("og =%d og =%d\n", nRow, nCol);
		//printf("row=%d col=%d\n", i, h);
		//printf("%d\n", state);
		//HORIZONTAL MOVEMENT==============================================================================================
		if(state==0){
			if(pNum>=3){
				if(i==nRow && h+1==nCol){
					h+=1;
					noEnd=1;
				}
						
				else if(i==nRow && h+2==nCol){
					h+=2;
					noEnd=1;
				}
						
				else if(i==nRow && h-1==nCol){
					h-=1;
					noEnd=1;
				}
						
				else if(i==nRow && h-2==nCol){
					h-=2;
					noEnd=1;
				}		
			}
			if(noEnd==0){//FUNCTION ENTERS IF THERE IS NO MOVE THAT LEADS TO THE INITIAL ROW AND COL VAL
			if(hori==-1 || hori==0){
				if(Best[i][h+1].quantity!=0 && Path[i][h+1]==0){// if quantity of coord is filled and has not been passed through or is the original position
					if(nextDest(Best, i, h+1, 1, Path, nRow, nCol, pNum)){//IF the next movement from this coord is a dead end, do not store.
						h+=1;
						moved=1;
					}
					else if(Best[i][h+2].quantity!=0 && Path[i][h+2]==0){
						if(nextDest(Best, i, h+2, 1, Path, nRow, nCol, pNum)){
							h+=2;
							moved=1;
						}
							
					}
				}
				else if(hori==-1){
					if(Best[i][h+2].quantity!=0 && Path[i][h+2]==0){
						if(nextDest(Best, i, h+2, 1, Path, nRow, nCol, pNum)){
							h+=2;
							moved=1;
						}	
					}
				}
			}
			if(hori==1 || hori==0){
				if(Best[i][h-1].quantity!=0 && Path[i][h-1]==0 ){
					if(nextDest(Best, i, h-1, 1, Path, nRow, nCol, pNum)){//IF the next movement from this coord is a dead end, do not store.
						h-=1;
						moved=1;
					}
					else if(hori==1){
						if(Best[i][h-2].quantity!=0 && Path[i][h-2]==0){
						if(nextDest(Best, i, h-2, 1, Path, nRow, nCol, pNum)){
							moved=1;
							h-=2;
						}
						}
					}
				}
				else if(hori==1){
					if(Best[i][h-2].quantity!=0 && Path[i][h-2]==0){
						if(nextDest(Best, i, h-2, 1, Path, nRow, nCol, pNum)){
							moved=1;
							h-=2;
							}
						}
					}
				}	
			}
		}
		//END OF HORIZONTAL====================================================================================
		//VERTICAL MOVEMENT======================================================================================
		if(state==1){
			if(pNum>=3){
				if(i+1==nRow && h==nCol){
					i+=1;
					noEnd=1;
				}
						
				else if(i+2==nRow && h==nCol){
					i+=2;
					noEnd=1;
				}
						
				else if(i-1==nRow && h==nCol){
					i-=1;
					noEnd=1;
				}
						
				else if(i-2==nRow && h==nCol){
					i-=2;
					noEnd=1;
				}		
			}
			if (noEnd==0){
			if(vert==-1 || vert==0){
				if(Best[i+1][h].quantity!=0 && Path[i+1][h]==0l){// if quantity of coord is filled and has not been passed through or is the original position
					if(nextDest(Best, i+1, h, 0, Path, nRow, nCol, pNum)){//IF the next movement from this coord is a dead end, do not store.
						i+=1;
						moved=1;
					}
					else if(vert==-1){
						if((Best[i+2][h].quantity!=0 && Path[i+2][h]==0) || (i+2==nRow && h==nCol)){
							if(nextDest(Best, i+2, h, 0, Path, nRow, nCol, pNum)){
								i+=2;
								moved=1;
							}
						}
					}
				}
			else if(vert==-1){
				if(Best[i+2][h].quantity!=0 && Path[i+2][h]==0){
					if(nextDest(Best, i+2, h, 0, Path, nRow, nCol, pNum)){
						i+=2;
						moved=1;
					}
					}
				}
			}
			if(vert==1 || vert==0){
				if(Best[i-1][h].quantity!=0 && Path[i-1][h]==0){
					if(nextDest(Best, i-1, h, 0, Path, nRow, nCol, pNum)){//IF the next movement from this coord is a dead end, do not store.
						i-=1;
						moved=1;
					}
					else if(vert==1){
						if(Best[i-2][h].quantity!=0 && Path[i-2][h]==0){
							if(nextDest(Best, i-2, h, 0, Path, nRow, nCol, pNum)){
								i-=2;
								moved=1;
							}
						}
					}
				}
			else if(vert==1){
					if(Best[i-2][h].quantity!=0 && Path[i-2][h]==0){
						if(nextDest(Best, i-2, h, 0, Path, nRow, nCol, pNum)){
							i-=2;
							moved=1;
						}
						}
					}
				}
			}
		}
		if(state==1){
			state=0;
		}
		else
			state=1;
		if(error>10){
			exit=1;
			Path[2][0]=4;
		}
		//END OF VERTICAL==================================================	
	}while((i!=nRow  || h!=nCol || pNum<3) && exit!=1 );
}
//MAIN FUNCTION FOR STEPPING STONE
void SteppingStone(int supply[], int demand[], Detail Best[][3], String28 labels[], int ogSupply[], int ogDemand[]){
	//path arrays
	int Path[3][3]; 
	//Loop variables
	int i, h, z, j, k=0;
	int exit=0;
	//state variables
	int isNegative=0;
	//Storing Variables
	float highestsum=0;
	int highestindex=-1; 
	pathinfo Pathresult[4];
	//desc variables
	int loopNum=1;//for display of what nth is the stepping stone
	
	//initialize arrays to 0
	init2dArray(Path);
	//Getting path and sum for every empty space-----------------------------------------------------------------
	while(exit!=1){
		isNegative=0;
		initPathresult(Pathresult);
		highestsum=0;
		k=0;
		highestindex=-1;
		for(i=0;i<3;i++){
			for(h=0;h<3;h++){
				init2dArray(Path);
				if(Best[i][h].quantity==0){
					CreateLoop(i, h, Best, Path);
					for(z=0;z<3;z++){
						for(j=0;j<3;j++){
							if(Path[z][j]!=0 && Path[z][j]%2==1)//add if the path number is odd
								Pathresult[k].sum+=Best[z][j].price;
							else if(Path[z][j]!=0 && Path[z][j]%2==0){//subtract if the path number is even
								Pathresult[k].sum-=Best[z][j].price;
								Path[z][j]*=-1;//turn the path value of this coord to negative. Will be used to determine where to add and subtract quantities.
							}
							Pathresult[k].Pathing[z][j]=Path[z][j];//copies the path per coord.
						}
					}
					if(Pathresult[k].sum<0)
						isNegative=1;
					k++;
				}
			}
		}
		//if isNegative is true(there is a negative number) the program will get the lowest of the negatives and adjusts the BEST table based on that and recalculates the cost.
		if(isNegative){
			for(i=0;i<4;i++){
				if(highestsum>Pathresult[i].sum){
					highestsum=Pathresult[i].sum;
					highestindex=i;
				}
			}
			//display table each stepping stone
			printf("\n\t\t\tStepping Stone %d\n", loopNum );
			displayTable(supply, demand, Best, labels, ogSupply, ogDemand);
			loopNum++;	
			adjustTable(Pathresult[highestindex], Best);
		}
		else{
			//display table each stepping stone
			printf("\n\t\t\tStepping Stone %d\n", loopNum );
			displayTable(supply, demand, Best, labels, ogSupply, ogDemand);
			loopNum++;
			exit=1;	
		}
	
		
		}
}
//==================================endStepping Stone Related Function=========================================================
int compareCost(float total1, float total2, float bestTotal)
{
	if (total1 - bestTotal < total2 - bestTotal)
		return 1;
	else if (total2 - bestTotal < total1 - bestTotal)
		return 2;
	else 
		return 0;
}
// =============================== END OF TURN FUNCTIONS =================================

int transpoProblem(void) {
  // ================== Variable Declarations =================
  //Gian's Variables
  String28 labels[6]={"LUZON","VISAYAS", "MINDANAO", "DHL AIRMAIL", "LBC LAND" , "PARCEL SHIPPING"};
 //Ben's variables
  	Detail details[3][3], player1[3][3], player2[3][3], best[3][3];
  	int ogSupply[3], ogDemand[3], supply[3], demand[3], degenerate;
	int nOption, over = 0, pos, gameResult;
	float total1, total2, bestTotal;
	char cOption;
	time_t t;
  // ================== End of Variable Declarations ============
  srand( (unsigned) time(&t));
	startMenu(&nOption);
	if (nOption == 1){
		do{
			OS_CLEAR();//change to OS_CLEAR
			do{
				generatePrice(details);
				generateSupply_Demand(ogSupply, ogDemand);
				degenerate = checkDegenerate(ogSupply, ogDemand);		
				//if (degenerate)
					//printf("Degenerate case: generating random numbers again\n\n");		// for test case, can remove for final product
			}while(degenerate);
			initializePlayers(details, player1, player2, best);
			copySupplyDemand(ogSupply, ogDemand, supply, demand);
			
			displayTable(supply, demand, details, labels, ogSupply, ogDemand);		// have to change to display player only	
			tutorial();
			
			do{
				printf("\t\t\tPlayer 1's Table\n");
				displayTable(supply, demand, player1, labels, ogSupply, ogDemand);
				pos=getPos(pos); 
				fillTable(supply, demand, player1, pos);
				if (isComplete(supply, demand)){
					displayTable(supply, demand, player1, labels, ogSupply, ogDemand);
					printf("\nAll allocations completed... End your turn? [Y/N]: ");
					scanf(" %c", &cOption);
					if (cOption == 'Y' || cOption == 'y')
						over = 1;
					else if (cOption == 'N' || cOption == 'n'){
						printf("\n\nEdit the quantities that you wish to change\n\n");
						OS_PAUSE();
					}
				}
				OS_CLEAR();
			}while(!over);	// calculate for total cost, then repeat for player 2
			total1 = calculateCost(player1);	//display this afterwards
			printf("=============================================\n");
			printf("Player 1's Total Cost: %.2f\n",total1);
			printf("=============================================\n\n");
			printf("Player 2's turn\n\n");
			OS_PAUSE();
			OS_CLEAR();
			
			//reset supply, demand, and over
			copySupplyDemand(ogSupply, ogDemand, supply, demand);
			over = 0;
			do{
				printf("\t\t\tPlayer 2's Table\n");
				displayTable(supply, demand, player2, labels, ogSupply, ogDemand);
				pos=getPos(pos); 
				fillTable(supply, demand, player2, pos);
				if (isComplete(supply, demand)){
					displayTable(supply, demand, player2, labels, ogSupply, ogDemand);
					printf("\nAll allocations completed... End your turn? [Y/N]: ");
					scanf(" %c", &cOption);
					if (cOption == 'Y' || cOption == 'y')
						over = 1;
					else if (cOption == 'N' || cOption == 'n'){
						printf("\n\nEdit the quantities that you wish to change\n\n");
						OS_PAUSE();
					}
				}
				OS_CLEAR();	
			}while(!over);
			total2= calculateCost(player2);	//display this afterward
			printf("=============================================\n");
			printf("Player 2's Total Cost: %.2f\n",total2);
			printf("=============================================\n\n");
			printf("Calculating most optimal cost...\n\n");
			OS_PAUSE();
			OS_CLEAR();
			
			//implement northwest corner rule and stepping stone method algorithm here
			//===================================== temporary placement of nwCornerRule for testing
			copySupplyDemand(ogSupply, ogDemand, supply, demand);
			nwCornerRule(best, supply, demand);
			printf("\t\t\tNorthwest Corner Rule\n");
			displayTable(supply, demand, best, labels, ogSupply, ogDemand);
			printf("\n\n");
			OS_PAUSE();//change to OS_PAUSE
			OS_CLEAR();
			// stepping stone
			SteppingStone(supply, demand, best, labels, ogSupply, ogDemand);
			printf("\t\t\tMost Optimal pattern:\n");
			displayTable(supply, demand, best, labels, ogSupply, ogDemand);
			printf("\n\n");
			OS_PAUSE();
			OS_CLEAR();
			//=====================================
			printf("\t\t\tPlayer 1's Table\n");
			displayTable(supply, demand, player1, labels, ogSupply, ogDemand);
			printf("\t\t\tPlayer 2's Table\n");
			displayTable(supply, demand, player2, labels, ogSupply, ogDemand);
			printf("\t\t\tMost Optimal pattern:\n");
			displayTable(supply, demand, best, labels, ogSupply, ogDemand);
			bestTotal = calculateCost(best);
			printf("=============================================\n");
			printf("Player 1's Total Cost: %.2f\n",total1);
			printf("Player 2's Total Cost: %.2f\n",total2);
			printf("Lowest cost: %.2f\n", bestTotal);
			printf("=============================================\n\n");
			gameResult = compareCost(total1, total2, bestTotal);
			
			switch (gameResult){
				case 0: printf("Game resulted in a tie... play again\n\n"); break;
				case 1: printf("Player 1 wins!\n\n"); break;
				case 2:	printf("Player 2 wins!\n\n"); break;
				default: fprintf(stderr, "Error encountered\n\n");
			}
			OS_PAUSE();
			//OS_CLEAR();
		}while(gameResult == 0);
		if (gameResult == 1)
			return 1;
		else
			return 2;
	}
  return -1;
}
