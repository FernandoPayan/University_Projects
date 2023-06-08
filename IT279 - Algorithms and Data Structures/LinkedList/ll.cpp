#include <iostream>
using namespace std;

class LinkedList
{
private:
    struct Node
    {
        int data;
        Node* next;
    };

    Node* root;

public:
    LinkedList()
    {
        root = nullptr;
    }

    void search(int data);

    void insert(int data);

    bool isEmpty();

    void deleteNode(int data);

    void printList();
};

int main()
{
    LinkedList test;
    test.insert(6);
    test.insert(4);
    test.insert(5);
    test.insert(2);
    test.insert(9);
    test.printList();
}

bool LinkedList::isEmpty()
{
    return root == nullptr;
}

void LinkedList::insert(int data)
{
    Node* temp = root;

    if (temp == nullptr)
    {
        root = new Node;
        root->data = data;
    }
    else
    {
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = new Node;
        temp->next->data = data;
        temp->next->next = nullptr;
    }
}

void LinkedList::deleteNode(int data)
{
    if (root->data = data)
    {
        delete root;
    }


    Node* temp = root;
}

void LinkedList::printList()
{
    Node* temp = root;
    while (temp != nullptr)
    {
        cout << temp->data << endl;
        temp = temp->next;
    }
}