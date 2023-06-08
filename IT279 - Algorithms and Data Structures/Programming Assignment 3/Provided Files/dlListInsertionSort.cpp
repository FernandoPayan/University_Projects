// simple C++ program to build a doubly linked list from a file of longs,
// sort the list using insertion sort, and then write the sorted data
// to a file
// By Mary Elaine Califf and _______

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

//The Node struct is set up so you physically cannot change the data value after creating the object.
//Do not change this. You must only modify the pointer values when moving nodes.
struct Node
{
    private:
        long dataVal;
    public:
        Node* next;
        Node* prev;

        Node(long data = 0, Node* nextPtr = nullptr, Node* prevPtr = nullptr)
            : dataVal(data), next(nextPtr), prev(prevPtr) {}
        
        //Getter for public access of the dataVal
        long getDataVal() const { return dataVal; }
};

// read the file into the linked list
void readFile(Node*& head, char* fileName);

// write the linked list to the file
void writeFile(Node* head, char* fileName);

// sort the linked list using an insertion sort following the standard algorithm
// for an array adapted to a doubly linked list
void insertionSort(Node*& head);

// add any function prototypes for any additional functions here


// do not modify the main function -- you must complete the empty methods below
int main(int argc, char** argv) {

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " infile outfile\n";
        exit(1);
    }
    char* inFileName = argv[1];
    char* outFileName = argv[2];
    Node* head = nullptr;

    readFile(head, inFileName);

    insertionSort(head);

    writeFile(head, outFileName);

    // clear out the list memory
    Node* temp = head;
    while (head)
    {
        head = head->next;
        delete temp;
        temp = head;
    }

    return 0;
}

void readFile(Node*& head, char* fileName)
{
    // your code here
}

void writeFile(Node* head, char* fileName)
{
    // your code here
}

void insertionSort(Node*& head)
{
    // your code here
}

// implementation code for any additional functions here

