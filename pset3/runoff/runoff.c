#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 100

typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];
int preference[MAX_VOTERS][MAX_CANDIDATES];
int num_candidates;
int num_voters;


bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    if (argc > MAX_CANDIDATES + 1 || argc < 2)
    {
        return 1;
    }

    //initialization
    num_candidates = argc - 1;

    for (int i = 0; i < num_candidates; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }


    do
    {
        num_voters = get_int("Number of voters: ");
    }
    while (num_voters <= 0);


    //vote part
    string name;
    for (int i = 0; i < num_voters; i++)
    {
        //rank
        for (int j = 0; j < num_candidates; j++)
        {
            do
            {
                name = get_string("Rank %i: ", j + 1);
            }
            while(!vote(i, j, name));
        }
        printf("\n");
    }

    int min;

    while(true)
    {
        tabulate();
        if(!print_winner())
        {
            min = find_min();
            if (!is_tie(min))
            {
                eliminate(min);
            }
            else
            {
                printf("The election is a tie.\n");
                break;
            }

        }
        else
        {
            break;
        }

    }

    return 0;

}

bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < num_candidates; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            //check if candidate is voted by the same voter.
            for (int j = 0; j < rank; j++)
            {
                if (preference[voter][j] == i)
                {
                    return false;
                }
            }
            preference[voter][rank] = i;
            return true;
        }
    }
    return false;
}

void tabulate(void)
{
    for (int i = 0; i < num_candidates; i++)
    {
        candidates[i].votes = 0;
    }

    for (int i = 0; i < num_voters; i++)
    {
        //check rank 0, if eliminate, check next one.
        for (int j = 0; j < num_candidates; j++)
        {
            if (candidates[preference[i][j]].eliminated == false)
            {
                candidates[preference[i][j]].votes += 1;
                break;
            }
            else
            {
                continue;
            }
        }
    }

}

bool print_winner(void)
{
    int condition = num_voters/2 + 1;
    for (int i = 0; i < num_candidates; i++)
    {
        if (candidates[i].votes >= condition)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

int find_min(void)
{
    int min = num_voters;
    for (int i = 0; i < num_candidates; i++)
    {
        if (candidates[i].votes < min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

bool is_tie(int min)
{
    for (int i = 0; i < num_candidates; i++)
    {
        if (candidates[i].votes != min && candidates[i].eliminated == false)
        {
            return false;
        }
    }

    return true;
}

void eliminate(int min)
{
    for (int i = 0; i < num_candidates; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            candidates[i].eliminated = true;
        }
    }
}