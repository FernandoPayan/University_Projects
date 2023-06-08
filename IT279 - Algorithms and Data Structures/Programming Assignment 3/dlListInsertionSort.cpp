// simple C++ program to build a doubly linked list from a file of longs,
// sort the list using insertion sort, and then write the sorted data
// to a file
// By Mary Elaine Califf and Fernando Payan

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

// The Node struct is set up so you physically cannot change the data value after creating the object.
// Do not change this. You must only modify the pointer values when moving nodes.
struct Node
{
private:
    long dataVal;

public:
    Node *next;
    Node *prev;

    Node(long data = 0, Node *nextPtr = nullptr, Node *prevPtr = nullptr)
        : dataVal(data), next(nextPtr), prev(prevPtr) {}

    // Getter for public access of the dataVal
    long getDataVal() const { return dataVal; }
};

// read the file into the linked list
void readFile(Node *&head, char *fileName);

// write the linked list to the file
void writeFile(Node *head, char *fileName);

// sort the linked list using an insertion sort following the standard algorithm
// for an array adapted to a doubly linked list
void insertionSort(Node *&head);

// add any function prototypes for any additional functions here

// Used to help break down the insertion sort method. Handles the insertion of nodes into the list.
void swapNodes(Node *&unsortedNode, Node *&sortedNode, Node *&head);

// Used to help break down the insertion sort method. Finds out where the node needs to be inserted into the list
void insertNode(Node *&unsortedNode, Node *&sortedNode, Node *&head);

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
    Node *head = nullptr;

    readFile(head, inFileName);

    insertionSort(head);

    writeFile(head, outFileName);

    // clear out the list memory
    Node *temp = head;
    while (head)
    {
        head = head->next;
        delete temp;
        temp = head;
    }

    return 0;
}

void readFile(Node *&head, char *fileName)
{
    long curLong;              // Keeps track of the current long from the file
    ifstream infile(fileName); // Gets the input file

    if (infile.fail()) // If input file could not be opened
    {
        cout << "Could not open " << fileName << " for the input. Please try again." << "\n";
        exit(1);
    }
    
    // Assign head a value
    infile >> curLong; // Gets the first value from the file
    head = new Node(curLong, nullptr, nullptr); // Creates a node for the first long and points head to it.
    Node* curPtr = head; // curPtr keeps track of the current pointer
    
    while (infile >> curLong) // Iterates through each number in the file
    {            
        // Reads all the longs in the file, assign them to a node, and add them to the list.
        while (curPtr->next != nullptr) // Finds the end of the list
            curPtr = curPtr->next;      // Moves to the next node in the list
        curPtr->next = new Node(curLong, nullptr, curPtr); // Assign's curPtr->next to a new node with the long value.
    }
}

void writeFile(Node *head, char *fileName)
{
    ofstream outFile(fileName); // Used to write to the outfile.

    while (head != nullptr) // Iterates through each node in the list
    {
        outFile << head->getDataVal() << "\n"; // Writes to the outFile
        head = head->next;                     // Moves to the next node
    }
}

// Insertion Sort
void insertionSort(Node *&head)
{
    // Since we don't need to pull head out of the list, we just skip to the next element in the list
    Node *unsortedNode = head;     // Keeps track of the previous node
    Node *sortedNode = head->next; // Keeps track of our current node

    // Outer loop that will walk through that unsorted list from the first item to the last item
    while (sortedNode != nullptr)
    {
        while (unsortedNode->getDataVal() < sortedNode->getDataVal()) // Iterate through list until we find the unsortedNode > sortedNode
        {
            // Move to the next pair of nodes
            unsortedNode = unsortedNode->next;
            sortedNode = sortedNode->next;
            if (sortedNode == nullptr) // If we reach the end of the list and it doesn't need to be sorted, break the loop
                break;
        }

        if (sortedNode != nullptr)
        {
            // Insert items from the unsorted list into the correct location in the sorted list
            insertNode(unsortedNode, sortedNode, head);

            sortedNode = unsortedNode->next;
        }
    }
}

// implementation code for any additional functions here
void swapNodes(Node *&unsortedNode, Node *&sortedNode, Node *&head)
{
    if (unsortedNode == head && unsortedNode->getDataVal() > sortedNode->getDataVal()) // Checks if we need to swap the head first
    {
        // Swaps the head and the sortedNode
        sortedNode->next = unsortedNode;
        sortedNode->prev = unsortedNode->prev;
        unsortedNode->prev = sortedNode;

        // Update the head of the list
        head = sortedNode;
    }
    else // Insert sortedNode in front of unsortedNode
    {
        unsortedNode->next->prev = sortedNode;
        sortedNode->next = unsortedNode->next;
        sortedNode->prev = unsortedNode;
        unsortedNode->next = sortedNode;
    }
}

void insertNode(Node *&unsortedNode, Node *&sortedNode, Node *&head)
{
    // Take the node out of the list
    unsortedNode->next = sortedNode->next; // Make head point to sortedNode's next and head's prev point to sorted node

    if (sortedNode->next != nullptr) // Check if we reached the end of the list
        sortedNode->next->prev = unsortedNode; // Change sortedNode's next prev node to point to the head

    sortedNode->next = sortedNode->prev = nullptr; // Remove the next and prev for sortedNode

    // Before doing any insertion, first check if we just need to swap the head
    if (unsortedNode == head)
        swapNodes(unsortedNode, sortedNode, head);
    else
    {
        // Save Temp Variables to update sortedNode and Unsorted node back to their original positions.
        Node *updatePositions = unsortedNode;

        unsortedNode = unsortedNode->prev; // Moves to check the previous node before starting inner loop

        while (unsortedNode->getDataVal() > sortedNode->getDataVal() && unsortedNode->prev != nullptr) // Finds the spot to insert the node at
            unsortedNode = unsortedNode->prev; // Moves unsortedNode backwards through the list

        swapNodes(unsortedNode, sortedNode, head); // Insert sortedNode into list

        // Update the nodes back to original positions in the list
        unsortedNode = updatePositions;
        sortedNode = unsortedNode;
    }
}