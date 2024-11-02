#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Filip Masarik
 */

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
    int a,b,c; 
    double d;

    while (fgets(stringFileCharArr, 100, *stringFile) != NULL &&
           fgets(dataFileCharArr, 100, *dataFile) != NULL &&
           fgets(parseFileCharArr, 100, *parseFile) != NULL)
    {
        printf("ID. met. modulu %s", stringFileCharArr);

        int spacesCount = 0;
        sscanf(dataFileCharArr,"%d %d %d %lf",&a,&b, &c,&d);
        printf("Hodnota 1: %d \n", c);
        printf("Hodnota 2: %g \n", d);
        printf("Poznámka %s \n", parseFileCharArr);
    }

    rewind(*dataFile);
    rewind(*stringFile);
    rewind(*parseFile);
}

void V2(char ***dataFileArr, char ***stringFileArr, char ***parseFileArr, int *lines)
{
    for (int i = 0; i < *lines; i++)
    {
        printf("ID. met. modulu %s\n", (*stringFileArr)[i]);

        int a,b,c; 
        double d;
        sscanf((*dataFileArr)[i],"%d %d %d %lf",&a,&b, &c,&d);
        printf("Hodnota 1: %d \n", c);
        printf("Hodnota 2: %g \n", d);
        printf("Poznámka %s \n\n", (*parseFileArr)[i]);
    }
}

void N(FILE **dataFile, FILE **stringFile, FILE **parseFile, char*** dataFileArr, char*** stringFileArr, char*** parseFileArr, int *lines)
{
    char c;
    *lines = 0;
    for (c = getc(*dataFile); c != EOF; c = getc(*dataFile))
    {
        if (c == '\n')
        {
            *lines = *lines + 1;
        }
    }
    rewind(*dataFile);
    rewind(*stringFile);
    rewind(*parseFile);
    
    *dataFileArr = (char **)malloc(*lines * sizeof(char *));
    *stringFileArr = (char **)malloc(*lines * sizeof(char *));
    *parseFileArr = (char **)malloc(*lines * sizeof(char *));
    for(int i = 0; i < *lines; i++)
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
}

void q(int Y, char ***dataFileArr, char ***stringFileArr, char ***parseFileArr, int *lines)
{
    Y = Y - 1;

    int i1, a, b, c;
    double d;
    char s1[100];
    char s2[100];

    scanf("%s", s1);                        //string.txt
    scanf("%d %d %d %lf", &a, &b, &c, &d);  //data.txt
    scanf("%s", s2);                        //parse.txt

    if(Y > *lines)
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

    //add an item to the center of the array
    *dataFileArr = (char **)realloc(*dataFileArr, (*lines + 1) * sizeof(char *));
    *stringFileArr = (char **)realloc(*stringFileArr, (*lines + 1) * sizeof(char *));
    *parseFileArr = (char **)realloc(*parseFileArr, (*lines + 1) * sizeof(char *));
    for (i1 = *lines; i1 >= Y; i1--)
    {
        //move the items to the right
        if(i1 <= 0)
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
    //insert the new item
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

    for(int i = 0; i < *lines; i++)
    {
        if(strcmp((*stringFileArr)[i], ToDelete) == 0)
        {
            for(int j = i; j < *lines - 1; j++)
            {
                sprintf((*dataFileArr)[j], "%s", (*dataFileArr)[j + 1]);
                sprintf((*stringFileArr)[j], "%s", (*stringFileArr)[j + 1]);
                sprintf((*parseFileArr)[j], "%s", (*parseFileArr)[j + 1]);
            }
            *lines = *lines - 1;
            *dataFileArr = (char **)realloc(*dataFileArr, *lines * sizeof(char *));
            *stringFileArr = (char **)realloc(*stringFileArr, *lines * sizeof(char *));
            *parseFileArr = (char **)realloc(*parseFileArr, *lines * sizeof(char *));
            deleted += 1;
        }
    }
    printf("W: Vymazalo sa : %d zaznamov! \n", deleted);
}

void e(char findMe[] ,char ***parseFileArr, int *lines)
{
    for(int i = 0; i < *lines; i++)
    {
        if(strstr((*parseFileArr)[i], findMe) != NULL)
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
    for ( i = 0; i < 26; i++)
    {
        velkePismena[i] = 'A' + i;
    }
    for ( i = 0; i < 26; i++)
    {
        malePismena[i] = 'a' + i;
    }
    for ( i = 0; i < 10; i++)
    {
        cisla[i] = '0' + i;
    }

    char c;
    while ((c = fgetc(*stringFile)) != EOF)
    {
        for (int i = 0; i < 26; i++)
        {
            if (c == malePismena[i])
            {
                malePismenaCount[i]++;
                continue;
            }
            if(c == velkePismena[i])
            {
                velkePismenaCount[i]++;
                continue;
            }
        }
        for (int i = 0; i < 10; i++)
        {
            if (c == cisla[i])
            {
                cislaCount[i]++;
                continue;
            }
        }
    }
    for( i = 0; i < 26; i++)
    {
        if(velkePismenaCount[i] != 0)
        {
            printf("%c : %d\n", velkePismena[i], velkePismenaCount[i]);
        }
    }

    for( i = 0; i < 26; i++)
    {
        if(malePismenaCount[i] != 0)
        {
            printf("%c : %d\n", malePismena[i], malePismenaCount[i]);
        }
    }

    for( i = 0; i < 10; i++)
    {
        if(cislaCount[i] != 0)
        {
            printf("%c : %d\n", cisla[i], cislaCount[i]);
        }
    }

    rewind(*stringFile);
}

int main()
{
    FILE *dataFile, *stringFile, *parseFile;
    bool opened = false;

    bool nActivated = false;
    int lines = 0;
    char **dataFileArr;
    char **stringFileArr;
    char **parseFileArr;

    char input;
    int inputNum;

    bool exit = false;

    while (exit == false)
    {
        scanf("%c", &input);

        if(input == '\n')
        {
            scanf("%c", &input);
        }

        if (input == 'v' || input == 'V')
        {
            scanf("%d", &inputNum);

            if (inputNum == 1)
            {
                if(!opened)
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
                if(!nActivated)
                {
                    printf("V2: nenaplnené polia\n");
                    continue;
                }

                V2(&dataFileArr, &stringFileArr, &parseFileArr, &lines);
            }
            else if (inputNum == 3)
            {
                printf("Este nie je hotove\n");
            }
            else
            {
                printf("Nespravna volba vypisu\n");
            }
        }
        else if(input == 'h' || input == 'H')
        {
            if(!opened)
            {
                printf("Histogram: Neotvoreny subor.\n");
                continue;
            }
            printf("h:\n");
            h(&stringFile);
        }
        else if(input == 'n' || input == 'N')
        {
            if(!opened) { printf("N: Neotvoreny subor.\n"); continue; }

            N(&dataFile, &stringFile, &parseFile, &dataFileArr, &stringFileArr, &parseFileArr, &lines);
            nActivated = true;
        }
        else if(input == 'q' || input == 'Q')
        {
            if(!nActivated)
            {
                printf("Q: Polia nie su vytvorene\n");
                continue;
            }
            int qNum;
            scanf("%d", &qNum);

            q(qNum, &dataFileArr, &stringFileArr, &parseFileArr, &lines);
        }
        else if(input == 'w' || input == 'W')
        {
            if(!nActivated)
            {
                printf("W: Polia nie su vytvorene\n");
                continue;
            }

            char idToDelete[100];
            scanf("%s", idToDelete);
            w(idToDelete, &dataFileArr, &stringFileArr, &parseFileArr, &lines);
        }
        else if(input == 'e' || input == 'E')
        {
            if(!nActivated)
            {
                printf("E: Polia nie su vytvorene\n");
                continue;
            }
            char findMe[100];
            scanf("%s", findMe);
            e(findMe, &parseFileArr, &lines);
        }
        else if(input == 'x' || input == 'X')//@Note: I added this so you can exit the program
        {
            exit = true;
            printf("Koniec programu\n");
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