from sys import argv
import csv
import math

def main():
    # if user enters any less than 3 command line arguments:
    if (len(argv) != 3):

        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # open the database file and text file:
    with open(argv[1], "r") as data_file:
        data_reader = csv.DictReader(data_file)

        times = next(data_reader)
        #open a new_file for writing the contents of the data_file:
        with open("data_file.csv", "w") as write_data:
            #even if the data base file entered is a small, it the values given to it, will only be assigned depending on the key:
            fieldnames = times

            write_file = csv.DictWriter(write_data, fieldnames = fieldnames, delimiter = ",")

            write_file.writeheader()
            for line in data_reader:
                write_file.writerow(line)


            #after writing into our new_data file:

    with open(argv[2], "r") as text_file:
        text_reader = csv.reader(text_file, delimiter = " ")
        with open("text.csv", "w") as text_write:
            text_writer = csv.writer(text_write)
            for line in text_reader:
                text_writer.writerow(line)


    # open the text_file for checking for patters:
    with open("text.csv", "r") as read_text:
        text_reader = csv.reader(read_text)
        # to get rid of the fieldname "name", because it is not a pattern:

        fieldname = iter(fieldnames)
        next(fieldname)
        for pat in text_reader:
            p = str(pat)
            pat = {}
            #loop throught the given pattern to find out the no of times a STR repeats in the text_file:
            for pattern in fieldname:
                #create an array giving it the name of the pattern:
                # a pat is one complete string in text_reader:
                i = 0
                j = len(pattern)
                k = 0
                temp = []
                while i <= len(p):
                    if p[i:i+j] in pattern:
                        i += j
                        k += 1
                    else:
                        i += 1
                        k = 0
                        #append values to the pattern:
                    temp.append(k)
                #add the maximum value in the temp list as a value to key in pat:
                # now we have a dictionary of key-value pairs where keys are pattern names and values is the times this pattern repeats itself
                pat[pattern] = max(temp)

            # now check if the file matches with the existing pattern values:
    with open("data_file.csv" ,"r") as check_file:

        file_read = csv.DictReader(check_file)
        t = 0
        l = 0
        for row in file_read:
            t = 0
            for pats in pat:
                value = int(row[pats])
                if value == pat[pats]:
                    t += 1
            if t == len(times) - 1:
                print(row["name"])
                exit(0)

        print("No match")
        exit(1)

main()