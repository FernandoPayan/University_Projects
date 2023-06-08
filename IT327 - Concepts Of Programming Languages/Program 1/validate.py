#Program Name: validate.py
#Description: Reads a database table in a tab-delimited format and validate it, reporting any errors in the data that are discovered to the output file.
#Author: Fernando Payan
#Class: IT 327

#Importing Libraries
import sys
import re 

def main():

    #Checks if the correct number of arguments have passed
    if (len(sys.argv) != 3): #If the user did not pass the correct number of parameters, it will print an error message and exit the program
        print("Not enough arguments passed. Please enter in this format: python3 validate.py <input_file> <output_file>")
        sys.exit()
    #Open the files based on the argument parameters passed
    input_file = open(sys.argv[1], "r")
    output_file = open(sys.argv[2], "w")

    #Regex Expressions
    regex_id = (r"^\d{3}[A-Z]{3}$") # 3 digits followed by 3 capital letters
    regex_name = (r"^[a-zA-Z]+(?:\s[a-zA-Z]+)*(?:\,\s(?:[Jr.]{3}|[Sr.]{3}|(?:[V?I]{0,4}|[IX]{2})))?$") #Any string of letters and spaces, optionally followed by a comma followed by a Jr., Sr., or a Roman Numeral
    regex_zip = (r"^(?:^\d{5}$)|(?:\d{5}[-]\d{4})$") # Either xxxxx or xxxxx-xxxx is considered valid, where x is a digit
    regex_num_purc = (r"^\d+[^-a-zA-Z\.]$") # Gets any positive integer that does NOT have letters, '-', or '.'
    regex_pur_amnt = (r"^\${1}\d+\.{1}\d{2}$") #Currency ammount in standard currency format including the dollar sign and cents with at least one digit in front of the decimal point

    #Enumerates and splits the file so we can easily access each data field
    for row_num, line in enumerate(input_file):
        line = line.strip().split('\t')
        for rank, item in enumerate(line): #Iterates through each item

            # If the item in the data field is: ID
            if (rank == 0): 
                if (not re.search(regex_id, item)): #If not valid, we write the error to the outfile
                    output_file.write("Error in ID field of record {}: {}\n".format((row_num + 1), item))

            # If the item in the data field is: Name
            elif (rank == 1): 
                if (not re.search(regex_name, item)): #If not valid, we write the error to the outfile
                    output_file.write("Error in Name field of record {}: {}\n".format((row_num + 1), item))

            # If the item in the data field is: Zip Code
            elif (rank == 2): 
                if (not re.search(regex_zip, item)): #If not valid, we write the error to the outfile
                    output_file.write("Error in Zip code field of record {}: {}\n".format((row_num + 1), item))

            # If the item in the data field is: Number Purchased
            elif (rank ==3): 
                if (not re.search(regex_num_purc, item)): #If not valid, we write the error to the outfile
                    output_file.write("Error in Number purchased field of record {}: {}\n".format((row_num + 1), item))
            
            # If the item in the data field is: Purchase amount
            else: 
                if (not re.search(regex_pur_amnt, item)):#If not valid, we write the error to the outfile
                    output_file.write("Error in Purchase amount field of record {}: {}\n".format((row_num + 1), item))
    # Closes the File
    input_file.close()
    output_file.close()

#Runs the main function
main()