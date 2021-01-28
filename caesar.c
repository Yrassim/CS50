#include <cs50.h>
#include <stdio.h>
#include <ctype.h> // check numeric
#include <stdlib.h> // use atoi to convert string to digit
#include <string.h> // including math to use strlen function

int main(int argc, string argv[])
{
    int switchnodigit = 0;

    if (argc == 2) // if there is 2 argument in main.
    {

        int n = strlen(argv[1]); // take length of the text to use it on a loop to check letters

        for (int i = 0; i < n; i++) // ckeck each letter
        {
            if (isdigit(argv[1][i]) == 0) // check for decimal digits
            {
                switchnodigit = 1; // if there is anything else than a digit in the second argument the switch will be at 1
            }
        }

        if (switchnodigit == 0) // if there is any other than digit
        {

            int k = atoi(argv[1]); // convert the string to number

            string plaintext = get_string("plaintext: ");

            n = strlen(plaintext); // take length of the text to use it on a loop to check letters

            for (int i = 0; i < n; i++) // ckeck each letter
            {
                if (isalpha(plaintext[i])) // test if text have alphabitic to use
                {
                    if (isupper(plaintext[i])) // check if letter is upper case.
                    {
                        int index = plaintext[i] - 65; // remove 65 to the lettrer to start from 0 to use the following formula

                        index = (index + k) % 26;

                        plaintext[i] = index + 65; // get back to the letter number
                    }

                    if (islower(plaintext[i])) // check if letter is lower case.
                    {
                        int index = plaintext[i] - 97;

                        index = (index + k) % 26;

                        plaintext[i] = index + 97;
                    }
                }
            }
            printf("ciphertext: %s\n", plaintext);
        }
        else // if the switch is at 1 wich means there is other than number in the argument
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else // if there is not 2 argument in main.
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}