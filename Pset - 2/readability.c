#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

int main(void)
{
    //print back what the user enters:
    string text = get_string("\nText:");

    //for a single string:
    int j = strlen(text);
    int char_count = 0;
    int word_count = 1;
    int sent_count = 0;
    //will loop through until the string ends:
    for (int i = 0; i < j; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'z') //checking whether the character entered is an alphabet or not.
        {
            char_count++;
        }
       else
        {
            if (text[i] == ' ') //since a space should not count as a char.
            {
                word_count ++;
            }
            if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
                char_count ++;
                sent_count ++;
            }
            else if (text[i] != ' ')
            {
                char_count ++;
            }
        }
    }
    printf("\n");

    float L = (char_count * 100) / (float)word_count;

    float S = (sent_count * 100) / (float)word_count;

    float index;
    index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1 || index > 16)
    {
        if (index < 1)
        {
            printf("Before grade 1!\n");
        }
        else
        {
            printf("Grade 16+\n");
        }
    }
    else
    {
        printf("Grade %.0f\n", roundf(index) - 1);
    }

}
