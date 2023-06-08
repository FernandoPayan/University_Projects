#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
using namespace std;

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

void insertionSort(Node *&head);
void swap(Node *&curPtr, Node *&prevPtr);
void addNode(int val, Node *&head);
void printList(Node *&head);
void printNode(Node *&theNode);
void swapNodes(Node *&head, Node *&sortedNode);
void toEnd(Node *&lastNode, Node *&sortedNode);
void insertNode(Node *&unsortedNode, Node *&sortedNode, Node *&head);
// Quicksort
void quicksort(vector<long> &arr, int left, int right);
long medianOfThree(vector<long> &arr, int left, int right);
void insertionSort(vector<long> &arr, int left, int right);
void partition(vector<long> &arr, int left, int right);

// Heapsort
void heapsort(vector<long> &arr);
void buildHeap(vector<long> &arr);
void sortHeap(vector<long> &arr, int parent, int size);
void percolateDown(vector<long> &arr, int parent);
void exchangeVals(vector<long> &arr, int parent, int child);

int main()
{
    // Quicksort
    vector<long> theArray;
    theArray.push_back(19);
    theArray.push_back(8);
    theArray.push_back(10);
    theArray.push_back(2);
    theArray.push_back(26);
    theArray.push_back(4);
    theArray.push_back(12);
    theArray.push_back(5);
    theArray.push_back(3);
    theArray.push_back(16);
    theArray.push_back(11);
    theArray.push_back(6);
    theArray.push_back(13);
    theArray.push_back(7);

    vector<long> secArray;
    secArray.push_back(12);
    secArray.push_back(2);
    secArray.push_back(9);
    secArray.push_back(16);
    secArray.push_back(20);
    secArray.push_back(41);
    secArray.push_back(13);
    secArray.push_back(8);
    secArray.push_back(9);
    secArray.push_back(1);
    secArray.push_back(51);
    secArray.push_back(18);
    secArray.push_back(19);
    secArray.push_back(5);
    secArray.push_back(10);
    secArray.push_back(14);


    cout << "Initial Array: [";
    for (int i = 0; i < theArray.size() - 1; i++)
        cout << theArray[i] << " ";
    cout << secArray[theArray.size() - 1] << "]" << endl;

    quicksort(theArray, 0, theArray.size() - 1);

    cout << "Sorted Array: [";
    for (int i = 0; i < theArray.size() - 1; i++)
        cout << theArray[i] << " ";
    cout << theArray[theArray.size() - 1] << "]" << endl;

    cout << "\n\n";

    cout << "Initial Array: [";
    for (int i = 0; i < secArray.size() - 1; i++)
        cout << secArray[i] << " ";
    cout << secArray[secArray.size() - 1] << "]" << endl;

    quicksort(secArray, 0, secArray.size() - 1);

    cout << "Sorted Array: [";
    for (int i = 0; i < secArray.size() - 1; i++)
        cout << secArray[i] << " ";
    cout << secArray[secArray.size() - 1] << "]" << endl;
}

// QuickSort
void quicksort(vector<long> &arr, int left, int right)
{
    if (right - left < 3)                // Checks for cutoff of 50
        insertionSort(arr, left, right); // If there's a cutoff, we need to do insertion sort.
    else
    {
        partition(arr, left, right); // Do the quicksort/partitioning process
    }
}

long medianOfThree(vector<long> &arr, int left, int right)
{
    int middle = (left + right) / 2;
    // cout << "Left is: " << arr[left] << " | Middle is: " << arr[middle] << " | Right is: " << arr[right] << endl;

    // Sort the first, middle, and last elements of the partition
    if (arr[middle] < arr[left]) // If the middle is less than the left, swap them.
        swap(arr[left], arr[middle]);

    if (arr[right] < arr[left]) // If the right is less than the left, swap them.
        swap(arr[left], arr[right]);

    if (arr[right] < arr[middle]) // If the right is less than the middle, swap them.
        swap(arr[middle], arr[right]);

    // cout << "END OF FIRST STEP: Left is: " << arr[left] << " | Middle is: " << arr[middle] << " | Right is: " << arr[right] << endl;

    // Swap the middle element with the next-to-last element (now the pivot)
    swap(arr[middle], arr[right - 1]);

    // cout << "END OF SECOND STEP: Left is: " << arr[left] << " | Middle is: " << arr[middle] << " | Right is: " << arr[right] << endl;
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
    int temp;
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
        // i and j have crossed
        swap(arr[i], arr[right - 1]);

        // now call quicksort on the two partitions
        quicksort(arr, left, i - 1); // left partition
        quicksort(arr, i + 1, right); // right partition
    }
}

// Heapsort
void heapsort(vector<long> &arr)
{
    // Build the heap
    buildHeap(arr);

    // Actually sort
    sortHeap(arr, 1, arr.size() - 1); // Passing in the root and the end of the list
}

void buildHeap(vector<long> &arr)
{
    // Calls sortHeap starting from the last parent
    for (int lastParent = arr[0] / 2; lastParent > 0; lastParent--)
        percolateDown(arr, lastParent);
}

void sortHeap(vector<long> &arr, int root, int end)
{
    for (int i = arr[0]; i > 1; i--)
    {
        //   DeleteMax until only one item is left in the heap, swapping root with the last item each time
        swap(arr[root], arr[i]); // Swapping root to end
        arr[0] = arr[0] - 1;     // Reduces the size by 1

        // Since heap is broken, we must percolateDown the new root value.
        if (arr[0] - 1 > 1) // If the heap size is not 1
            percolateDown(arr, root);
    }
}

void percolateDown(vector<long> &arr, int parent)
{
    int firstChild = (parent * 2);    // The first child of the parent
    int secondChild = firstChild + 1; // The second child of the parent

    bool twoChildren = true;

    if ((firstChild + 1) > arr[0])
        twoChildren = false; // Checks if the parent has a second child

    if (twoChildren) // If we have two children
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
    {
        sortedNode->next->prev = unsortedNode; // Change sortedNode's next prev node to point to the head
    }

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
            unsortedNode = unsortedNode->prev;                                                         // Moves unsortedNode backwards through the list

        swapNodes(unsortedNode, sortedNode, head); // Insert sortedNode into list

        // Update the nodes back to original positions in the list
        unsortedNode = updatePositions;
        sortedNode = unsortedNode;
    }
}

// Testing Purposes
void addNode(int val, Node *&head)
{
    Node *temp = head;
    while (temp->next != nullptr)
        temp = temp->next;
    temp->next = new Node(val, nullptr, temp);
}

void printList(Node *&head)
{
    Node *temp = head;
    cout << "[";
    while (temp != nullptr)
    {
        cout << temp->getDataVal() << " ";
        temp = temp->next;
    }
    cout << "]" << endl;
}

void printNode(Node *&theNode)
{
    cout << "Node is: " << theNode->prev->getDataVal() << " " << theNode->getDataVal() << " " << theNode->next->getDataVal() << endl;
}