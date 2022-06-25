#include <stdio.h>
#include "util.h"
#include <stdlib.h>

/**
 * @brief 
 * 
 * @param xs 
 * @param currentlen 
 * @param seqlen 
 * @param seq 
 */
void generate_sequence (int xs, int currentlen, int seqlen, int *seq)
{
    if (currentlen < seqlen)
    {
        seq[currentlen] = xs;
        if (xs % 2)
            xs = xs * 3 + 1;
        else
            xs = xs / 2; 

        generate_sequence(xs, currentlen + 1, seqlen, seq);
    }
}

/**
 * @brief 
 * 
 * @param f 
 * @param xs 
 * @param seqlen 
 * @param loop 
 * @param looplen 
 */
void check_loop_iterative(void (*f)(), int xs, int seqlen, int *loop, int *looplen)
{
    static int time = 0;
    if (time <= seqlen + 1 && time >= 0)
    {
        if (!time)
        {
            printf("\n\nSeq = {");
            time++;
            check_loop_iterative(f, xs, seqlen, loop, looplen);
        }
        else if (time == seqlen + 1) 
        {
            printf("\b\b}\n\n");
            time++;
            check_loop_iterative(f, xs, seqlen, loop, looplen);
        }
        if (time <= seqlen + 1 && time >= 0)
        {
            int *temp = (int *) malloc((time + 1) * sizeof(int));
            f(xs, 0, time, temp);
            printf("%d, ",temp[time - 1]);
            time++;
            free(temp);
            check_loop_iterative(f, xs, seqlen, loop, looplen);
        }
    }
    else
    {
        if (time == -1)
        {
            loop[0] = xs;
            int temp[3];
            f(xs, 0, 2, temp);
            int a = *looplen;
            a--;
            if (a > 0)
                {check_loop_iterative(f, temp[1], seqlen, &loop[1], &a);}
        }
        else
        {
            if (*looplen >= 2)
            {
                printf("Checking at %d...\n",*looplen);
                int * seq = (int *) malloc(seqlen * sizeof(int));
                f(xs, 0, seqlen, seq);
                int ls = 0;
                int le = 0;

                int check = has_loop(seq, seqlen, *looplen, &ls, &le);
                int temp_seq = seq[ls];
                free(seq);
                if (check)
                {
                    printf("\nLoop detected at %d\n",*looplen);
                    printf("First : %d, Last : %d\n",ls,le);
                    time = -1;
                    check_loop_iterative(f, temp_seq, seqlen, loop, looplen);
                    int deneme[9] = {0};
                }
                else
                {
                    *looplen -= 1;
                    check_loop_iterative(f, xs, seqlen, loop, looplen);
                }
            }
            else
            {
                *looplen = 0;
            }
        }
    }
    
}

/**
 * @brief 
 * 
 * @param arr 
 * @param n 
 * @param looplen 
 * @param ls 
 * @param le 
 * @return int 
 */
int has_loop(int *arr, int n, int looplen, int *ls, int *le)
{
    int returning = 0;
    int temp_n = n;
    while (arr[n - looplen - 1] == arr[n - 1] && returning < looplen)
    {
        returning++;
        n--;
    }
    if (returning == looplen) 
    {
        *ls = n - looplen;
        *le = temp_n - looplen - 1;
        return 1;
    }
    return 0;
}

/**
 * @brief 
 * 
 * @param f 
 * @param xs 
 * @param seqlen 
 * @param h 
 * @param digit 
 */
void hist_of_firstdigits(void (*f)(), int xs, int seqlen, int *h, int digit)
{
    if (digit < 10)
    {
        int * seq = (int *) malloc(seqlen * sizeof(int));
        f(xs, 0, seqlen, seq);
        for (int i = 0; i < seqlen; i++)
        {
            int temp = seq[i];
            while (temp > 9) {temp /= 10;}
            if (temp==digit) {h[digit - 1]++;}
        }
        free(seq);
        hist_of_firstdigits(f, xs, seqlen, h, digit + 1);
    }
}