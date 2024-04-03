#include "helpers.h"
#include <math.h>

#define BLUE_COLOR 0
#define GREEN_COLOR 1
#define RED_COLOR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int colum = 0; colum < width; colum++)
        {
            int rgbGray = round((image[row][colum].rgbtBlue + image[row][colum].rgbtGreen + image[row][colum].rgbtRed) / 3.0);
            image[row][colum].rgbtBlue = rgbGray;
            image[row][colum].rgbtGreen = rgbGray;
            image[row][colum].rgbtRed = rgbGray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;
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
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

int get_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float count = 0;
    int sum = 0;
    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int colum = j - 1; colum <= (j + 1); colum++)
        {
            if (row < 0 || row >= height || colum < 0 || colum >= width)
            {
                continue;
            }
            if (color_position == RED_COLOR)
            {
                sum += image[row][colum].rgbtRed;
            }
            else if (color_position == GREEN_COLOR)
            {
                sum += image[row][colum].rgbtGreen;
            }
            else
            {
                sum += image[row][colum].rgbtBlue;
            }
            count++;
        }
    }
    return round(sum / count);
}

// Blur image
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

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = get_blur(i, j, height, width, copy, BLUE_COLOR);
            image[i][j].rgbtGreen = get_blur(i, j, height, width, copy, GREEN_COLOR);
            image[i][j].rgbtRed = get_blur(i, j, height, width, copy, RED_COLOR);
        }
    }
    return;
}
