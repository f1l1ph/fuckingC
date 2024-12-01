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
    char Poznamka_ID[10];
    double Poznamka_N1;
    int Poznamka_Hodina;
    int Poznamka_Minuta;
    char Poznamka_T[10];
};

struct linkedList
{
    int id;
    struct data dataList;
    struct parse parseList;
    char string_txt[10];
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

void freeLinkedList(struct linkedList *head, int *nodes)
{
    struct linkedList *temp;
    int i = 0;
    while (head != NULL && i < *nodes)
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

// TODO: put Nan when empty on PoznamkaId and PoznamkaT
void V3(struct linkedList **head, int *nodes)
{
    struct linkedList *temp = *head;
    int i = 0;

    if (head == NULL || nodes == NULL)
    {
        printf("V3: Invalid input parameters\n");
        return;
    }

    while (temp != NULL && i < *nodes)
    {
        if (temp->string_txt != NULL && temp->parseList.Poznamka_ID != NULL && temp->parseList.Poznamka_T != NULL)
        {
            printf("ID. mer. modulu: %s \n", temp->string_txt);
            printf("Hodnota 1: %d \n", temp->dataList.Hodnota_1);
            printf("Hodnota 2: %g \n", temp->dataList.Hodnota_2);
            printf("PoznámkaId: %s \n", (temp->parseList.Poznamka_ID[0] == '\0' || temp->parseList.Poznamka_ID[0] == '\n') ? "NaN" : temp->parseList.Poznamka_ID);
            printf("Poznamka C: %d : %d => %g \n", temp->parseList.Poznamka_Hodina, temp->parseList.Poznamka_Minuta, temp->parseList.Poznamka_N1);
            printf("Poznamka T: %s \n", (temp->parseList.Poznamka_T[0] == '\0' || temp->parseList.Poznamka_T[0] == '\n') ? "NaN" : temp->parseList.Poznamka_T);
            printf("\n");
        }
        else
        {
            printf("V3: Corrupted data in node %d\n", i);
        }

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
        if (c >= 'a' && c <= 'z')
        {
            malePismenaCount[c - 'a']++;
        }
        else if (c >= 'A' && c <= 'Z')
        {
            velkePismenaCount[c - 'A']++;
        }
        else if (c >= '0' && c <= '9')
        {
            cislaCount[c - '0']++;
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

void m(FILE **dataFile, FILE **parseFile, FILE **stringFile, struct linkedList **head, int *lines, bool linkedListed, int *nodes)
{
    int i = 0;

    struct linkedList *temp = *head;
    struct linkedList *newNode;

    struct data dataList;
    struct parse parseList;
    char string_txt[10];

    char dataLine[100];
    char parseLine[100];

    char *token;
    char tempLine[100];

    setLines(dataFile, lines);

    temp = *head;

    rewind(*dataFile);
    rewind(*parseFile);
    rewind(*stringFile);

    if (linkedListed)
    {
        freeLinkedList(*head, nodes);
    }

    *nodes = *lines;

    for (i = 0; i < *lines; i++)
    {
        memset(dataLine, 0, sizeof(dataLine));
        memset(parseLine, 0, sizeof(parseLine));
        memset(string_txt, 0, sizeof(string_txt));
        memset(tempLine, 0, sizeof(tempLine));

        newNode = (struct linkedList *)malloc(sizeof(struct linkedList));
        if (newNode == NULL)
        {
            printf("M: Nepodarilo sa alokovat pamat\n");
            return;
        }

        // read from Files
        fgets(dataLine, sizeof(dataLine), *dataFile);
        fgets(parseLine, sizeof(parseLine), *parseFile);
        fgets(string_txt, sizeof(string_txt), *stringFile);
        // remove newline from string_txt
        string_txt[strcspn(string_txt, "\n")] = '\0';

        if (dataLine == NULL || parseLine == NULL || string_txt == NULL)
        {
            free(newNode);
            printf("M: Nepodarilo sa nacitat z jedneho zo suborou\n");
            return;
        }

        //?? parsing here actually works but need to figure out pointers and shid
        sscanf(dataLine, "%d %d %d %lf",
               &dataList.Hodnota_ID,
               &dataList.Hodnota_Zn,
               &dataList.Hodnota_1,
               &dataList.Hodnota_2);

        strcpy(tempLine, parseLine);

        // Get Poznamka_ID (before first #)
        token = strtok(tempLine, "#");
        if (token)
            strcpy(parseList.Poznamka_ID, token);

        // Get Poznamka_N1 (between first and second #)
        token = strtok(NULL, "#");
        if (token)
            parseList.Poznamka_N1 = atof(token);

        // Get time (between second and third #)
        token = strtok(NULL, "#");
        if (token)
            sscanf(token, "%2d%2d", &parseList.Poznamka_Hodina, &parseList.Poznamka_Minuta);

        // Get Poznamka_T (between third and fourth #)
        token = strtok(NULL, "#");
        if (token)
            strcpy(parseList.Poznamka_T, token);

        //* Create a new node for linked list
        newNode->dataList = dataList;
        newNode->parseList = parseList;
        strcpy(newNode->string_txt, string_txt);
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

void a(struct linkedList **head, int *nodes)
{
    int Y;
    int amountOfNodes = 0;
    struct linkedList *temp = *head;

    char parseLine[100];

    struct linkedList *newNode = (struct linkedList *)malloc(sizeof(struct linkedList));

    char *token;
    char tempLine[100];

    scanf("%d", &Y);
    Y = Y - 1;

    while (temp != NULL)
    {
        if (temp->id > amountOfNodes)
        {
            amountOfNodes = temp->id;
        }
        temp = temp->next;
    }

    if (Y > amountOfNodes)
    {
        Y = amountOfNodes;
    }
    *nodes += 1;
    if (newNode == NULL)
    {
        printf("A: Nepodarilo sa alokovat pamat\n");
        return;
    }

    scanf("%s", newNode->string_txt); // string.txt
    scanf("%d %d %d %lf",             // data.txt
          &newNode->dataList.Hodnota_ID,
          &newNode->dataList.Hodnota_Zn,
          &newNode->dataList.Hodnota_1,
          &newNode->dataList.Hodnota_2);
    scanf(" %[^\n]", parseLine); // parse.txt

    // Parse parse.txt content

    strcpy(tempLine, parseLine);

    // Get Poznamka_ID (before first #)
    token = strtok(tempLine, "#");
    if (token)
        strcpy(newNode->parseList.Poznamka_ID, token);

    // Get Poznamka_N1 (between first and second #)
    token = strtok(NULL, "#");
    if (token)
        newNode->parseList.Poznamka_N1 = atof(token);

    // Get time (between second and third #)
    token = strtok(NULL, "#");
    if (token)
        sscanf(token, "%2d%2d",
               &newNode->parseList.Poznamka_Hodina,
               &newNode->parseList.Poznamka_Minuta);

    // Get Poznamka_T (after third #)
    token = strtok(NULL, "#");
    if (token)
        strcpy(newNode->parseList.Poznamka_T, token);

    newNode->id = amountOfNodes + 1;

    // Insert node at position Y
    if (Y == 0)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        temp = *head; // Reset temp to head
        // Find position Y-1
        for (int i = 0; i < Y - 1 && temp != NULL; i++)
        {
            temp = temp->next;
        }

        if (temp != NULL)
        {
            // Insert new node
            newNode->next = temp->next;
            temp->next = newNode;

            // Update IDs for all nodes after insertion
            struct linkedList *current = newNode->next;
            int currentId = newNode->id + 1;
            while (current != NULL)
            {
                current->id = currentId++;
                current = current->next;
            }
        }
        else
        {
            // If position not found, add to end
            temp = *head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
}

void s(struct linkedList **head, int *nodes)
{
    char idToDelete[10];

    struct linkedList *temp;
    struct linkedList *prev;

    int deleted;

    scanf("%s", &idToDelete[0]);

    deleted = 0;
    temp = *head;
    prev = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->string_txt, idToDelete) == 0)
        {
            struct linkedList *toDelete = temp;
            if (prev == NULL)
            {
                *head = temp->next;
                temp = *head;
            }
            else
            {
                prev->next = temp->next;
                temp = temp->next;
            }
            free(toDelete);
            deleted++;
            *nodes -= 1;
            continue;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("S: Vymazalo sa %d zaznamov\n", deleted);
}

void d(struct linkedList **head)
{
    int id1, id2;
    scanf("%d %d", &id1, &id2);

    struct linkedList *node1;
    struct linkedList *node2;
    struct linkedList *temp;

    struct data tempData;
    struct parse tempParse;
    char tempString[10];

    node1 = NULL;
    node2 = NULL;
    temp = *head;

    while (temp != NULL)
    {
        if (temp->id == id1)
            node1 = temp;
        if (temp->id == id2)
            node2 = temp;
        temp = temp->next;
    }

    if (node1 == NULL || node2 == NULL)
    {
        printf("D: Jeden alebo viac ID neexistuje\n");
        return;
    }
    if (id1 == id2)
    {
        return;
    }

    memset(&tempData, 0, sizeof(struct data));
    memset(&tempParse, 0, sizeof(struct parse));

    tempData = node1->dataList;
    tempParse = node1->parseList;

    strcpy(tempString, node1->string_txt);
    node1->dataList = node2->dataList;
    node1->parseList = node2->parseList;

    strcpy(node1->string_txt, node2->string_txt);
    node2->dataList = tempData;
    node2->parseList = tempParse;
    strcpy(node2->string_txt, tempString);
}

void k(struct linkedList **head, int *nodes)
{
    struct linkedList *temp = *head;
    struct linkedList *toDelete = NULL;
    int deleted = 0;

    while (temp != NULL)
    {
        toDelete = temp;
        temp = temp->next;
        free(toDelete);
        deleted++;
    }
    *head = NULL;
    *nodes = 0;
    printf("D: Vymazalo sa %d zaznamov\n", deleted);
}

int main()
{
    FILE *dataFile, *stringFile, *parseFile;
    bool opened = false, linkedListed = false, nActivated = false;

    struct linkedList *head = NULL;

    int lines, i = 0, nodes = 0;
    char **dataFileArr, **stringFileArr, **parseFileArr;

    char input;
    int inputNum, qNum;
    char idToDelete[100];
    char findMe[100];

    while (true)
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
                V3(&head, &nodes);
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
            if (linkedListed)
            {
                k(&head, &nodes);
                linkedListed = false;
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
            m(&dataFile, &parseFile, &stringFile, &head, &lines, linkedListed, &nodes);
            linkedListed = true;
        }
        else if (input == 'a' || input == 'A')
        {
            if (!linkedListed)
            {
                printf("A: Nevytvoreny linked list\n");
                continue;
            }
            a(&head, &nodes);
        }
        else if (input == 's' || input == 'S')
        {
            if (!linkedListed)
            {
                printf("S: Nevytvoreny linked list\n");
                continue;
            }
            s(&head, &nodes);
        }
        else if (input == 'd' || input == 'D')
        {
            if (!linkedListed)
            {
                printf("D: Nevytvoreny linked list\n");
                continue;
            }
            d(&head);
        }
        else
        {
            printf("Nespravna volba vypisu\n");
        }
    }
}