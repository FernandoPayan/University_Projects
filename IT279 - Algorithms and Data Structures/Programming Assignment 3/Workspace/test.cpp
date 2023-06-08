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
void toHead(Node *&head, Node *&sortedNode);
void toEnd(Node *&lastNode, Node *&sortedNode);
void insertNode(Node *&unsortedNode, Node *&sortedNode);

// Quicksort
long medianOfThree(vector<long> &arr, int left, int right);
void insertionSort(vector<long> &arr, int left, int right);

// Heapsort
void heapsort(vector<long> &arr);
void buildHeap(vector<long> &arr);
void sortHeap(vector<long> &arr, int parent, int size);
void percolateDown(vector<long> &arr, int parent);
void exchangeVals(vector<long> &arr, int parent, int child);

void dumb(int left, int right);

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

    long med = medianOfThree(theArray, 0, theArray.size() - 1);
    cout << "Our pivot is: " << med << "\n\n";

    med = medianOfThree(secArray, 0, secArray.size() - 1);
    cout << "Our pivot is: " << med << endl;

}

void dumb(int left, int right)
{
    if (right - left < 50)
        cout << (left + right) - 1 << " is <= 50, so we need to do insertion sort" << endl;
    else
        cout << (left + right) - 1 << " is not <= 50. So we partition. " << endl;
}

// Heapsort
void heapsort(vector<long>& arr)
{
  // Build the heap
  buildHeap(arr);

  // Actually sort
  sortHeap(arr, 1, arr.size() - 1); // Passing in the root and the end of the list
}

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
    //   DeleteMax until only one item is left in the heap, swapping root with the last item each time
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

// QuickSort
long medianOfThree(vector<long> &arr, int left, int right)
{
    int middle = (left + right) / 2;
    int temp;
    cout << "Left is: " << arr[left] << " | Middle is: " << arr[middle] << " | Right is: " << arr[right] << endl;

    // Sort the first, middle, and last elements of the partition
    if( arr[middle] < arr[left]) // If the middle is less than the left, swap them.
        swap(arr[left], arr[middle]);

    if (arr[right] < arr[left]) // If the right is less than the left, swap them.
        swap(arr[left],arr[right]);

    if (arr[right] < arr[middle]) // If the right is less than the middle, swap them.
        swap(arr[middle], arr[right]);

    cout << "END OF FIRST STEP: Left is: " << arr[left] << " | Middle is: " << arr[middle] << " | Right is: " << arr[right] << endl;

    // Swap the middle element with the next-to-last element (now the pivot)
    swap(arr[middle], arr[right - 1]);

    cout << "END OF SECOND STEP: Left is: " << arr[left] << " | Middle is: " << arr[middle] << " | Right is: " << arr[right] << endl;
    return arr[right - 1]; // Returns the pivot
}

void insertionSort(vector<long> &arr, int left, int right)
{
    cout << "Before sorting: [";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << ", ";
    cout << "]" << endl;

    int i, j, temp;
    for (i = 1; i < arr.size(); i++)
    {
        j = i;
        temp = arr[i];
        while (j > 0 && temp < arr[j - 1])
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = temp;
    }

    cout << "After sorting: [";
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << ", ";
    cout << "]" << endl;
}

// Insertion Sort
void insertionSort(Node *&head)
{
    // Since we don't need to pull head out of the list, we just skip to the next element in the list
    Node *unsortedNode = head;     // Keeps track of the previous node
    Node *sortedNode = head->next; // Keeps track of our current node

    while (sortedNode != nullptr) // Outer loop
    {
        if (unsortedNode->getDataVal() < sortedNode->getDataVal()) // If the current node is smaller than the previous, we need to update
            unsortedNode = unsortedNode->next;

        while (sortedNode->prev != nullptr && sortedNode->prev->getDataVal() > sortedNode->getDataVal()) // Inner loop
        {
            // If we need to insert at the beginning of the list (i.e. have a new head)
            if (sortedNode->prev == head)
                toHead(head, sortedNode);
            else // Do regular insertion
                insertNode(unsortedNode, sortedNode);
        }
        sortedNode = unsortedNode->next; // Moves to the next item in the list
        printList(head);
    }
}

void toHead(Node *&head, Node *&sortedNode)
{
    // Change sortedNode's next prev node to point to the head
    sortedNode->next->prev = head;

    // Make head point to sortedNode's next and head's prev point to sorted node
    head->next = sortedNode->next;
    head->prev = sortedNode;

    // Update sortedNode to have next point to head and prev point to null (since it's the new head)
    sortedNode->next = head;
    sortedNode->prev = head->prev;

    // Update the head of the list
    head = sortedNode;
}

void insertNode(Node *&unsortedNode, Node *&sortedNode)
{
    if (sortedNode->next == nullptr) // Special case if we reach the end of the list
    {
        // Moves unsorted node to the end of the list
        unsortedNode->next = nullptr;

        // Update sorted node
        sortedNode->next = unsortedNode;
        sortedNode->prev = unsortedNode->prev;
        sortedNode->prev = sortedNode;
        sortedNode->next = unsortedNode;
    }
    else
    {
        sortedNode->next->prev = sortedNode->prev;
        sortedNode->prev->next = sortedNode->next;
        sortedNode->prev->prev->next = sortedNode;
        sortedNode->prev = sortedNode->next->prev->prev;
        sortedNode->next = sortedNode->next->prev;
        sortedNode->next->prev = sortedNode;
    }
}

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
        cout << temp->getDataVal() << ", ";
        temp = temp->next;
    }
    cout << "]" << endl;
}

void printNode(Node *&theNode)
{
    cout << "Node is: " << theNode->prev->getDataVal() << " " << theNode->getDataVal() << " " << theNode->next->getDataVal() << endl;
}