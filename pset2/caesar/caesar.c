#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
bool check_val(string a)
{
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if ((int) a[i] < 48 || (int) a[i] > 57)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, string argv[])
{
    if (argc != 2 || check_val(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
    }
    else
    {
        int key = atoi(argv[1]);
        string text;
        do
        {
            text = get_string("plaintext:  ");
        }
        while(text[0] == '\0');

        printf("ciphertext: ");
        for (int i= 0, n = strlen(text); i < n; i++)
        {

            if (isalpha(text[i]))
            {
                if (isupper(text[i]))
                {
                    printf("%c", (text[i] - 65 + key) % 26 + 65);
                }
                else
                {
                    printf("%c", (text[i] - 97 + key) % 26 + 97);
                }
            }
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");


    }
}