#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text;
    int letters = 0;
    int words = 0;
    int sentences = 0;
    bool start = false;
    do
    {
        text = get_string("Text: ");
    }
    while (text[0] == '\0');

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int num = (int) text[i];
        if ((num >= 65 && num <= 90) || (num >= 97 && num <= 122))
        {
            letters += 1;
            start = true;
        }
        else if (num == 32 && start == true)
        {
            words += 1;
            start = false;
        }
        else if ((num == 33 || num == 46 || num == 63) && start == true)
        {
            words += 1;
            sentences += 1;
            start = false;
        }
    }
    //printf("letters: %i, words: %i, sentences: %i\n", letters, words, sentences);

    float index = 5.88 * (letters / (float) words) - 29.6 * (sentences / (float) words) - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }

}