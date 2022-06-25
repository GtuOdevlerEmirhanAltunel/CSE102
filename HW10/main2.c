#include <stdio.h>
#include <stdlib.h>

#define STACK_BLOCK_SIZE 10;

typedef struct
{
    int * array;
    int currentsize;
    int maxsize;
} stack;


#define rod_count 3

#define rod_char '|'
#define first_char '<'
#define end_char '>'
#define floor_char '-'
#define connect_char '|'
#define empty ' '

int moves = 0;

void print_towers(int * towers, int floor_count);
int * tower_starter(int floor_count, int empyt);
void move_it(int * towers, int rod, int to_rod, int floor_count);
void solve(int * towers, int floor_count);
int pop(stack * s);
int push(stack * s, int d);
void print_e(int count)
{
    if (count) 
    {
        printf("%c", empty);
        print_e(count - 1);
    }
}

int main(int argc, char const *argv[])
{
    stack towers[3];
    for (int i = 0; i < 3; i++)
    {
        towers[i].maxsize = STACK_BLOCK_SIZE;
        towers[i].currentsize = 0;
        towers[i].array = 0;
    }
    
    
    /*
    int floor_count = 3;
    scanf("%d",&floor_count);
    getchar();
    int * towers = tower_starter(floor_count, 1);
    print_towers(towers, floor_count);

    for (int i = 0; i < floor_count; i++)
    {
        getchar();
        move_it(towers, 0, 1, floor_count);
        print_towers(towers, floor_count);
    }

    for (int i = 0; i < floor_count; i++)
    {
        getchar();
        move_it(towers, 1, 2, floor_count);
        print_towers(towers, floor_count);
    }
    printf("\e[%dH",floor_count + 3 + moves);,
    */
    return 0;
}

int pop(stack * s)
{
    if (s->currentsize)
    {
        s->currentsize -= 1;
        int temp = s->array[s->currentsize];
        s->array = realloc(s->array, s->currentsize);
        return temp;
    }
    return -1;
}

int push(stack * s, int d)
{
    if (s->currentsize + 1 == s->maxsize)
    {
        return -1;
    }
    else
    {
        s->currentsize += 1;
        int * temp = (s->array) ? (int *) realloc(s->array, sizeof(int) * s->currentsize) : 0;
        if (temp)
        {
            s->array = temp;
            temp[s->currentsize - 1] = d;
            return 1;
        }
        else
        {
            temp = (int *) calloc(s->currentsize, sizeof(int));
            for (int i = 0; i < s->currentsize - 1; i++)
            {
                temp[i] = s->array[i];
            }
            temp[s->currentsize - 1] = d;
            if (s->array) {free(s->array);}
            s->array = temp;
            return 2;
        }
    }
}




void print_towers(int * towers, int floor_count)
{
    int biggest = floor_count;
    printf("\e[0H");
    for (int rod = 0; rod < rod_count; rod++)
    {
        print_e(biggest + 1);
        printf("%c", rod_char);
        print_e(biggest + 1);
    }
    printf("\n");

    for (int floor = 0; floor < floor_count; floor++)
    {
        for (int rod = 0; rod < rod_count; rod++)
        {
            print_e(rod_count - towers[floor * rod_count + rod] + floor_count - 2);
            printf("\e[%dm%c",
                    (towers[floor * rod_count + rod]) ? 30 + (towers[floor * rod_count + rod] - 1) % 6 + 1: 0,
                    (towers[floor * rod_count + rod]) ? first_char : rod_char);

            for (int x = 0; x < 2 * towers[floor * rod_count + rod] - 1; x++)
            {
                printf("%c",(x == towers[floor * rod_count + rod] - 1) ? connect_char : floor_char);
            }
            
            printf("%c\e[0m",(towers[floor * rod_count + rod]) ? end_char : 0);
            print_e(rod_count - towers[floor * rod_count + rod] + floor_count - 2);
        }
        printf("\e[0m\n");
    }
    for (int rod = 0; rod < rod_count; rod++)
    {
        for (int x = 0; x < 2 * biggest + 3; x++)
        {
            printf("%c", (x == biggest + 1) ? connect_char : floor_char);
        }
    }
    printf("\e[%dHPress Enter ",floor_count + 3 + moves);
}

int * tower_starter(int floor_count, int empyt)
{
    int * tower = (int *) calloc(rod_count * floor_count,sizeof(int));
    if (empyt)
    {
        for (int i = 0; i < floor_count; i++)
        {
            tower[i * rod_count + 0] = i + 1;
        }
    }
    return tower;
}

void move_it(int * towers, int rod, int to_rod, int floor_count)
{
    static int move = 0;
    int temp_floor = -1;
    for (int i = 0; i < floor_count; i++)
    {
        if (towers[i * rod_count + rod])
        {
            temp_floor = i;
            break;
        }
    }
    if (temp_floor == -1)
    {
        return;
    }
    move++;
    moves = move;

    int temp = towers[temp_floor * rod_count + rod];
    printf("\e[%dHMove the disk %d from %d to %d.",floor_count + 2 + move,temp,rod,to_rod);

    towers[temp_floor * rod_count + rod] = 0;
    for (int i = floor_count - 1; i >= 0; i--)
    {
        if (towers[i * rod_count + to_rod] == 0)
        {
            temp_floor = i;
            break;
        }
    }
    towers[temp_floor * rod_count + to_rod] = temp;
}

void solve(int * towers, int floor_count)
{
    int from = 0;
    int aux = 1;
    int to = 2;
    for (int i = 1; i < floor_count; i++)
    {
        
    }
    for (int i = 1; i < floor_count; i++)
    {
        
    }
    
}




