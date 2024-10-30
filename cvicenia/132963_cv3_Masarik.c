#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

double mocnina(int a, int n)
{
    int base = a;

    for(int i = 1; i < n; i++) 
    {
        a *= base;
    }
    return a;
}

double nasobok(int a, int n)
{
    return a*n;
}

int main()
{
    //uloha 3.1
    printf("\nUloha 3.1\n");
    int num31, sum31 = 0;
    scanf("%d", &num31);

    for(int i = 0; i < num31; i++) 
    {
        int num311;
        scanf("%d", &num311);
        if(num311 > 0 && num311 <= 100) 
        {
            sum31 ++;
        }
    }
    printf("%d\n", sum31);

    //uloha 3.2
    printf("\nUloha 3.2\n");
    int num32;
    while (true)
    {
        scanf("%d", &num32);
        if(num32 == 0) 
        {
            break;
        }
        if(num32 > 0) 
        { 
            break;
        } 
        printf("Zadajte nezaporne cele cislo\n");
    }

    if(num32 == 0)
    {
        printf("0\n");
    } 
    else if(num32 == 1) 
    {
        printf("1\n");
    } 
    int result = 1;
    for(int i = 1; i <= num32; i++) 
    {
        result *= i;
    }
    printf("%d\n", result);

    //uloha 3.3
    printf("\nUloha 3.3\n");
    int f, g;
    scanf("%d %d", &f, &g);

    for(int i = f; i <= g; i++) 
    {
        if(i % 3 == 0) 
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    //uloha 3.4
    printf("\nUloha 3.4\n");
    int num34;
    scanf("%d", &num34);
    if(num34 < 1 || num34 > 15) 
    {
        printf("Zadajte cislo v intervale <1, 15>\n");
    } 
    else
    {
        for(int i = num34; i >= 1; i--)
        {
            printf("%d: ", num34-i+1);
            for(int j = i; j >= 1; j--)
            {
                printf("%d ", j);
            }
            printf("\n");
        }
    }

    //uloha 3.5
    printf("\nUloha 3.5\n");

    int num35;
    scanf("%d", &num35);

    for(int i = 0; i < num35; i++) 
    {
        for(int j = 0; j < num35; j++)
        {
            if(j == i || j == num35 - i - 1 || j == num35/2) 
            {
                printf("X");
            } 
            else 
            {
                printf("-");
            } 
           
        }
        printf("\n");
    }

    //uloha 3.6
    printf("\nUloha 3.6\n");
    double a36;
    int n36;

    scanf("%lf %d", &a36, &n36);

    for(int i = 1; i <= n36; i++) 
    {
        printf("%g^%d = %g \n", a36, i, mocnina(a36, i));
    }

    //uloha 3.7
    printf("\nUloha 3.7\n");
    double a37;
    int n37;

    scanf("%lf %d", &a37, &n37);

    for(int i = 1; i <= n37; i++) 
    {
        printf("%g * %d = %g \n", a37, i, nasobok(i, a37));
    }

    //uloha 3.8
    printf("\nUloha 3.8\n");

    FILE* fptr = fopen("cisla.txt", "r");
    char buf[100];

    double result38 = 0;
    char *endptr1;  
    if(fptr == NULL) 
    {
        printf("Neexistuje subor: cisla.txt ):\n");
        return 1;
    }
    while(true)
    {
        double num38;
        fgets(buf, 100, fptr);

        num38 = strtod(buf, &endptr1);  
        //num38 = atof(buf);
        result38 += num38;
        printf("%g\n", num38);


        num38 = 0;
        if(feof(fptr)) 
        {
            break;
        }
    }
    printf("Sucet: %g\n", result38);

    fclose(fptr);
}
