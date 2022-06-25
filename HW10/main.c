/**
 * ! Changes
 *      Pop functions changed. After that it doesnt change size when pop item from stack that have only 1 element.
 *          Line 161: "&& s->currentsize >= 10"
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_BLOCK_SIZE 10

typedef struct 
{
    int * array;
    int currentsize; /* Number of elements */
    int maxsize;
    char stack_name; /** I added not to send @param name_char additionally to functions */
} stack;

stack * init_return ();
int init (stack * s);

int push (stack * s, int d);
int pop (stack * s);

void change (stack * s1, stack * s2);
void solve (stack * rod_s, stack * rod_a, stack * rod_d, int disks);

int main()
{
    stack * s;
    stack * a;
    stack * d;
    int disks;

    s = init_return();
    a = init_return();
    d = init_return();

    s->stack_name = '1';
    a->stack_name = '2';
    d->stack_name = '3';

    printf("Enter Tower size : ");
    while (!scanf("%d", &disks))
    {
        printf("Invalid enter again : ");
        while (getchar() != '\n');
    }
    solve(s, a, d, disks);

    return 0;
}

/**
 * @brief Create an empty array. 
 * 
 *      It creates 0 sized array.
 *      When the push function called, it grows @param STACK_BLOCK_SIZE
 * 
 * @return stack
 */
stack * init_return ()
{
    stack * stacks;

    stacks = (stack *) malloc (sizeof (stack));

    while (!init(stacks));
    
    return stacks;
}

/**
 * @brief It is for putting 0s in stack. Nothing more.
 * 
 * @param s stack itself
 * @return bool 
 */
int init (stack * s)
{
    s->currentsize = 0;
    s->maxsize = STACK_BLOCK_SIZE;
    s->stack_name = 0;
    s->array = malloc (STACK_BLOCK_SIZE * sizeof (int));
    if (s->array)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief It pushes new element to stack. When stack is full, it makes stack grows @param STACK_BLOCK_SIZE.
 * 
 * @param s stack itself
 * @param d new value
 * @return 1, nothing more.
 */
int push (stack * s, int d)
{
    int * temp_array;
    int i;

    temp_array = 0;

    if (s->currentsize >= s->maxsize)
    {
        if (s->array)
        {
            temp_array = realloc (s->array, (s->maxsize + STACK_BLOCK_SIZE) * sizeof (int));
        }

        if (temp_array)
        {
            s->maxsize = s->maxsize + STACK_BLOCK_SIZE;
            s->array = temp_array;
        }
        else
        {
            while (!temp_array)
            {
                temp_array = malloc ((s->maxsize + STACK_BLOCK_SIZE) * sizeof(int));
            }
            for (i = 0; i < s->currentsize; i++)
            {
                temp_array[i] = s->array[i];
            }
            free(s->array);
            s->array = temp_array;
        }
    }

    s->array[s->currentsize] = d;
    s->currentsize = s->currentsize + 1;
    return 1;
}

/**
 * @brief Return last element of stack, if there is more space than @param STACK_BLOCK_SIZE it makes stack shrinks that much.
 * 
 * @param s stack
 * @return int last value
 */
int pop (stack * s)
{
    int * temp_array;
    int i;
    int temp_value;

    if (s->currentsize == 0)
    {
        return 0;
    }

    temp_value = s->array[s->currentsize - 1];

    if (s->maxsize >= s->currentsize + 9 && s->currentsize >= 10)
    {
        temp_array = realloc (s->array, (s->maxsize - STACK_BLOCK_SIZE) * sizeof (int));
        if (temp_array)
        {
            s->maxsize = s->maxsize - STACK_BLOCK_SIZE;
            s->array = temp_array;
        }
        else
        {
            while (!temp_array)
            {
                temp_array = malloc ((s->maxsize - STACK_BLOCK_SIZE) * sizeof(int));
            }
            for (i = 0; i < s->currentsize - 1; i++)
            {
                temp_array[i] = s->array[i];
            }
            s->array = temp_array;
        }
    }
    s->currentsize -= 1;
    return temp_value;
}

/**
 * @brief It only prints
 * 
 * @param s stack from
 * @param d stack to
 * @param k value
 */
void print_m(stack * s, stack * d, int k)
{
    printf("Move the disk %d from '%c' to '%c'\n",k,s->stack_name, d->stack_name);
}

/**
 * @brief Solving funciton
 * 
 * @param rod_s 
 * @param rod_a 
 * @param rod_d 
 * @param disks number of disks 
 */
void solve(stack * rod_s, stack * rod_a, stack * rod_d, int disks)
{
    int cha = 0;
    
    int i;
    int temp = 1;
    
    if (!(disks % 2)) /* If number of disks is even it changes aux and dest */
    {
        stack * temp = rod_a;
        rod_a = rod_d;
        rod_d = temp;
        cha++;
    }

    for (i = disks; i > 0; i--)
    {
        push(rod_s, i);
    }

    for (i = 0; i < disks; i++) /* Number of moves = 2 ^ (number of disks) - 1 */
    {
        temp *= 2;
    }
    
    /**
     * It goes in order until run out of moves.
     */
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
    }
}

/**
 * @brief It changes last values.
 *      
 *  + Cases :
 *      ! 1-) rod_s could be empty
 *          ? last rod_d value go to rod_s
 *      ! 2-) rod_d could be empyt
 *          ? last rod_s value go to rod_d
 *      ! 3-) last rod_s value > last rod_d value
 *          ? last values go to rod_s
 *      ! 4-) last rod_d value > last rod_s value
 *          ? last values go to rod_d
 * @param rod_s 
 * @param rod_d 
 */
void change(stack * rod_s, stack * rod_d)
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