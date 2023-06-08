//Nick Dunne and Fernando Payan - IT279 S2021
//Huffman Code decode file
#include "bitops.h"
#include "huffmanCommon.h"
#include <iostream>
#include <fstream>
using namespace std;

//Recursive method to build the tree
void buildTree(ibstream& inFile, Node*& curNode);

//Decode the .huf file, and write to the new file
void decodeFile(ibstream& inFile, ofstream& outFile, Node* root);

//It's main
int main(int argc, char** argv){

    //Check parameters
    if (argc != 2){
        cerr << "Incorrect usage: " << argv[0] << " readFromFile" << endl;
        exit(1);
    }

    //Parse parameters
    string fileName = argv[1];

    //Check file naming
    if (fileName.size() < 4 || fileName.substr(fileName.size() - 4) != ".huf"){
        cerr << "Only files ending with .huf may be decoded." << endl;
    } else {
        //Bit filestream for the .huf file
        ibstream inFile(fileName.c_str());
        //Outstream to store the resulting output file - naming easier for debugging purposes
        ofstream outFile(fileName.substr(0, fileName.size() - 4) + ".unhuf");

        //Build table from first part of filestream
        Node* huffmanTree = nullptr;
        buildTree(inFile, huffmanTree);

        //Write the encoded file contents to the output file
        decodeFile(inFile, outFile, huffmanTree);

        //Close files that are already open
        inFile.Close();
        outFile.close();

        //Clear dynamic memory
        cleanTree(huffmanTree);
    }

    //Return safely
    return 0;
}

void buildTree(ibstream& inFile, Node*& curNode){
    // Store the current bit obtained from the file
    int bitContents = inFile.Readbits(1);

    // Create a new node to be stored in the tree
    curNode = new Node();

    // If it's a leaf, read the character and put that in the node
    if (bitContents == 1)
    {
        // We want to read the next 8 bits
        bitContents = inFile.Readbits(8);

        // Save the contents into that node's data
        curNode->data = bitContents;

        // We need to state that the current node is a leaf
        curNode->isLeaf = true;
    }
    else // If not, we will recursively deal with reading the left subtree and then the right subtree
    {
        buildTree(inFile, curNode->left);
        buildTree(inFile, curNode->right);
    }
}

void decodeFile(ibstream& inFile, ofstream& outFile, Node* root){
    //Keep track of the current node in the tree
    Node* curNode = root;
    //Keep track of the current bit we are reading, and read the first bit
    int bitContents = inFile.Readbits(1);
    //Keep track of when we see a null character, so we know when we are done
    bool foundNullChar = false;

    //Iterate through the file while there are still bits to be read
    // i.e., as long as you don't find a null character, since this is how we end the file
    while(!foundNullChar){
        // Until we're at a leaf
        while (!curNode->isLeaf)
        {
            // If current bit is 0
            if (bitContents == 0)
            {
                // Go to left child
                curNode = curNode->left;
            }
            else 
            {
                // Go to right child
                curNode = curNode->right;
            }

            // Move to next bit of encoded message
            bitContents = inFile.Readbits(1);
        }

        // If we reach a leaf, we need to record the character of the leaf node
        if (curNode->data == 0)
            foundNullChar = true;
        else
        {
            // Write the character to the output file
            outFile << curNode->data;

            // Restart at the root
            curNode = root;
        }
    }
}