#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Filip Masarik
 */

void nacitaj(double *a, double *b)
{
    scanf("%lf %lf", a, b);
}

void obsahObvod(double a, double b, double *obsah, double *obvod)
{
    *obsah = a * b;
    *obvod = 2 * (a + b);
}

void vymenUkazovatele(int **a, int **b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}

int delitele(int x[], int pocetX, int **y, int k)
{
    int pocetY = 0;
    for (int i = 0; i < pocetX; i++)
    {
        if (k % x[i] == 0)
        {
            (*y)[pocetY] = x[i];
            pocetY++;
        }
    }
    return pocetY;
}

int alokuj_1D_pole(int **pole, int pocetPrvkov)
{
    *pole = (int *)malloc(pocetPrvkov * sizeof(int));
    if (*pole == NULL)
    {
        printf("Chyba alokovania pamati\n");
        return -1;
    }
    return 0;
}

int nacitaj_1D_pole(int *pole, int pocetPrvkov)
{
    for (int i = 0; i < pocetPrvkov; i++)
    {
        scanf("%d", &pole[i]);
    }
    return 0;
}

void vypis_1D_pole(int *pole, int pocetPrvkov)
{
    printf("%d", pole[0]);
    for (int i = 1; i < pocetPrvkov; i++)
    {
        printf(", %d", pole[i]);
    }
    printf("\n");
}

void uvolni_1D_pole(int **pole)
{
    if (*pole == NULL)
    {
        return;
    }
    free(*pole);
    *pole = NULL;
}

void max_min(int *pole, int pocetPrvkov, int **max, int **min)
{
    if (pocetPrvkov <= 0)
    {
        printf("Array is empty.\n");
        return;
    }

    *max = &pole[0];
    *min = &pole[0];
    for (int i = 1; i < pocetPrvkov; i++)
    {
        if (&pole[i] > *max)
        {
            *max = &pole[i];
        }
        if (&pole[i] < *min)
        {
            *min = &pole[i];
        }
    }
}

void Uloha51()
{
    printf("\nUloha 5.1\n");

    double a, b, obsah, obvod;
    nacitaj(&a, &b);
    obsahObvod(a, b, &obsah, &obvod);
    printf("Obsah: %.3f\n", obsah);
    printf("Obvod: %.3f\n", obvod);
}

void Uloha52()
{
    int num521, num522;
    printf("\nUloha 5.2\n");
    scanf("%d %d", &num521, &num522);

    if (num521 > num522)
    {
        printf("Cislo %d je väčšie\n", num521);
    }
    else if (num521 < num522)
    {
        printf("Cislo %d je väčšie\n", num522);
    }
    else
    {
        printf("Cisla su rovnake\n");
    }
}

void Uloha53()
{
    int a,b,c;
    scanf("%d %d %d", &a, &b, &c);
    double D = b*b - 4*a*c;

    int koreneCount = 1;

    if(D >= 0)
    {
        double x1 = (-b + sqrt(D)) / (2*a);
        double x2 = 0;

        if(D != 0)
        {
            koreneCount = 2;
            x2 = (-b - sqrt(D)) / (2*a);
        }

        printf("pocet korenov kvadratickej rovnice: %d\n", koreneCount);
        printf("Prvy koren ma hodnotu: %.3f\n", x1);
        printf("Druhy koren ma hodnotu: %.3f\n", x2);
    }
    else
    {
        printf("Rovnica nema realne korene\n");
    }
}

void Uloha54()
{
    int *a, *b;
    a = (int *)malloc(sizeof(int));
    b = (int *)malloc(sizeof(int));
    *a = 10;
    *b = 14;

    printf("p_a: %p %d\np_b: %p %d\n", (void*)&a, *a, (void*)&b, *b);
    vymenUkazovatele(&a, &b);
    printf("p_a: %p %d\np_b: %p %d\n", (void*)&a, *a, (void*)&b, *b);
}

void Uloha55()
{
    int x[10] = {4, 7, 10, 2, 3, 9, 6, 5, 8, 12};
    int *y = malloc(10 * sizeof(int));
    int pocetX = 10;
    int pocetY = delitele(x, pocetX, &y, 24);
    printf("pocetY: %d\n", pocetY);
    printf("y: {");
    for (int i = 0; i < pocetY; i++)
    {
        printf("%d", y[i]);
        if (i < pocetY - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

void Uloha56()
{
    int mSize;
    int *pole = NULL;
    int *max = (int *)malloc(sizeof(int));
    int *min = (int *)malloc(sizeof(int));

    scanf("%d", &mSize);

    if (alokuj_1D_pole(&pole, mSize) == -1)
    {
        return;
    }

    nacitaj_1D_pole(pole, mSize);

    vypis_1D_pole(pole, mSize);
    max_min(pole, mSize, &max, &min);
    printf("Max: %d\n", *max);
    printf("Min: %d\n", *min);
    uvolni_1D_pole(&pole);
}

int main()
{
    // Uloha51();

    // Uloha52();

    // Uloha53();

    // Uloha54();

    // Uloha55();

    // Uloha56();
}