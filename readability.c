#include <cs50.h>
#include <stdio.h>
#include <string.h> // including math to use strlen function
#include <math.h> // including math to use round function

int main(void)
{
    // The Coleman-Liau formula is: index = 0.0588 * L - 0.296 * S - 15.8

    // variables declaration

    int sentncount = 0;
    int letrcount = 0;
    int point = 0;
    int wordcount = 1; // starting by 1 because it count with space but the last word doesn't have space.

    // set the user to enter the text

    string text = get_string("Text: ");

    int n = strlen(text); // take length of the text to use it on a loop to check letters

    for (int i = 0; i < n; i++) // ckeck each letter
    {
        letrcount = letrcount + 1;

        if ((text[i] == '.' || text[i] == '?' || text[i] == '!')
            && point == 0) // where point works as a switch to check if there is another "." to avoid adding another sentence count.
        {
            letrcount = letrcount - 1;
            sentncount = sentncount + 1;
            point = 1;
        }

        else if ((text[i] == '?' || text[i] == '!' || text[i] == '.')
                 && point == 1) // this condition if there is any repetition of '.', '?', or '!' to not count them as senteces.
        {
            letrcount = letrcount - 1;
        }

        else
        {
            point = 0; // reset the switch to 0

            if (text[i] == ' ')
            {
                letrcount = letrcount - 1;
                wordcount = wordcount + 1;
            }

            if (text[i] == ',' || text[i] == '\'' || text[i] == '-' || text[i] == '_' || text[i] == ':'
                || text[i] == ';') // to avoid count them as letters.
            {
                letrcount = letrcount - 1;
            }
        }

    }

    float L = (float) letrcount * 100 / (float) wordcount; // function to finde L S following the theorem
    float S = (float) sentncount * 100 / (float) wordcount;

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // check for printing

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}