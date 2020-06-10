#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
bool validation(string a)
{
    int count[26] = {0};
    char idx = 'A';
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (islower(a[i]))
        {
            idx = 'a';
        }
        else
        {
            idx = 'A';
        }

        if (count[a[i] - idx] + 1 == 2)
        {
            return false;
        }
        else
        {
            count[a[i] - idx] += 1;
        }
    }
    return true;
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!validation(argv[1]))
    {
        printf("Not validate!\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        string text;
        do
        {
            text = get_string("plaintext:  ");
        }
        while (text[0] == '\0');

        printf("ciphertext: ");
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (isalpha(text[i]))
            {
                if (isupper(text[i]))
                {
                    if (islower(key[text[i] - 'A']))
                    {
                        printf("%c", key[text[i] - 'A'] - 32);
                    }
                    else
                    {
                        printf("%c", key[text[i] - 'A']);
                    }
                }
                else
                {
                    if (isupper(key[text[i] - 'a']))
                    {
                        printf("%c", key[text[i] - 'a'] + 32);
                    }
                    else
                    {
                        printf("%c", key[text[i] - 'A']);
                    }
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