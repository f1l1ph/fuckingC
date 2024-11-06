#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Filip Masarik 
 */

int magicky(const int square[3][3], int size)
{
    int i = 0;
    int j = 0;
    int subsum = 0;
    int sum = 0;
    for(i = 0; i < size; i++)
    {
        subsum = 0;
        for(j = 0; j < size; j++)
        {
            if(i == 0)
            {
                sum += square[i][j];
            }
            subsum += square[i][j];
        }
        if(subsum != sum)
        {
            return 0;
        }
    }

    return 1;
}

void Uloha71()
{
    int n;
    const int N = 3;
    const int Narray[3][3] = {
        {8, 1, 6},
        {3, 5, 7},
        {4, 9, 2}
    };

    scanf("%d", &n);

    if(n > N)
    {
        printf("Mimo rozsah\n");
        return;
    }

    if(magicky(Narray, N) == 1)
    {
        printf("Je magicky\n");
    }
    else
    {
        printf("Neni magicky\n");
    }
}

int main()
{
    Uloha71();
}