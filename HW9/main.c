/**
 * @file main.c
 * @author Emirhan Altunel
 * @brief 
 * @version 0.1
 * @date 2022-05-20
 */

#include <stdio.h>
#include <string.h>

#pragma region Definitions

#pragma endregion

#pragma region Structs & Unions
union Person
{
    char name[100];
    char address[100];
    long int phone;
};

// Bunları böyle kullanacaksak neden union yaptık?
// İnisiyatif alıp struct kullandım.
struct Loan 
{
    float amount;
    float interestRate;
    int period;
};

struct BankAccount
{
    union Person Customer;
    struct Loan Loans[3];
};
#pragma endregion

#pragma region Mandotary Functions

float calculateLoan(float amount, int period, float interestRate);
int getReport(struct BankAccount * Customers, int customer_count, int print);

/**
 * @brief 
 * 
 * @param Customers 
 * @param customer_count 
 * @return int 
 */
int listCustomers(struct BankAccount * Customers, int print, int customer_count)
{
    static int checkl = 0;
    if (!checkl)
    {
        customer_count = 0;
        FILE *f = fopen("customer.txt","rt");
        if (!f)
        {
            if (print) {printf("\n\e[31mThere is no customer.\e[0m\n\n");}
            return -1;
        }

        while (!feof(f))
        {
            fscanf(f,"%ld&%[^&]",
                    &Customers[customer_count].Customer.phone,
                    &Customers[customer_count].Customer.name[8]);
            fscanf(f,"&%[^&]&\n",
                    &Customers[customer_count].Customer.address[8 + strlen(&Customers[customer_count].Customer.name[8]) + 1]);
            customer_count += 1;
        }
        fclose(f);
    }
    if (!print)
    {
        return customer_count;
    }

    for (int i = 0; i < customer_count; i++)
    {
        int address_index = strlen(&Customers[i].Customer.name[8]);
        printf("\n Customer ID      = %d \
                \n Customer Name    = %s \
                \n Customer Phone   = %ld \
                \n Customer Address = %s \n",
                i + 1,
                &Customers[i].Customer.name[8],
                Customers[i].Customer.phone,
                &Customers[i].Customer.address[8 + address_index + 1]
                );
    }
    return customer_count;
}

/**
 * @brief 
 * 
 * It takes input from user.
 * If there is no space for new customer it warns the user.
 * I don't know how to store different data in union so I 
 *      find a different solution. 
 *      Union takes 100 Bytes space.
 *      First 8 Bytes for phone number.
 *      After that it stores username.
 *      Find username lenght and it writes address info
 *          after the username.
 *      So it looks like this : 
 *          [Long Int]Username\0Address\0
 * 
 * @param Customers 
 * @param customer_count 
 * @return Success or fail
 */
int addCustomer (struct BankAccount * Customers, int * customer_count)
{
    static int firsts = 0;
    if (!firsts)
    {
        *customer_count = listCustomers(Customers, 0, *customer_count);
    }
    if (*customer_count == 49)
    {
        printf("\n\e[31mThere is no place for new customer.\e[0m\n\n");
        return 0;
    }
    
    char temp_str[100];
    char temp_str1[100];

    printf("Enter username = ");
    scanf(" %[^\n]",temp_str);

    int address_index = strlen(temp_str);

    if (address_index + 8 + 1>= 100) // ! Check lenght
    {
        printf("\n\e[31mYou have entered too long information.\n\n");
        return -1;
    }

    printf("Enter phone number = ");
    while (!scanf("%ld",&Customers[*customer_count].Customer.phone)) // ! Check number
    {
        printf("\e[31;1mEnter phone number please = \e[0m");
        while (getchar() != '\n');
    }

    printf("Enter address = ");
    scanf(" %[^\n]",temp_str1);
    address_index += strlen(temp_str1);

    if (address_index + 2 + 8 >= 100) // ! Check length
    {
        printf("\n\e[31mYou have entered too long information.\n\n");
        return -1;
    }

    for (int i = 8; i < address_index; i++)
    {
        if (Customers[*customer_count].Customer.name[i] == '&')
        {
            Customers[*customer_count].Customer.name[i] = ' ';
        }
    }

    FILE *f = fopen("customer.txt","rt");
    if (!f)
    {
        printf("\n\e[32mThere was no file so it is created.");
        f = fopen("customer.txt","wt");
    }
    else
    {
        fclose(f);
        f = fopen("customer.txt","at");
    }

    if (f)
    {
        strcpy(&Customers[*customer_count].Customer.name[8],temp_str);
        strcpy(&Customers[*customer_count].Customer.address[8 + strlen(temp_str) + 1],temp_str1);
        printf("\n\e[32mUser succesfully added.\n\n");

        fprintf(f,"%ld&%s&%s&\n",
                Customers[*customer_count].Customer.phone,
                &Customers[*customer_count].Customer.name[8],
                &Customers[*customer_count].Customer.address[8 + strlen(temp_str) + 1]);
        fclose(f);
        *customer_count += 1;
        return 1;
    }
    else
    {
        printf("\n\e[31mFile couldn't created. ;\n\n");
        return 0;
    }
    
}

/**
 * @brief 
 * 
 * @return int 
 */
int newLoan (struct BankAccount * Customers, int customer_count)
{
    static int first = 0;
    if (!first)
    {
        customer_count = getReport(Customers, customer_count, 0);
        if (customer_count == -1)
        {
            printf("\n\e[31mThere is no customer.\e[0m\n\n");
            return -1;
        }
    }

    for (int i = 0; i < customer_count; i++)
    {
        printf("\t%d.%s\n",i + 1, &Customers[i].Customer.name[8]);
    }
    printf("\nWhich user you want to add loan for : ");
    int temp_int;
    if (scanf("%d",&temp_int) && temp_int > 0 && temp_int <= customer_count)
    {
        int loan_space = 0;
        for (int i = 0; i < 3; i++)
        {
            if (Customers[temp_int - 1].Loans[i].amount == 0.0f)
            {
                loan_space = i + 1;
                break;
            }
        }
        if (loan_space)
        {
            float loan_amount, interest_rate;
            int period;
            printf("Enter loan amount : ");
            while (!scanf("%f",&loan_amount) && loan_amount >= 0.0f) {printf("Wrong input.\n");return 0;}
            printf("Enter period : ");
            while (!scanf("%d",&period) && period >= 0) {printf("Wrong input.\n");return 0;}
            printf("Enter interest rate : ");
            while (!scanf("%f",&interest_rate) && interest_rate >= 0.0f) {printf("Wrong input.\n");return 0;}

            Customers[temp_int - 1].Loans[loan_space].amount = calculateLoan(loan_amount, period, interest_rate);
            for (int i = 1; i <= period; i++) {printf("%2d. Month = %5.2f\n",i,Customers[temp_int - 1].Loans[loan_space].amount / period);}
            FILE *f = fopen("loan.txt","at");
            fprintf(f,"%d&%d&%.2f\n",temp_int,loan_space,Customers[temp_int - 1].Loans[loan_space].amount);
            fclose(f);
        }
        else
        {
            printf("%d\n",loan_space);
            printf("This user can't have more loan.\n");
            return 0;
        }
    }
    else
    {
        printf("Wrong input.\n");
        return 0;
    }
}

/**
 * @brief 
 * 
 * @param amount 
 * @param period 
 * @param interestRate 
 * @return float 
 */
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

/**
 * @brief Get the Report object
 * 
 * @param Customers 
 * @return int 
 */
int getReport(struct BankAccount * Customers, int customer_count, int print)
{
    static int check = 0; 
    // Her zaman kontrol etmesini engelledim fakat uygulama çalışıyorken dosya değişirse sıkıntı çıkarıyor o yüzden iptal ettim.
    
    float max_loan = 0.0f; // En büyük ve en küçüğü bulmanın amacı renklendirme başka bir şey değil
    float min_loan = 100000.0f;
    if (!check) 
    {
        customer_count = listCustomers(Customers, 0, customer_count);
        if (customer_count == -1)
        {
            if (print) {printf("\n\e[31mThere is no customer.\e[0m\n\n");}
            return -1;
        }
        for (int i = 0; i < customer_count; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Customers[i].Loans[j].amount = 0.0f;
            }
        }
        
        FILE *f = fopen("loan.txt","rt");
        
        if (f)
        {
            while (!feof(f))
            {
                int id = 0;
                float loan;
                int loan_count;

                fscanf(f,"%d&%d&%f\n", &id, &loan_count, &loan);
                id--;
                if (id < 0)
                {
                    break;
                }

                Customers[id].Loans[loan_count - 1].amount = loan;
            }
        }
    }
    else
    {
        for (int id = 0; id < customer_count; id++)
        {
            float sum_loan = 0.0f;
            for (int i = 0; i < 3; i++) {sum_loan += Customers[id].Loans[i].amount;}
            if (sum_loan > max_loan) {max_loan = sum_loan;}
            if (sum_loan < min_loan) {min_loan = sum_loan;}
        }
    }
    
    if (print)
    {
        for (int i = 0; i < customer_count; i++)
        {
            float sum = 0.0f;
            for (int j = 0; j < 3; j++)
            {
                sum += Customers[i].Loans[j].amount;
                if (sum > max_loan) {max_loan = sum;}
                if (sum < min_loan) {min_loan = sum;}
            }
        }
        
        for (int i = 0; i < customer_count; i++)
        {
            int address_index = strlen(&Customers[i].Customer.name[8]);
            printf("\n Customer ID      = %d \
                    \n Customer Name    = %s \
                    \n Customer Phone   = %ld \
                    \n Customer Address = %s \
                    \n Customer Loans\n [",
                    i + 1,
                    &Customers[i].Customer.name[8],
                    Customers[i].Customer.phone,
                    &Customers[i].Customer.address[8 + address_index + 1]
                    );
            float sum = 0.0f;
            for (int j = 0; j < 3; j++)
            {
                if (Customers[i].Loans[j].amount != 0.0f)
                {
                    sum += Customers[i].Loans[j].amount;
                    printf("%.2f + ",Customers[i].Loans[j].amount);
                }
            }
            if (sum != 0.0f)
            {
                printf("\b\b\b] = \e[38;2;%d;%d;0m%.2f\e[0m\n",
                        (int)((sum - min_loan) / (max_loan - min_loan) * (255.0f)), // ! For coloring
                        255 - (int)((sum - min_loan) / (max_loan - min_loan) * (255.0f)), // ! For coloring
                        sum);
            }
            else
            {
                printf("\e[2K\e[F\e[31m There is no loan for this user.\e[0m\n");
            }
        }
    }
    return customer_count;
}
#pragma endregion 

#pragma region Custom Functions
int menu(int first)
{
    if (first == 1)
    {
        for(int i = 0; i < 41; i++) {printf("\e[33m=\e[0m");}
        printf("\n\e[32m  Welcome to the Bank Management System\e[0m\n");    
    }
    for(int i = 0; i < 41; i++) {printf("\e[33m=\e[0m");}
    printf("\n\t1. List All Customers \
            \n\t2. Add New Customer \
            \n\t3. New Loan Application \
            \n\t4. Report Menu \
            \n\t5. Exit System\n");
    for(int i = 0; i < 41; i++) {printf("\e[33m=\e[0m");}
    printf("\nInput => ");
    int choose;
    if (scanf("%d",&choose))
    {
        while (getchar() != '\n');
        if (choose >= 1 && choose <= 5)
        {
            return choose;
        }
        else
        {
            printf("\n\e[31mWrong option.\e[0m\n\n");
            return menu(first + 2);
        }
    }
    else
    {
        while (getchar() != '\n');
        printf("\n\e[31mWrong input.\e[0m\n\n");
        return menu(first + 1);
    }
}

#pragma endregion

int main()
{
    int choose, c=1;
    struct BankAccount Customers[50];
    int customer_count = 0;
    
    do
    {
        choose = menu(c++);
        switch (choose)
        {
        case 1:
            customer_count = listCustomers(Customers,1,customer_count);
            break;
        case 2:
            addCustomer(Customers, &customer_count);
            break;
        case 3:
            newLoan(Customers, customer_count);
            break;
        case 4:
            customer_count = getReport(Customers, customer_count,1);
            break;
        default:
            break;
        }
    } while(choose != 5);
    return 0;
}
