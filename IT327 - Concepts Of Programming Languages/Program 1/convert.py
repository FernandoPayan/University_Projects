#Program Name: convert.py
#Description: Reads a text file in English and makes it more formal by taking any numerals and repalcing them with the number written out. Ordinals are also changed into written format
#Author: Fernando Payan
#Class: IT 327
import sys
import re

def change_numeral_expression(line, regex, dictionary):
    temp_string = re.search(regex, line)
    first_part = line[:temp_string.start()]
    last_part = line[temp_string.end():]

    new_line = line[:temp_string.start()] #Gets the first part of the string before match

    new_line += dictionary[temp_string.group()] #Adds the new expression to the string

    new_line += line[temp_string.end():] #Gets the second half of the string after match
    return new_line

def change_ordinal_expression(line, regex, dictionary): 
    temp_string = re.search(regex, line)
    first_part = line[:temp_string.start()]
    last_part = line[temp_string.end():]

    new_line = line[:temp_string.start()] #Gets the first part of the string before match

    new_line += dictionary[temp_string.group()] #Adds the new expression to the string

    new_line += line[temp_string.end():] #Gets the second half of the string after match
    return new_line

def main():
    if (len(sys.argv) != 3): #If the user did not pass the correct number of parameters, it will print an error message and exit the program
        print("Not enough arguments passed. Please enter in this format: python3 convert.py <input_file> <output_file>")
        sys.exit()    
    # Regex Expressions
    regex_numerals = (r"\b(?:\d|10)\b")
    regex_ordinals = (r"(?:\b\d+(?:[st]{2}|[nd]{2}|[rd]{2}|[th]{2})\b)")

    # Opens the file
    input_file = open(sys.argv[1], "r")
    output_file = open(sys.argv[2], "w")

    # Dictionaries
    numerals_dictionary = {'0':'zero', '1':'one', '2':'two',
                           '3':'three', '4':'four', '5':'five',
                           '6':'six', '7':'seven', '8':'eight',
                           '9':'nine', '10':'ten'}
    ordinals_dictionary = {'0th':'zeroth', '1st':'first', '2nd':'second',
                           '3rd':'third', '4th':'fourth', '5th':'fifth',
                           '6th':'sixth', '7th':'seventh', '8th':'eighth',
                           '9th':'ninth', '10th':'tenth'}
    
    for line in input_file.readlines():
        #Checks if the word is a numeral
        if (re.search(regex_numerals, line)):
            line = change_numeral_expression(line, regex_numerals, numerals_dictionary)

            #Checks if the word is an ordinal
        if (re.search(regex_ordinals, line)):
            line = change_ordinal_expression(line, regex_ordinals, ordinals_dictionary)
        output_file.write(line)

    # Closes the File
    input_file.close()
    output_file.close()

main()