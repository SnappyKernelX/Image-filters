#include "helpers.h"
#include <math.h>

//to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i =0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            int temp;

            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width -1 - j].rgbtBlue;
            image[i][width -1 - j].rgbtBlue = temp;

            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width -1 - j].rgbtGreen;
            image[i][width -1 - j].rgbtGreen = temp;

            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width -1 - j].rgbtRed;
            image[i][width -1 - j].rgbtRed = temp;
        }
    }
    return;
}

// Blurring
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];

    for (int i=0; i< height; i++)
    {
        for (int j=0; j< width; j++)
        {
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i=0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            int k = 0;
            int avg_g=0, avg_b=0, avg_r=0;

            for (int m = (i-1); m < (i+2); m++)
            {
                for (int n = (j-1); n < (j+2); n++)
                {
                    if (m < 0 || n < 0 || m > (height-1) || n > (width-1))
                    {
                        continue;
                    }
                    avg_g += image_copy[m][n].rgbtGreen;
                    avg_b += image_copy[m][n].rgbtBlue;
                    avg_r += image_copy[m][n].rgbtRed;
                    k++;
                }
            }

            image[i][j].rgbtGreen = (int) round((float) avg_g / k);
            image[i][j].rgbtBlue = (int) round((float) avg_b / k);
            image[i][j].rgbtRed = (int) round((float) avg_r / k);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];

    for (int i=0; i< height; i++)
    {
        for (int j=0; j< width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    int Gx[3][3] =
    {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    int Gy[3][3] =
    {
        {-1,-2,-1},
        {0,0,0},
        {1,2,1}
    };

    for (int i=0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            int gx_g=0, gx_b=0, gx_r=0, gy_g=0, gy_b=0, gy_r=0;

            for (int m = (i-1), y = 0; m < (i+2); m++, y++)
            {
                for (int n = (j-1), z = 0; n < (j+2); n++, z++)
                {
                    if (m < 0 || n < 0 || m > (height-1) || n > (width-1))
                    {
                        gx_g += (Gx[y][z] * 0);
                        gx_b += (Gx[y][z] * 0);
                        gx_r += (Gx[y][z] * 0);

                        gy_g += (Gy[y][z] * 0);
                        gy_b += (Gy[y][z] * 0);
                        gy_r += (Gy[y][z] * 0);
                    }
                    else
                    {
                        gx_g += (Gx[y][z] * image_copy[m][n].rgbtGreen);
                        gx_b += (Gx[y][z] * image_copy[m][n].rgbtBlue);
                        gx_r += (Gx[y][z] * image_copy[m][n].rgbtRed);

                        gy_g += (Gy[y][z] * image_copy[m][n].rgbtGreen);
                        gy_b += (Gy[y][z] * image_copy[m][n].rgbtBlue);
                        gy_r += (Gy[y][z] * image_copy[m][n].rgbtRed);
                    }
                }
            }

            int g_new = (int) round(sqrt((pow(gx_g, 2) + pow(gy_g, 2))));
            if (g_new > 255)
            {
                g_new = 255;
            }
            int b_new = (int) round(sqrt((pow(gx_b, 2) + pow(gy_b, 2))));
            if (b_new > 255)
            {
                b_new = 255;
            }
            int r_new = (int) round(sqrt((pow(gx_r, 2) + pow(gy_r, 2))));
            if (r_new > 255)
            {
                r_new = 255;
            }

            image[i][j].rgbtGreen = g_new;
            image[i][j].rgbtBlue = b_new;
            image[i][j].rgbtRed = r_new;
        }
    }
    return;
}
