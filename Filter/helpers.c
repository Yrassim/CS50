#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float gray; // using this variable to stock the average result

    // 2 loops to go and change every pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // formula to get a gray image
            gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);

            // check if the the pixel is over 255 to stop there to not have overflow
            if (gray > 255)
            {
                gray = 255;
            }

            // change every colore of the pixel
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    // 2 loops to go and change every pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // using this variable to stock the color result after using the formula
            float sepiaRed;
            float sepiaGreen;
            float sepiaBlue;

            // Change every colore of the pixel following the spia formula
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // check if the the pixel is over 255 to stop there to not have overflow
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // change every colore of the pixel
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
    // 2 loops to go and change every pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // using this variable to stock the colors after switching between them
            float reflectRed;
            float reflectGreen;
            float reflectBlue;

            // change every colore of the pixel
            // switch bleu pixel
            reflectBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = reflectBlue;

            // switch green pixel
            reflectGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = reflectGreen;

            // switch red pixel
            reflectRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = reflectRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //an other image table to not alter the original
    RGBTRIPLE tempImage[height][width];

    // 2 loops to go and change every pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // we have 9 different steps to change the image.
            if (i == 0)
            {
                if (j == 0) // left up corner
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i +
                                                      1][j].rgbtBlue) / 4.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i +
                                                       1][j].rgbtGreen) / 4.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i +
                                                     1][j].rgbtRed) / 4.00);
                }
                else if (j == width - 1) // right up corner
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i +
                                                      1][j].rgbtBlue) / 4.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i +
                                                       1][j].rgbtGreen) / 4.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i +
                                                     1][j].rgbtRed) / 4.00);
                }
                else // the top edge
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i +
                                                      1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 6.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i +
                                                       1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 6.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i +
                                                     1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 6.00);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0) // left down corner
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j +
                                                      1].rgbtBlue) / 4.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j +
                                                       1].rgbtGreen) / 4.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j +
                                                     1].rgbtRed) / 4.00);
                }
                else if (j == width - 1) //right down corner
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i -
                                                      1][j].rgbtBlue) / 4.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i -
                                                       1][j].rgbtGreen) / 4.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i -
                                                     1][j].rgbtRed) / 4.00);
                }
                else // the bottom edge
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i -
                                                      1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 6.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i -
                                                       1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 6.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i -
                                                     1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 6.00);
                }
            }
            else
            {
                if (j == 0) // the right edge
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j +
                                                      1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue)/ 6.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j +
                                                       1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j +
                                                     1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.00);
                }
                else if (j == width - 1) // the left edge
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j -
                                                      1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j -
                                                       1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j -
                                                     1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.00);
                }
                else // the rest: the middle
                {
                    tempImage[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j +
                                                      1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                                      image[i][j + 1].rgbtBlue) / 9.00);
                    tempImage[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j +
                                                       1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                                       image[i][j + 1].rgbtGreen) / 9.00);
                    tempImage[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j +
                                                     1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                                     image[i][j + 1].rgbtRed) / 9.00);
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // change every colore of the pixel
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
        }
    }

    return;
}
