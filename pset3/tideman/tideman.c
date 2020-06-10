#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 100

typedef struct
{
    int winner;
    int loser;
}pair;


int preferences[MAX_CANDIDATES][MAX_CANDIDATES] = {0};
int candidate_count;
int pair_count = 0;
pair pairs[MAX_CANDIDATES * (MAX_CANDIDATES - 1) / 2];
int locked[MAX_CANDIDATES][MAX_CANDIDATES] = {0};
string candidates[MAX_CANDIDATES];
int num_voters;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void quick_sort(int start, int end);
void lock_pairs(void);
bool cycle(int s, int t);
void print_winner(void);


int main(int argc, string argv[])
{
    //initial
    if (argc > MAX_CANDIDATES + 1 || argc < 2)
    {
        return 1;
    }

    //initialization
    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
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
        int ranks[candidate_count];
        for (int j = 0; j < candidate_count; j++)
        {
            do
            {
                name = get_string("Rank %i: ", j + 1);
            }
            while(!vote(j, name, ranks));
        }
        printf("\n");
        record_preferences(ranks);

    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

}

bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            //check if candidate is voted by the same voter.
            for (int j = 0; j < rank; j++)
            {
                if (ranks[j] == i)
                {
                    return false;
                }
            }

            ranks[rank] = i;
            return true;
        }
    }
    //not found
    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
}

void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
            else
            {
                continue;
            }
        }
    }
}

void sort_pairs(void)//sorting algorithm
{
    quick_sort(0, pair_count - 1);
}

void quick_sort(int start, int end)
{
    if (end > start)
    {
        int j = start;
        pair compare = pairs[end];
        for (int i = 0; i < end; i++)
        {
            if ((preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]) > (preferences[compare.winner][compare.loser] - preferences[compare.loser][compare.winner]))
            {
                pair tmp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmp;
                j++;
            }
        }
        //swap
        pair tmp = pairs[j];
        pairs[j] = pairs[end];
        pairs[end] = tmp;
        //left
        quick_sort(start, j - 1);
        //right
        quick_sort(j + 1, end);
    }

}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool cycle(int s, int t)
{
    if (locked[s][t] == 1)
        return true;
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[s][i] == 1)
            {
                return cycle(i, t);
            }
        }
        return false;
    }

}

void print_winner(void)
{
    //1. sum each row, select the guy which the value equals to 0 because there is no one connect to him/her.
    //2. Also, check him/her if they are isolated node or not.
    //1.
    int sum[candidate_count];

    for (int i = 0; i < candidate_count; i++)
    {
        sum[i] = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            sum[i] += locked[j][i];
        }
    }

    int isolated = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (sum[i] == 0)
        {
            //check isolated
            for (int j = 0; j < candidate_count; j++)
            {
                isolated += locked[i][j];
            }

            if (isolated != 0)
            {
                printf("%s\n", candidates[i]);
            }
            else
            {
                //isolated
                continue;
            }
        }
    }
}