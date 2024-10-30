#include <stdio.h>
int main() {
    //uloha 1.1
    printf("\nUloha 1.1\n");
    printf("Hello, World!\n");

    //uloha 1.2
    char a;
    printf("\nUloha 1.2\n");
    printf("Zadajte znak: ");
    scanf("%c", &a);
    printf("Zadali ste: ");
    printf("%c\n", a);


    //uloha 1.3
    printf("\nUloha 1.3\n");
    int c1, c2;

    printf("Zadajte dve cisla: ");
    scanf("%d %d", &c1, &c2);

    printf("Sucin nacitanych cisel: %d\n", c1*c2);
    printf("Sucet nacitanych cisel: %d\n", c1+c2);
   

    //uloha 1.4
    printf("\nUloha 1.4\n");
    int _cislo;

    printf("Zadajte cislo: ");
    scanf("%d", &_cislo);

    printf("Druha mocnina cisla %d: %d\n", _cislo, _cislo*_cislo);    

    //uloha 1.5
    printf("\nUloha 1.5\n");
    int _cislo15;

    printf("Zadajte polomer kruhu: ");
    scanf("%d", &_cislo15);

    float result15 = 2 * 3.14 * _cislo15;
    printf("Obvod kruhu s polomerom %lf: %.2f\n", _cislo15, result15);


    //uloha 1.6
    printf("\nUloha 1.6\n");
    printf("\\*/Toto je \"backslash\": '\\'\*/\n");

    //uloha 1.7
    printf("\nUloha 1.7\n");

    double _cislo17;
    printf("Zadajte cenu bez dane: ");
    scanf("%lf", &_cislo17);
    double dan = 1.23;
    //po novom 23%
    printf ("S danou: %lf\n", _cislo17*dan);

    //uloha 1.8
    printf("\nUloha 1.8\n");
    printf("Zadajte rozmery kvadra: ");

    double a18, b18, c18;
    scanf("%lf %lf %lf", &a18, &b18, &c18);
    printf("Objem kvadra: %.3lf\n", a18*b18*c18);

    printf("konec\n");
    return 0;
}
