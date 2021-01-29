# to use get int
from cs50 import get_int

# asking for the height until get a number between 1 and 8
while True:
    n = get_int("Height: ")
    if n >= 1 and n <= 8:
        break

# draw the lines
for i in range(n):
    for j in range(n-i-1):  # draws the spaces on the left side
        print(" ", end="")
    for z in range(i+1):   # draws the hashes on the left side
        print("#", end="")

    print(end="  ")                 # print space between the 2 triangles

    for z in range(i+1):  # draw the line for the second shape
        print("#", end="")

    print()  # to go to the next line

