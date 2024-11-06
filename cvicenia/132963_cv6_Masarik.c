#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Filip Masarik 
 */

void reverse_array(char *array, int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        int temp = array[i];
        array[i] = array[n - i - 1];
        array[n - i - 1] = temp;
    }
}

void alokuj_2d_pole(int **pole, int n, int m)
{
    *pole = (int *)malloc((n*m) * sizeof(int));
}

void vypis_2d_pole(int *pole, int n, int m)
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", pole[i*m+j]);
        }
        printf("\n");
    }
}

void Uloha61()
{
    printf("Uloha 6.1\n");
    int n;
    scanf("%d", &n);
    char *pole = (char *)malloc(n * sizeof(char));
    scanf("%s", pole);

    reverse_array(pole, n);
    for(int i = 0; i < n; i++)
    {
        printf("%c", pole[i]);

    }
    printf("\n");
}

void Uloha62()
{
    printf("Uloha 6.2\n");
    int n = 255;

    char *fileName = (char *)malloc(n * sizeof(char));      
    scanf("%s", fileName);

    char pismena[52];
    int pisemanCount[26];

    for(int i = 0; i < 26; i++)
    {
        pismena[i+26] = 'a' + i;
        pismena[i] = 'A' + i;
        pisemanCount[i] = 0;
    }

    FILE *file = fopen(fileName, "r");

    if(file == NULL)
    {
        printf("Subor sa nepodarilo otvorit\n");
        return;
    }
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        for (int i = 0; i < 26; i++)
        {
            if (c == pismena[i] || c == pismena[i+26])
            {
                pisemanCount[i]++;
                continue;
            }
        }
    }

    for(int i = 0; i < 26; i++)
    {
        if(pisemanCount[i] != 0)
        {
            if(pisemanCount[i] > 100){pisemanCount[i] = 99;}
            printf("%c : %d\n", pismena[i], pisemanCount[i]);
        }
    }

    fclose(file);
    
}

void Uloha63()
{
    printf("Uloha 6.3\n");
    int n, m;

    scanf("%d", &n);
    scanf("%d" , &m);

    int size = m*n;
    int *pole;
    alokuj_2d_pole(&pole, n, m);

    for (int i = 0; i < n*m; i++)
    {
        int temp;
        scanf("%d", &temp);
        pole[i] = temp;
    }

    vypis_2d_pole(pole, n, m);

    free(pole);
}

int main()
{
    Uloha61();

    Uloha62();

    Uloha63();
}