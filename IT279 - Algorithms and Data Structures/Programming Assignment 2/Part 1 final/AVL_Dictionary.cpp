// Implementation file for the Dictionary class
// Stores data in a basic AVL search tree
// By Mary Elaine Califf and Fernando Payan

#include "Dictionary.h"
#include <iostream>
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
        string* newData = new string(*(origNode->data));

        // Recursively copy the left and right subtrees
        return new Node{newData, copy(origNode->left), copy(origNode->right), origNode->height};
    }
    else // If node is null
    {
        return nullptr;
    }
}

// recursive insert 
void Dictionary::insert(string* value, Node*& curPtr)
{
    if (curPtr == nullptr) // this is where the item goes
        curPtr = new Node(value, nullptr, nullptr);
    else if (*value < *(curPtr->data)) // heading left
        insert(value, curPtr->left);
    else // heading right
        insert(value, curPtr->right);

    balance(curPtr);
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
void Dictionary::balance(Node*& node)
{
    if (node == nullptr) // Does nothing if node is null
        return;
    
    // Checks if the height of the left child is > height of right child
    if (height(node->left) - height(node->right) > ALLOWED_IMBALANCE) 
        {
            if (height(node->left->left) >= height(node->left->right))
                rotateWithLeftChild(node);
            else
                doubleWithLeftChild(node);
        }
    else // Checks if the height of the right child is > height of left child
    {
        if (height(node->right) - height(node->left) > ALLOWED_IMBALANCE)
        {
            if (height(node->right->right) >= height(node->right->left))
                rotateWithRightChild(node);
            else
                doubleWithRightChild(node);
        }
        node->height = max(height(node->left), height(node->right)) + 1;
    }
}

int Dictionary::height(Node* node) const
{
    if (node == nullptr)
        return -1;
    else
        return node->height;
}

void Dictionary::rotateWithLeftChild(Node*& origNode)
{
    Node* childNode = origNode->left;
    origNode->left = childNode->right;
    childNode->right = origNode;
    origNode->height = max(height(origNode->left), height(origNode->right)) + 1;
    childNode->height = max(height(childNode->left), origNode->height) + 1;
    origNode = childNode;
}

void Dictionary::doubleWithLeftChild(Node*& origNode)
{
    rotateWithRightChild(origNode->left);
    rotateWithLeftChild(origNode);
}

void Dictionary::rotateWithRightChild(Node*& origNode)
{
    Node* childNode = origNode->right;
    origNode->right = childNode->left;
    childNode->left = origNode;
    origNode->height = max(height(origNode->left), height(origNode->right)) + 1;
    childNode->height = max(height(childNode->right), origNode->height) + 1;
    origNode = childNode;
}

void Dictionary::doubleWithRightChild(Node*& origNode)
{
    rotateWithLeftChild(origNode->right);
    rotateWithRightChild(origNode);
}