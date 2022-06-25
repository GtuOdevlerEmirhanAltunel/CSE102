#include <stdio.h>
#include "util.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    
    int k = 55;
    int l = 7;

    printf("Enter the sequence length : ");
    scanf("%d",&l);

    printf("Enter the first element : ");
    scanf("%d",&k);
    

    int b = l / 2;
    int *a = (int *) malloc(b * sizeof(int));
    check_loop_iterative(generate_sequence, k, l, a, &b);

    if (b)
    {
        printf("Loop = {");
        for (int i = 0; i < b; i++) {printf("%d, ",a[i]);}
        printf("\b\b}\n");
    }
    else
    {
        printf("No loop found.\n");
    }
    free(a);
    
    int h[9] = {0};

    hist_of_firstdigits(generate_sequence, k, l, h, 1);

    printf("Hist = {");
    for (int i = 0; i < 9; i++) {printf("%d, ",h[i]);}
    printf("\b\b}\n");
    

    return 0;
}