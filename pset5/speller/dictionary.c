// Implements a dictionary's functionality
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 16384;
int num_word = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    unsigned int pos = hash(word);
    bool exist = true;
    node *tmp = table[pos];
    //printf("%i\n", pos);
    if (tmp == NULL)
    {
        return false;
    }
    int offset = 0;
    while (tmp)
    {
        exist = true;
        for (int i = 0; word[i] != '\0'; i++)
        {
            offset = 0;
            if (isupper(word[i]))
            {
                offset = 32;
            }
            //check each character
            if ((word[i] + offset) != tmp->word[i])
            {
                exist = false;
                continue;
            }
        }
        if (exist)
        {
            break;
        }
        tmp = tmp->next;
    }
    return exist;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int seed = 31;
    unsigned int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isupper(word[i]))
        {
            sum = sum * seed + word[i] + 32;
        }
        else
        {
            sum = sum * seed + word[i];
        }

    }
    sum %= N;
    return sum;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    char *word = malloc(sizeof(char)*(LENGTH + 1));

    while(fscanf(dict, "%s", word) != EOF)
    {
        //creat node
        node *n = malloc(sizeof(node));
        for (int i = 0; word[i] != '\0'; i++)
        {
            if (isupper(word[i]))
            {
                word[i] = word[i] + 32;
            }
        }
        strcpy(n->word, word);
        n->next = NULL;
        //hash
        unsigned int pos = hash(word);
        //check if there is node in the position, insert to the front
        if (table[pos] == NULL)
        {
            table[pos] = n;
            num_word++;
        }
        else
        {
            node *tmp = table[pos];
            bool exist = false;
            while (tmp->next != NULL)
            {
                if (strcmp(tmp->word, word) == 0)
                {
                    exist = true;
                    break;
                }
                else
                {
                    tmp = tmp->next;
                }
            }
            if (!exist)
            {
                tmp->next = n;
                num_word++;
            }
        }
    }
    fclose(dict);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return num_word;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        node *cur = table[i];
        while (cur != NULL)
        {
            cur = cur->next;
            free(tmp);
            tmp = cur;
        }
    }
    return true;
}
