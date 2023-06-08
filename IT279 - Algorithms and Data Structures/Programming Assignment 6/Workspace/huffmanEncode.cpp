// Nick Dunne and Fernando Payan - IT279 S2021
// Huffman Code encode file
#include "bitops.h"
#include "huffmanCommon.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <unordered_map>
#include <math.h>
using namespace std;

// Comparator for the priority queue
template <>
struct std::less<Node *>
{
    bool operator()(Node *const &first, Node *const &second);
};

// Read all of the characters from the file, and track the counts of all the characters
void readCharCountsIntoArray(ifstream &inFile, vector<int> &charCounts);

// Populate the priority queue with character data, and return the number of characters that are in the string
int populatePriorityQueue(vector<int> &frequencyTable, priority_queue<Node *> &subtreePQ);

// Uses the created priority queue to make the tree and return the root
Node *generateHuffmanTree(priority_queue<Node *> &subtreePQ);

// Writes a table that contains the information for file translation
int generateEncodeTable(Node *&root, unordered_map<char, HuffmanChar> &charTable);

// Determines whether the new file will be smaller than the original
bool isNewFileSmaller(int originalCharCount, int newFileLength);

// Writes the huffman code tree to the output file
void writeTreeToFile(Node *root, obstream &outFile);

// Write the file contents encoded with the tree to the file
void writeCharsToFile(unordered_map<char, HuffmanChar> &charTable, ifstream &inFile, obstream &outFile);

//-- DEBUG METHODS -- Use them as you wish, but remove calls to them before you submit your program.

// Debug prints for the binary in the huffman tree
void printBinaryHuffmanTree(Node *&node, ostream &out = std::cout);

// Debug prints for the binary in the huffman tree
void printHuffmanTreeWithCodes(Node *&node, int counter = 0, int depth = 0, ostream &out = std::cout);

// Debug prints for the encoding function
void printHuffmanNode(Node *node, int counter, int depth, ostream &out);

// Debug method to convert integers to binary strings
string intToBinaryString(int num, int depth);

//-- HELPER METHODS --
// Used to populate the hash table with the characters
Node *populateHashTable(Node *&node, int counter, int depth, unordered_map<char, HuffmanChar> &charTable, int &encodedLength, int &treeLength);

// It's main
int main(int argc, char **argv)
{

    // Check parameters
    if (argc != 2)
    {
        cerr << "Incorrect usage: " << argv[0] << " readFromFile" << endl;
        exit(1);
    }

    // Parse parameters
    string fileName = argv[1];

    // Read from file
    ifstream inFile(fileName);

    // Don't skip whitespace inside file
    inFile >> std::noskipws;

    // Frequency of each character, indexing by extended-ascii value
    vector<int> frequencyTable(256, 0);
    // Terminating using the null character, so start at one instance
    frequencyTable[0] = 1;

    // Initialize priority queue to store the nodes and make the tree
    priority_queue<Node *> subtreePQ;

    // Initialize hash table to store the huffman codes by character
    unordered_map<char, HuffmanChar> hufHashTable;

    // Read all of the characters from the file into a frequency table named frequencyTable
    readCharCountsIntoArray(inFile, frequencyTable);

    // Populate the priority queue subtreePQ
    //   1 is subtracted to account for the null character we added to the frequency vector
    int originalCharCount = populatePriorityQueue(frequencyTable, subtreePQ) - 1;

    // Complete the function to generate the actual tree used for encoding and decoding
    Node *treeRoot = generateHuffmanTree(subtreePQ);

    // Generate the table used for encoding populated into hufHashTable, and return the new file length
    int newFileLength = generateEncodeTable(treeRoot, hufHashTable);
    newFileLength = ceil(newFileLength / 8.0);

    // Complete the method to determine whether the new file will have an improvement in size
    if (!isNewFileSmaller(originalCharCount, newFileLength))
    {
        cout << "The new file would not be smaller than the original. Compression has stopped." << endl;
    }
    else
    {
        obstream hufOut((fileName + ".huf").c_str());

        // Write the huffman code tree to the file
        writeTreeToFile(treeRoot, hufOut);

        // Complete the function to write all of the characters to the file, doing the actual encoding
        writeCharsToFile(hufHashTable, inFile, hufOut);

        // TODO Extra Credit opportunity: Output the compression % as formatted in the instructions to console.

        // Close the binary file writer
        hufOut.Close();
    }

    // Clear dynamic memory
    cleanTree(treeRoot);
    // Close the input file
    inFile.close();
    // Return exit code
    return 0;
}

bool std::less<Node *>::operator()(Node *const &first, Node *const &second)
{
    // Check if the first node has a greater frequency count than the second node
    if (first->count > second->count)
        return true;

    return false;
}

void readCharCountsIntoArray(ifstream &inFile, vector<int> &charCounts)
{
    // Placeholder character
    char currentChar;

    // Get first character
    inFile >> currentChar;
    acosf;

    // Read each character
    while (!inFile.eof())
    {
        // Increase the character counter for the ascii value
        charCounts[currentChar]++;

        // Get a character
        inFile >> currentChar;
    }
}

int populatePriorityQueue(vector<int> &frequencyTable, priority_queue<Node *> &subtreePQ)
{
    // Add in the null value to the priority queue
    subtreePQ.push(new Node(0, 1));

    int wordCount = 0;
    // Iterate through the frequency table
    for (int i = 1; i < frequencyTable.size(); i++)
    {
        int frequency = frequencyTable.at(i);

        // Add all the frequencies
        if (frequency > 0)
        {
            // Create a node and push it  into the PQ
            subtreePQ.push(new Node(i, frequency));

            // Increase the word count based on the frequency
            for (int i = 0; i < frequency; i++)
                wordCount++;
        }
    }
    return wordCount;
}

Node *generateHuffmanTree(priority_queue<Node *> &subtreePQ)
{
    Node *tree;

    // Keep iterating through the priority queue until we get our final tree
    while (subtreePQ.size() != 1)
    {
        // Store the first two nodes out of the PQ
        Node *node1 = subtreePQ.top();
        subtreePQ.pop();
        Node *node2 = subtreePQ.top();
        subtreePQ.pop();

        // Create a new node to be the root of a new tree that has node1 and node2 as subtrees
        tree = new Node(node1, node2, (node1->count + node2->count));

        // Push the resulting tree into the PQ
        subtreePQ.push(tree);
    }
    return tree;
}

int generateEncodeTable(Node *&root, unordered_map<char, HuffmanChar> &charTable)
{
    // Stores the length of the encoded message
    int encodedLength = 0;

    // Stores the length of the code tree
    int treeLength = 0;

    // Populates the hash table with character data
    populateHashTable(root, 0, 0, charTable, encodedLength, treeLength);

    // Returns the length of the new file in bits
    return (encodedLength + treeLength);
}

bool isNewFileSmaller(int originalCharCount, int newFileLength)
{
    if (newFileLength < originalCharCount)
        return true;
    return false;
}

void writeTreeToFile(Node *root, obstream &outFile)
{
    if (root)
    {
        if (root->isLeaf)
        {
            // Write positive char flag
            outFile.Writebits(1, 1);
            // Write char
            outFile.Writebits(root->data, 8);
        }
        else
        {
            // Write negative char flag
            outFile.Writebits(0, 1);
        }

        // Make the recursive calls with the subtrees
        writeTreeToFile(root->left, outFile);
        writeTreeToFile(root->right, outFile);
    }
}

void writeCharsToFile(unordered_map<char, HuffmanChar> &charTable, ifstream &inFile, obstream &outFile)
{
    // Reset the ifstream to read again
    inFile.clear();  // Clear flags (e.g., EOF flag)
    inFile.seekg(0); // Reset file pointer to beginning, so we can read through the file again

    // Stores the current character
    char currentChar;

    // We need to read before the loop
    inFile >> currentChar;

    // Read each character
    while (!inFile.eof())
    {
        // Find that character in our hash table
        HuffmanChar curChar = charTable.at(currentChar);

        // Print the bits to the outstream
        outFile.Writebits(curChar.code, curChar.depth);

        // Get the character
        inFile >> currentChar;
    }

    // Encode the "end of message" null character here
    outFile.Writebits(charTable.at(0).code, charTable.at(0).depth);
}

// Helpful debug functions
void printBinaryHuffmanTree(Node *&node, ostream &out)
{
    if (node)
    {
        if (node->isLeaf)
        {
            out << 1;
            out << '[';
            out << intToBinaryString(node->data, 8);
            out << ']';
        }
        else
        {
            out << 0;
        }

        // Make the recursive calls with the subtrees
        printBinaryHuffmanTree(node->left, out);
        printBinaryHuffmanTree(node->right, out);
    }
}

void printHuffmanTreeWithCodes(Node *&node, int counter, int depth, ostream &out)
{
    if (node)
    {
        if (node->isLeaf)
        {
            printHuffmanNode(node, counter, depth, out);
        }

        counter = counter << 1;
        depth++;

        // Make the recursive calls with the subtrees
        printHuffmanTreeWithCodes(node->left, counter, depth, out);
        printHuffmanTreeWithCodes(node->right, counter + 1, depth, out);
    }
}

void printHuffmanNode(Node *node, int counter, int depth, ostream &out)
{
    // Print beginning
    cout << "Count of ";

    // Special cases for weird characters
    switch (node->data)
    {
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

string intToBinaryString(int num, int depth)
{
    string result = "";
    while (depth > 0)
    {
        int bit = num % 2;
        num = num >> 1;
        depth--;
        result = to_string(bit) + result;
    }

    return result;
}

// Helper Methods
Node *populateHashTable(Node *&node, int counter, int depth, unordered_map<char, HuffmanChar> &charTable, int &encodedLength, int &treeLength)
{
    if (node)
    {
        if (node->isLeaf)
        {
            // Create the HuffmanChar object
            HuffmanChar encodedNode = HuffmanChar(counter, depth);

            // Append the encodedNode into the array
            charTable.insert(make_pair(node->data, encodedNode));

            // Update the encoded message length
            encodedLength += (node->count * intToBinaryString(encodedNode.code, encodedNode.depth).length());

            // Update the tree length
            treeLength += 9;
        }
        else // Add 1 bit to the tree Length
            treeLength += 1;

        // Update the counter and the depth
        counter = counter << 1;
        depth++;

        // Make the recursive calls with the subtrees
        populateHashTable(node->left, counter, depth, charTable, encodedLength, treeLength);
        populateHashTable(node->right, counter + 1, depth, charTable, encodedLength, treeLength);
    }
}