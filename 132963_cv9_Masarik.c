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

void uloha91()
{
    Navstevnik *navstevnici = NULL; // Start with a NULL pointer for the dynamic array
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

        // Look for an existing record with this name
        int i;
        for (i = 0; i < pocet_navstevnikov; i++)
        {
            if (strcmp(meno, navstevnici[i].meno) == 0)
            {
                navstevnici[i].pocet_navstev++;
                break;
            }
        }

        // If no existing record is found, create a new one
        if (i == pocet_navstevnikov)
        {
            // Reallocate memory to add a new visitor
            navstevnici = realloc(navstevnici, (pocet_navstevnikov + 1) * sizeof(Navstevnik));
            if (navstevnici == NULL)
            {
                fprintf(stderr, "Error allocating memory!\n");
                exit(1);
            }

            // Initialize the new visitor
            strcpy(navstevnici[pocet_navstevnikov].meno, meno);
            navstevnici[pocet_navstevnikov].pocet_navstev = 1;
            pocet_navstevnikov++;
        }
    }

    // Find the highest number of visits
    int max_navstev = 0;
    for (int i = 0; i < pocet_navstevnikov; i++)
    {
        if (navstevnici[i].pocet_navstev > max_navstev)
        {
            max_navstev = navstevnici[i].pocet_navstev;
        }
    }

    // Print visitors with the highest number of visits
    printf("\nNavstevnici, ktori chodia do kina najcastejsie:\n");
    for (int i = 0; i < pocet_navstevnikov; i++)
    {
        if (navstevnici[i].pocet_navstev == max_navstev)
        {
            printf("%s (%d navstev)\n", navstevnici[i].meno, navstevnici[i].pocet_navstev);
        }
    }

    // Free the allocated memory
    free(navstevnici);
}

int main()
{
    uloha91();
}