//Nick Dunne and Fernando Payan - IT279 S2021
//Huffman Code encode file
#include "bitops.h"
#include "huffmanCommon.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <unordered_map>
#include <math.h>
using namespace std;

//Comparator for the priority queue
template<>
struct std::less<Node*>
{
    bool operator()(Node* const& first, Node* const& second);
};

//Read all of the characters from the file, and track the counts of all the characters
void readCharCountsIntoArray(ifstream& inFile, vector<int>& charCounts);

//Populate the priority queue with character data, and return the number of characters that are in the string
int populatePriorityQueue(vector<int>& frequencyTable, priority_queue<Node*>& subtreePQ);

//Uses the created priority queue to make the tree and return the root
Node* generateHuffmanTree(priority_queue<Node*>& subtreePQ);

//Writes a table that contains the information for file translation
int generateEncodeTable(Node*& root, unordered_map<char, HuffmanChar>& charTable);

//Determines whether the new file will be smaller than the original
bool isNewFileSmaller(int originalCharCount, int newFileLength);

//Writes the huffman code tree to the output file
void writeTreeToFile(Node* root, obstream& outFile);

//Write the file contents encoded with the tree to the file
void writeCharsToFile(unordered_map<char, HuffmanChar>& charTable, ifstream& inFile, obstream& outFile);

//-- DEBUG METHODS -- Use them as you wish, but remove calls to them before you submit your program.

//Debug prints for the binary in the huffman tree
void printBinaryHuffmanTree(Node*& node, ostream& out = std::cout);

//Debug prints for the binary in the huffman tree
void printHuffmanTreeWithCodes(Node*& node, int counter = 0, int depth = 0, ostream& out = std::cout);

//Debug prints for the encoding function
void printHuffmanNode(Node* node, int counter, int depth, ostream& out);

//Debug method to convert integers to binary strings
string intToBinaryString(int num, int depth);

//It's main
int main(int argc, char** argv) {

    //Check parameters
    if (argc != 2) {
        cerr << "Incorrect usage: " << argv[0] << " readFromFile" << endl;
        exit(1);
    }

    //Parse parameters
    string fileName = argv[1];

    //Read from file
    ifstream inFile(fileName);

    //Don't skip whitespace inside file
    inFile >> std::noskipws;

    //Frequency of each character, indexing by extended-ascii value
    vector<int> frequencyTable(256, 0);
    //Terminating using the null character, so start at one instance
    frequencyTable[0] = 1;

    //Initialize priority queue to store the nodes and make the tree
    priority_queue<Node*> subtreePQ;

    //Initialize hash table to store the huffman codes by character
    unordered_map<char, HuffmanChar> hufHashTable;

    //Read all of the characters from the file into a frequency table named frequencyTable
    readCharCountsIntoArray(inFile, frequencyTable);

    //Populate the priority queue subtreePQ
    //  1 is subtracted to account for the null character we added to the frequency vector
    int originalCharCount = populatePriorityQueue(frequencyTable, subtreePQ) - 1;

    //Complete the function to generate the actual tree used for encoding and decoding
    Node* treeRoot = generateHuffmanTree(subtreePQ);

    //Generate the table used for encoding populated into hufHashTable, and return the new file length
    int newFileLength = generateEncodeTable(treeRoot, hufHashTable);
    newFileLength = ceil(newFileLength / 8.0);

    //Complete the method to determine whether the new file will have an improvement in size
    if (!isNewFileSmaller(originalCharCount, newFileLength)) {
        cout << "The new file would not be smaller than the original. Compression has stopped." << endl;
    }
    else {
        obstream hufOut((fileName + ".huf").c_str());

        //Write the huffman code tree to the file
        writeTreeToFile(treeRoot, hufOut);

        //Complete the function to write all of the characters to the file, doing the actual encoding
        writeCharsToFile(hufHashTable, inFile, hufOut);

        //TODO Extra Credit opportunity: Output the compression % as formatted in the instructions to console.

        //Close the binary file writer
        hufOut.Close();
    }

    //Clear dynamic memory
    cleanTree(treeRoot);
    //Close the input file
    inFile.close();
    //Return exit code
    return 0;
}

bool std::less<Node*>::operator()(Node* const& first, Node* const& second) {
    //TODO: Complete the less operator overload for Node*. Return true if the first should have lower priority than second (i.e. true if second should come off the priority queue before first)

}

void readCharCountsIntoArray(ifstream& inFile, vector<int>& charCounts) {
    //Placeholder character
    char currentChar;

    //Get first character
    inFile >> currentChar;
    acosf;

        //Read each character
        while (!inFile.eof()) {
            //Increase the character counter for the ascii value
            charCounts[currentChar]++;

            //Get a character
            inFile >> currentChar;
        }
}

int populatePriorityQueue(vector<int>& frequencyTable, priority_queue<Node*>& subtreePQ) {
    //TODO: Implement this function to populate the priority queue, and return the number of characters in the frequency table.

}

Node* generateHuffmanTree(priority_queue<Node*>& subtreePQ) {
    //TODO: Implement this function to generate the huffman code tree, and return a Node pointer to the root.

}

int generateEncodeTable(Node*& root, unordered_map<char, HuffmanChar>& charTable) {
    //TODO: Implement this function to populate the hash table with character data.
    //  The function must return the length of the new file (in bits), which will also include the code tree.
    //  You may want to consider creating a helper function for this.

}

bool isNewFileSmaller(int originalCharCount, int newFileLength) {
    //TODO: Implement this function to determine whether the .huf file would be smaller or not

}

void writeTreeToFile(Node* root, obstream& outFile) {
    if (root) {
        if (root->isLeaf) {
            //Write positive char flag
            outFile.Writebits(1, 1);
            //Write char
            outFile.Writebits(root->data, 8);
        }
        else {
            //Write negative char flag
            outFile.Writebits(0, 1);
        }

        //Make the recursive calls with the subtrees
        writeTreeToFile(root->left, outFile);
        writeTreeToFile(root->right, outFile);
    }
}

void writeCharsToFile(unordered_map<char, HuffmanChar>& charTable, ifstream& inFile, obstream& outFile) {
    //Reset the ifstream to read again
    inFile.clear(); //Clear flags (e.g., EOF flag)
    inFile.seekg(0); //Reset file pointer to beginning, so we can read through the file again

    //TODO: Encode the characters from the original file as well as an additional "end of message" null character, to the outFile.

}

//Helpful debug functions
void printBinaryHuffmanTree(Node*& node, ostream& out) {
    if (node) {
        if (node->isLeaf) {
            out << 1;
            out << '[';
            out << intToBinaryString(node->data, 8);
            out << ']';
        }
        else {
            out << 0;
        }

        //Make the recursive calls with the subtrees
        printBinaryHuffmanTree(node->left, out);
        printBinaryHuffmanTree(node->right, out);
    }
}

void printHuffmanTreeWithCodes(Node*& node, int counter, int depth, ostream& out) {
    if (node) {
        if (node->isLeaf) {
            printHuffmanNode(node, counter, depth, out);
        }

        counter = counter << 1;
        depth++;

        //Make the recursive calls with the subtrees
        printHuffmanTreeWithCodes(node->left, counter, depth, out);
        printHuffmanTreeWithCodes(node->right, counter + 1, depth, out);
    }
}

void printHuffmanNode(Node* node, int counter, int depth, ostream& out) {
    //Print beginning
    cout << "Count of ";

    //Special cases for weird characters
    switch (node->data) {
    case 0:
        out << "(null)";
        break;
    case ' ':
        out << "(sp)";
        break;
    case '\n':
        out << "\\n";
        break;
    default:
        out << node->data;
        break;
    }

    out << " is " << node->count << " // CODE:" << intToBinaryString(counter, depth) << endl;
}

string intToBinaryString(int num, int depth) {
    string result = "";
    while (depth > 0) {
        int bit = num % 2;
        num = num >> 1;
        depth--;
        result = to_string(bit) + result;
    }

    return result;
}