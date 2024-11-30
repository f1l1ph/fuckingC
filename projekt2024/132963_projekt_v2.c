#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Filip Masarik
 * @id 132963
 */

struct data
{
    int Hodnota_ID;
    int Hodnota_Zn;
    int Hodnota_1;
    double Hodnota_2;
};

struct parse
{
    // char *Poznamka_ID;
    int Poznamka_N1;
    int Poznamka_Hodina;
    int Poznamka_Minuta;
    int Poznamka_T;
};

struct linkedList
{
    int id;
    struct data dataList;
    struct parse parseList;
    struct linkedList *next;
};

void setLines(FILE **dataFile, int *lines)
{
    char c;
    *lines = 0;
    rewind(*dataFile);
    for (c = getc(*dataFile); c != EOF; c = getc(*dataFile))
    {
        if (c == '\n')
        {
            *lines = *lines + 1;
        }
    }
    rewind(*dataFile);
}

void freeLinkedList(struct linkedList *head, int *lines)
{
    struct linkedList *temp;
    int i = 0;
    while (head != NULL && i < *lines)
    {
        temp = head;
        head = head->next;
        printf("Deleting node with id: %d\n", temp->id);
        free(temp);
        temp = NULL;
        i++;
    }
}

int nacitajSubory(FILE **dataFile, FILE **stringFile, FILE **parseFile, bool *opened)
{
    *dataFile = fopen("data.txt", "r");
    *stringFile = fopen("string.txt", "r");
    *parseFile = fopen("parse.txt", "r");
    if (*dataFile == NULL || *stringFile == NULL || *parseFile == NULL)
    {
        return 0;
    }
    *opened = true;
    return 1;
}

void V1(FILE **dataFile, FILE **stringFile, FILE **parseFile)
{
    char stringFileCharArr[100];
    char dataFileCharArr[100];
    char parseFileCharArr[100];
    int a, b, c;
    double d;

    while (fgets(stringFileCharArr, 100, *stringFile) != NULL &&
           fgets(dataFileCharArr, 100, *dataFile) != NULL &&
           fgets(parseFileCharArr, 100, *parseFile) != NULL)
    {
        printf("ID. mer. modulu: %s", stringFileCharArr);

        sscanf(dataFileCharArr, "%d %d %d %lf", &a, &b, &c, &d);
        printf("Hodnota 1: %d \n", c);
        printf("Hodnota 2: %g \n", d);
        printf("Poznámka: %s \n", parseFileCharArr);
    }

    rewind(*dataFile);
    rewind(*stringFile);
    rewind(*parseFile);
}

void V2(char ***dataFileArr, char ***stringFileArr, char ***parseFileArr, int *lines)
{
    int a, b, c;
    double d;
    int i = 0;
    for (i = 0; i < *lines; i++)
    {
        (*stringFileArr)[i][strcspn((*stringFileArr)[i], "\n")] = '\0';
        printf("ID. mer. modulu: %s\n", (*stringFileArr)[i]);

        sscanf((*dataFileArr)[i], "%d %d %d %lf", &a, &b, &c, &d);
        printf("Hodnota 1: %d \n", c);
        printf("Hodnota 2: %g \n", d);
        printf("Poznámka: %s \n\n", (*parseFileArr)[i]);
    }
}

void V3(struct linkedList *head, int *lines)
{
    struct linkedList *temp = head;
    int i = 0;

    while (temp != NULL && i < *lines)
    {
        printf("Id: %d\n", temp->id);
        printf("ID. mer. modulu: %d\n", temp->dataList.Hodnota_Zn); // Todo: check this later
        printf("Hodnota 1: %d \n", temp->dataList.Hodnota_1);
        printf("Hodnota 2: %g \n", temp->dataList.Hodnota_2);
        // printf("Poznámka ID: %s \n\n", temp->parseList.Poznamka_ID);
        printf("Poznamka C: %d : %d => %d \n", temp->parseList.Poznamka_Hodina, temp->parseList.Poznamka_Minuta, temp->parseList.Poznamka_N1);
        printf("Poznamka T: %d \n\n", temp->parseList.Poznamka_T);

        temp = temp->next;
        i++;
    }
}

void N(FILE **dataFile, FILE **stringFile, FILE **parseFile, char ***dataFileArr, char ***stringFileArr, char ***parseFileArr, int *lines)
{
    int i = 0;
    setLines(dataFile, lines);
    rewind(*dataFile);
    rewind(*stringFile);
    rewind(*parseFile);

    *dataFileArr = (char **)malloc(*lines * sizeof(char *));
    *stringFileArr = (char **)malloc(*lines * sizeof(char *));
    *parseFileArr = (char **)malloc(*lines * sizeof(char *));
    for (i = 0; i < *lines; i++)
    {
        (*dataFileArr)[i] = (char *)malloc(100 * sizeof(char));
        fgets((*dataFileArr)[i], 100, *dataFile);
        (*dataFileArr)[i][strcspn((*dataFileArr)[i], "\n")] = '\0';

        (*stringFileArr)[i] = (char *)malloc(100 * sizeof(char));
        fgets((*stringFileArr)[i], 100, *stringFile);
        (*stringFileArr)[i][strcspn((*stringFileArr)[i], "\n")] = '\0';

        (*parseFileArr)[i] = (char *)malloc(100 * sizeof(char));
        fgets((*parseFileArr)[i], 100, *parseFile);
        (*parseFileArr)[i][strcspn((*parseFileArr)[i], "\n")] = '\0';
    }
    printf("done\n");
}

void q(int Y, char ***dataFileArr, char ***stringFileArr, char ***parseFileArr, int *lines)
{
    int i1, a, b, c;
    double d;
    char s1[100];
    char s2[100];

    Y = Y - 1;

    scanf("%s", s1);                       // string.txt
    scanf("%d %d %d %lf", &a, &b, &c, &d); // data.txt
    scanf(" %[^\n]", s2);                  // parse.txt

    if (Y > *lines)
    {
        *lines = *lines + 1;
        *dataFileArr = (char **)realloc(*dataFileArr, *lines * sizeof(char *));
        *stringFileArr = (char **)realloc(*stringFileArr, *lines * sizeof(char *));
        *parseFileArr = (char **)realloc(*parseFileArr, *lines * sizeof(char *));
        (*dataFileArr)[*lines - 1] = (char *)malloc(100 * sizeof(char));
        (*stringFileArr)[*lines - 1] = (char *)malloc(100 * sizeof(char));
        (*parseFileArr)[*lines - 1] = (char *)malloc(100 * sizeof(char));

        sprintf((*dataFileArr)[*lines - 1], "%d %d %d %lf", a, b, c, d);
        sprintf((*stringFileArr)[*lines - 1], "%s", s1);
        sprintf((*parseFileArr)[*lines - 1], "%s", s2);

        return;
    }

    // add an item to the center of the array
    *dataFileArr = (char **)realloc(*dataFileArr, (*lines + 1) * sizeof(char *));
    *stringFileArr = (char **)realloc(*stringFileArr, (*lines + 1) * sizeof(char *));
    *parseFileArr = (char **)realloc(*parseFileArr, (*lines + 1) * sizeof(char *));
    for (i1 = *lines; i1 >= Y; i1--)
    {
        // move the items to the right
        if (i1 <= 0)
        {
            break;
        }
        (*dataFileArr)[i1] = (char *)malloc(100 * sizeof(char));
        sprintf((*dataFileArr)[i1], "%s", (*dataFileArr)[i1 - 1]);
        (*stringFileArr)[i1] = (char *)malloc(100 * sizeof(char));
        sprintf((*stringFileArr)[i1], "%s", (*stringFileArr)[i1 - 1]);
        (*parseFileArr)[i1] = (char *)malloc(100 * sizeof(char));
        sprintf((*parseFileArr)[i1], "%s", (*parseFileArr)[i1 - 1]);
    }
    // insert the new item
    (*dataFileArr)[Y] = (char *)malloc(100 * sizeof(char));
    sprintf((*dataFileArr)[Y], "%d %d %d %lf", a, b, c, d);
    (*stringFileArr)[Y] = (char *)malloc(100 * sizeof(char));
    sprintf((*stringFileArr)[Y], "%s\n", s1);
    (*parseFileArr)[Y] = (char *)malloc(100 * sizeof(char));
    sprintf((*parseFileArr)[Y], "%s\n", s2);

    *lines = *lines + 1;
}

void w(char ToDelete[], char ***dataFileArr, char ***stringFileArr, char ***parseFileArr, int *lines)
{
    int deleted = 0;

    for (int i = 0; i < *lines; i++)
    {
        if (strcmp((*stringFileArr)[i], ToDelete) == 0)
        {
            free((*dataFileArr)[i]);
            free((*stringFileArr)[i]);
            free((*parseFileArr)[i]);
            for (int j = i; j < *lines - 1; j++)
            {
                (*dataFileArr)[j] = (*dataFileArr)[j + 1];
                (*stringFileArr)[j] = (*stringFileArr)[j + 1];
                (*parseFileArr)[j] = (*parseFileArr)[j + 1];
            }
            i--;
            *lines = *lines - 1;
            deleted += 1;
        }
    }
    printf("W: Vymazalo sa : %d zaznamov ! \n", deleted);
}

void e(char findMe[], char ***parseFileArr, int *lines)
{
    for (int i = 0; i < *lines; i++)
    {
        if (strstr((*parseFileArr)[i], findMe) != NULL)
        {
            printf("%s\n", (*parseFileArr)[i]);
        }
    }
}

void h(FILE **stringFile)
{
    char velkePismena[26];
    int velkePismenaCount[26] = {0};
    char malePismena[26];
    int malePismenaCount[26] = {0};
    char cisla[10];
    int cislaCount[10] = {0};
    int i = 0;
    char c;

    for (i = 0; i < 26; i++)
    {
        velkePismena[i] = 'A' + i;
        malePismena[i] = 'a' + i;
        if (i < 10)
        {
            cisla[i] = '0' + i;
        }
    }

    while ((c = fgetc(*stringFile)) != EOF)
    {
        switch (c)
        {
        case 'a' ... 'z':
            malePismenaCount[c - 'a']++;
            break;
        case 'A' ... 'Z':
            velkePismenaCount[c - 'A']++;
            break;
        case '0' ... '9':
            cislaCount[c - '0']++;
            break;
        default:
            break;
        }
    }
    for (i = 0; i < 26; i++)
    {
        if (velkePismenaCount[i] != 0)
        {
            printf("%c : %d\n", velkePismena[i], velkePismenaCount[i]);
        }
    }

    for (i = 0; i < 26; i++)
    {
        if (malePismenaCount[i] != 0)
        {
            printf("%c : %d\n", malePismena[i], malePismenaCount[i]);
        }
    }

    for (i = 0; i < 10; i++)
    {
        if (cislaCount[i] != 0)
        {
            printf("%c : %d\n", cisla[i], cislaCount[i]);
        }
    }

    rewind(*stringFile);
}

void m(FILE **dataFile, FILE **parseFile, struct linkedList **head, int *lines, bool linkedListed)
{
    int i = 0;

    struct linkedList *temp = *head;
    struct linkedList *newNode = (struct linkedList *)malloc(sizeof(struct linkedList));

    struct data dataList;
    struct parse parseList;
    setLines(dataFile, lines);

    if (linkedListed)
    {
        freeLinkedList(*head, lines);
    }

    for (i = 0; i < *lines; i++)
    {
        struct linkedList *newNode = (struct linkedList *)malloc(sizeof(struct linkedList));
        if (newNode == NULL)
        {
            printf("M: Nepodarilo sa alokovat pamat\n");
            return;
        }
        char dataLine[100];
        char parseLine[100];

        // Read from data file
        if (fgets(dataLine, sizeof(dataLine), *dataFile) == NULL)
        {
            free(newNode);
            printf("M: Nepodarilo sa nacitat data.txt\n");
            return;
        }
        if (sscanf(dataLine, "%d %d %d %lf",
                   &dataList.Hodnota_ID,
                   &dataList.Hodnota_Zn,
                   &dataList.Hodnota_1,
                   &dataList.Hodnota_2) != 4)
        {
            free(newNode);
            printf("M: Nespravny format v data.txt\n");
            return;
        }

        // Read from parse file
        if (fgets(parseLine, sizeof(parseLine), *parseFile) == NULL)
        {
            free(newNode);
            printf("M: Nepodarilo sa nacitat parse.txt\n");
            return;
        }
        if (sscanf(parseLine, "%d %d %d %d",
                   &parseList.Poznamka_N1,
                   &parseList.Poznamka_Hodina,
                   &parseList.Poznamka_Minuta,
                   &parseList.Poznamka_T) != 4)
        {
            // free(newNode);
            // printf("M: Nespravny format v parse.txt\n");
            // return;
        }

        //* Create a new node for linked list
        newNode->dataList = dataList;
        newNode->parseList = parseList;
        newNode->next = NULL;
        newNode->id = i;

        if (*head == NULL)
        {
            *head = newNode;
            temp = newNode;
        }
        else
        {
            temp->next = newNode;
            temp = newNode;
        }
    }

    rewind(*dataFile);
    rewind(*parseFile);

    printf("M: Nacitalo sa %d zaznamov\n", i);
}

int main()
{
    FILE *dataFile, *stringFile, *parseFile;
    bool opened = false;

    bool linkedListed = false;
    struct linkedList *head = NULL;

    bool nActivated = false;
    int lines = 0;
    char **dataFileArr;
    char **stringFileArr;
    char **parseFileArr;

    char input;
    int inputNum;
    int qNum;
    char idToDelete[100];

    bool exit = false;
    int i = 0;
    char findMe[100];

    while (exit == false)
    {
        scanf("%c", &input);

        if (input == '\n')
        {
            scanf("%c", &input);
        }

        if (input == 'v' || input == 'V')
        {
            scanf("%d", &inputNum);

            if (inputNum == 1)
            {
                if (!opened)
                {
                    if (nacitajSubory(&dataFile, &stringFile, &parseFile, &opened) == 0)
                    {
                        printf("V1: Neotvorene txt subory\n");
                        continue;
                    }
                }
                V1(&dataFile, &stringFile, &parseFile);
            }
            else if (inputNum == 2)
            {
                if (!nActivated)
                {
                    printf("V2: Nenaplnene polia.\n");
                    continue;
                }

                V2(&dataFileArr, &stringFileArr, &parseFileArr, &lines);
            }
            else if (inputNum == 3)
            {
                if (!linkedListed)
                {
                    printf("V3: Nenaplneny spajany zoznam\n");
                    continue;
                }
                V3(&head, &lines);
            }
            else
            {
                printf("Nespravna volba vypisu\n");
            }
        }
        else if (input == 'h' || input == 'H')
        {
            if (!opened)
            {
                printf("Histogram: Neotvoreny subor.\n");
                continue;
            }
            printf("h:\n");
            h(&stringFile);
        }
        else if (input == 'n' || input == 'N')
        {
            if (!opened)
            {
                printf("N: Neotvoreny subor.\n");
                continue;
            }
            N(&dataFile, &stringFile, &parseFile, &dataFileArr, &stringFileArr, &parseFileArr, &lines);
            nActivated = true;
        }
        else if (input == 'q' || input == 'Q')
        {
            if (!nActivated)
            {
                printf("Q: Polia nie su vytvorene.\n");
                continue;
            }
            scanf("%d", &qNum);
            q(qNum, &dataFileArr, &stringFileArr, &parseFileArr, &lines);
        }
        else if (input == 'w' || input == 'W')
        {
            if (!nActivated)
            {
                printf("W: Polia nie su vytvorene\n");
                continue;
            }
            scanf("%s", idToDelete);
            w(idToDelete, &dataFileArr, &stringFileArr, &parseFileArr, &lines);
        }
        else if (input == 'e' || input == 'E')
        {
            if (!nActivated)
            {
                printf("E: Polia nie su vytvorene\n");
                continue;
            }
            scanf("%s", findMe);
            e(findMe, &parseFileArr, &lines);
        }
        else if (input == 'x' || input == 'X') /*@Note: I added this so you can exit the program*/
        {
            exit = true;
            printf("Koniec programu\n");
        }
        else if (input == 'k' || input == 'K')
        {
            if (!opened)
            {
                // printf("K: Neotvoreny subor.\n");
                continue;
            }
            fclose(dataFile);
            fclose(stringFile);
            fclose(parseFile);
            opened = false;
            if (nActivated)
            {
                for (i = 0; i < lines; i++)
                {
                    free(dataFileArr[i]);
                    free(stringFileArr[i]);
                    free(parseFileArr[i]);
                }
                free(dataFileArr);
                free(stringFileArr);
                free(parseFileArr);
                nActivated = false;
                lines = 0;
            }
            return 0;
        }
        else if (input == 'm' || input == 'M')
        {
            if (!opened)
            {
                printf("M: Neotvoreny subor.\n");
                continue;
            }
            m(&dataFile, &parseFile, &head, &lines, linkedListed);
            linkedListed = true;
        }
        else
        {
            printf("Nespravna volba výpisu\n");
        }
    }
    fclose(dataFile);
    fclose(stringFile);
    fclose(parseFile);
}