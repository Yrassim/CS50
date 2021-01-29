#include <cs50.h>
#include <stdio.h>
#include <ctype.h> // check numeric
#include <stdlib.h> // use atoi to convert string to digit
#include <string.h>

int main(int argc, string argv[])
{
    int switchnodigit = 0;
    int repeat = 0;

    if (argc == 2) // if there is 2 argument in main.
    {

        int n = strlen(argv[1]); // take length of the text to use it on a loop to check letters

        if (n == 26)
        {

            for (int i = 0; i < n; i++) // ckeck each letter
            {
                if (isdigit(argv[1][i])) // check for decimal digits
                {
                    switchnodigit = 1; // if there is  a digit in the second argument the switch will be at 1
                }
                for (int j = i + 1; j < n; j++) // checking for repeatition in the argument.
                {
                    if (argv[1][i] == argv[1][j])
                    {
                        repeat = 1;
                    }
                }
            }

            if (switchnodigit == 0 && repeat == 0) // if there is any no digit and no repeation in the argument
            {

                string plaintext = get_string("plaintext: ");

                n = strlen(plaintext); // take length of the text to use it on a loop to check letters

                for (int i = 0; i < n; i++) // ckeck each letter
                {
                    if (isalpha(plaintext[i])) // test if text have alphabitic to use
                    {
                        if (isupper(plaintext[i])) // check if letter is upper case.
                        {
                            int index = plaintext[i] - 65; // remove 65 to the lettrer to start from 0

                            if (isupper(argv[1][index]))
                            {
                                plaintext[i] = argv[1][index]; // switch letters following the key
                            }
                            else
                            {
                                plaintext[i] = argv[1][index] - 32; // sustract 32 to go to uppercase following ascII
                            }
                        }

                        else // check if letter is lower case.
                        {
                            int index = plaintext[i] - 97;

                            if (islower(argv[1][index]))
                            {
                                plaintext[i] = argv[1][index]; // switch letters following the key
                            }
                            else
                            {
                                plaintext[i] = argv[1][index] + 32; // add 32 to go to lowercase following ascII
                            }

                        }
                    }
                }
                printf("ciphertext: %s\n", plaintext);

            }
            else if (repeat == 1)
            {
                printf("There is a letter repetition in the argument.\n");
                return 1;
            }
            else // if the switch is at 1 wich means there is one ore more numbers in the argument
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else // if there is not 2 argument in main.
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}