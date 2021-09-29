#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Max number of candidates
const int MAX = 9;

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of Candidates:
int candidate_count;
int voter_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i.\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
            continue;
        }
    }
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Check whether the vote is given to a valid candidate or not:
    for (int i = 0; i < candidate_count; i ++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes ++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner()
{
    if (voter_count != 0)
    {
        int win = (voter_count / candidate_count) + 1;
        int ab = 0;

        // Print the name of the winner:
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes >= win)
            {
                printf("%s\n", candidates[i].name);
                ab ++;
            }
        }
        // If there are no absolute winners:
        if (ab == 0)
        {
            int can_ind = candidate_count - 1;
            for (int j = 0; j < candidate_count; j++)
            {
                int count = 0;
                for (int k = can_ind; k > j; k--)
                {
                    if (candidates[j].votes >= candidates[k].votes)
                    {
                        count ++;
                    }
                }
                if (count == (can_ind - j))
                {
                    printf("%s\n", candidates[j].name);
                }
            }
        }
    }
    else
    {
        printf("No one voted\n.");
    }
}

