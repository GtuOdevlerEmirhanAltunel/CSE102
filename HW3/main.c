#include <stdio.h>
#include <math.h>
#define MAX 2147483647

//error_codes
#define ERROR__FILE_IS_EMPYT printf("\033[0;31;1mFile is empyt.\033[0m\n");
#define ERROR__FILE_IS_NOT_EXISTS printf("\033[0;31;1mThe result file is not exists so new file is created.\033[0m\n");
#define ERROR__INVALID_INPUT printf("\033[0;31;1mInvalid input.\033[0m\n");
#define ERROR__NEGATIVE_NUMBERS {printf("\033[0;31;1mThe input must be bigger than 0.\033[0m\n");return -1;}
#define ERROR__PRIME {printf("\033[0;31;1mThe input must be bigger than 1.\033[0m\n");return -1;}
#define CLEARED printf("\033[0;33;1mIt is clear now.\033[0m\n");

// Amacı part 2 deki sayıların hizalı yazılmasına yardımcı olmak. En büyük sayı kaç basamaklı onu veriyor.
int digits (int n) {int c = 0; n--; do{n /= 10; c++;} while (n != 0); return c;}
void write_file (int number);
void print_file ();
void clear() {FILE *fp = fopen ("result.txt","w"); fclose (fp);CLEARED}

/*Part 1*/

int sum (int n1, int n2, int flag){

    int result = 0;
    
    if (n1 < 0 || n2 < 0) ERROR__NEGATIVE_NUMBERS

    switch (flag){
        case 0:
            for (int i = n1 + 2 - n1 % 2; i < n2; i += 2) {result += i; printf ("%d + ",i);}
            printf ("\b\b= ");
            write_file (result);
            return result;
            break;
        case 1:
            for (int i = n1 + 1 + n1 % 2; i < n2; i += 2) {result += i; printf ("%d + ",i);}
            printf ("\b\b= ");
            write_file (result);
            return result;
            break;
        default:
            ERROR__INVALID_INPUT
    }
    return -1;
}

int multi (int n1, int n2, int flag){

    int result = 1;

    if (n1 < 0 || n2 < 0) ERROR__NEGATIVE_NUMBERS

    switch (flag){
        case 0:
            for (int i = n1 + 2 - n1 % 2; i < n2; i += 2) {result *= i; printf ("%d x ",i);}
            printf ("\b\b= ");
            write_file (result);
            return result;
            break;
        case 1:
            for (int i = n1 + 1 + n1 % 2; i < n2; i += 2) {result *= i; printf ("%d x ",i);}
            printf ("\b\b= ");
            write_file (result);
            return result;
            break;
        default:
            ERROR__INVALID_INPUT
    }
    return -1;
}

/*Part 2*/

int isprime (int a){
    if (a < 2) ERROR__PRIME
    for (int i = 2; i <= sqrt(a); i++) if (a % i == 0) return i; return 1;
}

/*Part 3*/

void swap (int* n1, int* n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void write_file (int number) {
    
    FILE *fp = fopen ("result.txt","a");
    if (fp != NULL) {
        fprintf (fp,"%d ",number);
    }
    fclose(fp);
}

void sort_file () {
    /*
    Çalışma mantığı :
    İlk turda en küçük 3 sayıyı buluyor. Eğer en küçük sayılardan biri tekrarlıyorsa bunu count değişkeni ile sayıyor.
    Bulduğu en küçük sayıları temp dosyasına yazıyor. 
    */
    FILE *fpt = fopen ("temp.txt","w");
    printf ("\nResult\n");
    if (fpt != NULL) {
        int last = -1;
        int temp, min1, min2, min3 = MAX;
        do {
            FILE *fp;
            if (fp = fopen ("result.txt","r")) {
            temp = min1 = min2 = min3 = MAX;
            int count = 0;
            while (!feof (fp)) {
                fscanf (fp,"%d ",&temp);
                if (temp > last && temp < min3) {
                    min3 = temp;
                    if (min2 > min3) {
                        swap (&min2,&min3);
                        if (min1 > min2) swap (&min1,&min2);
                    }
                }else if (temp > last && temp == min3) {
                    count++;
                }
            }
            
            if (min1 != MAX) fprintf (fpt,"%d ",min1);
            if (min2 != MAX) fprintf (fpt,"%d ",min2);
            if (min3 != MAX) for (int i = 0; i < count + 1; i++) fprintf (fpt,"%d ",min3);
            last = min3;
            fclose (fp);
            } else ERROR__FILE_IS_NOT_EXISTS
        } while (min1 != MAX && min2 != MAX && min3 != MAX);
    }
    fclose (fpt);
    FILE *fpa = fopen ("result.txt","w");
    FILE *fpb = fopen ("temp.txt","r");
    int a = MAX;
    while (!feof(fpb)) {
        fscanf (fpb,"%d ",&a);
        if (a != MAX) fprintf (fpa,"%d ",a);
    }
    fclose(fpa);
    fclose(fpb);
    remove("temp.txt");
    print_file();
}

void print_file () {

    FILE *fp;

    if (fp = fopen ("result.txt","r")) {
        int number = MAX;
        int number_c = 0;
        while (!feof (fp)) {
            fscanf (fp,"%d ",&number);
            if (number != MAX) {
                printf ("%d,",number); 
                number_c++;
            }
        }
        if (number_c) printf("\b \n");
        else ERROR__FILE_IS_EMPYT
    } else {
        ERROR__FILE_IS_NOT_EXISTS
        fp = fopen ("result.txt","w");
    }
    fclose(fp);
}

int main () {

    /*Menü*/
    
    int menu_choice;

    do {

        printf ("\nSelect operation\n");
        printf ("1. Calculate sum/multiplication between two numbers\n");
        printf ("2. Calculate prime numbers\n");
        printf ("3. Show number sequence in file\n");
        printf ("4. Sort number sequence in file\n");
        printf ("5. Clear Result.txt\n");

        menu_choice = 0;
        scanf ("%d",&menu_choice);

        /*Part 1*/
        switch (menu_choice) {
            case 1:
                int part_1_choice_1 = -1;
                printf ("\nSelect operation\n");
                printf ("Please enter '0' for sum, '1' for multiplication\n");
                scanf ("%d",&part_1_choice_1);

                if (part_1_choice_1 == 0 || part_1_choice_1 == 1) {
                
                    int part_1_choice_2 = -1;
                    printf ("\nSelect operation\n");
                    printf ("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
                    scanf ("%d",&part_1_choice_2);
    
                    if (part_1_choice_2 == 0 || part_1_choice_2 == 1) {
                    
                        printf ("\nPlease enter two positive numbers\n");
                        int number_1, number_2 = 0;
                        printf ("Number 1 : "); scanf ("%d",&number_1);
                        printf ("Number 2 : "); scanf ("%d",&number_2);
    
                        if (number_1 >= 0 && number_2 >= 0) {
                            printf ("\nResult\n");
    
                            switch (part_1_choice_1 ) {
                                case 0:
                                    printf ("%d\n",sum (number_1,number_2,part_1_choice_2));
                                    break;
                                case 1:
                                    printf ("%d\n",multi (number_1,number_2,part_1_choice_2));
                                    break;
                                default:
                                    ERROR__INVALID_INPUT
                                    break;
                            }
                        } else ERROR__NEGATIVE_NUMBERS
                    } else ERROR__INVALID_INPUT
                } else ERROR__INVALID_INPUT
                break;
            case 2:
                int part_2_choice = -1;
                printf ("\nPlease enter a positive integer bigger or equal to 2\n");
                scanf ("%d",&part_2_choice);

                if (part_2_choice > 1) {
                    printf ("\nResult\n");
                    for (int i = 2; i < part_2_choice; i++)
                    if (isprime (i) == 1) printf ("\033[0;32m%*d is a prime.\033[0m\n",digits (part_2_choice),i);
                    else printf ("%*d / %*d = %*d\n",digits (part_2_choice),i,digits (sqrt(part_2_choice)),isprime (i),digits (part_2_choice/2),i / isprime (i));
                } else ERROR__INVALID_INPUT
                break;
            case 3:
                printf ("\nResult\n");
                print_file ();
                break;
            case 4:
                sort_file();
                break;
            case 5:
                clear();
                break;
            default:
                ERROR__INVALID_INPUT
                break;
        }

    } while (menu_choice >= 1 && menu_choice <= 5);

    printf ("Goodbye :d\n");

    return 0;
}