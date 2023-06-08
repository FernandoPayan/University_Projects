// simple C++ program to read in an array of longs, sort
// the array using quicksort (with median of 3 and cutoffs of 50),
// and then write the sorted data to a file
// By Mary Elaine Califf and Fernando Payan

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

// read the file into the vector
void readFile(vector<long> &arr, char *fileName);

// write the vector to the file
void writeFile(const vector<long> &arr, char *fileName);

// sort the specified partition of the vector using quicksort
// left and right are the first and last index of the partition to sort
void quicksort(vector<long> &arr, int left, int right);

// add any function prototypes for any additional functions here

// Finds the median of three
long medianOfThree(vector<long> &arr, int left, int right);

// Insertion Sort for when we reach the cutoff
void insertionSort(vector<long> &arr, int left, int right);

// Takes care of the partitioning portion of the quicksort
void partition(vector<long> &arr, int left, int right);

// do not modify the main function -- you must complete/modify the methods below
int main(int argc, char **argv)
{

  if (argc < 3)
  {
    cout << "Usage: " << argv[0] << " infile outfile\n";
    exit(1);
  }
  char *inFileName = argv[1];
  char *outFileName = argv[2];
  vector<long> theArray;

  readFile(theArray, inFileName);

  quicksort(theArray, 0, theArray.size() - 1);

  writeFile(theArray, outFileName);

  return 0;
}

void readFile(vector<long> &arr, char *fileName)
{
  long curLong; // Keeps track of the current long from the file
  ifstream infile(fileName); // Gets the input file

  if (infile.fail())
  {
    cerr << "Could not open " << fileName << " for input" << endl;
    exit(1);
  }

  while (infile >> curLong) // Reads the input file and adds the values to the vector
    arr.push_back(curLong); // Adds value to the vector
}

void writeFile(const vector<long> &arr, char *fileName)
{
  ofstream outfile(fileName); // Used to write to the outfile.

  for (int i = 0; i < arr.size(); i++) // Iterates through each item in the vector, and writes them to the output file.
    outfile << arr[i] << "\n";
}

// you must modify this to include median of 3 and cutoffs of 50
void quicksort(vector<long> &arr, int left, int right)
{
  if (right - left < 50) // Checks for cutoff of 50
    insertionSort(arr, left, right); // If there's a cutoff, we need to do insertion sort.
  else
    partition(arr, left, right); // Do the quicksort/partitioning process
}

// any additional function implementations go here
long medianOfThree(vector<long> &arr, int left, int right)
{
  int middle = (left + right) / 2; // Finds the middle of the array

  // Sort the first, middle, and last elements of the partition
  if (arr[middle] < arr[left]) // If the middle is less than the left, swap them.
    swap(arr[left], arr[middle]);

  if (arr[right] < arr[left]) // If the right is less than the left, swap them.
    swap(arr[left], arr[right]);

  if (arr[right] < arr[middle]) // If the right is less than the middle, swap them.
    swap(arr[middle], arr[right]);

  // Swap the middle element with the next-to-last element (now the pivot)
  swap(arr[middle], arr[right - 1]);

  return arr[right - 1]; // Returns the pivot
}

void insertionSort(vector<long> &arr, int left, int right)
{
  long temp;

  for (int i = left; i < (right + 1); i++) // Iterates through the size of the array
  {
    int tracker = i; // Keeps track of the index
    temp = arr[i];   // Sets temp to the value at index i

    while (tracker > left && temp < arr[tracker - 1]) // Insertion Sort
    {
      arr[tracker] = arr[tracker - 1];
      tracker--;
    }
    arr[tracker] = temp; // Updates temp
  }
}

void partition(vector<long> &arr, int left, int right)
{
    int i, j;              
    long pivot; 
    if (right - left > 0) // there are at least two items in the partition
    {
        pivot = medianOfThree(arr, left, right); //v is the pivot
        i = left; // 1 to the left of the begining
        j = right - 1; // 1 to the right of where search should start

        //we're going to tolerate an infinite loop here and use break
        while (true)
        {

        // pre-increment i until arr[i] is >= the pivot
        while ( arr[++i] < pivot );

        // post-decrement j until arr[j] is <= the pivot
        while ( pivot < arr[--j]);

        //if i and j have crossed -- get out of the loop
        if (i < j)
            swap(arr[i], arr[j]);
        else
            break;

        }

        swap(arr[i], arr[right - 1]);

        // now call quicksort on the two partitions
        quicksort(arr, left, i - 1); // left partition
        quicksort(arr, i + 1, right); // right partition
    }
}