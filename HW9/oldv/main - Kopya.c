/**
 * @file main.c
 * @author Emirhan Altunel
 * @brief 
 * @version 0.1
 * @date 2022-05-19
 */

#pragma region Libraries // !
#include <stdio.h>
#pragma endregion

#pragma region Settings // !
#define BUF_SIZE 50
#define LINE_SEPERATOR "="
#define ERROR printf("\n\e[31mWrong Value\e[0m\n\n");
char WHITE_SPACES[] = " ,.";
typedef union getter_return
{
    int i;
    char s[BUF_SIZE];
} getter_return;

struct Changeable
{
    char name[BUF_SIZE];
    char value[BUF_SIZE];
    char def[BUF_SIZE];
    int type;
} Values[] =
{
    {"LINE_LENGTH","41","41",0},
    {"SEPERATOR_STYLE","33","33",1}
};
size_t Values_size = sizeof(Values) / sizeof(struct Changeable);

#pragma endregion

#pragma region Structs // !
union Person
{
    char name[50];
    char address[50];
    int phone;
};

union Loan
{
    float amount;
    float interestRate;
    int period;
};

struct BankAccount
{
    union Person Customer;
    union Loan Loans[3];
};
#pragma endregion

#pragma region Mandotary Functions // !
void listCustomers()
{

}
void addCustomer ()
{

}
void newLoan ()
{

}
void calculateLoan(float amount, int period, float interestRate)
{

}
void getReport()
{

}
#pragma endregion

#pragma region Custom Funtions // !
int toInt(char const * str, int len)
{
    if(len)
	{
		len--;
        if (str[len] < '0' || str[len] > '9') {return -1;}
        int next = toInt(str,len);
        if (next == -1) {return -1;}
		return str[len] - 48 + 10 * next;
	}
	return 0;
}
int strcopy(char * str1, char const * str2)
{
    if (!*str2) {*str1 = 0; return 0;}
    *str1 = *str2;
    strcopy(str1 + 1, str2 + 1);
}
int strlength(char const * str)
{
    if (!str[0]) return 1;
    else return 1 + strlength(str + 1);
}
int strcompare(char const * str1, char const * str2)
{
    if (!!*str1 ^ !!*str2) {return 0;}
    else if (!*str1 && !*str2) {return 1;}
    else if (*str1 == *str2) {return strcompare(str1 + 1, str2 + 1);}
    else if (*str1 >= 'a' && *str1 - 'a' + 'A' == *str2) {return strcompare(str1 + 1, str2 + 1);}
    else if (*str2 >= 'a' && *str2 - 'a' + 'A' == *str1) {return strcompare(str1 + 1, str2 + 1);}
    else {return 0;}
}
getter_return getter(char const * str)
{
    for (int i = 0; i < Values_size; i++)
    {
        if (strcompare(str, Values[i].name))
        {
            getter_return new;
            if (!Values[i].type) {new.i = toInt(Values[i].value,strlength(Values[i].value) - 1);}
            else {strcopy(new.s,Values[i].value);}
            return new;
        }
    }
}
int setter(char const * str, char const * val)
{
    for (int i = 0; i < Values_size; i++)
    {
        if (strcompare(Values[i].name, str))
        {
            strcopy(Values[i].value, val);
            return 0;
        }
    }
    return -1;
}
int commands(char const * input)
{
    if (*input != ':') return 0;
    char command[BUF_SIZE];
    char values[BUF_SIZE][BUF_SIZE];
    int lent = strlength(input);
    sscanf(input + 1,"%s",command);
    int cursor = strlength(command) + 1;
    int value_count = 0;
    while (cursor < lent && sscanf(input + cursor, "%s", values[value_count]) && value_count < BUF_SIZE)
    {
        value_count++;
        while (input[cursor] != ' ' && input[cursor] != 0) {cursor++;}
        if (input[cursor] == ' ') {cursor++;}
        else if (input[cursor] == 0) {break;}
    }
    
    if (strcompare(command, "change") && value_count == 2)
    {
        if (setter(values[0],values[1])) {ERROR}
        return 1;
    }
    else if (strcompare(command, "restart") && value_count == 0)
    {
        return 442;
    }
    else if (strcompare(command, "clear") && value_count == 0)
    {
        return 442;
    }
    else if (strcompare(command, "def") && value_count == 0)
    {
        for (int i = 0; i < Values_size; i++)
        {
            strcopy(Values[i].value,Values[i].def);
        }
        return 442;
    }
    ERROR
}
int menu()
{
    int static first_time = 1;
    int length = getter("LINE_LENGTH").i;
    if (first_time)
    {
        for (int i = 0; i < length; i++) {printf("\e[%sm%s\e[0m",getter("SEPERATOR_STYLE").s,LINE_SEPERATOR);}
        char welcome[] = "Welcome to the Bank Management System";
        printf("\n");
        if (length - strlength(welcome) > 0) {printf("%*c",(length - strlength(welcome)) / 2 + 1,' ');}
        printf("\e[32m%s\n\e[0m",welcome);
        first_time--;
    }
    for (int i = 0; i < length; i++) {printf("\e[%sm%s\e[0m",getter("SEPERATOR_STYLE").s,LINE_SEPERATOR);}
    printf("%s%s%s%s%s\n",
        "\n\t1. List All Customers",
        "\n\t2. Add New Customer",
        "\n\t3. New Loan Application",
        "\n\t4. Report Menu",
        "\n\t5. Exit System"
        );
    for (int i = 0; i < length; i++) {printf("\e[%sm%s\e[0m",getter("SEPERATOR_STYLE").s,LINE_SEPERATOR);}
    printf("\nInput : \n");
    char input[BUF_SIZE];

    int count = -1;
    char temp = getchar();
    while (temp != '\n') 
    {
        if (++count <= BUF_SIZE) {input[count] = temp;} 
        temp = getchar();
    }
    input[count+1] = 0;
    int ret;
    if (*input == ':') 
    {
        int com = commands(input);
        if (com == 442) {printf("\e[0H\e[0J");first_time = 1;}
        return menu();
    }
    else if (sscanf(input,"%d",&ret) && ret >= 1 && ret <= 5) {return ret;}
    ERROR
    return menu();
}

#pragma endregion

int main()
{
    int main_while_loop = menu();
    int count = 40;
    while (main_while_loop >= 1 && main_while_loop <= 4)
    {        
        main_while_loop = menu();
    }
    
    return 0;
}

/**
 * + Geliştirici Notları
 * 
 * + Eklenen Özellikler :
 *      * Welcome yazısı ortalıyor
 */