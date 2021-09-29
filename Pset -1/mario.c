#include<stdio.h>
#include<cs50.h>

int main(void)
{
    //for loop for taking in the right height:
    int height;
    
    do
    {
        height = get_int("Enter height: \n");
    }
    while(height < 1 || height > 8);
}