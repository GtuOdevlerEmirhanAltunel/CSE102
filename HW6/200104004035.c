/**
 * @file 200104004035.c
 * @author Emirhan Altunel
 * @date 2022-04-17
 * 
 * * Recommended to using "Better Comments extenion for VS-Code" for better reading.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @param ROWS Number of rows. Changeable.
 * 
 * @param COLS Number of columns. Changeable.
 * 
 * @param OYUNCU_SAYISI Number of players. Changable between [1,6]. Select appropriate values for ROWS and COLS values.
 * 
 * @param CEZA_SAYISI Number of penalties. Changable but if you increase it, you have to write new locations.
 * 
 * ! Warning if you change ROWS and COLS, penalties will make some trouble. ;(
 */
#define ROWS 15
#define COLS 30
#define OYUNCU_SAYISI 2
#define CEZA_SAYISI 9

// TODO "kose" values are for printing non-ascii corner characters.
enum Map
{
    bosluk = ' ',
    yatay_cizgi = '-',
    duz_cizgi = '|',
    kose1 = '+',
    kose2 = '.',
    kose3 = 'o',
    kose4 = '*',
    ceza = 'x',
    bitis = '_'
};

/** printMap
 * 
 * * Filling the map by using given information and printing it.
 * 
 * @param oyuncular Raw info about players location.  
 * @param cezalar Location of penalty point.
 * 
 * @param playGround Map
 * 
 * @param temp Temporary variable that hold which element should be on that exact location.
 * 
 * @param oyuncu 
 *  It takes values between 1 to number_of_player + borders.
 *  It is for printing.
 * 
 * @param deger 
 *  It takes values between 0 to number_of_player - 1 
 *  It is for getting info about player.
 * 
 */
void printMap(int playGround[ROWS][COLS] ,int oyuncular[OYUNCU_SAYISI], int cezalar[][2])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            char temp = bosluk;

            for (int oyuncu = 1; oyuncu <= 2 * OYUNCU_SAYISI + 1; oyuncu++)
            {
                int deger = oyuncu / 2 - 1;
                int hareket = oyuncular[deger] % (2 * COLS + 2 * ROWS - 8 * oyuncu + 4);
                /** @param hareket It goes to 0 after full turn. */

                if (oyuncu % 2) // TODO Borders
                {
                    if ((i == oyuncu - 1 || i == ROWS - oyuncu) && (j >= oyuncu && j <= COLS - oyuncu - 1))
                        temp = yatay_cizgi;

                    else if ((j == oyuncu - 1 || j == COLS - oyuncu) && (i >= oyuncu && i <= ROWS - oyuncu - 1))
                        temp = duz_cizgi;

                    else if (i == oyuncu - 1 && j == oyuncu - 1)
                        temp = kose1;

                    else if (i == oyuncu - 1 && j == COLS - oyuncu)
                        temp = kose2;

                    else if (i == ROWS - oyuncu && j == oyuncu - 1)
                        temp = kose3;

                    else if (i == ROWS - oyuncu && j == COLS - oyuncu)
                        temp = kose4;
                }
                else // TODO Players
                {
                    if (i == oyuncu && j == oyuncu - 1) // TODO Finish line
                        temp = bitis;

                    // TODO Determining which part the players are in.
                    if (hareket <= COLS - 2 * oyuncu + 1) 
                    {
                        if (i == oyuncu - 1 && j == hareket + oyuncu - 1)
                            temp = deger + 49;
                    }
                    else if (hareket <= COLS + ROWS - 4 * oyuncu + 2)
                    {
                        if (i == hareket - COLS + 3 * oyuncu - 2 && j == COLS - oyuncu)
                            temp = deger + 49;
                    }
                    else if (hareket <= 2 * COLS + ROWS - 6 * oyuncu + 3)
                    {
                        if (i == ROWS - oyuncu && j == 2 * COLS + ROWS - hareket - 5 * oyuncu + 2)
                            temp = deger + 49;
                    }
                    else if (hareket <= 2 * COLS + 2 * ROWS - 8 * oyuncu + 4)
                    {
                        if (i == 2 * COLS + 2 * ROWS - hareket - 7 * oyuncu + 3 && j == oyuncu - 1)
                            temp = deger + 49;
                    }
                }
            }

            // TODO Put penalty points into the Map and check if any player got penalty.
            for (int x = 0; x < CEZA_SAYISI; x++) 
                if (i == cezalar[x][0] && j == cezalar[x][1] && i != 0)
                {
                    if (temp >= 49 && temp <= 57)
                    {
                        oyuncular[temp - 49] -= 2;
                        printf("\e[%dm%d. player\e[0m got penalty.", temp - 18, temp - 48);
                        return printMap(playGround, oyuncular, cezalar); // TODO Restart printMap funtions with changed values.
                    }

                    temp = ceza;
                }

            playGround[i][j] = temp;
        }
    }

    printf("\n\n");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (playGround[i][j] >= 49 && playGround[i][j] <= 49 + OYUNCU_SAYISI)
                printf("\e[%dm%c\e[0m", playGround[i][j] - 18, playGround[i][j]);

            else if (playGround[i][j] == yatay_cizgi)
                printf("─");

            else if (playGround[i][j] == duz_cizgi)
                printf("│");

            else if (playGround[i][j] == kose1)
                printf("┌");

            else if (playGround[i][j] == kose2)
                printf("┐");

            else if (playGround[i][j] == kose3)
                printf("└");

            else if (playGround[i][j] == kose4)
                printf("┘");

            else if (playGround[i][j] == ceza)
                printf("\e[31mX\e[0m");

            else if (playGround[i][j] == bitis)
                printf("\e[32m_\e[0m");

            else
                printf("%c", playGround[i][j]);
        }

        printf("\n");
    }
}

/**
 * dice
 * 
 * @return Random numbers between [1,6]  
 */
int dice()
{
    return rand() % 6 + 1;
}

/**
 * start_game
 * 
 * * Decide order of players
 * 
 * ! It is not fully compatible for more than 6 player because it is not possible that all of them get different dice value. 
 * 
 * @param siralama Order of players.
 * 
 * @param zarlar Dice values of players.
 * 
 */
void start_game(int siralama[OYUNCU_SAYISI])
{
    int devam = 1;

    srand(time(NULL));

    int zarlar[OYUNCU_SAYISI] = {0};

    // TODO Dice...
    while (devam)
    {
        if (devam != 2)
            printf("Decide who starts first. \e[%dm%d\e[0m player mode. %dx%d map.", OYUNCU_SAYISI + 30, OYUNCU_SAYISI,COLS,ROWS);

        devam = 0;

        for (int oyuncu = 0; oyuncu < OYUNCU_SAYISI; oyuncu++)
        {
            printf("\n\e[0;%dmPlayer %d : \e[0m", oyuncu + 31, oyuncu + 1);

            while (getchar() != '\n')
                continue;

            zarlar[oyuncu] = dice();
            siralama[oyuncu] = oyuncu + 1;
            printf("Dice - %d\n", zarlar[oyuncu]);
        }

        for (int oyuncu = 0; oyuncu < OYUNCU_SAYISI - 1; oyuncu++)
            for (int oyuncu1 = oyuncu + 1; oyuncu1 < OYUNCU_SAYISI; oyuncu1++)
            {
                if (zarlar[oyuncu] == zarlar[oyuncu1])
                    devam = 2;
            }

        if (devam)
            printf("\nSame dice value please try again.\n\n");
    }

    // TODO Sorting orders.
    for (int j = 0; j < OYUNCU_SAYISI; j++)
        for (int i = 0; i < OYUNCU_SAYISI - 1; i++)
            if (zarlar[i] < zarlar[i + 1])
            {
                int temp = zarlar[i];
                zarlar[i] = zarlar[i + 1];
                zarlar[i + 1] = temp;

                int temp1 = siralama[i];
                siralama[i] = siralama[i + 1];
                siralama[i + 1] = temp1;
            }

    printf("\nOrder is : \n");

    for (int i = 0; i < OYUNCU_SAYISI; i++)
        printf("%d. Order - \e[%dm%d. Player\e[0m\n", i + 1, siralama[i] + 30, siralama[i]);

    printf("\n\n");
}

/**
 * main
 * 
 * @param oyuncular Holds how many steps each player has taken.
 * 
 * @param cezalar Holds exact locations of penalty points.
 * 
 * @param winner Holds who won.
 */
int main()
{

    srand(time(NULL));

    int oyuncular[OYUNCU_SAYISI] = {0};
    int playGround[ROWS][COLS] = {0};

    int cezalar[CEZA_SAYISI][2] =
    {
        {1, 14},
        {7, 28},
        {13, 14},
        {3, 10},
        {3, 18},
        {5, 26},
        {10, 26},
        {11, 10},
        {11, 18}
    };

    printMap(playGround, oyuncular, cezalar);

    int siralama[OYUNCU_SAYISI];
    int zarlar[OYUNCU_SAYISI];

    start_game(siralama);

    int devam = 1;
    int winner = -1;

    while (devam)
    {

        // TODO Dice for moving.
        for (int i = 0; i < OYUNCU_SAYISI; i++)
        {
            printf("\e[%dm%d. player turn.\e[0m", siralama[i] + 30, siralama[i]);

            while (getchar() != '\n') // ? Normally i made it for getch() funtion but that funtion has some problems.
                continue;

            zarlar[siralama[i] - 1] = dice();

            printf("Dice - %d\n", zarlar[siralama[i] - 1]);

            oyuncular[siralama[i] - 1] += zarlar[siralama[i] - 1];
        }

        // TODO Check if any player passes finish line.
        for (int i = 0; i < OYUNCU_SAYISI; i++)
        {
            if (oyuncular[i] >= 2 * COLS + 2 * ROWS - 16 * i - 13)
            {
                devam = 0;
                winner = i;
            }
        }

        // TODO Print the map.
        printMap(playGround, oyuncular, cezalar);
    }
    
    printf("Winner is \e[%dm%d. Player\e[0m\n", winner + 31, winner + 1);

    return 0;
}
