/**
 * @file main.c
 * @author Emirhan Altunel
 * @brief 
 * @version 1.1
 * @date 2022-04-25 - 2022-04-26
 * 
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


#define ROWS 15
#define COLS 15
#define WORD_LIST_COUNT 50
#define WORD_COUNT 7 // Max = WORD_LIST_COUNT
#define WORD_LENGTH 10

#if WORD_COUNT > WORD_LIST_COUNT
#error Invalid numbers.
#endif

int main()
{
    FILE *fp;
    srand(time(0));

    char matrix[ROWS][COLS] = {0};

    char wordlist[WORD_LIST_COUNT][WORD_LENGTH];
    
    int used_word[WORD_COUNT];
    char wordlist_rotation[WORD_COUNT];
    
    int coords[WORD_COUNT][2];
    int points = 0;

    if (fp = fopen("wordlist.txt","rt"))
    {
        for (int i = 0; i < WORD_LIST_COUNT; i++)
        {   
            fscanf(fp,"%s",wordlist[i]);
        }
        for (int i = 0; i < WORD_COUNT; i++)
        {
            int numara = rand() % WORD_LIST_COUNT;
            int used = 0;
            for (int j = 0; j < i; j++) if (used_word[j] == numara) {
                used = 1;
                break;
            }
            if (used) {
                i--;
                used = 0;
                continue;
            }

            used_word[i] = numara;

            wordlist_rotation[i] = rand() % 8;
            int x = !!(wordlist_rotation[i] % 4) * (1 - wordlist_rotation[i] / 4 * 2);
            int y = !!((wordlist_rotation[i] + 2) % 8 % 4) * (1 - (wordlist_rotation[i] + 2) % 8 / 4 * 2);

            int length = strlen(wordlist[used_word[i]]) - 1;
            int pass = 1;
            while (pass)
            {
                coords[i][0] = rand() % ROWS;
                coords[i][1] = rand() % COLS;

                if (coords[i][0] + length * y >= ROWS - 1 || coords[i][0] + length * y < 1 || coords[i][1] + length * x < 1 || coords[i][1] + length * x >= COLS - 1) continue;
                pass = 0;
                for (int k = 0; k <= length; k++) 
                {
                    if (matrix[coords[i][0] + k * y][coords[i][1] + k * x]) pass = 1;
                    for (int u = -1; u < 2; u++) for (int d = -1; d < 2; d++) if (matrix[coords[i][0] + k * y + d][coords[i][1] + k * x + u]) pass = 1;
                }
            }
            for (int k = 0; k <= length; k++)
                matrix[coords[i][0] + k * y][coords[i][1] + k * x] = wordlist[used_word[i]][k];
            matrix[coords[i][0]][coords[i][1]] += 'A' - 'a';
        }
    }

    // ! Boş yerleri doldurma
    for (int i = 0; i < 15; i++) for (int j = 0; j < 15; j++)
    if (!matrix[i][j]) matrix[i][j] = rand() % 26 + 10;
    

    int heart = 3;
    int hint = 0;

    while(heart)
    {
        // ! Ekrana bastırma
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            if (hint && matrix[i][j] >= 'A') printf("\e[47;30m%2c\e[0m",matrix[i][j]);
            else if (matrix[i][j] >= 'a') printf("%2c",matrix[i][j]);
            else if (matrix[i][j] >= 'A') printf("%2c",matrix[i][j] + 'a' - 'A');
            else if (matrix[i][j] == 1) printf("\e[31m X\e[0m");
            else if (matrix[i][j]) printf("%2c",matrix[i][j] + 'a' - 10);
            else printf("\e[31m  \e[0m");
            printf("\n");
        }

        int corx = 0,cory = 0;
        char input[WORD_COUNT * 2];
        char raw[WORD_COUNT * 2];

        scanf("%[^\n]",raw);

        if (sscanf(raw,"%d %d %s",&corx,&cory,input) != 3) 
        {
            sscanf(raw,"%[^\n] ",input);
            if (!strcmp(input,":q")) break;
            else if (!strcmp(input,":hint")) hint = !hint;
        }
        else if (matrix[cory][corx] > 'A')
        {
            int word;
            for (word = 0; word <= WORD_COUNT; word++)
            {
                if (word == WORD_COUNT)
                {
                    word = -1;
                    break;
                } 
                if (coords[word][0] == cory && coords[word][1] == corx && !strcmp(wordlist[used_word[word]],input)) 
                    break;
            }
            printf("%d\n",word);
            if (word >= 0)
            {
                int x = !!(wordlist_rotation[word] % 4) * (1 - wordlist_rotation[word] / 4 * 2);
                int y = !!((wordlist_rotation[word] + 2) % 8 % 4) * (1 - (wordlist_rotation[word] + 2) % 8 / 4 * 2);

                int length = strlen(wordlist[used_word[word]]);

                points+= 2;
                printf("Nice +2 points(%d). %s\n",points,wordlist[used_word[word]]);

                for (int k = 0; k < length; k++)
                    matrix[coords[word][0] + k * y][coords[word][1] + k * x] = 1;  
            }
        }
    }

    return 0;
}
