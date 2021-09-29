#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
const int MAX = 9;

// preferences[i][j] is number of voters who prefer i over j
int preferences[9][9];

// locked[i][j] means i is locked in over j
bool locked[9][9];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int strength;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair temp[1];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int can_ind = 0;
    // Loop through candidates_names:
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // Update the ranks array:
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Looping through ranks contents:
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (i != candidate_count - 1)
            {
                preferences[ranks[i]][ranks[j]] ++;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int p = ((candidate_count * (candidate_count - 1)) / 2);
    int k = 0;
    // Looping through candidates:
    for (int i = 0; i < p ; i++)
    {
        for (int j = i + 1; j <= p; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                pairs[k].strength = preferences[i][j] - preferences[j][i];
                pair_count ++;
                k++;
            }
            else if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }
            else
            {
                pairs[k].winner = j;
                pairs[k].loser = i;
                pairs[k].strength = preferences[j][i] - preferences[i][j];
                pair_count ++;
                k++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Array for rearranging the pairs indexes:
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j <= pair_count; j++)
        {
            if (pairs[i].strength < pairs[j].strength)
            {
               // Swap them, since one is greater than the other:
               temp[0] = pairs[j];
               pairs[j] = pairs[i];
               pairs[i] = temp[0];
            }
        }
    }
    printf("Indexes of candidates: \n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i ", pairs[i].strength);
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int k = pair_count - 1;
    int cycle_count = 0;
    // Looping through the pairs now rearranged:
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    // Avoid cycles:
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i + (1 % k)].loser] == true)
        {
            cycle_count ++;
        }
    }
    if (cycle_count == pair_count)
    {
        printf("Repeating cycles.\n");
        for (int i = k; i > 1; i--)
        {
            // Check for the equal last numbers:
            for (int j = i - 1; j >= 1; j--)
            {
                if (pairs[i].strength == pairs[j].strength)
                {
                    locked[pairs[i].winner][pairs[i].loser] = false;
                    locked[pairs[j].winner][pairs[j].loser] = false;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    int k = 0;
    int l = 0;
    // Loop through the pairs list one last time:
    for (int i = 0; i < pair_count; i ++)
    {
        for (int j = i + 1; j <= pair_count; j++)
        {
            if (locked[j][i] == false)
            {
                k++;
            }
            else if (locked[j][i] == true)
            {
                break;
            }
        }
    if (k == pair_count - 1)
    {
        printf("Winner: \n%s", candidates[pairs[i].winner]);
    }
    }
    return;
}