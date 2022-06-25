#include <stdio.h>
#include <math.h>

#define PI 3.14
#define HATA printf("\n\n\n\033[0;31mERROR\033[0m\n");

void flush(void){
    int c = 0;
    do
        c = getchar();
    while (c != '\n' && c != EOF);
}

enum Shapes{
    Triangle = 1,
    Quadrilateral,
    Circle,
    Pyramid,
    Cylinder
};

enum Calculators{
    Area = 1,
    Perimeter,
    Volume
};

int select_shape(){
    enum Shapes selection = Triangle;
    while (selection >= Triangle){
        printf("\033[3H\033[KSelect a shape\n");
        printf("1. Triangle\n");
        printf("2. Quadrilateral\n");
        printf("3. Circle\n");
        printf("4. Pyramid\n");
        printf("5. Cylinder\n");
        printf("Input : \033[K");
        if (scanf("%u",&selection) && selection >= Triangle && selection <= Cylinder) {
            printf("\033[0H\033[0JShape = \033[33mTRIANGLE\033[0m\n");
            return selection;
        } else if (selection != 0) {
            HATA
            printf("Wrong choice of shape.\n");
            flush();
        } 
    }
    return 0;
}

int select_calc(){
    enum Calculators selection = Area;
    while (selection >= Area){
        printf("\033[2HSelect a calculator\n");
        printf("1. Area\n");
        printf("2. Perimeter\n");
        printf("3. Volume\n");
        printf("0. Exit\n");
        printf("Input : \033[K");
        if (scanf("%u",&selection) && selection >= 0 && selection <= Volume) return selection;
        else if (selection != 0) {
            HATA
            printf("Wrong choice of shape.\n");
            flush();
        }
    }
    return 0;
}

int calc_triangle(enum Calculators Calculator){
    printf("\033[2H\033[J");
    while(1)
    switch (Calculator) {
        case Area:
            printf("\033[2HCalculator = \033[33mAREA\033[0m\n");
            double sonuc = 0;
            int hata = 0;
            while (1){
                if(hata) HATA
                hata = 1;
                printf("Enter sides : \n");
                int p1,p2,p3 = 0;
                flush();
                if(!scanf("%d",&p1)) continue;
                if(!scanf("%d",&p2)) continue;
                if(!scanf("%d",&p3)) continue;
                double s = (p1 + p2 + p3) / 2.0;
                sonuc = s * (s - p1) * (s - p2) * (s - p3);
                if (p1 <= 0 || p2 <= 0 || p3 <= 0 || sonuc <= 0) continue;
                else break;
            }
            printf("Answer = %lf\n",sqrt(sonuc));
            return sqrt(sonuc);
        case Perimeter:
            break;
        case Volume:
            HATA
            printf("You cannot calculate the volume of 2D shape.\n");
            continue;
        case 0:
            break;
        default:
            HATA
            printf("Wrong choice of calculator.\n");
            return -1;
    }
    return -1;
}

int calc_quadrilateral(int);
int calc_circle(int);
int calc_pyramid(int);
int calc_cylinder(int);

int calculate(int (*shape)(), int (*calc)()){
    switch (shape()){
        case 0: //exit
            return 0;
            break;
        case Triangle:
            return calc_triangle(calc());
            break;
        default:
            break;
    }
}

int main(){
    int exit = 10;
    while(exit != 0){
        exit = calculate(select_shape,select_calc);
    }
    printf("Goodbye :d\n");
    return 0;
}