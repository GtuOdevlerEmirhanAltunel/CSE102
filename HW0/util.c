#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    if(numerator==0) printf("0");
    else if(denominator==1) printf("%d",numerator);
    else printf("%d/%d", numerator, denominator);
}

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
}

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
}

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * n2;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
}

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * d2;
    *d3 = d1 * n2;
    fraction_simplify(n3, d3);
}

void fraction_simplify(int * n, int * d) {
    int gcd = 2;
    do{
        if(*n%gcd==0 && *d%gcd==0){
		    *n /= gcd;
            *d /= gcd;
        }
        else{
			gcd++;
		}
    }while(*n >= gcd && *d >= gcd);
}
