#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            // Find out the average colour value of the pixel:
            int avg = roundf((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);

            // Assign the average value to pixel:
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel in the image:
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // Stores the original red, green, blue values of pixel:
                int originalBlue = image[i][j].rgbtBlue;
                int originalGreen = image[i][j].rgbtGreen;
                int originalRed = image[i][j].rgbtRed;

            // Change the rgbt values of pixel based on the algorithm;
            int sepiaGreen = roundf(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = roundf(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int sepiaRed = roundf(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            // Check if the values are within 0 and 255;
            check(&sepiaBlue, &sepiaGreen, &sepiaRed);

            // Assign new values of green, blue and red to the pixel:
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every single row:
    for (int i = 0; i < height; i++)
    {
        int k = 1;
        // Swap elements at the extreme ends for each row:
        for (int j = 0; j != k; j++)
        {
            for (k = width - j - 1; k > j; k--)
            {
                swap(&image[i][j], &image[i][k]);
                break;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy:
    RGBTRIPLE image_copy[height][width];

    // store the original values:
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            // Give the function the address of the pixels:
            store(&image[a][b], &image_copy[a][b]);
        }
    }

    // Loop through the image array:
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check for edge cases and store the return value:
            char result = check_case(i, j, (height - 1), (width- 1));

            if (result == 'e')
            {
                // Addresses to give the function edge_case;
                if (i == 0 && j == 0)

                    edge_case(&image_copy[i][j], &image_copy[i][j + 1], &image_copy[i + 1][j], &image_copy[i + 1][j + 1], &image[i][j]);

                else if (i == height - 1&& j == 0)

                        edge_case(&image_copy[i][j], &image_copy[i - 1][j], &image_copy[i - 1][j + 1], &image_copy[i][j + 1], &image[i][j]);

                else if (j == width - 1 && i == 0)

                        edge_case(&image_copy[i][j], &image_copy[i][j - 1], &image_copy[i + 1][j - 1], &image_copy[i + 1][j], &image[i][j]);

                    else if (i == height && j == width)

                        edge_case(&image_copy[i][j], &image_copy[i][j - 1], &image_copy[i - 1][j], &image_copy[i - 1][j - 1], &image[i][j]);
            }

            // Edge cases (6 blocks);
            else if (result == 'd')
            {
                int avgrBlue = 0, avgrGreen = 0, avgrRed = 0;
                //Here we can use loops to pass pointers to functions:
                // 2 columns, 1 row;
                if (i == 0 || i == width)
                {
                    if (i == 0)
                    {
                        for (int k = i; k < i + 2; k++)
                        {
                            for (int l = j - 1; l < j + 2; l++)
                            {
                                end_case(&avgrBlue, &avgrGreen, &avgrRed, &image_copy[k][l]);
                            }
                        }
                        end_c(&avgrBlue, &avgrGreen, &avgrRed, &image[i][j]);
                    }
                    else
                    {
                        for (int k = i; k > i - 2; k--)
                        {
                            for (int l = j - 1; l < j + 2; j++)
                            {
                                end_case(&avgrBlue, &avgrGreen, &avgrRed, &image_copy[k][l]);
                            }
                        }
                        end_c(&avgrBlue, &avgrGreen, &avgrRed, &image[i][j]);
                    }
                }
                // Cases here require 2 rows and 1 column;
                else
                {
                    if (j == 0)
                    {
                        for (int k = i - 1; k < i + 2; k++)
                        {
                            for (int l = j; l < j + 2; l++)
                            {
                                end_case(&avgrBlue, &avgrGreen, &avgrRed, &image_copy[k][l]);
                            }
                        }
                        end_c(&avgrBlue, &avgrGreen, &avgrRed, &image[i][j]);
                    }
                    else
                    {
                        for (int k = i - 1; k < i + 2; k++)
                        {
                            for (int l = j - 1; l < j + 2; l++)
                            {
                                end_case(&avgrBlue, &avgrGreen, &avgrRed, &image_copy[k][l]);
                            }
                        }
                        end_c(&avgrBlue, &avgrGreen, &avgrRed, &image[i][j]);
                    }
                }
            }
            // Normal case, 9 blocks;
            else
            {
                int avgrBlue = 0, avgrGreen = 0, avgrRed = 0;
                for (int k = i - 1; k < i + 2; k++)
                {
                    for (int l = j - 1; l < j + 2; l++)
                    {
                        norm_case(&avgrBlue, &avgrGreen, &avgrRed, &image_copy[k][l]);
                    }
                }
                normal(&avgrBlue, &avgrGreen, &avgrRed, &image[i][j]);
            }
        }
    }
    return;
}

// Create edges in the image;
void edge(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height + 2][width + 2];
    // Create a copy of the all the pixels;
    for (int i = 0; i <= height + 1; i++)
    {
        for (int j = 0; j <= width + 1; j++)
        {
            // Creating the copy with a black box;
            if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
            {
                image_copy[i][j].rgbtBlue = 0;
                image_copy[i][j].rgbtGreen = 0;
                image_copy[i][j].rgbtRed = 0;
            }
            // Now we can treat every single block alike;
            else

                store(&image[i - 1][j - 1], &image_copy[i][j]);
        }
    }

    // Loop through pixels;
    for (int i = 0; i < height; i++)
    {
        // In image_copy, the values are 1 index ahead of the original values;
        for (int j = 0; j < width; j++)
        {
            // Implement Gx and Gy for each pixel;
            int gxblue = 0, gxgreen = 0, gxred = 0;
            int gyblue = 0, gygreen = 0, gyred = 0;

            // Remember that the copy has all the values at +1 the original values;
            for (int k = i + 1; k <= i + 3; k++)
            {
                int timesx = 0;
                for (int l = j + 1; l <= j + 3; l++)
                {
                    // Implement Gx;
                    timesx++;
                    edge_gx(timesx, &image_copy[k - 1][l - 1], &gxblue, &gxgreen, &gxred);

                    // Implement Gy;
                    edge_gy(timesx, &image_copy[k - 1][l - 1], &gxblue, &gxgreen, &gxred);
                }
            }
            square(&gxblue, &gxgreen, &gxred, &gyblue, &gygreen, &gyred, &image[i][j]);

        }
    }
}

// Check values or cap them to 255;
void check(int *b, int *g, int *r)
{
    if (*b > 255)

        *b = 255;

    if (*g > 255)

        *g = 255;

    if (*r > 255)

        *r = 255;
}

// Swap colours of two pixels:
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    // Store values of one pixel in temporary variables:
    int pixelBlue = (*pixel1).rgbtBlue;
    int pixelGreen = (*pixel1).rgbtGreen;
    int pixelRed = (*pixel1).rgbtRed;

    // Swap one pixels values to another:
    (*pixel1).rgbtBlue = (*pixel2).rgbtBlue;
    (*pixel1).rgbtGreen = (*pixel2).rgbtGreen;
    (*pixel1).rgbtRed = (*pixel2).rgbtRed;

    // Assign the values stored in temporary variable:
    (*pixel2).rgbtBlue = pixelBlue;
    (*pixel2).rgbtGreen = pixelGreen;
    (*pixel2).rgbtRed = pixelRed;

}

// Store values;
void store(RGBTRIPLE *images_add, RGBTRIPLE *images_copy)
{
    (*images_copy).rgbtBlue = (*images_add).rgbtBlue;
    (*images_copy).rgbtGreen = (*images_add).rgbtGreen;
    (*images_copy).rgbtRed = (*images_add).rgbtRed;
}


char check_case(int a, int b, int h, int w)
{
    // Check for corner case (4 blocks);
    if (abs(a - b) == 0 || abs(a - b) == w || abs(a - b) == h || (a == h && b == w))

        return 'e';


    // Check for end case (6 blocks);
    else if (a == 0 || b == 0 || a == h || b == w)

        return 'd';


    // Check for normal case (9 blocks);
    else

        return 'n';

}

// Edge function takes in 4 blocks:
void edge_case(RGBTRIPLE *copy1, RGBTRIPLE *copy2, RGBTRIPLE *copy3, RGBTRIPLE *copy4, RGBTRIPLE *original)
{
    // We have to change the original pixels contents:

    (*original).rgbtBlue = ((*copy1).rgbtBlue + (*copy2).rgbtBlue + (*copy3).rgbtBlue + (*copy4).rgbtBlue) / 4;
    (*original).rgbtGreen = ((*copy1).rgbtGreen + (*copy2).rgbtGreen + (*copy3).rgbtGreen + (*copy4).rgbtGreen) / 4;
    (*original).rgbtRed = ((*copy1).rgbtRed + (*copy2).rgbtRed + (*copy3).rgbtRed + (*copy4).rgbtRed) / 4;
}

// Increments the values of red, green and blue;
void end_case(int *b, int *g, int *r, RGBTRIPLE *copy)
{
    *b += (*copy).rgbtBlue;
    *g += (*copy).rgbtGreen;
    *r += (*copy).rgbtRed;
}

// Assign values  to the original struct;
void end_c(int *b, int *g, int *r, RGBTRIPLE *original)
{
    (*original).rgbtBlue = *b / 6;
    (*original).rgbtGreen = *g / 6;
    (*original).rgbtRed = *r / 6;
}
// Helps calculating averages in normal case;
void norm_case(int *b, int *g, int *r, RGBTRIPLE *copy)
{
    *b += (*copy).rgbtBlue;
    *g += (*copy).rgbtGreen;
    *r += (*copy).rgbtRed;
}

// Assign value to original pixel;
void normal(int *b, int *g, int *r, RGBTRIPLE *original)
{
    (*original).rgbtBlue = *b / 9;
    (*original).rgbtGreen = *g / 9;
    (*original).rgbtRed = *r / 9;
}

// Apply Gx to pixel and get values of gx for red, green and blue;
void edge_gx(int a, RGBTRIPLE *copy1, int *xblue, int *xgreen, int *xred)
{
    // a, b, c = timesx are used to check for the what to apply;
    if (a % 2 != 0)
    {
        if ((a / 2) < 1) // odd;
        {
            // -1 case
            *xblue += -1 *(*copy1).rgbtBlue;
            *xgreen += -1 * (*copy1).rgbtGreen;
            *xred += -1 * (*copy1).rgbtRed;
        }
        else
        {
            // 1 case;
            *xblue += 1 *(*copy1).rgbtBlue;
            *xgreen += 1 * (*copy1).rgbtGreen;
            *xred += (*copy1).rgbtRed;
        }
    }
    else
    {
        // 2 case;
        if ((a / 2) < 1)
        {
            *xblue += 2 *(*copy1).rgbtBlue;
            *xgreen += 2 * (*copy1).rgbtGreen;
            *xred += 2 * (*copy1).rgbtRed;
        }
        else
        {
            *xblue += (-2 *(*copy1).rgbtBlue);
            *xgreen += (-2 * (*copy1).rgbtGreen);
            *xred += (-2 * (*copy1).rgbtRed);
        }
    }
    return;
}

void edge_gy(int a, RGBTRIPLE *copy2, int *yblue, int *ygreen, int *yred)
{
    if (a % 2 != 0)
    {
        // 1 case;
        if ((a / 2) < 1)
        {
            // Negative 1 case;
            *yblue += -1 * (*copy2).rgbtBlue;
            *ygreen += -1 * (*copy2).rgbtGreen;
            *yred += -1 * (*copy2).rgbtRed;
        }
        else
        {
            // Postive 1 case;
            *yblue += 1 * (*copy2).rgbtBlue;
            *ygreen += 1 * (*copy2).rgbtGreen;
            *yred += 1 * (*copy2).rgbtRed;
        }
    }
    else
    {
        if ((a / 2) < 1)
        {
            // Negative 2 case;
            *yblue += -2 * (*copy2).rgbtBlue;
            *ygreen += -2 * (*copy2).rgbtGreen;
            *yred += -2 * (*copy2).rgbtRed;
        }
        else
        {
            // Positive 2 case;
            *yblue += 2 * (*copy2).rgbtBlue;
            *ygreen += 2 * (*copy2).rgbtGreen;
            *yred += 2 * (*copy2).rgbtRed;
        }
    }
    return;
}

// Calculate and return square root sums to update original value;
int square(int *xb, int *xg, int *xr, int *yb, int *yg, int *yr, RGBTRIPLE *original)
{
    // Intializing integers for checking;
    int b = 0, g = 0, r = 0;

    b = roundf(sqrt((*xb * *xb) + (*yb * *yb)));
    g = roundf(sqrt((*xg * *xg) + (*yg * *yg)));
    r = roundf(sqrt((*xr * *xr) + (*yr * *yr)));

    check(&b, &g, &r);

    // Assign new values to original pixel;
    (*original).rgbtBlue = b;
    (*original).rgbtGreen = g;
    (*original).rgbtRed = r;

    return 0;
}
