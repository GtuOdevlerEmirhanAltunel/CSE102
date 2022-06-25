#include <stdio.h>
#include "util.h"

int find_divisible(int x, int y, int z){

	if (x > y)
		return -2;
    else if (x == y)
		return -3;

	for(int i = x + 1; i < y; i++)
		if (i % z == 0)
			return i;

	return -1;
}

int find_nth_divisible(int n, int f_I, int z){

	for (int i = 0; i < n && f_I != -1; i++)
		f_I = f_I + z;

	return f_I;
    // Fonksiyona dahil edilmediği için kontrolü main fonksiyonun içinde yaptım.
}

int validate_identity_number(char identity_number []){

    /*
	-1 reserved for "more digits"
	-2 -12 reserved for "less digits"
	-13 -23 reserved for "non-digit chars"
	-24 reserved for "first "0" digit"
	-25 reserved for "odd-even"
	-26 reserved for "sum of first 10 digits"
	*/

	int sume = 0, sumo = 0, suma = 0;

	if (identity_number[11] != 0 && identity_number[11] != 10)
		return -1; // check if there is a 12. char

	for (int i = 0; i < 11; i++) {

		if (identity_number[i] == 0)
			return -1 - i;

		if (identity_number[i] < 48 || identity_number[i] > 57)
			return -13 - i;

		if (i < 9)
			if (i % 2 == 0)
				sumo += identity_number[i] - 48;
			else
				sume += identity_number[i] - 48;

		if (i != 10)
			suma += identity_number[i] - 48;
	}

	if (identity_number[0] == 48)
		return -24;

	if ((sumo * 7 - sume) % 10 != identity_number[9] - 48)
		return -25;

	if (suma % 10 != identity_number[10] - 48)
		return -26;

	return 1;
}

int create_customer(char identity_number [], int password){

    FILE *fp;
	fp = fopen("./customer.txt", "w");

	fprintf(fp, "%11s,%d", identity_number, password);
	fclose(fp);

	return 1;
}

int check_login(char identity_number [], int password){

    char c_identity[11] = {0};
	int c_pass = 0;
	FILE *fp;
	fp = fopen("./customer.txt", "r");

	fscanf(fp, "%11s,%d", c_identity, &c_pass);
	fclose(fp);

	for(int i = 0 ; i < 11; i++)
		if(identity_number[i] != c_identity[i])
			return -1;

	if (c_pass != password)
		return -2;

	return 1;
}

int withdrawable_amount(float cash_amount){
    return cash_amount - (int) cash_amount % 10;
}
