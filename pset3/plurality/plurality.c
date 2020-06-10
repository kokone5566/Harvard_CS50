#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#define MAX 9
typedef struct
{
    string name;
    int votes;
}
candidate;

bool vote(string name);
void print_winner(void);

candidate candidates[MAX];
int num_candidate;

int main(int argc, string argv[])
{
    if (argc > MAX + 1 || argc < 2)
    {
        return 1;
    }

    num_candidate = argc - 1;

    for (int i = 0; i < num_candidate; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int num;
    do
    {
        num = get_int("Number of voters: ");
    }
    while (num <= 0);
    for (int i = 0; i < num; i++)
    {
        string voter = get_string("Vote: ");
        if (!vote(voter))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();

}

bool vote(string name)
{
    for (int i = 0; i < num_candidate; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;

}

void print_winner(void)
{
    int max = 0;
    for (int i = 0; i < num_candidate; i++)
    {
        if (max < candidates[i].votes)
        {
            max = candidates[i].votes;
        }
    }

    for (int i = 0; i < num_candidate; i++)
    {
        if (max == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}