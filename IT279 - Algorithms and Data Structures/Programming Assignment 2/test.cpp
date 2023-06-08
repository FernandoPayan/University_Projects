#include <iostream>
using namespace std;

class LinkedList
{
private:
    struct Node
    {
        int data;
        Node* next;

        Node(int theData, Node* node): data(theData), next(node) {};
    };

    Node* root;
    int size = 0;

public:
    LinkedList()
    {
        root = nullptr;
        size++;
    }

    LinkedList(Node* root)
    {
        this->root = root;
        root->next = nullptr;
        size++;
    }

    bool search(int data);

    void insert(int data);

    bool isEmpty();

    void deleteNode(int pos);

    void printList();
};

int main()
{
    LinkedList test;    

    //cout << test.isEmpty() << endl;
    test.insert(6);
    test.insert(5);
    test.insert(3);
    test.insert(4);
    test.printList();
    test.deleteNode(1);
    cout << "\n\n" << endl;
    test.printList();
    cout << "\n\n" << endl;
    cout << test.search(4) << endl;
}

void LinkedList::printList()
{
    if (!isEmpty())
    {
        Node* curPtr = root;
        while (curPtr != nullptr)
        {
            cout << curPtr->data << endl;
            curPtr = curPtr->next;
        }
        delete curPtr;
    }
}

bool LinkedList::search(int data)
{
    if (!isEmpty())
    {
        Node* curPtr = root;
        while (curPtr != nullptr)
        {
            if (curPtr->data == data)
                return true;
            curPtr = curPtr->next;
        }
        delete curPtr;
        return false;
    }
}

bool LinkedList::isEmpty()
{
    return root == nullptr;
}

void LinkedList::insert(int data)
{
    if (isEmpty())
    {
        root = new Node(data, root);
    }
    else
    {
        Node* curPtr = root;
        while (curPtr->next != nullptr)
        {
            curPtr = curPtr->next;
        }
        curPtr->next = new Node(data, nullptr);
        size++;
    }
}

void LinkedList::deleteNode(int pos)
{
    if (!isEmpty())
    {
        if (pos > size)
            cout << "Out of range " << endl;
        else
        {
            Node* temp = root;
            if (pos == 0)
            {
                temp = root;
                root = root->next;
                delete temp;
            }
            else
            {
                for (int i = 0; i < pos - 1; i++)
                {
                    temp = temp->next;
                }
                Node* del = temp->next; Node* aft = del->next;
                temp->next = aft;
                delete del;
            }
        }
    }
}