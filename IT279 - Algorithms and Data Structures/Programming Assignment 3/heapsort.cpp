// simple C++ program to read in an array of longs, sort
// the array using heapsort, and then write the sorted data
// to a file
// By Mary Elaine Califf and Fernando Payan

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// read the file into the vector (starting at index 1)
void readFile(vector<long> &arr, char *fileName);

// write the vector to the file (starting at index 1)
void writeFile(const vector<long> &arr, char *fileName);

// sort the vector using heapsort (data starts at index 1)
void heapsort(vector<long> &arr);

// add any function prototypes for any additional functions here

// Builds the heap
void buildHeap(vector<long> &arr);

// Used to sort the heap
void sortHeap(vector<long> &arr, int i, int size);

// Performs percolateDown
void percolateDown(vector<long> &arr, int parent);

// Exchanges values of the parent and child
void exchangeVals(vector<long> &arr, int parent, int child);

// do not modify the main function -- you must complete the empty methods below
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

  heapsort(theArray);

  writeFile(theArray, outFileName);

  return 0;
}

void readFile(vector<long> &arr, char *fileName)
{
  long curLong;     // Keeps track of the current long from the file
  int lineNum = 0; // Keeps track of the line numbers

  ifstream infile(fileName); // Gets the input file
  if (infile.fail())
  {
    cerr << "Could not open " << fileName << " for input" << endl;
    exit(1);
  }

  arr.push_back(0); // Pushes 0 to the array. This will be updated to be the size of the array.
  while (infile >> curLong) // Reads the input file and adds the values to the vector
  {
    lineNum++; // Increments the lineNum by 1.
    arr.push_back(curLong); // Adds value to the vector
  }
  arr[0] = lineNum; // Sets index 0 to the size of the array based on lineNum
}

void writeFile(const vector<long> &arr, char *fileName)
{
  ofstream outfile(fileName); // Used to write to the outfile.

  for (int i = 1; i < arr.size(); i++) // Iterates through each item in the vector, and writes them to the output file.
    outfile << arr[i] << "\n";
}

void heapsort(vector<long>& arr)
{
  // Build the heap
  buildHeap(arr);

  // Actually sort the heap
  sortHeap(arr, 1, arr.size() - 1);
}

// implementation code for any additional functions here
void buildHeap(vector<long>& arr)
{
  // Calls sortHeap starting from the last parent
  for (int lastParent = arr[0] / 2; lastParent > 0; lastParent--)
    percolateDown(arr, lastParent);
}

void sortHeap(vector<long>& arr, int root, int end)
{
  for (int i = arr[0]; i > 1; i--)
  {
    // DeleteMax until only one item is left in the heap, swapping root with the last item each time
    swap(arr[root], arr[i]); // Swapping root to end
    arr[0] = arr[0] - 1;     // Reduces the size by 1

    // Since heap is broken, we must percolateDown the new root value.
    if (arr[0] - 1 > 1) // If the heap size is not 1
      percolateDown(arr, root);
  }
}

void percolateDown(vector<long>& arr, int parent)
{
  int firstChild = (parent * 2);    // The first child of the parent
  int secondChild = firstChild + 1; // The second child of the parent

  bool hasTwoChildren = true; // Used to keep track if the parent has two parents. If true, parents has two children. If false, the parent does not have two children.

  if ((firstChild + 1) > arr[0])
    hasTwoChildren = false; // Checks if the parent has a second child

  if (hasTwoChildren) // If we have two children
  {
    // Pull largest child of the parent
    if (arr[parent] < arr[firstChild] && arr[firstChild] > arr[secondChild]) // If the first child is the greatest child, it will swap with the parent
      exchangeVals(arr, parent, firstChild);
    
    else if (arr[parent] < arr[secondChild]) // If the second child is the greatest child, it will swap with the parent
      exchangeVals(arr, parent, secondChild);
  }
  else // If we have only one child
    if (arr[parent] < arr[firstChild])
      exchangeVals(arr, parent, firstChild);
}

void exchangeVals(vector<long> &arr, int parent, int child)
{
  swap(arr[parent], arr[child]); // Swaps parent with the first child

  if ((child * 2) <= arr[0]) // Checks if there's still children
    percolateDown(arr, child);
}