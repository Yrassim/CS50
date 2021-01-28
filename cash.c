#include <cs50.h>
#include <stdio.h>
#include <math.h> // including math to use round function

int main(void)
{
    // variables declaration
    float dollars;
    int cents;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;

    // set the user to enter the right variable
    do
    {

        dollars = get_float("Change owed: ");
        cents = round(dollars * 100);

    }
    while (cents < 1);

    //loops to check number of quarters, dimes, nickels, and pennies.

    while (cents >= 25)
    {
        cents = cents - 25;
        quarters++; // make it as counter to add them in the end.
    }

    while (cents >= 10 && cents < 25)
    {
        cents = cents - 10;
        dimes++; // make it as counter to add them in the end.
    }

    while (cents >= 5 && cents < 10)
    {
        cents = cents - 5;
        nickels++; // make it as counter to add them in the end.
    }

    while (cents >= 1 && cents < 5)
    {
        cents = cents - 1;
        pennies++; // make it as counter to add them in the end.
    }

    int coins =  quarters + dimes + nickels + pennies; // add all the counters

    printf("%i\n", coins); // show the result

}