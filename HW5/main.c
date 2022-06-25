#include <stdio.h>
#include <math.h>

#pragma region Enums
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

#pragma region Define
    #define PI 3.14
    #define dec 2 // Ekrana basılacak sayının kapyalacağı minumum alan. Şu anda efektiv değil.
    #define pre 2 // Virgülden sonra kaç basamağın görüneceği.

    #define up_size  4 // Üst bölmenin boyutu
    #define mid_size 8 // Orta bölmenin boyutu
    #define bottom_size 2 // Alt bölmenin boyutu. Efektiv değil

    #define print_up printf("\e[%dH\e[1J\e[K\e[1H",up_size); // Üst kısmı temizliyor ve imceli üst kısma yazacak şekilde ayarlıyor.
    #define print_mid printf("\e[%dH",up_size+1); for(int i = 0; i < mid_size; i++) printf("\e[K\n"); printf("\e[%dH",up_size+1);
    // Orta kısmın temizliğinden sorumlu ve imleci orta kısma ayarlıyor.

    #define answer print_up printf("\e[0;1;33mANSWER\e[0m\n"); // Üst kısma cevap yazmayı sağlıyor.

    void print_location(enum Shapes i){ // Alt kısım ilk bilgilendirme çubuğunun ve ismin yazılmasını sağlıyor.
        printf("\e[%dH\e[0;45m",up_size+mid_size+2);
        switch (i){
            case Triangle:          printf("    Triangle   "); break;
            case Quadrilateral:     printf(" Quadrilateral "); break;
            case Circle:            printf("     Circle    "); break;
            case Pyramid:           printf("    Pyramid    "); break;
            case Cylinder:          printf("    Cylinder   "); break;
            case 0:                 printf("   Main Menu   "); break;
            default: break;
        }
        printf("\e[0m");
    }
    void print_location2(enum Calculators j){ // Alt kısım ikinici bilgilendirme çubuğunu yazıyor ve alt kısmı temizliyor.
        printf("\e[%d;%dH\e[0;44m",up_size+mid_size+2,16);
        switch (j){
            case Area:          printf("      Area     "); break;
            case Perimeter:     printf("    Perimeter  "); break;
            case Volume:        printf("     Volume    "); break;
            default:    printf("\e[0m\e[K\n\e[K");break;
        }
        printf("\e[%dH\e[48;2;22;159;204;38;2;247;218;0m Emirhan Altunel 200104004035 ",up_size+mid_size+3);
        printf("\e[0m");
    }

    void flush(){ // fflush her zaman çalışmadığı için kendim yazmak zorunda kaldım.
        int c;
        do {
            c = getchar();
        } while (c != '\n' && c != EOF);
    }
#pragma endregion

#pragma region Error_Messages
    #define ERROR print_up printf("\e[0;31mERROR\e[0m\n"); flush(); // Ana şablon

    // Şekil seçme hata Mesajları
    #define INVALID_SHAPE_INPUT {ERROR printf("You have entered invalid input. Error code : 1"); continue;}
    #define NON_SHAPE_INPUT {ERROR printf("You have entered non-listed input. Error code : 2"); continue;}

    // Hesaplama hata mesajları
    #define INVALID_CALCULATOR_INPUT {ERROR printf("You have entered invalid input. Error code : 3"); continue;}
    #define NON_CALCULATOR_INPUT {ERROR printf("You have entered non-listed input. Error code : 4"); continue;}

    // Şekil hataları
    #define INVALID_INPUT {ERROR printf("You have entered invalid input. Error code : 5"); continue;}
    #define INVALID_SHAPE {ERROR printf("You can't create a shape like that. Error code : 6"); continue;}
    #define VOLUME_OF_2D {ERROR printf("You cannot find volume of a 2d shape. Error code : 7"); return 0;}
    #define SLANT_HEIGHT_CANNOT_BE_SMALLER {ERROR printf("Slant height cannot be smaller than base side/2. Error code : 8"); continue;}
#pragma endregion

#pragma region Selection_Methods
    int select_shape(){
        print_location(0);
        print_location2(0);
        enum Shapes selection = Triangle;
        while (selection >= Triangle){
            print_location(0);
            print_mid
            printf("Select a shape\n");
            printf("1. Triangle\n");
            printf("2. Quadrilateral\n");
            printf("3. Circle\n");
            printf("4. Pyramid\n");
            printf("5. Cylinder\n");
            printf("0. Exit\n");
            printf("Input : \e[K");

            // Yanlış input engelleme
            if (scanf("%u",&selection) != 1) INVALID_SHAPE_INPUT
            if (selection >= Triangle && selection <= Cylinder || !selection) { 
                print_up
                print_location(selection); 
                return selection;
            }
            else NON_SHAPE_INPUT
        }
    }

    int select_calc(){
        print_location2(0);
        enum Calculators selection = Area;
        while (selection >= Area){
            print_mid
            printf("Select a calculator\n");
            printf("1. Area\n");
            printf("2. Perimeter\n");
            printf("3. Volume\n");
            printf("4. Upper Menu\n");
            printf("0. Exit\n");
            printf("Input : \e[K");

            // Yanlış input engelleme
            if (scanf("%u",&selection) != 1) INVALID_CALCULATOR_INPUT
            if (selection >= Area && selection <= Volume || !selection || selection == 4) {
                print_up 
                print_location2(selection);
                return selection;
            }
            else NON_CALCULATOR_INPUT 
        }
    }
#pragma endregion

#pragma region Calculation_Methods
    int calc_triangle(enum Calculators c){
        int p1 = 0,p2 = 0,p3 = 0; // 3 input
        double s = 0, ans = 0; // 1 temp, 1 output

        switch (c){
            case Area:
                while(1){
                    print_mid
                    
                    printf("Please enter three sides of the Triangle\n");

                    // Hem yazıyı yazıyor hem de yanlış input gelirse hata mesajı veriyor
                    printf("Side 1 : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT 
                    printf("Side 2 : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT
                    printf("Side 3 : "); if(!scanf("%d",&p3) || p3 < 0) INVALID_INPUT
                    
                    s = (p1 + p2 + p3) / 2.0; 
                    ans = s * (s - p1) * (s - p2) * (s - p3);

                    if (ans < 0) INVALID_SHAPE // Üçgen olma kuralını burada kontrol edebiliyoruz. 
                    // Kenarlarından birini 0 olma koşulunu da kabul ediyorum burada
                    
                    else {answer printf("Area of the Triangle : %*.*f",dec,pre,sqrt(ans));}
                    return 1;
                }
            case Perimeter:
                while(1){
                    print_mid
                    printf("Please enter three sides of the Triangle\n");

                    printf("Side 1 : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Side 2 : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT
                    printf("Side 3 : "); if(!scanf("%d",&p3) || p3 < 0) INVALID_INPUT

                    s = (p1 + p2 + p3) / 2.0;
                    ans = s * (s - p1) * (s - p2) * (s - p3);

                    if (ans < 0) INVALID_SHAPE
                    else {answer printf("Perimeter of the Triangle : %*.*f",dec,pre,s*2);}
                    return 1;
                }
            case Volume:
                VOLUME_OF_2D
            default: break;
        }
        return 0;
    }

    int calc_quadrilatera(enum Calculators c){
        int p1 = 0,p2 = 0,p3 = 0,p4 = 0; // 4 input
        double s = 0, ans = 0; // 1 temp, 1 output

        switch (c){
            case Area:
                while(1){
                    print_mid
                    printf("Please enter four sides of the Quadrilatera\n");

                    printf("Side 1 : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Side 2 : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT
                    printf("Side 3 : "); if(!scanf("%d",&p3) || p3 < 0) INVALID_INPUT
                    printf("Side 4 : "); if(!scanf("%d",&p4) || p4 < 0) INVALID_INPUT

                    s = (p1 + p2 + p3 + p4) / 2.0;
                    ans = (s - p1) * (s - p2) * (s - p3) * (s - p4);

                    if (ans < 0) INVALID_SHAPE // Dörtgen olma koşuluna bakılıyor ve yine 0 kabul ediliyor
                    else {answer printf("Area of the Quadrilater : %*.*f",dec,pre,sqrt(ans));}
                    return 1;
                }
            case Perimeter:
                while(1){
                    print_mid
                    printf("Please enter four sides of the Quadrilatera\n");

                    printf("Side 1 : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Side 2 : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT
                    printf("Side 3 : "); if(!scanf("%d",&p3) || p3 < 0) INVALID_INPUT
                    printf("Side 4 : "); if(!scanf("%d",&p4) || p4 < 0) INVALID_INPUT

                    s = (p1 + p2 + p3 + p4) / 2.0;
                    ans = (s - p1) * (s - p2) * (s - p3) * (s - p4);

                    if (ans < 0) INVALID_SHAPE
                    else {answer printf("Perimeter of the Quadrilatera : %*.*f",dec,pre,s*2);}
                    return 1;
                }
            case Volume:
                VOLUME_OF_2D
            default: break;
        }
        return 0;
    }

    int calc_circle(enum Calculators c){
        int p1 = 0; // 1 input
        double ans = 0; // 1 output

        switch (c){
            case Area:
                while(1){
                    print_mid
                    printf("Please enter the radius of the Circle\n");

                    printf("Radius : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT

                    ans = PI * p1 * p1;

                    answer printf("Area of the Circle : %*.*f",dec,pre,ans);
                    return 1;
                }
            case Perimeter:
                while(1){
                    print_mid
                    printf("Please enter the radius of the Circle\n");

                    printf("Radius : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT

                    ans = 2 * PI * p1;

                    answer printf("Perimeter of the Circle : %*.*f",dec,pre,ans);
                    return 1;
                }
            case Volume:
                VOLUME_OF_2D
            default: break;
        }
        return 0;
    }

    int calc_pyramid(enum Calculators c){
        int p1 = 0,p2 = 0; // 2 input
        double s = 0, ans = 0, ans2 = 0, ans3 = 0; // 1 temp, 3 output

        switch (c){
            case Area:
                while(1){
                    print_mid
                    printf("Please enter base side and slant height of the Pyramid\n");

                    printf("Base Side    : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Slant Height : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT

                    s = p2-p1/2.0;

                    if(s < 0) SLANT_HEIGHT_CANNOT_BE_SMALLER

                    ans = p1 * p1;
                    ans2 = 2 * p1 * p2;
                    ans3 = ans + ans2;

                    answer printf("Area of the Pyramid > \nBase Surface : %*.*f, Lateral Surface : %*.*f, Surface : %*.*f",dec,pre,ans,dec,pre,ans2,dec,pre,ans3);
                    return 1;
                }
            case Perimeter:
                while(1){
                    print_mid
                    printf("Please enter base side and \"slant\" height of the Pyramid\n");
                    printf("Base Side    : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Slant Height : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT

                    s = p2-p1/2.0;

                    if(s < 0) SLANT_HEIGHT_CANNOT_BE_SMALLER 

                    ans = 4 * p1;
                    ans2 = sqrt((p1 / 2.0)*(p1 / 2.0) + p2 * p2) * 4;
                    ans3 = ans + ans2;

                    // Burada tam ne yapacağımdan emin olmadım o yüzden bu şekilde çıktı verdim.
                    answer printf("Perimeter of the Pyramid > \nBase : %*.*f, Lateral : %*.*f, Total : %*.*f",dec,pre,ans,dec,pre,ans2,dec,pre,ans3);
                    return 1;
                }
            case Volume:
                while(1){
                    print_mid
                    printf("Please enter base side and height of the Pyramid\n");

                    printf("Base Side : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Height    : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT

                    ans = 1.0 / 3.0 * p1 * p1 * p2;

                    answer printf("Volume of the Pyramid : %*.*f",dec,pre,ans);
                    return 1;
                }
            default: break;
        }
        return 0;
    }

    int calc_cylinder(enum Calculators c){
        int p1 = 0,p2 = 0; // 2 input
        double s = 0, ans = 0, ans2 = 0, ans3 = 0; // 1 temp , 3 output

        switch (c){
            case Area:
                while(1){
                    print_mid
                    printf("Please enter base radius and height of the Cyclinder\n");

                    printf("Radius : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Height : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT

                    ans = PI * p1 * p1;
                    ans2 = 2 * p1 * PI * p2;
                    ans3 = ans + ans + ans2;

                    answer printf("Area of the Cylinder > \nBase Surface : %*.*f, Lateral Surface : %*.*f, Surface : %*.*f",dec,pre,ans,dec,pre,ans2,dec,pre,ans3);
                    return 1;
                }
            case Perimeter:
                while(1){
                    print_mid
                    printf("Please enter base radius and height of the Cyclinder\n");

                    printf("Radius : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Height : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT

                    ans = 2 * PI * p1;

                    answer printf("Perimeter of the Base of the Cyclinder %*.*f",dec,pre,ans);
                    return 1;
                }
            case Volume:
                while(1){
                    print_mid
                    printf("Please enter base radius and height of the Cyclinder\n");

                    printf("Radius : "); if(!scanf("%d",&p1) || p1 < 0) INVALID_INPUT
                    printf("Height : "); if(!scanf("%d",&p2) || p2 < 0) INVALID_INPUT

                    ans = PI * p1 * p1 * p2;
                    
                    answer printf("Volume of the Pyramid : %*.*f",dec,pre,ans);
                    return 1;
                }
            default: break;
        }
        return 0;
    }

#pragma endregion

#pragma region Main
int calculate (int (*shape)(), int (*calc)()){
    enum Shapes s = shape();
    if (s == 0) return 0;

    while(1) {
        enum Calculators c = calc();
        if (c == 4) return 1;
        else if (c == 0) return 0;
        switch (s){
            case Triangle: if(!calc_triangle(c)) continue; break;
            case Quadrilateral: calc_quadrilatera(c); break;
            case Circle: calc_circle(c); break;
            case Pyramid: calc_pyramid(c); break;
            case Cylinder: calc_cylinder(c); break;
            default: break;
        }
        return 1;
    }
    return 0;
}

int main(){
    while(calculate(select_shape,select_calc));
    printf("\e[%dHGoodbye.\n\e[0m",up_size+mid_size+5);
    return 0;
}
#pragma endregion