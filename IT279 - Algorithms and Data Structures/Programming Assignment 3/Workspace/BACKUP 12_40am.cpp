#include <iostream>
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
void insertNode(Node *&unsortedNode, Node *&sortedNode, Node*& head);

int main()
{
    Node *head = new Node(13, nullptr, nullptr);
    addNode(7, head);
    addNode(9, head);
    addNode(2, head);
    addNode(15, head);
    addNode(10, head);
    addNode(5, head);
    addNode(12, head);

    // Node *head = new Node(2, nullptr, nullptr);
    // addNode(4, head);
    // addNode(6, head);
    // addNode(7, head);
    // addNode(3, head);
    // addNode(10, head);
    // addNode(11, head);

    printList(head);
    insertionSort(head); // Points to 3
    // printList(head);
}

void insertionSort(Node*& head)
{
    // Since we don't need to pull head out of the list, we just skip to the next element in the list
    Node *unsortedNode = head;     // Keeps track of the previous node
    Node *sortedNode = head->next; // Keeps track of our current node

    while (sortedNode != nullptr)
    {
        Node* temp = sortedNode;
        cout << "Unsortred is: " << unsortedNode->getDataVal() << " | Sorted is: " << sortedNode->getDataVal() << endl;
        insertNode(unsortedNode, sortedNode, head);
    }
}

void insertNode(Node *&unsortedNode, Node *&sortedNode, Node*& head)
{
    if (unsortedNode->getDataVal() < sortedNode->getDataVal())
    {
        cout << unsortedNode->getDataVal() << " is smaller than " << sortedNode->getDataVal() << endl;
        unsortedNode = unsortedNode->next;
        sortedNode = sortedNode->next;
    }
    else // If the previous node is > the current node
    {
        cout << unsortedNode->getDataVal() << " is greater than " << sortedNode->getDataVal() << endl;

        // Changes previous node's next to head's next node
        unsortedNode->next = sortedNode->next;
        if (sortedNode->next != nullptr)
            sortedNode->next->prev = unsortedNode;

        // Set temps for unsortedNode and sortedNode
        Node *tempForSortedNode = unsortedNode->next; // Keeps track of where sortedNode was at in the list
        Node *tempForUnsortedNode = unsortedNode;      // Keeps track of where unsortedNode was at in the list
        cout << "tempForUnsortedNode is: " << tempForUnsortedNode->getDataVal() << " | tempForSortedNode is: " << tempForSortedNode->getDataVal() << endl;

        while (unsortedNode->getDataVal() > sortedNode->getDataVal() && unsortedNode->prev != nullptr) // Finds the spot to insert the node at
        {
            cout << unsortedNode->getDataVal() << " is greater than " << sortedNode->getDataVal() << ". Moving to next element." << endl;
            unsortedNode = unsortedNode->prev; // Moves unsortedNode backwards through the list
        }

        cout << unsortedNode->getDataVal() << " is less than " << sortedNode->getDataVal() << ". Moving to calculation." << endl;
        if (unsortedNode->prev != head)
            cout << "unsortedNode: " << unsortedNode->prev->getDataVal() << " | " << unsortedNode->getDataVal() << " | " << unsortedNode->next->getDataVal() << endl;
        else
            cout << "We accessed the head" << endl;
        if (unsortedNode->prev != head && unsortedNode->getDataVal() > sortedNode->getDataVal()) // Inserting node in a place that is not at the head
        {
            cout << "Inserting " << sortedNode->getDataVal() << " in first if statement" << endl;
            Node *temp = unsortedNode->next;
            cout << "Temp: " << temp->prev->getDataVal() << " | Next: " << temp->prev->next->getDataVal() << endl;

            unsortedNode->next = sortedNode;
            cout << "unsortedNode Next: " << unsortedNode->next->getDataVal() << " | Next: " << unsortedNode->next->next->getDataVal() << endl;

            sortedNode->prev = unsortedNode;
            sortedNode->next = temp;
            cout << "sortedNode: " << sortedNode->prev->getDataVal() << " | Value: " << sortedNode->getDataVal() << " | Next: " << sortedNode->next->getDataVal() << endl;

            printList(unsortedNode);
        }
        else // Adding at the beginning of the list (i.e. new head)
        {
            cout << "Inserting " << sortedNode->getDataVal() << " in else statement" << endl;
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

        cout << "\n\n";
        // printList(unsortedNode);

        // Set unsortedNode and sortedNode back to their positions
        unsortedNode = tempForUnsortedNode;
        sortedNode = tempForSortedNode;
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