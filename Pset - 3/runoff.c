#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// candidates stores every single candidate's index:
candidate candidates[MAX_CANDIDATES];

// Minimum votes given to candidates:
int min_vote[MAX_CANDIDATES][MAX_VOTERS];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Number of eliminated candidates:
int elim;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Loop through candidate names
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Updating preferences:
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Updating the votes of each candidate using preferences;
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Index 0 represents the first preference:
            if (preferences[i][0] == j)
            {
                if (candidates[j].eliminated == false)
                {
                    candidates[j].votes++;
                }
                else
                {
                    int eli = 1;
                    int m = j;
                    while (candidates[m].eliminated == true)
                    {
                        for (int k = 0; k < candidate_count; k++)
                        {
                            if (preferences[i][0 + eli] == k)
                            {
                                m = k;
                                break;
                            }
                        }
                    }
                    if (candidates[m].eliminated == false)
                    {
                        candidates[m].votes++;
                    }

                }

            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // A candidate wins who has more than 50% first preference;
    int win = (voter_count / 2);

    // Check if any candidate has more than half the votes:

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes > win)
            {
                printf("\n%s\n", candidates[i].name);
                return true;
            }
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int k = candidate_count - 1 - elim;
    int min = 0;

    // Find candidate(s) with the minimum votes:
    for (int i = 0; i < candidate_count; i++)
    {
        int mun = 0;
        if (!candidates[i].eliminated)
        {
            for (int j = k; j > i; j--)
            {
                if (candidates[j].eliminated == true)
                {
                    j --;
                    continue;
                }
                else if (i == k)
                {
                    if (candidates[i].votes <= candidates[i - 1].votes)
                    {

                        min = candidates[i].votes;
                        break;

                    }
                }
                else
                {
                    if (candidates[i].votes <= candidates[j].votes)
                    {
                        mun ++;
                    }
                }

                if (mun == (k - i - elim))
                {
                    min = candidates[i].votes;
                }
            }
        }
    }
    return 0;
}


// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int tied = 0;
    // Check whether all are tied or not:
    for (int i = 0; i < candidate_count; i ++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                tied ++;
            }
        }
    }
    if (tied == candidate_count - elim)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // Loop through all candidates within min:
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            elim++;
        }
    }
    return;
}
