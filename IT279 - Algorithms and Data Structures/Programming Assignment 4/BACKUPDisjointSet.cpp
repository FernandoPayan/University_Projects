// DisjointSet implementation using union by size and path compression
// By Mary Elaine Califf and Fernando Payan

#include "DisjointSet.h"
#include <iostream>

DisjointSet::DisjointSet(int numObjects)
{
    // Adds the number of objects to the vector
    for (int i = 0; i < numObjects; i++)
        theArray.push_back(-1);
    
    // Path Compression Example
    // theArray.push_back(1);
    // theArray.push_back(2);
    // theArray.push_back(-1);
    // theArray.push_back(1);
    // theArray.push_back(8);
    // theArray.push_back(0);
    // theArray.push_back(8);
    // theArray.push_back(6);
    // theArray.push_back(-1);
    // theArray.push_back(4);
    
}

//recursive method to find the item -- does path compression on the way out of the recursion
int DisjointSet::find(int objectIndex)
{
    // to do -- see assignment instructions for details

    if (theArray[objectIndex] < 0) // Base Case: If we found the root
        return objectIndex;
    else
    {
        // Save off the result of the find
        int setLabel = find(theArray[objectIndex]); 

        // Each item points directly to the root
        theArray[objectIndex] = setLabel; 

        // Returns the set label for an object given its index
        return setLabel; 
    }
    
}

bool DisjointSet::doUnion(int objIndex1, int objIndex2)
{    
    std::cout << "Doing doUnion(" << objIndex1 << ", " << objIndex2 << ")" << std::endl;
    
    // Check if the two indices are of the same size
    if (theArray[objIndex1] < 0 && theArray[objIndex1] == theArray[objIndex2])
    {
        std::cout << "Indicies are the same. Making " << objIndex2 << " point to " << objIndex1 << "\n";
        
        // Update the size of the root
        if (theArray[objIndex1] < 0)
            theArray[objIndex1] = theArray[objIndex1] + theArray[objIndex2];

        theArray[objIndex2] = objIndex1;
    } else
    {
        // Variables that will store the set label for each index
        int indexOneRoot = find(objIndex1);
        int indexTwoRoot = find(objIndex2);
        std::cout << indexOneRoot << std::endl;
        std::cout << indexTwoRoot << std::endl;

        // Testing Purposes. To be deleted
        std::cout << objIndex1 << "'s root is at: " << indexOneRoot << " with height " << theArray[indexOneRoot] << "\n";
        std::cout << objIndex2 << "'s root is at: " << indexTwoRoot << " with height " << theArray[indexTwoRoot] << "\n";

        // If the second index's set is < than the first index's set, we make objIndex1's root point to objIndex2's root
        if (theArray[indexTwoRoot] < theArray[indexOneRoot])
        {
            // Testing Purposes. To be deleted.
            std::cout << "Set " << indexTwoRoot << " is larger" << "\n";

            // Update the size of the root
            if (theArray[indexTwoRoot] < 0)
                theArray[indexTwoRoot] = theArray[indexTwoRoot] + theArray[indexOneRoot];
            else
                theArray[indexTwoRoot]--;

            // Points to it's parent
            theArray[indexOneRoot] = indexTwoRoot;
            

            // Testing Purposes. To be deleted
            std::cout << indexOneRoot << " now points at: " << theArray[indexOneRoot] << "\n";
            std::cout << indexTwoRoot << "'s height is now: " <<  theArray[indexTwoRoot] << "\n";
        }
        // If the first index's set is < than the second index's set, we make objIndex2's root point to objIndex1's root
        else if (theArray[indexOneRoot] < theArray[indexTwoRoot])
        {
            std::cout << "Set " << objIndex1 << " is bigger. Making " << objIndex2 << " point to it." << std::endl;

            if (theArray[indexOneRoot] < 0) // If objIndex1 has more than 1 node associated, we need to account for all that nodes
                theArray[indexOneRoot] = theArray[indexOneRoot] + theArray[indexTwoRoot];
            else
                theArray[indexOneRoot]--;
            theArray[indexTwoRoot] = indexOneRoot;

            // Testing Purposes. To be deleted
            std::cout << indexOneRoot << " now points at: " << theArray[indexOneRoot] << "\n";
            std::cout << indexTwoRoot << "'s height is now: " <<  theArray[indexTwoRoot] << "\n";
        }
    }

    // Testing Purposes: Prints the current array. To be deleted
        for (int i = 0; i < theArray.size(); i++)
        {
            std::cout << theArray[i] << " | ";
        }
        std::cout << "\n";

    // Returns true if the resulting set is the same size as the number of objects
    
}

void DisjointSet::printArrayValues(std::ostream &outputStream)
{
    for (int i = 0; i < numValues; i++)
    {
        outputStream << theArray[i] << " ";
    }
    outputStream << std::endl;
}
