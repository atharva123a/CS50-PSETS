// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 841;

// The size of the word array in which we store our list
char words[143091][LENGTH + 1]; // for null terminating character;

 // The actual number of words loaded are given by (i - 1);
int ind = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // First check for the index of the word entered using hash function;
    // Copy the char and covert it to lower case;
    int len = strlen(word);

    // Allocate enough space for storing the copied word;
    char cha[len];

    // Iterate over and convert chars to lower case if they are upper case;
    // Also get rid of all the non-alphabetical chars at the end;
    for (int i = 0; i < len; i++)
    {
        // It means the above char is an alphabet;
        if (isalpha(word[i]) != 0)
        {
            // If it is a capital char convert it to lower case;
            if (word[i] >= 65 && word[i] <= 90)
            {
                cha[i] = word[i] + 32;
            }
            else
            {
                cha[i] = word[i];
            }
        }
        else if (i != len - 1)
        {
            cha[i] = word[i];
        }
        // It is a non-alpha char, but in between;
    }

    // Run the hash function and store the index of the array returned;
    int ret = hash(cha, len);
    // Go to the returned value and check if the term exists in the linked list or not;
    // Create an array and only store alphabets in it;


    node *temp = table[ret];
    // Keep on looping until you reach null or find the term;
    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        else
        {
            temp = temp->next;
        }
    }
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word, unsigned int length)
{
    //Title: DJBHash source code;
    //Author: Professor Daniel J. Bernstein;
    //Date: -;
    //Code version: -;
    //Availability:http://www.partow.net/programming/hashfunctions/index.html#RSHashFunction

    // This algorithm was modified for the purpose to be used in our program;

    // 5381 is a magic number, that resulted in very less collisions and hence better performance;
    unsigned int h = 5381;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(word[i]) != 0)
        {
            h = ((h << 5) + h) + (*word);
        }
    }
    return h % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file;
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)

        return false;

    int t = 0;

    // Keep scanning until you reach EOF;
    while (fscanf(file, "%s", words[t]) != EOF)
    {
        t++;
    }
    // Loaded all words in the dictionary into words;

    // For creating a node;
    node *num = NULL;

    // For inserting a node into a linked list;
    node *temp = NULL;

    unsigned int l = 0;
    int i = 0;
    int r = 0;
    // Load elements into node;
    while (i < t)
    {
        num = malloc(sizeof(node));
        if (num == NULL)

            return false;

        // Copy word into node;
        strcpy(num->word, words[i]);
        num->next = NULL;

        l = strlen(words[i]);

        // Now determine the index for inserting load into linked list;
        r = hash(words[i], l);

        temp = table[r];
        table[r] = num;
        num->next = temp;

        num = NULL;
        i++;
    }
    ind = t;
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // The number of words read from the dictionary are basically the (i - 1);
    printf("%i" ,ind);
    return (ind);
    // Basically we stop looping when we reach i > t, where in t is the number of words in words[];
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loop through every single element of the array;
    node *cursor = table[0];
    printf("%i", ind);
    for (int i = 0; i < 841; i++)
    {
        cursor = table[i];
        while (table[i] != NULL)
        {
            cursor = cursor->next;
            free(table[i]);
            table[i] = cursor;
        }
    }
    return true;
}
