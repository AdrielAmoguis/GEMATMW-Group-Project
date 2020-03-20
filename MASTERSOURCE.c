/*
	AMOGUIS, ADRIEL ISAIAH V.
	SUN, BENEDICT C.
	TEE, GIANCARLO
	LIM, KYLE FRANCIS
	
	GEMATMW - S15 : Dr. April Say-Awen
	Group Project
	
	Source Code Created On: March 15, 2020
	Source Code Last Edited On: March 15, 2020
	
	SOURCE NOTES:
		- [Adi - 03/15/2020] Let's get this rollin'!
*/

// Library Imports
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Header Imports


// Macro Definitions



// Type Definitions


// Functions
int main() {
	char* cCities[7] = {"Muntinlupa","Taguig","Pasig","Mandaluyong","Manila","Quezon","Caloocan"};
	char* cMunicipality[5][7];

	cMunicipality[0][0] = "New Bilibid";
	cMunicipality[1][0] = "Starmall Alabang";
	cMunicipality[2][0] = "Yexel's Toy Museum";
	cMunicipality[3][0] = "Jamboree Lake";
	cMunicipality[4][0] = "Sports Complex";
	
	cMunicipality[0][1] = "SM Aura";
	cMunicipality[1][1] = "BGC";
	cMunicipality[2][1] = "Mind Museum";
	cMunicipality[3][1] = "Enderun University";
	cMunicipality[4][1] = "Manila American Cemetery";
	
	cMunicipality[0][2] = "Hampton Gardens";
	cMunicipality[1][2] = "St Paul College";
	cMunicipality[2][2] = "Estancia";
	cMunicipality[3][2] = "Medical City";
	cMunicipality[4][2] = "C5 Road";
	
	cMunicipality[0][3] = "Lourdes School";
	cMunicipality[1][3] = "Shaw Boulevard";
	cMunicipality[2][3] = "EDSA";
	cMunicipality[3][3] = "Meralco";
	cMunicipality[4][3] = "LaSalle GH";
	
	cMunicipality[0][4] = "SM Mall of Asia";
	cMunicipality[1][4] = "De La Salle University";
	cMunicipality[2][4] = "University of St Thomas";
	cMunicipality[3][4] = "Rizal Park";
	cMunicipality[4][4] = "Fort Santiago";
	
	cMunicipality[0][5] = "Ateneo De Manila";
	cMunicipality[1][5] = "Memorial Circle";
	cMunicipality[2][5] = "Eastwood";
	cMunicipality[3][5] = "Cubao";
	cMunicipality[4][5] = "Araneta Coliseum";
	
	cMunicipality[0][6] = "Malabon Zoo";
	cMunicipality[1][6] = "La Mesa Nature Reserve";
	cMunicipality[2][6] = "Glorieta Park";
	cMunicipality[3][6] = "San Bartolome Church";
	cMunicipality[4][6] = "LRT Caloocan Mall";
	
	//Major City
	printf("%s\t\t  %s\t\t   %s   %s\t       %s\t\t %s\t\t  %s", cCities[0], cCities[1], cCities[2], cCities[3], cCities[4], cCities[5], cCities[6]); printf("\n\n");
	//Municipality
	printf("%s\t\t %s\t  %s  %s %s\t %s %s\n", cMunicipality[0][0],cMunicipality[0][1],cMunicipality[0][2],cMunicipality[0][3],cMunicipality[0][4],cMunicipality[0][5],cMunicipality[0][6]);
	printf("%s\t %s\t\t  %s  %s %s %s  %s\n", cMunicipality[1][0],cMunicipality[1][1],cMunicipality[1][2],cMunicipality[1][3],cMunicipality[1][4],cMunicipality[1][5],cMunicipality[1][6]);
	printf("%s\t%s\t\t %s  %s\t\t  %s %s\t  %s\n", cMunicipality[2][0],cMunicipality[2][1],cMunicipality[2][2],cMunicipality[2][3],cMunicipality[2][4],cMunicipality[2][5],cMunicipality[2][6]);
	printf("%s\t\t%s   %s  %s\t  %s\t\t %s\t\t  %s\n", cMunicipality[3][0],cMunicipality[3][1],cMunicipality[3][2],cMunicipality[3][3],cMunicipality[3][4],cMunicipality[3][5],cMunicipality[3][6]);
	printf("%s     %s\t  %s  %s\t  %s\t\t %s %s\n", cMunicipality[4][0],cMunicipality[4][1],cMunicipality[4][2],cMunicipality[4][3],cMunicipality[4][4],cMunicipality[4][5],cMunicipality[4][6]);
	
	return 0;
}
