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

int get_edges(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    int sum_gx = 0;
    int sum_gy = 0;

    // Use 3x3 matrix to keep the values of Gx and Gy

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int colum = j - 1; colum <= (j + 1); colum++)
        {
            // Pass edges
            if (colum < 0 || colum >= width || row < 0 || row >= height)
            {
                continue;
            }
            if (color_position == BLUE_COLOR)
            {
                sum_gx = sum_gx + image[row][colum].rgbtBlue * gx[row - i + 1][colum - j + 1];
                sum_gy = sum_gy + image[row][colum].rgbtBlue * gy[row - i + 1][colum - j + 1];
            }
            else if (color_position == GREEN_COLOR)
            {
                sum_gx = sum_gx + image[row][colum].rgbtGreen * gx[row - i + 1][colum - j + 1];
                sum_gy = sum_gy + image[row][colum].rgbtGreen * gy[row - i + 1][colum - j + 1];
            }
            else
            {
                sum_gx = sum_gx + image[row][colum].rgbtRed * gx[row - i + 1][colum - j + 1];
                sum_gy = sum_gy + image[row][colum].rgbtRed * gy[row - i + 1][colum - j + 1];
            }
        }
    }

    // If the value exceeds the max channel value of 255, cap the value at the number 255

    return fmin(255, round(sqrt(sum_gx * sum_gx + sum_gy * sum_gy)));
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate over the image pixel by pixel and apply the Sobel operator for each pixel

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = get_edges(i, j, height, width, copy, BLUE_COLOR);
            image[i][j].rgbtGreen = get_edges(i, j, height, width, copy, GREEN_COLOR);
            image[i][j].rgbtRed = get_edges(i, j, height, width, copy, RED_COLOR);
        }
    }
    return;
}
