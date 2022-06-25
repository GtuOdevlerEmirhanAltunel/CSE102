#pragma region Libraries
#include <stdio.h>
#include <math.h>
#pragma endregion Libraries

#pragma region Defines
#define PI 3.14
#define pre 2
char flush = 0;
double sonuc = 0;
int hata = 0;
#define ERROR printf("\033[1H\033[2J\033[0;31mERROR\033[0m\n\033[K");
#define ERROR2 printf("\033[1H\033[0;31mERROR\033[K\033[0m\n\033[K");
#define FLUSH flush = 0;do{flush = getchar();}while (flush != '\n' && flush != EOF);
void print(double x){
    printf("\033[1H\033[32mANSWER\033[0m \n%.*lf\033[0m\033[K\n\033[K",pre,x);
} 
#pragma endregion

#pragma region Enumlar
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
#pragma endregion

#pragma region Methods
int select_shape(){
    enum Shapes selection = Triangle;
    while (selection >= Triangle){

        printf("\033[4H\033[K"); // Third Row
        printf("Select a shape\033[K\n");
        printf("1. Triangle\033[K\n");
        printf("2. Quadrilateral\033[K\n");
        printf("3. Circle\033[K\n");
        printf("4. Pyramid\033[K\n");
        printf("5. Cylinder\033[K\n");
        printf("0. Exit\033[K\n");
        printf("Input : \033[K");
        
        if (scanf("%u",&selection) && selection >= Triangle && selection <= Cylinder) {
            printf("\033[3H\033[J");
            return selection;
        } else if (selection != 0) {
            ERROR
            printf("Wrong choice of shape.\033[K\n");
            FLUSH
        }
    }
    return 0;
}

int select_calc(){
    enum Calculators selection = Area;
    while (selection >= Area){

        printf("\033[4HSelect a calculator\033[K\n"); //Third Row
        printf("1. Area\033[K\n");
        printf("2. Perimeter\033[K\n");
        printf("3. Volume\033[K\n");
        printf("9. Main Menu\033[K\n");
        printf("0. Exit\033[K\n");
        printf("Input : \033[K");
        if (scanf("%u",&selection) && selection >= Area && selection <= Volume) return selection;
        else if (selection == 9) return -1;
        else if (selection != 0) {
            ERROR
            printf("Wrong choice of calculator.\033[K\n");
            FLUSH
        }
    }
    return 0;
}

int calc_triangle(enum Calculators Calculator){
    printf("\033[4H\033[KShape = \033[33mTRIANGLE\033[0m\n");
    if (Calculator) {
        int p1,p2,p3 = 0;
        double s = 0;
        switch (Calculator) {
            case Area:
                printf("\033[5HCalculator = \033[33mAREA\033[0m\033[K\n");
                break;
            case Perimeter:
                printf("\033[5HCalculator = \033[33mPERIMETER\033[0m\033[K\n");
                break;
            case Volume:
                ERROR
                printf("You cannot calculate the volume of 2D shape.\033[K\n");
                return 0;
            default:
                ERROR
                printf("Wrong choice of calculator.\033[K\n");
                return 0;
        }
        sonuc = 0;
        hata = 0;
        do {
            if(hata) {ERROR2;printf("Wrong Input.");}
            if(!hata) printf("\033[K");
            hata = 1;
            printf("\033[6HEnter sides : \033[J\n");
            p1,p2,p3 = 0;
            if(printf("Side 1 : ") && !scanf("%d",&p1) || p1 <= 0) {FLUSH continue;}
            if(printf("Side 2 : ") && !scanf("%d",&p2) || p2 <= 0) {FLUSH continue;}
            if(printf("Side 3 : ") && !scanf("%d",&p3) || p3 <= 0) {FLUSH continue;}
            s = (p1 + p2 + p3) / 2.0;
            sonuc = s * (s - p1) * (s - p2) * (s - p3);
        } while (sonuc <= 0);
        switch (Calculator) {
            case Area:
                print(sqrt(sonuc));
                return 1;
            case Perimeter:
                print(s * 2);
                return 1;
        }
    }
    return -1;
}

int calc_quadrilateral(enum Calculators Calculator){
    printf("\033[4H\033[KShape = \033[33mQUADRILATERAL\033[0m\n");
    if (Calculator) {
        int p1,p2,p3,p4 = 0;
        double s = 0;
        switch (Calculator) {
            case Area:
                printf("\033[5HCalculator = \033[33mAREA\033[0m\033[K\n");
                break;
            case Perimeter:
                printf("\033[5HCalculator = \033[33mPERIMETER\033[0m\033[K\n");
                break;
            case Volume:
                ERROR
                printf("You cannot calculate the volume of 2D shape.\033[K\n");
                return 0;
            default:
                ERROR
                printf("Wrong choice of calculator.\033[K\n");
                return 0;
        }
        sonuc = 0;
        hata = 0;
        do {
            if(hata) {ERROR2;printf("Wrong Input.");}
            if(!hata) printf("\033[K");
            hata = 1;
            printf("\033[6HEnter sides : \033[J\n");
            p1,p2,p3,p4 = 0;
            if(printf("Side 1 : ") && !scanf("%d",&p1) || p1 <= 0) {FLUSH continue;}
            if(printf("Side 2 : ") && !scanf("%d",&p2) || p2 <= 0) {FLUSH continue;}
            if(printf("Side 3 : ") && !scanf("%d",&p3) || p3 <= 0) {FLUSH continue;}
            if(printf("Side 4 : ") && !scanf("%d",&p4) || p4 <= 0) {FLUSH continue;}
            s = (p1 + p2 + p3 + p4) / 2.0;
            sonuc = (s - p1) * (s - p2) * (s - p3) * (s - p4);
        } while (sonuc <= 0);
        switch (Calculator) {
            case Area:
                print(sqrt(sonuc));
                return 1;
            case Perimeter:
                print(s * 2);
                return 1;
        }
    }
    return -1;
}

int calc_circle(enum Calculators Calculator){
    printf("\033[4H\033[KShape = \033[33mCIRCLE\033[0m\n");
    if (Calculator) {
        int p1 = 0;
        double s = 0;
        switch (Calculator) {
            case Area:
                printf("\033[5HCalculator = \033[33mAREA\033[0m\033[K\n");
                break;
            case Perimeter:
                printf("\033[5HCalculator = \033[33mPERIMETER\033[0m\033[K\n");
                break;
            case Volume:
                ERROR
                printf("You cannot calculate the volume of 2D shape.\033[K\n");
                return 0;
            default:
                ERROR
                printf("Wrong choice of calculator.\033[K\n");
                return 0;
        }
        sonuc = 0;
        hata = 0;
        do {
            if(hata) {ERROR2;printf("Wrong Input.");}
            if(!hata) printf("\033[K");
            hata = 1;
            printf("\033[6HEnter radius : \033[J\n");
            p1 = 0;
            if(printf("Radius : ") && !scanf("%d",&p1) || p1 <= 0) {FLUSH continue;}
            sonuc = 1;
        } while (sonuc <= 0);
        switch (Calculator) {
            case Area:
                print(PI * p1 * p1);
                return 1;
            case Perimeter:
                print(2 * PI * p1);
                return 1;
        }
    }
    return -1;
}

int calc_pyramid(enum Calculators Calculator){
    printf("\033[4H\033[KShape = \033[33mPYRAMID\033[0m\n");
    if (Calculator) {
        int p1,p2 = 0;
        double s = 0;
        switch (Calculator) {
            case Area:
                printf("\033[5HCalculator = \033[33mAREA\033[0m\033[K\n");
                break;
            case Perimeter:
                printf("\033[5HCalculator = \033[33mPERIMETER\033[0m\033[K\n");
                break;
            case Volume:
                printf("\033[5HCalculator = \033[33mVOLUME\033[0m\033[K\n");
            default:
                ERROR
                printf("Wrong choice of calculator.\033[K\n");
                return 0;
        }
        sonuc = 0;
        hata = 0;
        do {
            if(hata) {ERROR2;printf("Wrong Input.");}
            if(!hata) printf("\033[K");
            hata = 1;
            printf("\033[6HEnter side and height : \033[J\n");
            p1,p2 = 0;
            if(printf("Side : ") && !scanf("%d",&p1) || p1 <= 0) {FLUSH continue;}
            if(printf("Height : ") && !scanf("%d",&p2) || p2 <= 0) {FLUSH continue;}
            sonuc = 1;
        } while (sonuc <= 0);
        switch (Calculator) {
            case Area:
                printf("\e[1H\033[32mANSWER\033[K\033[0;33m\nBase Area\033[0m : %0.*lf , \033[0;33mLateral Area\033[0m : %0.*lf , \033[0;33mSurface Area\033[0m : %0.*lf",pre,1.0*p1*p1,pre,2.0*p1*p2,pre,p1*p1+2.0*p1*p2);
                return 1;
            case Perimeter:
                print(4 * p1);
                return 1;
            case Volume:
                print(1/3*p1*p1*p2);
        }
    }
    return -1;
}

int calc_cylinder(enum Calculators Calculator){
    printf("\033[4H\033[KShape = \033[33mCYLINDER\033[0m\n");
    if (Calculator) {
        int p1,p2 = 0;
        double s = 0;
        switch (Calculator) {
            case Area:
                printf("\033[5HCalculator = \033[33mAREA\033[0m\033[K\n");
                break;
            case Perimeter:
                printf("\033[5HCalculator = \033[33mPERIMETER\033[0m\033[K\n");
                break;
            case Volume:
                printf("\033[5HCalculator = \033[33mVOLUME\033[0m\033[K\n");
            default:
                ERROR
                printf("Wrong choice of calculator.\033[K\n");
                return 0;
        }
        sonuc = 0;
        hata = 0;
        do {
            if(hata) {ERROR2;printf("Wrong Input.");}
            if(!hata) printf("\033[K");
            hata = 1;
            printf("\033[6HEnter radius and height : \033[J\n");
            p1,p2 = 0;
            if(printf("Radius : ") && !scanf("%d",&p1) || p1 <= 0) {FLUSH continue;}
            if(printf("Height : ") && !scanf("%d",&p2) || p2 <= 0) {FLUSH continue;}
            sonuc = 1;
        } while (sonuc <= 0);
        switch (Calculator) {
            case Area:
                printf("\e[1H\033[32mANSWER\033[K\033[0;33m\nBase Area\033[0m : %0.*lf ,\033[0;33m Lateral Area \033[0m: %0.*lf , \033[0;33mSurface Area\033[0m : %0.*lf",pre,PI*p1*p1,pre,2*PI*p1*p2,pre,2*PI*p1*(p1+p2));
                return 1;
            case Perimeter:
                print(2 * PI * p1);
                return 1;
            case Volume:
                print(p1 * p1 * PI * p2);
        }
    }
    return -1;
}
#pragma endregion Methods

int calculate (int (*shape)(), int (*calc)()){
    enum Shapes s = shape();
    while(s) {
        enum Calculators c = calc();
        if(c == -1) return 1;
        while(c) {
            switch (s) {
                case Triangle:
                    if(calc_triangle(c)>0) return -1;
                    break;
                case Quadrilateral:
                    if(calc_quadrilateral(c)>0) return -1;
                    break;
                case Circle:
                    if(calc_circle(c)>0) return -1;
                    break;
                case Pyramid:
                    if(calc_pyramid(c)>0) return -1;
                    break;
                case Cylinder:
                    if(calc_cylinder(c)>0) return -1;
                    break;
                default:
                    break;
            }
            c = calc();
            if(c == -1) return 1;
        }
        break;
    }
    printf("Goodbye :d\n");
    return 0;
}

int main(){
    printf("\033[1HWelcome");
    while(calculate(select_shape,select_calc)) continue;
    return 0;
}