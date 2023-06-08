//Implementation of exercises 1.5 and 1.6 from the textbook.
// By Fernando Payan, Albert Nytko, and Sean Kim; IT279 F2022
#include <string>
#include <iostream>
using namespace std;

//First exercise - method used to count the number of one's in the given integer
// Precondition: num is non-negative
int countBinaryOnes(int num);

//Second exercise - recursive driver
void permute(const string& str);

//Second exercise - recursive method to perform all possible permutations of the given string
//  When using the string class, you don't need to pass in the "high" integer that the book uses.
void permute(const string& str, int low);

//Implementation
int main()
{
    //Testing binaryOnes
    cout << "BinaryOnes: " << countBinaryOnes(0) << " == " << 0 << endl;
    cout << "BinaryOnes: " << countBinaryOnes(42) << " == " << 3 << endl;
    cout << "BinaryOnes: " << countBinaryOnes(65) << " == " << 2 << endl;
    cout << "BinaryOnes: " << countBinaryOnes(214748) << " == " << 10 << endl;

    //Testing string permutations
    cout << "permute(\"a\"):\n";
    permute("a");
    cout << "permute(\"to\"):\n";
    permute("to");
    cout << "permute(\"abc\"):\n";
    permute("abc");
    cout << "permute(\"\"):\n";
    permute("");
    cout << "permute(\"blue\"):\n"; 
    permute("blue");
    cout << "permute(\"ranged\"):\n";
    permute("ranged");
}

//----- Exercise 1.5 -----
int countBinaryOnes(int num)
{
    if (num == 0) // Base case where we want to reach 0.
        return 0;
    else 
        return countBinaryOnes(num/2) + num%2; //The num%2 will determine whether we're adding 0 or 1. We divide the num by 2 to get closer to the base case.

    /*
    if (num < 2)
        return num;
    else
        return countBinaryOnes(num / 2) + num % 2;
    */
}

//----- Exercise 1.6 -----
void permute(const string& str)
{
    permute(str, 0); // Driver function calls the recursive function with the defined string and initializing int low as 0 so we start at the beginning of the string.
}

void permute(const string& str, int low)
{
    string tempString = str; // Temp string that is used to keep track and find the permutations of the string.
    if (low == str.length()) // Base case where we reach the end of the string.
        cout << str << endl;
    else
        for (int i = low; i < str.length(); i++)
        {
            swap(tempString[low], tempString[i]); // Swaps the characters at position low and position i (values depend on the loop count and recursion iteration)

            permute(tempString, low + 1); // Recursive method that calls the permute function and increases the int low by one so we move positions in the string.
        }

    /*
    if (low + 1 >= str.length())
        cout << str << "\n";
    else
        string tempStr = str;
        permute(str, low + 1);
        for (int i = low + 1; i < str.length(); i++)
        {
            tempStr[low] = str[i];
            tempStr[i] = str[low];
            permute(tempStr, low + 1);
            tempStr[low] = str[low];
            tempStr[i] = str[i];
        }
    */
}
