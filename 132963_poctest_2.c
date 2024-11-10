#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/**
 * @author: Filip Masarik
 * @id: 132963
 */
#define Pocet_Zaznamov 15 /*  nemenit  */ 

void UPRAVA2(int *pole_dataR[], char ***outputArray)
{
	char temp[10];
	int i = 0;
	int j = 0;

	*outputArray = (char **)malloc(Pocet_Zaznamov * sizeof(char *));
	for (i = 0; i < Pocet_Zaznamov; i++) { (*outputArray)[i] = (char *)malloc(7 * sizeof(char)); }//array allocation

	if (*outputArray == NULL || pole_dataR == NULL || Pocet_Zaznamov <= 0)  {
		printf("Chyba.\n");
		return;
	}

	for(i = 0; i < Pocet_Zaznamov; i++)
	{
		char finalStr[6] = "ID";
		for(j = 0; j < 3; j++)
		{
			if(j == 0)
			{
				memset(temp, 0, sizeof(temp));

				sprintf(temp, "%d", pole_dataR[i][j]);
				strcat(finalStr, temp);
			}

			if(j == 1)
			{
				memset(temp, 0, sizeof(temp));

				sprintf(temp, "%c", pole_dataR[i][j]);
				strcat(finalStr, temp);
			}
		}
		strcpy((*outputArray)[i], finalStr);
	}
}

void VYPIS2(char **outputArray)
{
	int i = 0;

	if(outputArray == NULL)
	{
		printf("Prazdne pole.\n");
		return;
	}
	for(i = 0; i < Pocet_Zaznamov; i++)
	{
		printf("%s - %d\n", outputArray[i], i);
	}
	printf("\n");
}

void ZORAD(int *pole_dataR[])
{
	int i = 0;
	int j = 0;
	int *temp = 0;

	if(pole_dataR == NULL)
	{
		printf("Prazdne pole.\n");
		return;
	}
	
	for(i = 0; i < Pocet_Zaznamov; i++)
	{
		for(j = 0; j < Pocet_Zaznamov; j++)
		{
			if(pole_dataR[i][1] < pole_dataR[j][1])
			{
				temp = pole_dataR[i];
				pole_dataR[i] = pole_dataR[j];
				pole_dataR[j] = temp;
			}
		}
	}

	printf("Zoradene pole:\n");
	for(i = 0; i < Pocet_Zaznamov; i++)
	{
		printf("%d - %c - %d\n", pole_dataR[i][0], pole_dataR[i][1], pole_dataR[i][2]);
	}
}

int main() {
	int** pole_dataR = NULL;
  
	int i = 0;
        srand(time(NULL));

        if(Pocet_Zaznamov != 0){ 
           pole_dataR = (int **)malloc(Pocet_Zaznamov * sizeof(int*));
    	   for (i = 0; i < Pocet_Zaznamov; i++) {
    	           pole_dataR[i]=(int*)malloc(3 * sizeof(int));
                   pole_dataR[i][0] = rand() %1000;
                   pole_dataR[i][1] = 'a' + ( rand() % ('z'-'a'+1));
                   pole_dataR[i][2] = rand() %1000;
           }
        }

	/* vypis */
	/*  vase riesenia / your solution   */
	char **outputArray = NULL;//pole do ktoreho sa to uklada

	UPRAVA2(pole_dataR, &outputArray);
	VYPIS2(outputArray);
	ZORAD(pole_dataR);

	/*  uvolnenie poli  */
	for (i = 0; i < Pocet_Zaznamov; i++) {
		free(*(pole_dataR + i));
		*(pole_dataR + i) = NULL;

	}
	free(pole_dataR);
        pole_dataR = NULL;

	for (i = 0; i < Pocet_Zaznamov; i++) {
		free(*(outputArray + i));
		*(outputArray + i) = NULL;
	}
	return 0;
}