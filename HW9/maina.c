/**
 * @file main.c
 * @author Emirhan Altunel
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ! Defining
#define string_length 50
#define max_user 50
#define long_max 9223372036854775807
// ! Struct & Unions

typedef struct
{
    unsigned long int phone; // Normally I wrote phone at 2. line but in this way it saves 8 bytes.
    char name[string_length];
    char address[string_length];
} Person;

typedef struct
{
    float amount;
    int period;
    float interest_rate;
} Loan;

typedef struct
{
    Person Customer;
    Loan Loans[3];
} BankAccount;

// ! Funtions *******************************

long int menu(char menu_opt[][string_length], int option_count);
long int getInt(long int min, long int max);
float getFloat(float min, float max);
char getStr(char input[string_length], char endpoint, int length);
void error(char * error_message);
void print_line();
int getData(BankAccount * Customer, int * Customer_count);
int getReport(BankAccount * Customers, int customer_count);
float calculateLoan(float amount, int period, float interestRate);
int newLoan (BankAccount * Customers, int customer_count);
int addCustomer (BankAccount * Customers, int * customer_count);
int listCustomers(BankAccount * Customers, int customer_count);

/********************************************
 * @brief 
 * 
 * @return int 
 */
int main()
{
    char starting_menu[][string_length] = {
        "Select Option :",
        "List All Customers",
        "Add New Customer",
        "New Loan Application",
        "Get Report",
        "Exit System"
    };
    
    BankAccount Customers[max_user] = {};
    int customer_count = 0;
    long int choice;

    getData(Customers, &customer_count);

    while ((choice = menu(starting_menu, sizeof(starting_menu) / string_length)) != 5)
    {
        switch (choice)
        {
            case 1:
                listCustomers(Customers, customer_count);
                break;
            case 2:
                addCustomer(Customers, &customer_count);
                break;
            case 3:
                newLoan(Customers, customer_count);
                break;
            case 4:
                getReport(Customers, customer_count);
                break;
            default:
                break;
        }
    }
    printf(" Goodbye\n");
    return 0;
}

long int menu(char menu_opt[][string_length], int option_count)
{
    print_line();
    printf(" %s\n",menu_opt[0]);
    for (int option = 1; option < option_count; option++)
    {
        printf(" %d. %s\n",option, menu_opt[option]);
    }
    print_line();
    return getInt(1, option_count - 1);
}

char getStr(char input[string_length], char endpoint, int length)
{
    int i = 0;
    char temp;
    int end = 1;
    while ((temp = getchar()) != '\n')
    {
        if (i < length && temp != endpoint && end)
        {
            if (temp != '&')
            {
                input[i] = temp;
            }
            else
            {
                input[i] = ' ';
            }
            i++;
        }
        else if (temp == endpoint)
        {
            end = 0;
            input[i] = 0;
        }
    }
    input[49] = 0;
    fflush(stdin);
}

long int getInt(long int min, long int max)
{
    printf(" Input -> ");
    char input[string_length] = {0};
    getStr(input, '\n', string_length);
    long int value;
    for (int i = 0; i < string_length; i++)
    {
        if ((input[i] < '0' || input[i] > '9') && input[i] != 0)
        {
            error("Wrong Input.");
            return getInt(min, max);
        }
    }
    
    if (sscanf(input, "%ld", &value) != 1)
    {
        error("Wrong Input.");
        return getInt(min, max);
    }
    if (value >= long_max)
    {
        error("Too big input.");
        return getInt(min, max);
    }
    if ((value < min || value > max) && max > min)
    {
        error("Input is outside of range.");
        return getInt(min, max);
    }
    if (max == min && value <= 0)
    {
        error("Input can not be 0 or lower.");
        return getInt(min, max);
    }
    return value;
}

float getFloat(float min, float max)
{
    printf(" Input -> ");
    char input[string_length] = {};
    getStr(input, '\n', string_length);
    float value;

    for (int i = 0; i < string_length; i++)
    {
        if ((input[i] < '0' || input[i] > '9') && input[i] != 0 && input[i] != '.')
        {
            error("Wrong Input.");
            return getFloat(min, max);
        }
    }

    if (sscanf(input, "%f", &value) != 1)
    {
        error("Wrong Input.");
        return getFloat(min, max);
    }
    if (value < min || value > max && max > min)
    {
        error("Input is outside of range.");
        return getFloat(min, max);
    }
    if (max == min && value <= 0.0f)
    {
        error("Input can not be 0 or lower.");
        return getFloat(min, max);
    }
    return value;
}

void error(char * error_message)
{
    printf("\n\e[31m ERROR # \e[33m%s\e[0m\n\n",error_message);
}

void print_line()
{
    printf("\e[32m");
    for (int i = 0; i < string_length; i++) {printf("-");}
    printf("\e[0m\n");
}

int getData(BankAccount * Customers, int * Customer_count)
{
    FILE * customer = fopen("customer.txt","rt");
    FILE * loan = fopen("loan.txt","rt");
    if (customer)
    {
        int i = 0;
        while (!feof(customer))
        {
            if (fscanf(customer, "%[^&]&%[^&]&%ld\n",
                        Customers[i].Customer.name,
                        Customers[i].Customer.address,
                        &Customers[i].Customer.phone
                        ) == 3)
            {
                i++;
                (*Customer_count)++;
            }
        }
        fclose(customer);
    }
    else
    {
        return 1;
    }
    if (loan)
    {
        int i = 0;
        int customer_index;
        int loan_index;
        while (!feof(loan))
        {
            fscanf(loan, "%d&%d&\n",
                        &customer_index,
                        &loan_index);
            fscanf(loan, "%f&%f&%d\n",
                        &Customers[customer_index].Loans[loan_index].amount,
                        &Customers[customer_index].Loans[loan_index].interest_rate,
                        &Customers[customer_index].Loans[loan_index].period
                        );
        }
        fclose(loan);
    }
    return 0;
}



int listCustomers(BankAccount * Customers, int customer_count)
{
    if (!customer_count)
    {
        error(" No User Found.");
        return 0;
    }

    for (int i = 0; i < customer_count; i++)
    {
        printf("\n Customer ID = %d\
                \n Customer Name = %s\
                \n Customer Address = %s\
                \n Customer Phone = %ld\n\n",
                i,
                Customers[i].Customer.name,
                Customers[i].Customer.address,
                Customers[i].Customer.phone);
    }
    return 0;
}

int addCustomer (BankAccount * Customers, int * customer_count)
{
    printf(" Enter user name = ");
    getStr(Customers[*customer_count].Customer.name, '\n', string_length);
    printf(" Enter user address = ");
    getStr(Customers[*customer_count].Customer.address, '\n', string_length);
    printf(" Enter user phone number\n");
    Customers[*customer_count].Customer.phone = getInt(0,-1);
    FILE * customer = fopen("customer.txt","at");
    if (customer)
    {
        fprintf(customer,"%s&%s&%ld\n",
                Customers[*customer_count].Customer.name,
                Customers[*customer_count].Customer.address,
                Customers[*customer_count].Customer.phone);
    }
    (*customer_count)++;
}

int newLoan (BankAccount * Customers, int customer_count)
{
    if (!customer_count)
    {
        error(" No User Found.");
        return 0;
    }
    printf(" Which user you want to add new loan : \n");
    for (int i = 0; i < customer_count; i++)
    {
        printf("\t %d-Customer Name = %s\n",
                i, Customers[i].Customer.name);
    }
    int customer_index = (int) getInt(0,customer_count);
    int loan_index = -1;
    for (int i = 0; i < 3; i++)
    {
        if(Customers[customer_index].Loans[i].amount == 0.0)
        {
            loan_index = i;
            break;
        }
    }
    if (loan_index >= 0)
    {
        printf(" Enter loan amount\n");
        Customers[customer_index].Loans[loan_index].amount = getFloat(0,0);
        printf(" Enter period\n");
        Customers[customer_index].Loans[loan_index].period = (int) getInt(0,0);
        printf(" Enter interest rate\n");
        Customers[customer_index].Loans[loan_index].interest_rate = getFloat(0,0);
        
        Customers[customer_index].Loans[loan_index].amount = calculateLoan( 
                        Customers[customer_index].Loans[loan_index].amount,
                        Customers[customer_index].Loans[loan_index].period,
                        Customers[customer_index].Loans[loan_index].interest_rate);
        
        FILE * loan = fopen("loan.txt","at");
        if (loan)
        {
            fprintf(loan,"%d&%d&%f&%f&%d\n",
                        customer_index,
                        loan_index,
                        Customers[customer_index].Loans[loan_index].amount,
                        Customers[customer_index].Loans[loan_index].interest_rate,
                        Customers[customer_index].Loans[loan_index].period);
            fclose(loan);
        }
    }
}

float calculateLoan(float amount, int period, float interestRate)
{
    if (period--)
    {
        return calculateLoan(amount * (1 + interestRate), period, interestRate);
    }
    else
    {
        return amount;
    }
}

int getReport(BankAccount * Customers, int customer_count)
{
    float min;
    float max;
    for (int i = 0; i < customer_count; i++)
    {
        float sum = 0;
        printf("\n Customer ID = %d\
                \n Customer Name = %s\
                \n Customer Address = %s\
                \n Customer Phone = %ld\
                \n Customer Loans \n",
                i,
                Customers[i].Customer.name,
                Customers[i].Customer.address,
                Customers[i].Customer.phone);
        
        if (Customers[i].Loans[0].amount == 0.0f)
        {
            printf(" \e[31mThis user have not any loan.\e[0m\n");
        }
        else
        {
            printf(" [");
            for (int j = 0; j < 3; j++)
            {
                if (Customers[i].Loans[j].amount != 0.0f)
                {
                    sum += Customers[i].Loans[j].amount;
                    printf("%.2f + ",Customers[i].Loans[j].amount);
                }
                else
                {
                    break;
                }
            }
            printf("\b\b\b] = %.2f\n\n", sum);
        }
    }
    
}