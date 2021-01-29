from sys import argv, exit
import csv
import cs50

#Ask for the right number of arguments on the command line
if len(argv) != 2:
    print("Usage: python roster.py House_Name")
    exit(1)

# Recall students database after being imported SQL from cs50
db = cs50.SQL("sqlite:///students.db")

# execute SQL request and save it in result
result = db.execute("SELECT first, middle, last, birth from students WHERE house = ? ORDER BY last, first", argv[1])

# print result asking by avoiding middle name print if it is NULL
for row in result:
    if row["middle"] == None:
        print(row["first"], row["last"] + ", born", row["birth"])
    else:
        print(row["first"], row["middle"], row["last"] + ", born", row["birth"])