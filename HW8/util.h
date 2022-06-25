#ifndef _UTIL_H_
#define _UTIL_H_

// Part 1
void generate_sequence (int xs, int currentlen, int seqlen, int *seq);

// Part 2
void check_loop_iterative(void (*f)(), int xs, int seqlen, int *loop, int *looplen);

// Part 3
int has_loop(int *arr, int n, int looplen, int *ls, int *le);

// Part 4
void hist_of_firstdigits(void (*f)(int xs, int currentlen, int seqlen, int *seq), int xs, int seqlen, int *h, int digit);

#endif