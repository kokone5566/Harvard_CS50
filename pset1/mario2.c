#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height:");
    }while( n<1 || n>8);
    
    for(int i = 0; i < n ; i++)//row
    {
        for (int  j = 0; j < n; j++)//col
        {
            if(j<n-i-1)//space
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for(int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");

    }



}