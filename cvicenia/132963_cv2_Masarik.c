#include <stdio.h>
#include<math.h>
#include <stdbool.h>

int main() 
{
    
    //uloha 2.1
    printf("\nUloha 2.1\n");
    double a, b, c;

    scanf("%lf %lf %lf", &a, &b, &c);
    printf("Priemer cisel %g, %g, %g je: %g\n", a, b, c, (a+b+c)/3.0);

    //uloha 2.2
    printf("\nUloha 2.2\n");

    double height, weight;
    scanf("%lf %lf", &height, &weight);
    printf("BMI: %.3f", weight/(height*height)*10000);

    //uloha 2.3
    printf("\nUloha 2.3\n");
    double num23;
    scanf("%lf", &num23);

    int intPart = (int)num23;
   
    printf("%d %g\n", intPart, round(num23));
    
    //uloha 2.4
    printf("\nUloha 2.4\n");
    char c1, c2;
    scanf(" %c %c", &c1, &c2);
    printf("%c %d \n%c %d\n", c1-32, c1-32, c2-32, c2-32);
    
    //uloha 2.5
    printf("\nUloha 2.5\n");

    double num15, num25;
    char op25;

    scanf("%lf %lf %c", &num15, &num25, &op25);
    printf("%g %c %g = ", num15, op25, num25);

    if(op25 == '+') 
    {
        printf("%g", num15+num25);
    } 
    else if(op25 == '-') 
    {
        printf("%g", num15-num25);
    } 
    else if(op25 == '*') 
    {
        printf("%g", num15*num25);
    } 
    else if(op25 == '/') 
    {
        printf("%g", num15/num25);
    } 
    else 
    {
        printf("Invalid operator");
    }
    
    //uloha 2.6
    printf("\nUloha 2.6\n");

    double num1, num2;
    char op;

    scanf("%lf %lf %c", &num1, &num2, &op);
    printf("%g %c %g = ", num1, op, num2);

    switch(op) {
        case '+':
            printf("%g", num1+num2);
            break;
        case '-':
            printf("%g", num1-num2);
            break;
        case '*':
            printf("%g", num1*num2);
            break;
        case '/':
            printf("%g", num1/num2);
            break;
        default:
            printf("Invalid operator");
    }

    //uloha 2.7
    printf("\nUloha 2.7\n");
    int a27,b27,c27,d27,e27;
    scanf("%d %d %d %d %d", &a27, &b27, &c27, &d27, &e27);
    int result27 = e27/--a27 * b27++/c27++;
    printf("Vysledok: %d\n", result27);

    int a272,b272,c272,d272,e272;
    scanf("%d %d %d %d %d", &a272, &b272, &c272, &d272, &e272);
    int result272 = (a272 %= b272 = d272 = 1 + e272) / 2;
    printf("Vysledok: %d\n", result272);


    //uloha 2.8
    printf("\nUloha 2.8\n");

    int num28;
    scanf("%d", &num28);
    double min28, max28;
    for(int i = 0; i < num28; i++) 
    {
        double num282;
        scanf("%lf", &num282);
        if(i == 0) 
        {
            min28 = num282;
            max28 = num282;
        }

        if(num282 < min28) 
        {
            min28 = num282;
        }

        if(num282 > max28) 
        {
            max28 = num282;
        }
    }
    printf("Minimum: %g \nMaximum: %g\n", min28, max28);
    
    //uloha 2.9
    printf("\nUloha 2.9\n");

    int num29;

    int array[11];
    bool postupnost = true;
    for(int i = 0; i<11; i++) 
    {
       scanf("%d", &num29);
       if(i == 0 && num29 >= 0 && num29 <= 10)
       {
            array[0] = num29;
            continue;
       }
       if(num29 > 1 && array[i-1]*2 >= num29 && num29 >= array[i-1]/2) 
       {
        array[i] = num29;
        continue;
       }
        postupnost = false;
    }
    if(postupnost) 
    {
        printf("Postupnost je spravna\n");
    } 
    else 
    {
        printf("Postupnost je nespravna\n");
    }
}