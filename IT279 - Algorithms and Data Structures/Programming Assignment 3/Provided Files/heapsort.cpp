// simple C++ program to read in an array of longs, sort
// the array using heapsort, and then write the sorted data
// to a file
// By Mary Elaine Califf and _______

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// read the file into the vector (starting at index 1)
void readFile(vector<long>& arr, char* fileName);

// write the vector to the file (starting at index 1)
void writeFile(const vector<long>& arr, char* fileName);

// sort the vector using heapsort (data starts at index 1)
void heapsort(vector<long>& arr);

// add any function prototypes for any additional functions here

// do not modify the main function -- you must complete the empty methods below
int main(int argc, char** argv) {

  if (argc < 3) {
    cout << "Usage: " << argv[0] << " infile outfile\n";
    exit(1);
  }
  char* inFileName = argv[1];
  char* outFileName = argv[2];
  vector<long> theArray;
  
  readFile(theArray, inFileName);

  heapsort(theArray);
  
  writeFile(theArray, outFileName);

  return 0;
}

void readFile(vector<long>& arr, char* fileName)
{
  // your code here
}

void writeFile(const vector<long>& arr, char* fileName)
{
  // your code here
}

void heapsort(vector<long>& arr)
{
  // your code here
}

// implementation code for any additional functions here
  
