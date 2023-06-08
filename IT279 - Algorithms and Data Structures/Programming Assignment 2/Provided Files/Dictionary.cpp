// Implementation file for the Dictionary class
// Stores data in a basic binary search tree
// By Mary Elaine Califf

#include "Dictionary.h"
using namespace std;

Dictionary& Dictionary::operator=(const Dictionary& rhs)
{
    if (this->root != rhs.root) //comparing the tree roots because that's as effective as comparing the object addresses here
    {
        clear(this->root);           // delete the current tree;
        this->root = copy(rhs.root); // copy rhs's tree into this
    }
    return *this;
}

void Dictionary::addEntry(string* anEntry)
{
    // call private recursive insert method
    insert(anEntry, root);
}

bool Dictionary::findEntry(const string& key) const
{
    Node* curNode = root;
    while (curNode && *(curNode->data) != key)
    {
        if (*(curNode->data) > key)
        {
            curNode = curNode->left;
        }
        else
        {
            curNode = curNode->right;
        }
    }
    return curNode != nullptr;
}

void Dictionary::printDictionaryInOrder(ostream& outputStream) const
{
    if (root)
        printInOrder(outputStream, root);
}

void Dictionary::printDictionaryKeys(ostream& outputStream) const
{
    if (root)
        printTree(outputStream, root, 0);
}

// this is doing a postOrder traversal of the tree, deleting the string and then Node in each node of the tree
// the Dictionary is taking responsibility for the Entry objects, because they have to be dynamically allocated
// and only the tree has them all
void Dictionary::clear(Node* node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        delete node->data;
        delete node;
    }
}

// this is doing a postOrder traversal of the original tree, making a copy of each node
Dictionary::Node* Dictionary::copy(Dictionary::Node* origNode)
{
    if (origNode)
    {
        // recursively copy the left and right subtrees
        Node* newLeft = copy(origNode->left);
        Node* newRight = copy(origNode->right);

        string* newData = new string(*(origNode->data)); // copies the Entry from the original node

        Node* node = new Node(newData);
        node->left = newLeft;
        node->right = newRight;

        return node;
    }
    else
    {
        return nullptr;
    }
}

// recursive insert 
void Dictionary::insert(string* value, Node*& curPtr)
{
    if (!curPtr) // this is where the item goes
        curPtr = new Node(value);
    else if (*value < *(curPtr->data)) // heading left
        insert(value, curPtr->left);
    else // heading right
        insert(value, curPtr->right);

    // no need to do anything else, because this is a basic binary search tree
}

// this is doing an inOrder traversal of the tree, calling printEntry on each entry in the tree
void Dictionary::printInOrder(ostream& outputStream, Node* curNode) const
{
    string endOfLine = "\n"; // dealing with weird compiler issue
    if (curNode->left)
        printInOrder(outputStream, curNode->left);
    outputStream << (*(curNode->data)) << endOfLine;
    if (curNode->right)
        printInOrder(outputStream, curNode->right);
}

// this is doing a preOrder traversal of the tree, printing it out in a way that shows the structure
void Dictionary::printTree(ostream& outputStream, Node* curNode, int depth) const
{
    string padding = "  "; // dealing with weird compiler error
    string endOfLine = "\n";
    for (int i = 0; i < depth; i++)
    {
        outputStream << padding;
    }
    outputStream << *(curNode->data) << endOfLine;
    if (curNode->left)
    {
        printTree(outputStream, curNode->left, depth + 1);
    }
    if (curNode->right)
    {
        printTree(outputStream, curNode->right, depth + 1);
    }
}

// additional private function implementations go here
