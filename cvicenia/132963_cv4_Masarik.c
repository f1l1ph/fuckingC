/**
 * @author Filip Masarik
 * Prepacte ze meskam s touto ulohou, bol som na hackatone
 * kedze uz su tie ulohy trochu dlhsie tak som dal kazdu do zvlast funkcie 
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool zisti_prvocislo(int num)
{
    if(num < 2) 
    {
        return false;
    }

    for(int i = 2; i <= num/2; i++) 
    {
        if(num % i == 0) 
        {
            return false;
        }
    }
    return true;
}

void reverzne_cislo(const char *str, char *reversed, int size)
{
    int i, j;
    for(i = 0, j = size - 1; i < size; i++, j--)
    {
        reversed[j] = str[i];
    }
    reversed = '\0';
}

void Uloha41(){
printf("\nUloha 4.1\n");
    int num411, num412;
    scanf("%d %d", &num411, &num412);
    for(int i = num411; i <= num412; i++)
    {
        if(zisti_prvocislo(i)) 
        {
            printf("%d \n", i);
        }
    }
}

void Uloha42(){
printf("\nUloha 4.2\n");
    
    int num421;
    double finalResult = 0;

    scanf("%d", &num421);
    for(int i = 0; i < num421;i++)
    {
        double mzda, hodiny;
        scanf("%lf %lf", &mzda, &hodiny);
        if(hodiny > 60)
        {
            double hodNad = hodiny - 60;
            hodNad = hodNad * 2;
            finalResult += mzda * 40 + mzda * 20*1.5 + mzda * hodNad;
            printf("%d: %g\n", i+1, mzda * 40 + mzda * 20*1.5 + mzda * hodNad);
            continue;
        }

        if(hodiny > 40)
        {
            double hodNad = hodiny - 40;
            hodNad = hodNad * 1.5;
            finalResult += mzda * 40 + mzda * hodNad;
            printf("%d: %g\n", i+1, mzda * 40 + mzda * hodNad);
            continue;
        }

        finalResult += mzda * hodiny;
        printf("%d: %g\n", i+1, mzda*hodiny);
    }

    printf("Celkova mzda: %g\n", finalResult);
}

void Uloha43(){
printf("\nUloha 4.3\n");
    long num431;
    int digits = 0;
    scanf("%ld", &num431);

    long num431Copy;
    num431Copy = num431;


    while (num431Copy != 0) {
        num431Copy /= 10;
        digits++;
    }

    char str43[digits];
    char reversed[digits];

    sprintf(str43, "%ld", num431); 
    reverzne_cislo(str43, reversed, digits);

    if(strcmp(str43, reversed) == 0)
    {
        printf("Cislo %ld je palindrom\n", num431);
    }
    else
    {
        printf("Cislo %ld nie je palindrom\n", num431);
        printf("Cislo %ld v reverznom poradi: %s\n", num431, reversed);
    }
}

void Uloha44(){
printf("\nUloha 4.4\n");
    double num441;
    scanf("%lf", &num441);

    //open file and write to it
    FILE *file = fopen("nasobky.txt", "w");
    if(file == NULL)
    {
        printf("Subor sa nepodarilo otvorit\n");
        return 1;
    }
    for(int i = 1; i < 10; i++)
    {
        double res = i*num441;
        fprintf(file, " %g\n", res);
    }
}

int Uloha45(){
    printf("\nUloha 4.5\n");

    char znak45;
    scanf("%c", &znak45);
    FILE *file = fopen("znaky.txt", "r");
    FILE *secondFile = fopen("novy.txt","w");

   if(file == NULL || secondFile == NULL)
   {
        printf("Subor sa nepodarilo otvorit\n");
        return 0;
   }
   if(znak45 == 's')
   {
        char c;
        while((c = fgetc(file)) != EOF)
        {
            fputc(c, secondFile);
        }
   }
   else
   {
        char c;
        while((c = fgetc(file)) != EOF)
        {
            printf("%c", c);
        }
   }
   fclose(file);
   fclose(secondFile);
   return 1;
}

void Uloha46()
{
        printf("\nUloha 4.6\n");
    FILE *file = fopen("text.txt", "r");

    if(file == NULL)
    {
        printf("Subor sa nepodarilo otvorit\n");
        return 1;
    }
    char c;
    int whiteSpaces = 0;
    while((c = fgetc(file)) != EOF)
    {
        switch (c)
        {
            case '*':
                printf("Koniec \n" );
                printf("Pocet precitanych medzier: %d\n", whiteSpaces);
                return 0;
                break;
            case ' ':
                whiteSpaces++;
                break;
            case 'x': 
            case 'X':
                printf("Precital som X\n");
                break;
            case 'y':
            case 'Y':
                printf("Precital som Y\n");
                break;
            case '#':
            case '$':
            case '&':
                printf("Precital som riadiaci znak\n");
                break;
            default:
                break;
        }
    }
    fclose(file);
}

void Uloha47()
{
    printf("\nUloha 4.7\n");

    FILE *fp1, *fp2;
    char ch1, ch2;
    int count = 0;

    fp1 = fopen("prvy.txt", "r");
    fp2 = fopen("druhy.txt", "r");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Chyba pri otvarani suborov.\n");
        return 1;
    }

    while ((ch1 = fgetc(fp1)) != EOF && (ch2 = fgetc(fp2)) != EOF) {
        if (ch1 != ch2) {
            count++;
        }
    }

    if (count == 0) {
        printf("Subory su identicke.\n");
    } else {
        printf("Pocet roznych znakov: %d\n", count);

        fseek(fp1, 0, SEEK_SET);
        fseek(fp2, 0, SEEK_SET);
        int len1 = 0, len2 = 0;
        while (fgetc(fp1) != EOF) {
            len1++;
        }
        while (fgetc(fp2) != EOF) {
            len2++;
        }
        if (len1 != len2) {
            int res = len1 - len2;
            if(res < 0)
            {
                res = res * -1;
            }
            printf("Jeden zo suborov je dlhsi o %d znakov\n", res);
        }
    }

    fclose(fp1);
    fclose(fp2);
}

void Uloha48()
{
    printf("\nUloha 4.8\n");

    char samohlasky[] = {'a','e','i','o','u','A','E','U','O','U'};
    char spoluhlasky[] =
    {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z',
    'B','C','D','F','G','H','J','K','L','M','N','P','Q','R','S','T','V','W','X','Z'};
    char cislice[] = {'0','1','2','3','4','5','6','7','8','9'};
    char samohlasky_ret[] = "aeiouAEUOU";
    char spoluhlasky_ret[] = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
    char cislice_ret[] = "0123456789";

    FILE *file = fopen("vstup.txt", "r");
    int samohlaskyCount = 0;
    int spoluhlaskyCount = 0;
    int cisliceCount = 0;
    char c;
    while((c = fgetc(file)) != EOF)
    {
        for(int i = 0; i < sizeof(samohlasky); i++)
        {
            if(c == samohlasky[i])
            {
                samohlaskyCount++;
            }
        }
        for(int i = 0; i < sizeof(spoluhlasky); i++)
        {
            if(c == spoluhlasky[i])
            {
                spoluhlaskyCount++;
            }
        }
        for(int i = 0; i < sizeof(cislice); i++)
        {
            if(c == cislice[i])
            {
                cisliceCount++;
            }
        }
    }
    fclose(file);
    printf("Pocet samohlasok: %d, ", samohlaskyCount);
    printf("Pocet hlasok: %d, ", spoluhlaskyCount);
    printf("Pocet cislic: %d, ", cisliceCount);
}

int main()
{
    Uloha41(); 
    Uloha42();
    Uloha43();
    Uloha44();
    Uloha45();
    Uloha46();    
    Uloha47();
    Uloha48();
}