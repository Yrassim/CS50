#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // variables declaration
    long number;
    int count = 0;
    int some = 0;
    int digit = 0;
    int doubleDigit;
    int doubleDigit1;
    int doubleDigit2;
    int AmeriExMacterCard;

    // set the user to enter the right variable
    do
    {

        number = get_long("Number: ");

    }
    while (number < 0);

    while (number > 0) //loop to split the number untill num greater than  0
    {
        if (number < 100 && number > 10) // this condition to check and take the first and second digit for American Ex and Master Card.
        {
            AmeriExMacterCard = number;
        }

        digit = number % 10;  //split last digit from number

        if (count % 2 == 0)
        {
            some = some + digit; // to add all the digit
        }
        else
        {
            doubleDigit = digit * 2;
            if (doubleDigit < 10)  // split the two first degit when it is sup to 9
            {
                some = some + (doubleDigit);
            }
            else
            {
                doubleDigit1 = doubleDigit % 10;
                doubleDigit2 = doubleDigit / 10;
                some = some + doubleDigit1 + doubleDigit2;
            }
        }
        number = number / 10;    //divide by 10 to remove the last digit

        count++; // count number of digit on the number gives.

    }

    some = some % 10; // split the last digit of the some to know if it is 0 or not.


    // Checking conditions to know which carte it is

    if ((count == 15 && AmeriExMacterCard == 34 && some == 0) || (count == 15 && AmeriExMacterCard == 37 && some == 0))
    {
        printf("AMEX\n");
    }
    else if (count == 16 && AmeriExMacterCard < 56 && AmeriExMacterCard > 50 && some == 0)
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 16 && digit == 4 && some == 0) || (count == 13 && digit == 4 && some == 0))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}