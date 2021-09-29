#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Defining a new data type to use for storing the jpegs buffer;
typedef uint8_t BYTE;

int main(int argc, char *argv[2])
{
    // Make sure that the user enters exactly one command line argument;
    if (argc != 2)
    {
        printf("Usage: ./recover 'filename'...\n");
        return 1;
    }

    // Open a file to read contents from it;
    FILE *file = fopen(argv[1], "r");

    // Check if the file can be read or not;
    if (!file)
    {
        printf("Cannot be read.\n");
        return 1;
    }

    // Create a place for storing the 4 buffer of JPEG;
    BYTE buffer[512];
    int times = 0, how_long = 1;

    // Here, we created a file pointer to save the original pointer;
    FILE *ptr;

    // Filename gets some space in memory;
    char *filename = malloc(7);

    while (how_long > 0)
    {
        how_long = fread(buffer, 512, 1, file);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // JPEG FOUND;
            times ++;

            if (times == 1)
            {
                 // Pointer to a string;
                sprintf(filename, "%03i.jpg", times);

                FILE *image = fopen(filename, "w");
                ptr = image;

                // Write in this file;
                fwrite(buffer, 512, 1, image);
            }

            else
            {
                // Close the last file;
                fclose(ptr);

                // Open a new file with a new file name;
                sprintf(filename, "%03i.jpg", times);

                FILE *image = fopen(filename, "w");
                ptr = image;

                fwrite(buffer, 512, 1, image);
            }
        }
        else if (times != 0)
        {
            // Continue writing in the same file;
            fwrite(buffer, 512, 1, ptr);
        }
    }
    fclose(ptr);
    free(filename);
    return 0;
}