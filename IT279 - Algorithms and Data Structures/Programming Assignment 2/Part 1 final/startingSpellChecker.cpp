// Program to perform spell checking
// The program will take 3 command line parameters, the names of two input files and one output file.
// The input files will be
//      1) a list of correctly spelled words, which will be stored in a dictionary
//      2) a file to check for correct spelling
// The output file will show the structure of the dictionary that was created (done for grading purposes)
// The program will output a list of incorrectly spelled words and suggestions for each word.
// By Mary Elaine Califf and Fernando Payan
// COMPILE CODE: g++ startingSpellChecker.cpp Dictionary.cpp -o spellchecker
// EXECUTE CODE: ./spellchecker smalldict.txt test1.txt outfile.txt

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <algorithm> // Used to erase certain characters from strings
#include <sstream> // Used to read word by word
#include <vector> // Used to keep a list of the passed values
using namespace std;

// function prototypes

// opens and reads the word list input file, building the dictionary
void buildDictionary(const string& inFileName, Dictionary& dict);

// opens the input file and checks the spelling of the input file, producing output to standard out
void checkSpelling(const string& inFileName, const Dictionary& dict);

// open the dictionary structure file and write the structure of the dictionary to it
void writeDictionaryStructure(const string& outFileName, const Dictionary& dict);

// Additional function prototypes go here

// Holds all of the methods used to check the spelling of the word
void findSuggestions(string& word, const Dictionary& dict);

// Adds each char of the alphabet to the string
vector<string> addAlphabet(string& s, const Dictionary& dict, vector<string> vector);

// Removes letter from the word
vector<string> removeLetter(string& s, const Dictionary& dict, vector<string> vector);

// Switches adjacent characters in a string
vector<string> switchLetters(string& s, const Dictionary& dict, vector<string> vector);

// Used to check if a word in the dictionary was already passed as a suggestion
bool isCopy(string& word, const Dictionary& dict, vector<string> vector);

// Converts a string to lowercase
string makeLowerCase(string& s);

// Used for add each char of the alphabet to the string
string charToString(char c);

//
string addWord(string s, Dictionary& dict);
int main(int argc, char** argv)
{
    // gather the file name arguments
    if (argc < 4)
    {
        // we didn't get enough arguments, so complain and quit
        cout << "Usage: " << argv[0] << " wordListFile inputFile dictionaryStructureFile" << endl;
        exit(1);
    }

    string wordListFileName = argv[1];
    string inputFileName = argv[2];
    string dictFileName = argv[3];

    Dictionary dict; // set up the dictionary

    // build the dictionary
    buildDictionary(wordListFileName, dict);

    // write the dictionary to the concordance file
    checkSpelling(inputFileName, dict);

    // write the dictionary structure to the dictionary structure file
    writeDictionaryStructure(dictFileName, dict);
}

void buildDictionary(const string& inFileName, Dictionary& dict)
{
    string curWord = ""; //current word

    // open the file
    ifstream infile(inFileName);
    if (infile.fail())
    {
        cerr << "Could not open " << inFileName << " for input" << endl;
       exit(1);
    }
    
    string word; // Holds the current edited word

    // Gets every word from the input file and builds a dictionary
    while (getline(infile, curWord))
    {     
        if (word.length() >= 1) // If we moved to a new line and there's still a word stored, we will add the currently stored word
        {
            addWord(makeLowerCase(word), dict); // Adds the word to the dictionary
        }
        word = addWord(makeLowerCase(curWord), dict); // Adds the word to dictionary. Stores the word we created into "word". Should be "".
    }
    // close the file
    infile.close();
}

void checkSpelling(const string& inFileName, const Dictionary& dict)
{
    int lineNum = 1;
    string curWord = "";
    
    ifstream infile(inFileName);
    if (infile.fail())
    {
        cerr << "Could not open " << inFileName << " for input\n";
        return;
    }

    string curLine; // Keeps track of the line and words respectively
    string specialCharacters = "!.,\";\'?-@#$"; // String of special characters that can be found in text
    istringstream iss; // Used to keep track of words

    getline(infile, curLine); // Gets the current line and assigns it to string line
    while (!infile.eof())
    {
        iss.clear(); // Clears out the iss
        iss.str(curLine); // Copies the current line to read from

        while (iss >> curWord) // Iterates through each word in the line
        {
            for (char c : specialCharacters)
                curWord.erase(remove(curWord.begin(), curWord.end(), c), curWord.end()); // Removes special characters from the word
        
            // If the word is spelled incorrectly, it will look for suggesstions.
            if (curWord.length() >= 1) // Ensures no empty string
                if (!dict.findEntry(makeLowerCase(curWord)))
                {
                    cout << curWord << " on line " << lineNum << endl;
                    findSuggestions(curWord, dict);
                }
        }
        getline(infile, curLine); // Iterates to the next line
        lineNum++; // Increases the line number by 1
    }
}

void writeDictionaryStructure(const string& outFileName, const Dictionary& dict)
{
    ofstream outfile(outFileName);
    if (outfile.fail())
    {
        cerr << "Could not open " << outFileName << " for output\n";
        cerr << "Dictionary structure file not written " << endl;
        return;
    }
    dict.printDictionaryKeys(outfile);
    outfile.close();
}

// Additional function implementations used for the Spell Checker

void findSuggestions(string& word, const Dictionary& dict)
{
    vector<string> suggestions; // Holds all of the suggestions passed from the three rules to check spelling

    // 1.) Add one letter to the word at any position
    suggestions = addAlphabet(word, dict, suggestions); // Iterates through the three rules and returns all suggestions found to the suggestions vector.

    if (suggestions.size() == 0) // If no suggestions were found, it will print "no suggestions found" to the terminal
        cout << "No suggestions found\n";
    else // If suggestions were found
        {
            cout << "Suggested corrections:\n";
            for (int i = 0; i < suggestions.size(); i++) // Iterates through each item in the vector and prints each suggestion found in order
            {
                cout << "\t" << suggestions.at(i) << "\n";
            }
        }
}

vector<string> addAlphabet(string& word, const Dictionary& dict, vector<string> vector)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz"; // Used to iterate through each letter of the alphabet

    for (int i = 0; i <= word.length(); i++)
    {
        string temp = word; // This string will be edited to test each possible combination

        // Iterates through each character of the alphabet
        for (char c : alphabet)
        {
            temp.insert(i, charToString(c)); // Inserts the character at position i

            if (dict.findEntry(temp)) // Checks if the generated word is in the dictionary
                if (!isCopy(temp, dict, vector)) // Checks if the word was already added to the suggestions vector
                    vector.push_back(temp); // Adds the string to the vector
            
            temp = word; //Resets the string before adding a new character to the string
        }
    }
    // 2.) Remove one letter from the word
    return removeLetter(word, dict, vector);
}

vector<string> removeLetter(string& word, const Dictionary& dict, vector<string> vector)
{
    for (int i = 0; i < word.length(); i++)
    {
        string temp = word; // Creates a temp string to hold what the string will look like with a removed letter
        temp.erase(i, 1); // Erases the letter at index i from the string

        if (dict.findEntry(temp)) // Checks if the generated word is in the dictionary
            if (!isCopy(temp, dict, vector)) // Checks if the word was already added to the suggestions vector
                 vector.push_back(temp); // Adds the string to the vector
    }
    // 3.) Exchange adjacent characters
    return switchLetters(word, dict, vector);
}

vector<string> switchLetters(string& word, const Dictionary& dict, vector<string> vector)
{

    for (int i = 0; i < word.length() - 1; i++)
    {
        string temp = word; // Used to reset the string when swapping
        
        // Swapping Process
        int char1 = i; int char2 = i + 1;
        char c = word[char1];
        temp[char1] = temp[char2];
        temp[char2] = c;

        // Checks if the newly swapped string exists in the dictionary
        if (dict.findEntry(temp)) // Checks if the generated word is in the dictionary
            if (!isCopy(temp, dict, vector)) // Checks if the word was already added to the suggestions vector
                vector.push_back(temp); // Adds the string to the vector
    }
    return vector;
}

bool isCopy(string& word, const Dictionary& dict, vector<string> vector)
{
    for (int i = 0; i < vector.size(); i++) // Iterates through each suggestion in the vector
    {
        if (word == vector.at(i)) // Checks if the word is at the current index at vector
            return true;
    }
    return false;     
}

string makeLowerCase(string& s){
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

string charToString(char c)
{
    return string(1, c);
}

string addWord(string curWord, Dictionary& dict)
{
    string word; // The edited word
    for (int i = 0; i < curWord.length(); i++)
    {
        // When we reach the last char in the word
        if (i == (curWord.length() - 1))
        {
            if (isalpha(curWord[i])) // Checks if the last word is a letter
            {
                word = word + curWord[i]; // Appends the character to our word
                if (!dict.findEntry(makeLowerCase(word))) // Checks if the word generated exists in the dictionary
                    dict.addEntry(new string((word))); // Adds the word to the dictionary

                //resets the word
                word = "";
            }
        } else if (!isalpha(curWord[i])) // If the character is not a letter
        {
            if (!dict.findEntry(makeLowerCase(word)) && word != "") // Checks if the word generated exists in the dictionary
                    dict.addEntry(new string((word))); // Adds the word to the dictionary

            //resets the word
            word = "";
        } else
            word = word + curWord[i]; // If character is a letter and we're not at the end of the string, we append the character to our string word
    }
    return word;
}