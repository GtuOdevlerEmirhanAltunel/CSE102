/**
 * @file main.c
 * @author  Emirhan Altunel
 *          200104004035
 * 
 * @brief
 * @version 2.4
 * @date 2022.04.25 - 2022.05.05
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Things you can change
#define WORD_COUNT 7 // * How many number we put on. You should pick appropriate rows and cols value.
#define ROW 15
#define COL 15
#define HEALTH 3
#define POINTS 2 // ! Players get that much points when they find a word.

// Things you should not change
#define TOTAL_WORDS 50      //  I want to make it dynamicly but I think malloc is not allowed
#define WORD_SIZE 6
#define CONTROL_CHECK 1     //  Check if there is "enough" space for words. Dont increase too much! 
                            //  1 or 0 is ideal for you.
#define PRINT_SPACE 3       //  Additinioal space between letters. More than 2 add rulers.
#define DIAGONAL_PASS 1     //  1 is on, 2 is off. Other values would cause errors.
#define REVERSE_PASS 2      //  0 is off, others are on.
#define PALINDROME_PASS 5   //  3 is off, 5 is on. Other values would cause errors.
                            //  Some words are palindromes like "mom". 
                            //  These words are hard to know where they start.
                            //  If this value are on, program accept ending points 
                            //  if word is palindrome.
#define INPUT_SIZE 20       //  Main input size

int abs (int x) 
{ 
    if (x < 0)
    {
        return -x; 
    }
    return x; 
}

int palindrome (char x[WORD_SIZE]) // * Check palindrome
{ 
    int len = strlen (x), pass = 1; 
    for (int i = 0; i < len; i++)
    {
        if (x[i] != x[len - i - 1])
        {
            pass = 0; 
        } 
    }
    return pass; 
}

int chooseWords 
/**
 * * Choosing words. 
 * * It take all of the words into an array. 
 * * After that took $WORD_COUNT of them randomly.
 * @return Boolean
 */
(
    char word_list[WORD_COUNT][WORD_SIZE] // * Empyt array.
)
{
    FILE *fp = fopen("wordlist.txt","rt");
    int choosed_words[WORD_COUNT];
    char chr[WORD_SIZE];
    
    if (fp)
    {
        for (int i = 0; i < WORD_COUNT; i++)
        {
            choosed_words[i] = rand() % TOTAL_WORDS;
            for (int j = 0; j < i; j++)
            {
                if (choosed_words[j] == choosed_words[i])
                {
                    i--; 
                }
            }
        }
        int k = 0;
        for (int i = 0; i < TOTAL_WORDS; i++)
        {
            if (fscanf(fp,"%s",chr) != 1) {return 1;}
            for (int j = 0; j < WORD_COUNT; j++)
            {
                if (i == choosed_words[j])
                {
                    strcpy(word_list[k],chr);
                    k++;
                }
            }
        }
        fclose(fp);
        return 0;
    }
    return 1;
}

int placeToMatrix 
(
    int starting_points[WORD_COUNT][PALINDROME_PASS],
        // * It contains starting points and rotation.
        // * If $PALINDROME_PASS is true, it also contains ending points.
    char matrix[ROW][COL],
        // * Main matrix
    char word_list[WORD_COUNT][WORD_SIZE]
        // * Array that we filled in $chooseWords
)
{
    int limit = 0;
    for (int i = 0; i < WORD_COUNT; i++)
    {
        limit = 0;
        int r = starting_points[i][2] = rand() % 8;
        r = r - r % DIAGONAL_PASS;
        // Unit vector
        int y_unit = !!(r % 4) * (1 - r / 4 * 2);
        int x_unit = !!((r + 2) % 8 % 4) * (1 - (r + 2) % 8 / 4 * 2); 
        if (!REVERSE_PASS)
        {
            y_unit = abs(y_unit);
            x_unit = abs(x_unit);
        }
        int len = strlen(word_list[i]) - 1;
        int pass = 1;
        while (pass && limit < 400)
        {
            starting_points[i][0] = rand() % ROW;
            starting_points[i][1] = rand() % COL;
            if (PALINDROME_PASS == 5 && palindrome(word_list[i]))
            {
                starting_points[i][3] = starting_points[i][0] + len * y_unit;
                starting_points[i][4] = starting_points[i][1] + len * x_unit;
            }
            else
            {
                starting_points[i][3] = -1;
                starting_points[i][4] = -1;
            }
            if 
            ( // ! Check end points are also inside the matrix
                starting_points[i][0] + len * y_unit >= ROW || 
                starting_points[i][0] + len * y_unit < 0 || 
                starting_points[i][1] + len * x_unit >= COL || 
                starting_points[i][1] + len * x_unit < 0
            )
            {
                continue;
            }
            pass = 0;
            for (int k = 0; k < len; k++) // ! Check if there is "enough" space
            {
                for (int d = -CONTROL_CHECK; d <= CONTROL_CHECK; d++)
                {
                    for (int u = -CONTROL_CHECK; u <= CONTROL_CHECK; u++)
                    {
                        if (starting_points[i][0] + k * y_unit + u >= ROW) {continue;}
                        if (starting_points[i][1] + k * x_unit + d >= COL) {continue;}
                        if (starting_points[i][0] + k * y_unit + u < 0) {continue;}
                        if (starting_points[i][1] + k * x_unit + d < 0) {continue;}
                        if 
                        (
                            matrix
                                [starting_points[i][0] + k * y_unit + u]
                                [starting_points[i][1] + k * x_unit + d]
                        )
                        {
                            pass = 1;
                        }
                    }
                }
            }
            limit++;
        }
        if (pass)
        { 
            // ! That means program tried too many times to put to the matrix. 
            // ! I accepted it as failure and it starts from the beginning.
            i = 0;
            for (int y = 0; y < ROW; y++)
            {
                for (int x = 0; x < COL; x++) 
                {
                    matrix[y][x] = 0;
                }
            }
            continue;
        }
        for (int k = 0; k <= len; k++)
        {
            matrix
                [starting_points[i][0] + k * y_unit]
                [starting_points[i][1] + k * x_unit] = word_list[i][k];
        }
    }
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (!matrix[i][j])
            {
                matrix[i][j] = rand() % 26 + 'A';
                // ! Capital A is important for hints. 
            }
        }
    }
    return 0;
}

void printMatrix 
(
    char matrix[ROW][COL], 
    int hint
        // * If this value is true, words will be highlighted.
)
{
    printf("\n\n");
    if (PRINT_SPACE < 3) // ! Remove ruler if there is not enough space.
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if (hint && matrix[i][j] >= 'a')    {printf("\e[32m%-*c\e[0m",PRINT_SPACE,matrix[i][j]);}
                else if (matrix[i][j] >= 'a')       {printf("%-*c",PRINT_SPACE,matrix[i][j]);}
                else if (matrix[i][j] >= 'A')       {printf("%-*c",PRINT_SPACE,matrix[i][j] - 'A' + 'a');}
                else if (matrix[i][j] == 1)         {printf("\e[31m%-*c\e[0m",PRINT_SPACE,'X');}
                else                                {printf("  ");}
            }
            printf("\n");
        }
    }
    else
    {
        for (int i = -1; i < ROW; i++)
        {
            for (int j = -1; j < COL; j++)
            {
                if (j == -1 || i == -1)
                {
                    if (j == -1 && i == -1)     {printf("%*c",PRINT_SPACE + 1,' ');}
                    else if (i == -1)           {printf("%-*d",PRINT_SPACE,j);}
                    else                        {printf("%-*d",PRINT_SPACE + 1,i);}
                }
                else
                {
                    if (hint && matrix[i][j] >= 'a')    {printf("\e[32m%-*c\e[0m",PRINT_SPACE,matrix[i][j]);}
                    else if (matrix[i][j] >= 'a')       {printf("%-*c",PRINT_SPACE,matrix[i][j]);}
                    else if (matrix[i][j] >= 'A')       {printf("%-*c",PRINT_SPACE,matrix[i][j] - 'A' + 'a');}
                    else if (matrix[i][j] == 1)         {printf("\e[31m%-*c\e[0m",PRINT_SPACE,'X');}
                    else                                {printf("%*c",PRINT_SPACE,' ');}
                }
            }
            printf("\n");
        }
    }
    printf("\n\n");
}

int deleteWord
/**
 * * Replace words with X.
 * @return Boolean
 */
(
    int coords[3],
        // * Starting points and rotation. 
        // * It doesnt include ending points.
    char matrix[ROW][COL], 
    int len
)
{
    int r = coords[2];
    int y_unit = !!(r % 4) * (1 - r / 4 * 2);
    int x_unit = !!((r + 2) % 8 % 4) * (1 - (r + 2) % 8 / 4 * 2); 
    for (int k = 0; k < len; k++)
    {
        matrix[coords[0] + k * y_unit][coords[1] + k * x_unit] = 1;
    }
    return 1;
}

int checkMatrix
/**
 * * Check if input values are true.
 * @return Boolean
 */
(
    int y,
    int x,
    char word[WORD_SIZE],
    char matrix[ROW][COL],
    int starting_points[WORD_COUNT][PALINDROME_PASS],
    char word_list[WORD_COUNT][WORD_SIZE]
)
{
    if (matrix[y][x] >= 'a')
    {
        for (int k = 0; k < WORD_COUNT; k++)
        {
            if (y == starting_points[k][0] && x == starting_points[k][1] && !strcmp(word,word_list[k]))
                {return deleteWord(starting_points[k], matrix, strlen(word_list[k]));}
            else if (PALINDROME_PASS == 5 && y == starting_points[k][3] && x == starting_points[k][4] && !strcmp(word,word_list[k]))
                {return deleteWord(starting_points[k], matrix, strlen(word_list[k])) + 1;}
        }
    }
    return 0;
}

int main ()
{
    int restart = 1;
    while (restart)
    {
        srand(time(0));

        int health = HEALTH;
        int points = 0;
        char word_list[WORD_COUNT][WORD_SIZE];

        if (chooseWords(word_list)) {return 1;}

        int starting_points[WORD_COUNT][PALINDROME_PASS]; // y,x
        char matrix[ROW][COL] = {0};

        placeToMatrix(starting_points,matrix,word_list);

        int game = 1;
        int hint = 0;
        int help = 0;
        int godmode = 0;

        while (game)
        {
            restart = 1;
            int x,y;
            char input[WORD_SIZE];
            char main_input[INPUT_SIZE] = {};

            printMatrix(matrix,hint);
            char temp;
            int temp_index = 0;

            while ((temp = getchar()) != '\n' && temp_index < INPUT_SIZE) 
                {main_input[temp_index++] = temp;}
            while (temp != '\n' && temp != 0) {temp = getchar();} // Flush

            if (sscanf(main_input,"%d %d %s",&y,&x,input) == 3)
            {
                int result = checkMatrix(y,x,input,matrix,starting_points,word_list);
                if (result == 1)
                {
                    points += POINTS;
                    printf("Great you have gained %d points.\nTotal point is %d\n",POINTS,points);
                    for (int i = 0; i < points; i++) {printf("\e[33m* \e[0m");}
                    printf("\n");
                }
                else if (result == 2)
                {
                    points += POINTS;
                    printf("Well that word is palindrome and you have entered its end points.\nYou have gained %d points.\nTotal point is %d\n",POINTS,points); 
                    for (int i = 0; i < points; i++) {printf("\e[33m* \e[0m");}
                    printf("\n");
                }
                else
                {
                    if (!godmode)
                    {
                        if (health > 1)
                        {
                            health--;
                            printf("You have failed. You lose 1 heart.\nRemain heart is %d\n",health);
                            for (int i = 0; i < health; i++) {printf("\e[31m+ \e[0m");}
                            printf("\n");
                        }
                        else
                        {
                            health--;
                            printf("You have failed. You lose 1 heart.\nYou have lost.\n");
                            game = 0;
                        }
                    }
                    else
                    {
                        printf("You have failed. But godmode is active.\n");
                    }
                    
                }
            }
            else if (sscanf(main_input,"%s",input))
            {
                if (!strcmp(input,":q") || !strcmp(input,":quit")) {game = 0;}
                else if (!strcmp(input,":y") || !strcmp(input,":hint")) {hint = !hint;}
                else if (!strcmp(input,":h") || !strcmp(input,":help")) {help = !help;}
                else if (!strcmp(input,":+")) 
                {
                    health++;
                    printf("Remain heart is %d\n",health);
                    for (int i = 0; i < health; i++)
                        {printf("\e[31m+ \e[0m");} 
                    printf("\n");
                }
                else if (!strcmp(input,":g")) {godmode = !godmode;}
                else if (!strcmp(input,":r") || !strcmp(input,":restart")) {break;}
                else {printf("Unknown command. Enter :h or :help.\n");}
            }
            if (points == POINTS * WORD_COUNT) 
            {
                game = 0;
                printMatrix(matrix,hint);
            }    
            if (help)
            {
                printf("\nCommands : \n:h, :help = %d\n:q, :quit\n:y, :hint Open hints = %d\n:r, :restart Restart game\n:+ Add health = %d\n:g Open godmode = %d",help--,hint,health,godmode);
            }
            restart = 0;
        }
        printf("Your total point is : %d.\n",points);
    }
    printf("Goodbye\n");
    return 0;
}

/**
 *  * Current Problems
 *      ! If $CONTROL_CHECK bigger than 1
 *          ? Sometimes it doesnt put the last word.
 */