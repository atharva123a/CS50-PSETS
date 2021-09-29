#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution 'KEY'.");
        return 1;
    }

    string key = argv[1];
    int len = strlen(key);
    int char_count = 0;

    for (int i = 0; i < len; i++)
    {
        //reduces the amount of memory usage since, all chars are converted to uppercase.
        if (toupper(key[i]) >= 'A' && toupper(key[i]) <= 'Z')
        {
            char_count ++;
        }
        else //tell the user to enter valid characters;
        {
            printf("error: Enter alphabetical characters only!");
            return 1;
        }
    }

    if (char_count != 26)
    {
        printf("error: enter 26 characters only!\n");
        return 1;
    }

    else //only if 26 alphabets are entered:
    {
        for (int j = 0; j < 25; j++)
        {
            for (int k = 25; k > j; k--)
                //the condition is such that, at every iteration, the for loop will check for one less char.
            {
                if (key[k] != key[j])
                {
                    continue;
                }
                else
                {
                    printf("error: enter non-repeating characters.\n");
                    return 1;
                }
            }
        }
    }
    printf("\n");

    string plain_text = get_string("plain text: ");
    int length = strlen(plain_text);
    string cypher_text = NULL;

    printf("cypher_text:");
    for (int ind = 0; ind < length; ind++)
    {
        //to check whether the variable in plain_text[a] is lowercase:
        if (plain_text[ind] >= 'a' && plain_text[ind] <= 'z')
        {
            //use ASCII code to determine position of that particular char.
            printf("%c", tolower(key[plain_text[ind] - 97]));
        }
        else if (plain_text[ind] >= 'A' && plain_text[ind] <= 'Z')
        {
            //as per ASCII 'A' has int value 65;
            printf("%c", toupper(key[plain_text[ind] - 65]));
        }
        else
        {
            //telling the program to basically ignore anything other than alphabets
            printf("%c", plain_text[ind]);
        }
    }
    printf("\n\n");
}