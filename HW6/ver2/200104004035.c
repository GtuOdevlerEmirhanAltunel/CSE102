/**
 * @file 200104004035.c
 * @author Emirhan Altunel
 * @brief 
 * @version 0.3
 * @date 2022-04-18
 * 
 * * Recommended to using "Better Comments extenion for VS-Code" for better reading.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/**
 * @param ROWS Number of rows. Changeable.
 * 
 * @param COLS Number of columns. Changeable.
 * 
 * @param PLAYER_COUNT Number of players. Changable between [1,6]. Select appropriate values for ROWS and COLS values.
 * 
 * @param PENALTY_COUNT Number of penalties. Changable but if you increase it, you have to write new locations.
 * 
 * @param PENALTY Amount of going back of players who got penalty.
 * 
 * ! Warning if you change ROWS and COLS, penalties will make some trouble. ;(
 */
#define ROWS 15
#define COLS 30
#define PLAYER_COUNT 2
#define PENALTY_COUNT 9
#define PENALTY 2

/**
 * * Global Variables 
 * 
 * @param MapElements It makes easy to change map items.
 * 
 * @param OldPlayersLocation It helps to delete players from array.
 * 
 * @param PlayersLocation It keeps their location.
 * 
 * @param PlayerMove It keeps how far they are from starting point.
 * 
 * @param Dices It keeps dice values but I think I could do that without it.
 * 
 * @param PlayerOrder It determines which player should start.
 * 
 * @param PenaltyLocations It keeps penalty locations.
 */
enum MapElements
{
    space = ' ',
    h_lines = '-',
    v_lines = '|',
    corner1 = '+',
    corner2 = '.',
    corner3 = 'o',
    corner4 = '*',
    penalty = 'x',
    finish_l = '_'
};
enum MapElements Map[ROWS][COLS] = {0};

int OldPlayersLocation[PLAYER_COUNT][2] = {0};
int PlayersLocation[PLAYER_COUNT][2] = {0}; // ! x,y
int PlayerMove[PLAYER_COUNT] = {0};

int Dices[PLAYER_COUNT] = {0};
int PlayerOrder[PLAYER_COUNT] = {0};
int PenaltyLocation[PENALTY_COUNT][2] = { // ! y,x
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

/**
 * * calculate_player_location
 * 
 * TODO Calculating players location from how far they are from starting point.
 * 
 * @param movement When players pass the starting point, everything would be mess if this parameter was not there.
 */
void calculate_player_location()
{
    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        int movement = PlayerMove[player] % (2 * ROWS + 2 * COLS - 16 * player - 12);
        
        if (movement <= COLS - 4 * player - 3) 
        {
            PlayersLocation[player][0] = movement + 2 * player + 1;
            PlayersLocation[player][1] = 2 * player + 1;
        }
        else if (movement <= COLS + ROWS - 8 * player - 6)
        {
            PlayersLocation[player][0] = COLS - 2 * player - 2;
            PlayersLocation[player][1] = movement - COLS + 4 * player + 3 + 2 * player + 1;
        }
        else if (movement <= 2 * COLS + ROWS - 12 * player - 9)
        {
            PlayersLocation[player][0] = 2 * COLS + ROWS - movement - 10 * player - 8;
            PlayersLocation[player][1] = ROWS - 2 * player - 2;
        }
        else if (movement <= 2 * COLS + 2 * ROWS - 16 * player - 12)
        {
            PlayersLocation[player][0] = 2 * player + 1;
            PlayersLocation[player][1] = 2 * COLS + 2 * ROWS - movement - 14 * player - 11;
        }
    }
}

/**
 * * fill_map
 * 
 * TODO Updating array
 */
void fill_map()
{   
    calculate_player_location();
    for (int player = 0; player < PLAYER_COUNT; player++)
    {
        Map[OldPlayersLocation[player][1]][OldPlayersLocation[player][0]] = 0;
        OldPlayersLocation[player][1] = PlayersLocation[player][1];
        OldPlayersLocation[player][0] = PlayersLocation[player][0];

        Map[PlayersLocation[player][1]][PlayersLocation[player][0]] = player + 49;
    }
    for (int j = 0; j < PENALTY_COUNT; j++) Map[PenaltyLocation[j][0]][PenaltyLocation[j][1]] = penalty;
    // ! It is important because if some player got penalty it would delete penalty point without that.
}

/**
 * * print_map
 * 
 * TODO Print it to screen + it makes it cool.
 */
void print_map()
{   
    fill_map();
    printf("\n\n");

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            char element = Map[row][col];

            if (element >= '1' && element <= '9') printf("\e[0;%dm%c\e[0m",31+element-49,element);

            else if (element == 0) printf(" ");

            else if (element == h_lines) printf("─");
            else if (element == v_lines) printf("│");

            else if (element == corner1) printf("┌");
            else if (element == corner2) printf("└");
            else if (element == corner3) printf("┐");
            else if (element == corner4) printf("┘");

            else if (element == penalty) printf("\e[31mX\e[0m");

            else if (element == finish_l) printf("\e[0;%dm_\e[0m",row / 2 + 30);

            else printf("%c",element);
        }
        printf("\n");
    }
    printf("\n");
}

int dice()
{
    return rand() % 6 + 1;
}

/**
 * * start_game
 * 
 * TODO First turn of game + It determines players order.
 */
void start_game()
{
    for (int player = 0; player < PLAYER_COUNT; player++) // ? Players
    {
        OldPlayersLocation[player][0] = 2 * player + 1;
        OldPlayersLocation[player][1] = 2 * player + 1;
        PlayersLocation[player][0] = 2 * player + 1;
        PlayersLocation[player][1] = 2 * player + 1;
        Map[2 * player + 2][2 * player + 1] = finish_l;
    }

    for (int border = 1; border <= PLAYER_COUNT + 1; border++) // ? Race Borders
    {
        for (int hori = 2 * border - 1; hori < COLS - 2 * border + 1; hori++)
        {
            Map[2 * border - 2][hori] = h_lines;
            Map[ROWS - 2 * border + 1][hori] = h_lines;
        }
        for (int ver = 2 * border - 1; ver < ROWS - 2 * border + 1; ver++)
        {
            Map[ver][2 * border - 2] = v_lines;
            Map[ver][COLS - 2 * border + 1] = v_lines;
        }
        Map[2 * border - 2][2 * border - 2] = corner1;
        Map[ROWS - 2 * border + 1][2 * border - 2] = corner2;
        Map[2 * border - 2][COLS - 2 * border + 1] = corner3;
        Map[ROWS - 2 * border + 1][COLS - 2 * border + 1] = corner4;
    }

    print_map();
    
    int start_game_flag = 1;

    while(start_game_flag)
    {
        if (start_game_flag != 2)
            printf("Decide who starts first.\n");
        
        start_game_flag = 0;

        for (int player = 0; player < PLAYER_COUNT; player++)
        {
            printf("\n\e[0;%dmPlayer %d : \e[0m", player + 31, player + 1);

            while (getchar() != '\n')
                continue;

            Dices[player] = dice();
            PlayerOrder[player] = player + 1;
            printf("Dice - %d\n", Dices[player]);
        }
        
        for (int player = 0; player < PLAYER_COUNT - 1; player++)
            for (int player1 = player + 1; player1 < PLAYER_COUNT; player1++)
            {
                if (Dices[player] == Dices[player1])
                    start_game_flag = 2;
            }

        if (start_game_flag)
            printf("\nSame dice value please try again.\n\n");
    }    

    // TODO Sorting orders.
    for (int j = 0; j < PLAYER_COUNT; j++)
        for (int i = 0; i < PLAYER_COUNT - 1; i++)
            if (Dices[i] < Dices[i + 1])
            {
                int temp = Dices[i];
                Dices[i] = Dices[i + 1];
                Dices[i + 1] = temp;

                int temp1 = PlayerOrder[i];
                PlayerOrder[i] = PlayerOrder[i + 1];
                PlayerOrder[i + 1] = temp1;
            }
    printf("\nOrder:\n");
    for (int i = 0; i < PLAYER_COUNT; i++)
    {
        printf("%d. Order - \e[0;%dm%d. Player\e[0m\n",i+1,PlayerOrder[i]+30,PlayerOrder[i]);
    }
    
}

int main()
{
    srand(time(NULL));
    start_game();
    int main_flag = 1;
    while(main_flag) 
    {
        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            printf("\n\e[0;%dm%d. Player\e[0m Turn :",PlayerOrder[i]+30,PlayerOrder[i]);

            while (getchar() != '\n')
                continue;
            
            Dices[i] = dice();
            PlayerMove[PlayerOrder[i] - 1] += Dices[i];
            printf("Dice - %d\n", Dices[i]);
            fill_map();
            for (int j = 0; j < PENALTY_COUNT; j++)
            {
                if (PlayersLocation[PlayerOrder[i] - 1][0] == PenaltyLocation[j][1] && PlayersLocation[PlayerOrder[i] - 1][1] == PenaltyLocation[j][0])
                {
                    printf("\e[0;%dm%d. Player\e[0m got \e[31mpenalty\e[0m.\n",PlayerOrder[i]+30,PlayerOrder[i]);
                    PlayerMove[PlayerOrder[i] - 1] -= PENALTY;
                }
            }

            if (PlayerMove[PlayerOrder[i] - 1] >= 2 * COLS + 2 * ROWS - 16 * PlayerOrder[i] + 3)
            {
                print_map();
                main_flag = 0;
                printf("Winner is \e[0;%dm%d. Player\e[0m.\n",PlayerOrder[i]+30,PlayerOrder[i]);
                break;
            }
        }
        if (!main_flag) break;

        print_map();
    }

    return 0;
}