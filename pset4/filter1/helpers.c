#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy
    int sepiaRed = 0, sepiaGreen = 0, sepiaBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaGreen  = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            image[i][j].rgbtRed = sepiaRed < 255? sepiaRed: 255;
            image[i][j].rgbtGreen = sepiaGreen < 255? sepiaGreen: 255;
            image[i][j].rgbtBlue = sepiaBlue < 255? sepiaBlue: 255;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
RGBTRIPLE avg(RGBTRIPLE neighbor[], int num)
{
    int red = 0, blue = 0, green = 0;
    RGBTRIPLE result;
    for (int i = 0; i < num; i++)
    {
        red  += neighbor[i].rgbtRed;
        blue += neighbor[i].rgbtBlue;
        green += neighbor[i].rgbtGreen;
    }
    result.rgbtRed = round(red / (float) num);
    result.rgbtBlue = round(blue / (float) num);
    result.rgbtGreen = round(green / (float) num);
    return result;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int idx[3] = {1, 0, -1};
    RGBTRIPLE neighbor[9];
    int counter = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            counter = 0;
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    if (i + idx[a] >= 0 && j + idx[b] >= 0 && i + idx[a] < height && j + idx[b] < width)
                    {
                        neighbor[counter] = image[i + idx[a]][j + idx[b]];
                        counter++;
                    }

                }
            }
            copy[i][j] = avg(neighbor, counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
