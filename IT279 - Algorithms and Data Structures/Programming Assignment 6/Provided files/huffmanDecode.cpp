//Nick Dunne and __________ - IT279 S2021
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
    //TODO: Complete the method to build the decoding tree from the file

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
        //TODO: Complete the loop which decodes the file and writes the resulting characters to outFile
        
    }
}