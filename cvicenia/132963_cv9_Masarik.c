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

typedef struct Node
{
    char meno[50];
    int pocet_navstev;
    struct Node *next;
} Node;

void hladaj_max(Navstevnik *navstevnici, int pocet_navstevnikov) // uloha 9.2
{
    // Inicializácia premenných
    int max_navstev = 0;
    int i = 0;
    char najcastejsi_navstevnik[50];

    // Nájdenie maximálneho počtu návštev a príslušného mena
    for (i = 0; i < pocet_navstevnikov; i++)
    {
        if (navstevnici[i].pocet_navstev > max_navstev)
        {
            max_navstev = navstevnici[i].pocet_navstev;
            strcpy(najcastejsi_navstevnik, navstevnici[i].meno);
        }
    }

    // Vypísanie výsledku
    printf("Najcastejsi navstevnik: %s (%d navstev)\n", najcastejsi_navstevnik, max_navstev);
}

void uvolni_zoznam(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

Node *hladaj_maxLL(Node *head)
{
    if (head == NULL)
    {
        return NULL; // Return NULL if the list is empty
    }
    Node *max_node = head;
    Node *current = head;
    while (current != NULL)
    {
        if (current->pocet_navstev > max_node->pocet_navstev)
        {
            max_node = current;
        }
        current = current->next;
    }
    return max_node;
}

void uloha91()
{
    Navstevnik *navstevnici = NULL; // Start with a NULL pointer for the dynamic array
    int pocet_navstevnikov = 0;
    char meno[50];
    int i;

    printf("Zadajte mena navstevnikov (zastavte zadavanie znakom '#'):\n");

    while (1)
    {
        scanf("%s", meno);
        if (strcmp(meno, "#") == 0)
        {
            break;
        }

        // Look for an existing record with this name
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

    hladaj_max(navstevnici, pocet_navstevnikov); // na vypisanie najcastejsieho navstevnika

    // alebo mozeme pouzit aj tento kod na vypisanie vsetkych
    // int max_navstev = 0;
    // for (int i = 0; i < pocet_navstevnikov; i++)
    // {
    //     if (navstevnici[i].pocet_navstev > max_navstev)
    //     {
    //         max_navstev = navstevnici[i].pocet_navstev;
    //     }
    // }
    //
    // printf("\nNavstevnici, ktori chodia do kina najcastejsie:\n");
    // for (int i = 0; i < pocet_navstevnikov; i++)
    // {
    //     if (navstevnici[i].pocet_navstev == max_navstev)
    //     {
    //         printf("%s (%d navstev)\n", navstevnici[i].meno, navstevnici[i].pocet_navstev);
    //     }
    // }

    // Free the allocated memory
    free(navstevnici);
}

void uloha93()
{
    Node *head = NULL;
    Node *tail = NULL;
    char meno[50];

    printf("Zadajte mena navstevnikov (zastavte zadavanie znakom '#'):\n");

    while (1)
    {
        scanf("%s", meno);
        if (strcmp(meno, "#") == 0)
        {
            break;
        }

        Node *current = head;
        int found = 0;
        while (current != NULL)
        {
            if (strcmp(current->meno, meno) == 0)
            {
                current->pocet_navstev++;
                found = 1;
                break;
            }
            current = current->next;
        }

        if (!found)
        {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (new_node == NULL)
            {
                printf("Error: Could not allocate memory.\n");
                uvolni_zoznam(head);
                return;
            }
            strcpy(new_node->meno, meno);
            new_node->pocet_navstev = 1;
            new_node->next = NULL;

            if (head == NULL)
            {
                head = new_node;
                tail = new_node;
            }
            else
            {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }

    Node *max_node = hladaj_maxLL(head);
    if (max_node != NULL)
    {
        printf("\nNavstevnik s najvacsim poctom navstev:\n");
        printf("%s (%d navstev)\n", max_node->meno, max_node->pocet_navstev);
    }

    uvolni_zoznam(head);

    return;
}

int main()
{
    uloha93();
}