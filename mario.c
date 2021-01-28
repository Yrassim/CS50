// less

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        // draw the line for the first shape
        for (int j = 0; j < n - i - 1; j++) // draw the line regarding to the height-number of #
        {
            printf(" ");
        }
        for (int z = 0; z < i + 1; z++)
        {
            printf("#");
        }

        printf("  ");  // print space between the 2 triangles

        // draw the line for the second shape
        for (int z = 0; z < i + 1; z++)
        {
            printf("#");
        }

        printf("\n");  // to go to the next line
    }
}