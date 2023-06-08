// simple C++ program to read in an array of longs, sort
// the array using quicksort (with median of 3 and cutoffs of 50), 
// and then write the sorted data to a file
// By Mary Elaine Califf and _______

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

// read the file into the vector
void readFile(vector<long>& arr, char* fileName);

// write the vector to the file
void writeFile(const vector<long>& arr, char* fileName);

// sort the specified partition of the vector using quicksort
// left and right are the first and last index of the partition to sort
void quicksort(vector<long>& arr, int left, int right);

// add any function prototypes for any additional functions here


// do not modify the main function -- you must complete/modify the methods below
int main(int argc, char** argv) {

  if (argc < 3) {
    cout << "Usage: " << argv[0] << " infile outfile\n";
    exit(1);
  }
  char* inFileName = argv[1];
  char* outFileName = argv[2];
  vector<long> theArray;
  
  readFile(theArray, inFileName);

  quicksort(theArray,0,theArray.size()-1);
  
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

// you must modify this to include median of 3 and cutoffs of 50
void quicksort(vector<long>& arr,int left, int right)
{

  int i, j;
  long pivot;
  long temp;

  if (right - left > 0) { // there are at least two items in the partition
    pivot = arr[right]; //v is the pivot
    i = left - 1; // 1 to the left of the begining
    j = right; // 1 to the right of where search should start

    //we're going to tolerate an infinite loop here and use break
    while (true)
    {
      // pre-increment i until arr[i] is >= the pivot
      while ( arr[++i] < pivot );

      // post-decrement j until arr[j] is <= the pivot
      while ( j > 0 && arr[--j] > pivot );

      //if i and j have crossed -- get out of the loop
      if (i >= j)
        break;

      // otherwise, swap a[i] and a[j]
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }

    // i and j have crossed, so swap a[i] and the pivot
    arr[right] = arr[i];
    arr[i] = pivot;

    // the pivot is now in place at i
    // now call quicksort on the two partitions
    quicksort(arr, left, i-1); // left partition
    quicksort(arr, i+1, right); // right partition
  }
}

// any additional function implementations go here
