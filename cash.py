# to use get float
from cs50 import get_float

# set the user to enter the right variable
while True:
    dollars = get_float("Change owed: ")
    cents = round(dollars * 100)
    if cents > 0:
        break

# make counters to add them in the end.
quarters = 0
dimes = 0
nickels = 0
pennies = 0
while cents >= 25:
    cents -= 25
    quarters += 1

# loops to check number of quarters, dimes, nickels, and pennies.
while cents >= 10 and cents < 25:
    cents -= 10
    dimes += 1

while cents >= 5 and cents < 10:
    cents -= 5
    nickels += 1

while cents >= 1 and cents < 5:
    cents -= 1
    pennies += 1

# add all the counters and show the result
print(quarters + dimes + nickels + pennies)



