#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAVSTEVNICI 100

/**
 * @author Filip Masarik
 * @id 132963
 */

typedef struct
{
    char meno[50];
    int pocet_navstev;
} Navstevnik;

int magicky(const int square[4][4], int size)
{
    int i = 0;
    int j = 0;
    int subsum = 0;
    int negsubsum = 0;
    int sum = 0;
    for (i = 0; i < size; i++)
    {
        subsum = 0;
        for (j = 0; j < size; j++)
        {
            if (i == 0)
            {
                sum += square[i][j];
            }
            subsum += square[i][j];
        }
        if (subsum != sum)
        {
            return 0;
        }
    }

    for (i = 0; i < size; i++)
    {
        subsum = 0;
        negsubsum = 0;
        for (j = 0; j < size; j++)
        {
            if (i == j)
            {
                subsum += square[i][i];
            }
            if (size - 1 - j == i)
            {
                negsubsum += square[i][size - 1 - j];
            }
        }
        if (subsum != sum && j == size - 1 && negsubsum != sum)
        {
            return 0;
        }
    }

    return 1;
}

void Uloha71()
{
    int n;
    const int N = 4;
    const int Narray[4][4] = {
        {16, 3, 2, 13},
        {5, 10, 11, 8},
        {9, 6, 7, 12},
        {4, 15, 14, 1},
    };

    scanf("%d", &n);

    if (n > N)
    {
        printf("Mimo rozsah\n");
        return;
    }

    if (magicky(Narray, N) == 1)
    {
        printf("Je magicky\n");
    }
    else
    {
        printf("Neni magicky\n");
    }
}

void Uloha72()
{
    int N;
    scanf("%d", &N);

    char matrix[N][N];
    char currentChar = 'a';
    int i = 0, j = 0;

    for (i = 0; i < N; i++)
    {
        if (i % 2 == 0)
        {
            for (j = 0; j < N; j++)
            {
                matrix[i][j] = currentChar;
                currentChar++;
                if (currentChar > 'z')
                    currentChar = 'a';
            }
        }
        else
        {
            for (j = N - 1; j >= 0; j--)
            {
                matrix[i][j] = currentChar;
                currentChar++;
                if (currentChar > 'z')
                    currentChar = 'a';
            }
        }
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void Uloha73()
{
    int pocet_retazcov;

    printf("Zadajte počet reťazcov: ");
    scanf("%d", &pocet_retazcov);

    char **pole_retazcov = (char **)malloc(pocet_retazcov * sizeof(char *));

    for (int i = 0; i < pocet_retazcov; i++)
    {
        printf("Zadajte %d. reťazec: ", i + 1);
        char buffer[100];
        scanf("%s", buffer);

        // Alokácia pamäte pre aktuálny reťazec
        pole_retazcov[i] = (char *)malloc(strlen(buffer) + 1); // +1 pre nulový znak
        strcpy(pole_retazcov[i], buffer);
    }

    // Vypísanie poľa reťazcov
    printf("\nVami zadané reťazce:\n");
    for (int i = 0; i < pocet_retazcov; i++)
    {
        printf("%s\n", pole_retazcov[i]);
    }

    // Uvoľnenie pamäte
    for (int i = 0; i < pocet_retazcov; i++)
    {
        free(pole_retazcov[i]);
    }
    free(pole_retazcov);
}

void Uloha74()
{
    Navstevnik navstevnici[MAX_NAVSTEVNICI];
    int pocet_navstevnikov = 0;
    char meno[50];

    printf("Zadajte mena navstevnikov (zastavte zadavanie znakom '#'):\n");

    while (1)
    {
        scanf("%s", meno);
        if (strcmp(meno, "#") == 0)
        {
            break;
        }

        // Hladanie, ci uz existuje zaznam o tomto mene
        int i;
        for (i = 0; i < pocet_navstevnikov; i++)
        {
            if (strcmp(meno, navstevnici[i].meno) == 0)
            {
                navstevnici[i].pocet_navstev++;
                break;
            }
        }

        // Ak neexistuje zaznam, vytvorime novy
        if (i == pocet_navstevnikov)
        {
            strcpy(navstevnici[pocet_navstevnikov].meno, meno);
            navstevnici[pocet_navstevnikov].pocet_navstev = 1;
            pocet_navstevnikov++;
        }
    }

    // Vyhladanie najvacsieho poctu navstev
    int max_navstev = 0;
    for (int i = 0; i < pocet_navstevnikov; i++)
    {
        if (navstevnici[i].pocet_navstev > max_navstev)
        {
            max_navstev = navstevnici[i].pocet_navstev;
        }
    }

    // Vypis mien s najvacsim poctom navstev
    printf("\nNavstevnici, ktori chodia do kina najcastejsie:\n");
    for (int i = 0; i < pocet_navstevnikov; i++)
    {
        if (navstevnici[i].pocet_navstev == max_navstev)
        {
            printf("%s (%d navstev)\n", navstevnici[i].meno, navstevnici[i].pocet_navstev);
        }
    }
}

int main()
{
    Uloha71();

    Uloha72();

    Uloha73();

    Uloha74();
}