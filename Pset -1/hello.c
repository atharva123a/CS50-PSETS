#include <stdio.h>
#include <cs50.h>

//customizing the printf statement so that it can print anything the user prompts!
int main(void)
{
    string name = get_string("Enter your name here: \n");
    
    printf("Hi there, %s!", name);
}
