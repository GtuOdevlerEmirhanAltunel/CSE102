#include <stdio.h>
#include "util.h"

char *in = "<\033[0;32mINP\033[0m>"; //Input prefix
char *ou = "<\033[0;33mOUT\033[0m>"; //Output prefix
char *er = "<\033[0;31mERR\033[0m>"; //Error prefix
char *pt = "\n\033[0;1;3;4m%s\n\n\033[0m"; // Part text

int main(){

// Görev-1 ──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────

	int x,y,divisor,next;

	printf(pt,"Part 1");
	printf("%s Enter the first integer  : ",in); scanf("%d",&x);
	printf("%s Enter the second integer : ",in); scanf("%d",&y);
	printf("%s Enter the divisor        : ",in); scanf("%d",&divisor);

	int result1 = find_divisible(x,y,divisor);

	if(result1>0) {

		printf("%s The first integer between %d and %d divided by %d is %d.\n",ou,x,y,divisor,result1);
		printf("%s Enter the number how many next : ",in); scanf("%d",&next);

		int result1_1 = find_nth_divisible(next,result1,divisor);

		if(result1_1 > y)
			printf("%s There is not any %d. integer between %d and %d can be divided by %d.\n",er,next+1,x,y,divisor);
		else
			printf("%s The %d. integer between %d and %d divided by %d is %d.\n",ou,next+1,x,y,divisor,result1_1);

	}
	else if(result1==-1)
		printf("%s There is not any integer between %d and %d can be divided by %d.\n",er,x,y,divisor);
	else if(result1==-2)
		printf("%s First number cannot be bigger than the second number.\n",er);
	else if(result1==-3)
		printf("%s First number cannot be equal to the second number.\n",er);

// Görev-2 ──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────

	char tc[12] = {0};

	printf(pt,"Part 2");
	printf("%s Enter your Identity Number : ",in); scanf("%12s",tc);

	int result2 = validate_identity_number(tc);

	/* Hata Mesajları / Opsiyonel bir bölüm olduğu için olabildiğince kısa yazdım. Karışıklık için kusura bakmayın.*/
	if (result2==-1) {
		printf("%s Identity Number cannot be more than 11 characters. -> ",er);
		for (int i=0;i<11;i++) printf("\033[0;32m%c\033[0m",tc[i]);
		printf("%c\n",tc[11]);
	}else if (result2<=-2 && result2>=-12){
		printf("%s Identity Number cannot be less than 11 characters. -> ",er);
		for (int i=0;i<-result2-1;i++) printf("\033[0;32m%c\033[0m",tc[i]);
		for (int i=-result2-1;i<11;i++) printf(".");
		printf("\n");
	}else if (result2<=-13 && result2>=-23){
		printf("%s Identity Number must be made up of digits. -> ",er);
		for (int i=0;i<-result2-13;i++) printf("\033[0;32m%c\033[0m",tc[i]);
		printf("%c\n",tc[-result2-13]);
	}else if (result2 == -24) {
		printf("%s Identity Number cannot start with 0. -> ",er);
		printf("%c",tc[0]);
		for (int i=1;i<11;i++) printf("\033[0;32m%c\033[0m",tc[i]);
		printf("\n");
	}else if (result2==-25) {
		printf("%s Invalid Identity Number.\n",er);
	}else if (result2==-26) {
		printf("%s Invalid Identity Number.\n",er);
	}/* Hata Mesajları */

	else if (result2==1){

		int password = 0;

		printf("%s Your Identity Number is valid.\n",ou);
		printf("%s Please enter a password (4 digit) : ",in); scanf("%d",&password);

		if (password<1000||password>=10000){

			printf("%s Your password is invalid. Try again later.\n",er);

			return 0;

		}
		else if (create_customer(tc,password)==1)
			printf("%s Customer created.\n",ou);

// Görev-3 ───────────────────────────────────────────────────────────────────────────────────────────────────Yukarıdaki else if'in içinde

		char c_tc[11];
		int c_password;

		printf(pt,"Part 3");
		printf("%s Enter your Identity Number : ",in); scanf("%12s",c_tc);

		if(validate_identity_number(c_tc) >= -23 && validate_identity_number(c_tc) <= -1){
			printf("%s There is a problem with your Identity Number\n",er);
			return 0;
		}

		printf("%s Enter your Password        : ",in); scanf("%4d",&c_password);

		int result3 = check_login(c_tc,c_password);

		if (result3==-1)
			printf("%s Wrong Identity Number.\n",er);
		else if (result3==-2)
			printf("%s Wrong Password.\n",er);
		else if (result3==1) {
			float withdraw = 0.0;
			printf("%s Login Successful.\n",ou);
			printf("%s Enter your withdraw amount : ",in); scanf("%f",&withdraw);
			int result3_3 = withdrawable_amount(withdraw);
			printf("%s Withdrawable amount is : %d\n",ou,result3_3);
		}
	}
	return 0;
}
