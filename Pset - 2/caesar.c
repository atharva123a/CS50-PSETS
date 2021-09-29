#include<stdio.h>
#include<cs50.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, string argv[]) //argv indicates the string of command arguments.
{
    //let's check for the command line arguments:
    int key = 3;

    string plain_text = get_string("plaintext: "); //prompt for text.

    int len = strlen(plain_text);
    printf("cyper text: ");
    for (int i = 0; i < len; i++)
    {

        if (plain_text[i] >= 'a' && plain_text[i] <= 'z') //to ensure the character is an alphabet.
        {

            if (plain_text[i] + key > 'z') //for re-arranging z back to a.
            {
                int mult = ((plain_text[i] + key) - 97) / 26;
                if (mult > 1) //for even higher values!
                {
                    printf("%c", ((plain_text[i] + key)) - (26 * mult));
                }
                else //where the difference is less than 26.
                {
                    printf("%c", ((plain_text[i] + key)) - 26);
                }
            }

            if (plain_text[i] + key < 'z') //alphabet doesn't exceed 'z'.
            {
                printf("%c", plain_text[i] + key);
            }
        }

        else if (plain_text[i] >= 'A' && (plain_text[i]) <= 'Z') //same thing for uppercase.
        {
            if (plain_text[i] + key > 'Z')
            {
                int multi = ((plain_text[i] + key) - 65) / 26;
                if (multi > 1)
                {
                    printf("%c", (plain_text[i] + key) - (26 * multi));
                }
                else
                {
                    printf("%c", (plain_text[i] + key) - 26);
                }
            }
            else
            {
                printf("%c", plain_text[i] + key);
            }
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n"); //for new line.
}