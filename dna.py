from sys import argv, exit
import csv

#Ask for the right number of arguments on the command line
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open the cvs file where is the database and save it as "r" in reader
with open(argv[1], "r") as csvfile:
    reader = csv.reader(csvfile)
    for rows in reader:  # Take the first line in reader, where str list is,and save it in STR_list
        STR_list = rows
        break
    # Take the rest of the file and make it a dictionary list
    dict_list = []
    for line in reader:
        dict_list.append(line)

# Convert all the numbers of the list to int, but not the names, to make it easy to compare with list sequence
for j in range(len(dict_list)):
    for i in range(len(dict_list[j][1:])):
        dict_list[j][i+1] = int(dict_list[j][i+1])

i = 0 # starting with 0 to check each letter in the sequence file
num = 0 # a temp number to count number of str repeat
count = 0 # save temp if it is greater than befor
adn_num = [] # list of str numbers found in the file sequence

# open the second file where the dna sequences are and save it in reader_adn
with open(argv[2], "r") as file:
    for rows in file:
        reader_adn = rows
        break
# count each str in the sequence file (if the str is not found i will increment by one to check all letters)
    for STR in STR_list[1:]:
        while i < len(reader_adn):
            if reader_adn[i : i+len(STR)] == STR:
                num += 1
                if num > count:
                    count = num
                i += len(STR) # if an str is found increment i by lenth of the str to check the number of repeat
            else:
                num = 0
                i += 1
        # when it found the greater number of str repeat, append it to the list and reset everything
        adn_num.append(count)
        count = 0
        i = 0
        num = 0
# check our list of str found with the database by removing the name(to check just the int)
for i in range(len(dict_list)):
    if adn_num == dict_list[i][1:]:
        print(dict_list[i][0]) # if a match is found with the list, print the first variable of the list which is the name and stop
        exit(0)
print("No match") # if no match is found return "no match"
