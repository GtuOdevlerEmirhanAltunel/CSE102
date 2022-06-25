#include <stdio.h>
#define x_max 56
#define y_max 16
#define x_olcek 10 
#define y_olcek 5

int main(){

    int exit = 1;
    do {
        printf("\nSelect\n");
        printf("1 - Coefficients\n");
        printf("2 - Draw\n");
        printf("3 - Draw to file\n");
        printf("4 - Exit\n");

        int input = 0;
        fflush(stdout);
        scanf(" %d",&input);

        FILE *fp;
        int a = 0;
        int b = 0;
        int c = 0;

        switch (input){
            case 1:
                fp = fopen("coefficients.txt","w");
                printf("\nEnter : ax^2 + bx + c\n");
                int i;
                printf("a : "); scanf("%d",&i); fprintf(fp,"%d\n",i);
                printf("b : "); scanf("%d",&i); fprintf(fp,"%d\n",i);
                printf("c : "); scanf("%d",&i); fprintf(fp,"%d\n",i);
                fclose(fp);
                break;
            case 2:
                if (fp = fopen("coefficients.txt","r")) {

                    fscanf(fp,"%d %d %d",&a,&b,&c);
                    for (int j = y_max;j >= -y_max;j -= 1) {
                        for (int i = -x_max;i <= x_max;i += 1) {

                            int r = a * j * j + b * j + c;

                            if (r == i) printf("\033[0;31m#\033[0m");

                            else if (j == y_max && i == 0) printf("^");
                            else if (j == -y_max && i == 0) printf("v");
                            else if (j == 0 && i == -x_max) printf("<");
                            else if (j == 0 && i == x_max) printf(">");

                            else if (i == -1 && j == -1) printf("\033[0;33m0\033[0m");

                            else if ((j == 0 && i % x_olcek == 0) || (i == 0 && j % y_olcek == 0)) printf("┼");
                            else if (i == 0 && j == 0) printf("┼");
                            else if (i == 0) printf("│");
                            else if (j == 0) printf("─");

                            else if (j == -1 && (i - 2) % x_olcek == 0 && i - 2 != 0) printf("\033[0;33m\b\b%+-3d\033[0m",i - 2);

                            else if (i == -1 && j % y_olcek == 0) printf("\033[0;33m\b\b%+-3d\033[0m",j);

                            else printf(" ");
                        }
                        printf("\n");
                    }
                    fclose(fp);
                }
                break;
            case 3:
                if (fp = fopen("coefficients.txt","r")) {
                    fscanf(fp,"%d %d %d",&a,&b,&c);
                    FILE *f = fopen("graph.txt","w");
                    for (int j = y_max;j >= -y_max;j -= 1) {
                        for (int i = -x_max;i <= x_max;i += 1) {
                            int r = a * j * j + b * j + c;

                            if (r == i) fprintf(f,"#");

                            else if (j == y_max && i == 0) fprintf(f,"^");
                            else if (j == -y_max && i == 0) fprintf(f,"v");
                            else if (j == 0 && i == -x_max) fprintf(f,"<");
                            else if (j == 0 && i == x_max) fprintf(f,">");

                            else if ((j == 0 && i % x_olcek == 0) || (i == 0 && j % y_olcek == 0)) fprintf(f,"┼");
                            else if (i == 0 && j == 0) fprintf(f,"┼");
                            else if (i == 0) fprintf(f,"│");
                            else if (j == 0) fprintf(f,"─");

                            else fprintf(f," ");
                        }
                        fprintf(f,"\n");
                    }
                    fclose(fp);
                    fclose(f);
                }                 
                break;
            case 4:
                printf("\nGoodbye :d\n");
                exit = 0;
            default:
                break;
        }
    } while (exit);
    return 0;
}