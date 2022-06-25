#include <stdio.h>
#include <stdlib.h>

#define STACK_BLOCK_SIZE 10

typedef struct {int * array; char rod_name; int currentsize; int maxsize;} stack;

int disks_number = 0;
int moves = 0;

stack * init_return();
int init(stack * s);
int pop(stack * s);
int push(stack * s, int d);

int change(stack * rod_s, stack * rod_d);
int solve(int disks, stack * rod_s, stack * rod_a, stack * rod_d);

int print_s(stack * s)
{
    if (s)
    {
        printf("N : %c, C : %d, M : %d\n",s->rod_name,s->currentsize,s->maxsize);
        if (s->currentsize)
        {
            printf("\tA : ");
        }
        int i;
        for (i = 0; i < s->currentsize; i++)
        {
            printf("%d, ",s->array[i]);
        }
        if (s->currentsize)
        {
            printf("\b\b \n");
        }
        printf("\n\n");
    }
    else
    {
        printf("It is empyt\n");
    }
}
int print_m(stack * s, stack * d, int k)
{
    moves++;
    printf("\e[500D");
    printf("Number %d from %c to %c\e[0K\n",k,s->rod_name, d->rod_name);
}
int print_i(stack * s, stack * a, stack * d, int cha);

int main()
{
    stack * rod_s = init_return();
    rod_s->rod_name = 'S';
    stack * rod_a = init_return();
    rod_a->rod_name = 'A';
    stack * rod_d = init_return();
    rod_d->rod_name = 'D';

    printf("Disk numbers : ");
    disks_number = 4;
    scanf("%d",&disks_number);
    getchar();
    solve(disks_number, rod_s, rod_a, rod_d);

    return 0;
}

stack * init_return()
{
    stack * temp = (stack *) malloc(sizeof(stack));
    temp->array = 0;
    temp->currentsize = 0;
    temp->maxsize = 0;
    return temp;
}

int init(stack * s)
{
    int * temp = calloc(s->maxsize + STACK_BLOCK_SIZE, sizeof(int));
    
    if (temp)
    {
        int i;
        for (i = 0; i < s->currentsize; i++)
        {
            temp[i] = s->array[i];
        }
        s->maxsize += STACK_BLOCK_SIZE;
        s->array = temp;
        return 1;
    }
    else
    {
        return 0;
    }
}

int pop(stack * s)
{
    if (s->currentsize <= 0)
    {
        return 0;
    }
    int tempp = s->array[s->currentsize - 1];
    s->currentsize--;
    if (s->maxsize - s->currentsize >= 10)
    {
        int * temp = calloc(s->maxsize - STACK_BLOCK_SIZE,sizeof(int));
        s->maxsize -= STACK_BLOCK_SIZE;
        int i;
        for (i = 0; i < s->currentsize + 1; i++)
        {
            temp[i] = s->array[i];
        }
        free(s->array);
        s->array = temp;
    }
    return tempp;
}

int push(stack * s, int d)
{
    if (++(s->currentsize) >= s->maxsize)
    {
        int * temp = calloc(s->maxsize + STACK_BLOCK_SIZE, sizeof(int));
        if (temp)
        {
            int i;
            for (i = 0; i < s->currentsize - 1; i++)
            {
                temp[i] = s->array[i];
            }
            s->maxsize += STACK_BLOCK_SIZE;
            free(s->array);
            s->array = temp;
        }
        else
        {
            return 0;
        }
    }
    s->array[s->currentsize - 1] = d;
    return 1;
}

int solve(int disks, stack * rod_s, stack * rod_a, stack * rod_d)
{
    int cha = 0;
    if (!(disks % 2))
    {
        stack * temp = rod_a;
        rod_a = rod_d;
        rod_d = temp;
        cha++;
    }
    int i;
    for (i = disks; i > 0; i--)
    {
        push(rod_s, i);
    }

    int temp = 1;
    for (i = 0; i < disks; i++)
    {
        temp *= 2;
    }
    for (i = 1; i < temp; i++)
    {
        switch (i % 3)
        {
            case 0:
                change(rod_a, rod_d);
                break;
            case 1:
                change(rod_s, rod_d);
                break;
            case 2:
                change(rod_s, rod_a);
                break;
        }
        print_i(rod_s, rod_a, rod_d, cha);
    }
    printf("\e[%dB\e[500D",disks_number + 2);
}

int change(stack * rod_s, stack * rod_d)
{
    int temp1 = pop(rod_s);
    int temp2 = pop(rod_d);
    if (!temp1)
    {
        push(rod_s, temp2);
        print_m(rod_d, rod_s, temp2);
    }
    else if (!temp2)
    {
        push(rod_d, temp1);
        print_m(rod_s, rod_d, temp1);
    }
    else if (temp1 > temp2)
    {
        push(rod_s, temp1);
        push(rod_s, temp2);
        print_m(rod_d, rod_s, temp2);
    }
    else if (temp1 < temp2)
    {
        push(rod_d, temp2);
        push(rod_d, temp1);
        print_m(rod_s, rod_d, temp1);
    }
}



#define rod_char '|'
#define first_char '<'
#define end_char '>'
#define floor_char '-'
#define connect_char '|'
#define empty ' '

void print_e(int count)
{
    if (count) 
    {
        printf("%c", empty);
        print_e(count - 1);
    }
}

int print_i(stack * s, stack * a, stack * d, int cha)
{
    printf("\e[500D");
    int rod;
    for (rod = 0; rod < 3; rod++)
    {
        print_e(disks_number + 1);
        printf("%c", rod_char);
        print_e(disks_number + 1);
    }
    printf("\n");

    stack * towers[3];
    towers[0] = s;
    if (!cha)
    {
        towers[1] = a;
        towers[2] = d;
    }
    else
    {
        towers[1] = d;
        towers[2] = a;
    }
    int i;
    for (i = disks_number - 1; i >= 0; i--)
    {
        int j;
        for (j = 0; j < 3; j++)
        {
            if (towers[j]->currentsize >= i + 1)
            {
                int temp = towers[j]->array[i];
                print_e(3 + disks_number - 2 - temp);
                printf("\e[%dm%c",
                    30 + (temp - 1) % 6 + 1,
                    first_char);
                int x;
                for (x = 0; x < 2 * temp - 1; x++)
                {
                    printf("%c",(x == temp - 1) ? connect_char : floor_char);
                }
                printf("%c\e[0m",end_char);
                print_e(3 - temp + disks_number - 2);
            }
            else
            {
                print_e(3 + disks_number - 2);
                printf("%c",rod_char);
                print_e(3 + disks_number - 2);
            }
        }
        printf("\e[0m\n");
    }
    for (rod = 0; rod < 3; rod++)
    {
        int x;
        for (x = 0; x < 2 * disks_number + 3; x++)
        {
            printf("%c", (x == disks_number + 1) ? connect_char : floor_char);
        }
    }
    printf("\nPress Enter");
    getchar();
    printf("\e[%dA",disks_number + 3);
}