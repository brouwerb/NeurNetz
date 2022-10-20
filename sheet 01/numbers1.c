#include <stdio.h>

int main()
{
    printf("numbers 1-10:  ");
    for (int i = 1; i < 11; i++)
    {
        printf("%i ", i);
    }
    
    printf("\n print odd numbers 1-99:  ");
    int i = 1;
    do
    {
        printf("%i ", i);
        i += 2;
    } while (i < 100);

    printf("\n numbers 1 - 100:  ");
    i = 0;
    while(i <= 100)
    {
        printf("%i ", i);
        i +=2;
    }

    printf("\n alphabet a-z:  ");
    for(int i = 'a'; i <= 'z'; ++i)
    {
        printf("%c ", i);
    }
    
    printf("\n")

}