from sys import argv, exit
import csv
import cs50

#Ask for the right number of arguments on the command line
if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)


# Create database
open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")

# Create tables
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")


# open the cvs file where is the students and save it as "r" in reader
with open(argv[1], "r") as csvfile:
    reader = csv.DictReader(csvfile)


    # Iterate over CSV file

    for row in reader:

        name = row["name"].split(' ')
        # check name if it has middle name
        if len(name) == 2:
            first = name[0]
            middle = None
            last = name[1]
        elif len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]

        # Insert students
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, row["house"], int(row["birth"]))




