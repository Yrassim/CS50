# to use get float
from cs50 import get_string

# The Coleman-Liau formula is: index = 0.0588 * L - 0.296 * S - 15.8

# variables declaration
sentncount = 0
letrcount = 0
point = 0
wordcount = 1 # starting by 1 because it count with space but the last word doesn't have space.

#set the user to enter the text
text = get_string("Text: ")

n = len(text); # take length of the text to use it on a loop to check letters

for i in range(n): # ckeck each letter
    letrcount = letrcount + 1
    if (text[i] == '.' or text[i] == '?' or text[i] == '!') and point == 0: # where point works as a switch to check if there is another "." to avoid adding another sentence count.
        letrcount = letrcount - 1
        sentncount = sentncount + 1
        point = 1

    elif (text[i] == '?' or text[i] == '!' or text[i] == '.') and point == 1: # this condition if there is any repetition of '.', '?', or '!' to not count them as senteces.
        letrcount = letrcount - 1

    else:
        point = 0 # reset the switch to 0

        if text[i] == ' ':
            letrcount = letrcount - 1
            wordcount = wordcount + 1


        elif text[i] == ',' or text[i] == '\'' or text[i] == '-' or text[i] == '_' or text[i] == ':' or text[i] == ';': # to avoid count them as letters.
            letrcount = letrcount - 1

L = letrcount * 100 / wordcount # function to finde L S following the theorem
S = sentncount * 100 / wordcount

index = round((0.0588 * L) - (0.296 * S) - 15.8)

# check for printing
if index >= 16:
    print("Grade 16+")

elif index < 1:
    print("Before Grade 1")

else:
    print(f"Grade {index}")
