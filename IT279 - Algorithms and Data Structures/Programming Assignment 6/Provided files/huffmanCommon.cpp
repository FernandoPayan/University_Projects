//Nick Dunne - IT279 S2021
//Huffman Code structures used in encoding and decoding
#include "huffmanCommon.h"
#include <iostream>
using namespace std;

Node::Node() {
    data = 0;
    count = 0;
    isLeaf = false;
    left  = nullptr;
    right = nullptr;
}

Node::Node(Node* leftSubtree, Node* rightSubtree, int charCount) : Node() {
    left = leftSubtree;
    right = rightSubtree;
    count = charCount;
}

Node::Node(char charData, int charCount) : Node() {
    data = charData;
    count = charCount;
    isLeaf = true;
}

void cleanTree(Node*& root){
    if (root->left) cleanTree(root->left);
    if (root->right) cleanTree(root->right);

    delete root;
}