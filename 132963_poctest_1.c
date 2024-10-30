#include <stdio.h>
#include<math.h>
#include <stdbool.h>

//Filip Masarik 

int Vykreslenie_S3(char n, char charDraw, char uselessChar)
{
    if(n <= 0)
    {
        if(uselessChar == "V")
        {
            printf("V_S3: Neuspesne vykreslenie!\n");
        }
        return -1;
    }
    for(int i = 0; i < n*2-1; i++)
    {
        if(i <n && i != 0)
        {
            charDraw = charDraw + 1;
            if(charDraw > 'Z')
            {
                charDraw = 'A';
            }
        }
        else if(i >= n){
            charDraw = charDraw - 1;
            if(charDraw < 'A')
            {
                charDraw = 'Z';
            }
        }
        
        for(int j = 0; j < n*2-1; j++)
        {
            if(j<=i && i <= n)
            {
                printf("%c", charDraw);
            }
            else if(j >= (n*2)-i-2 && i < n)
            {
                printf("%c", charDraw);
            }
            else if(j<=i-n && i > n)
            {
                printf("%c", charDraw);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 1;
}

char nacitajZnak(int m)
{
    char input;
    scanf("%c", &input);
    if(input >= 'a' && input <= 'z')
    {
        if(input-m <= 0)
        {
            return 0;
        }
    }
    char result = input+m;

    if(result > 'z')
    {
        result = 'a' + (result - 'z') - 1;
    }

    printf("%c\n", result);
    return result;
}

int main() 
{
   /* char znak = nacitajZnak(3);
    if(znak == 0)
    {
        printf("Neuspesne nacitanie!\n");
        return 1;
    }
    printf("Nacitanie prebehlo uspesne, nacitany znak %c sa zasifroval posunom doprava o M znakov.\n", znak);
    */

   Vykreslenie_S3(4, 'Z', 'V');
    return 0;
}