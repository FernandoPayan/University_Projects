// DisjointSet implementation using union by size and path compression
// By Mary Elaine Califf and Fernando Payan

#include "DisjointSet.h"
#include <iostream>

DisjointSet::DisjointSet(int numObjects)
{
    // Adds the number of objects to the vector. The N items are numbered 0 to N - 1.
    for (int i = 0; i < numObjects; i++)
        theArray.push_back(-1);

    // Update the number of values to the argument passed.
    numValues = numObjects;
}

// recursive method to find the item -- does path compression on the way out of the recursion
int DisjointSet::find(int objectIndex)
{
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
    // Variables that will store the set label for each index
    int indexOneRoot = find(objIndex1);
    int indexTwoRoot = find(objIndex2);

    int curSize = 0;

    // Check if the two indices are of the same size
    if (theArray[indexOneRoot] < 0 && theArray[indexOneRoot] == theArray[indexTwoRoot])
    {
        // Update the size of the root
        theArray[indexOneRoot] = theArray[indexOneRoot] + theArray[indexTwoRoot];

        // Points to it's parent
        theArray[indexTwoRoot] = indexOneRoot;

        // Update curSize to the value of the resulting set.
        curSize = theArray[indexOneRoot];
    }
    // If the second index's set is < than the first index's set, we make objIndex1's root point to objIndex2's root
    else if (theArray[indexTwoRoot] < theArray[indexOneRoot])
    {
        // Update the size of the root
        theArray[indexTwoRoot] = theArray[indexTwoRoot] + theArray[indexOneRoot];

        // Points to it's parent
        theArray[indexOneRoot] = indexTwoRoot;

        // Update curSize to the value of the resulting set.
        curSize = theArray[indexTwoRoot];
    }
    // If the first index's set is < than the second index's set, we make objIndex2's root point to objIndex1's root
    else if (theArray[indexOneRoot] < theArray[indexTwoRoot])
    {
        // Checks if we're adding root
        theArray[indexOneRoot] = theArray[indexOneRoot] + theArray[indexTwoRoot];

        // Points to it's parent
        theArray[indexTwoRoot] = indexOneRoot;

        // Update curSize to the value of the resulting set.
        curSize = theArray[indexOneRoot];
    }

    // Returns true if the resulting set is the same size as the number of objects (numValues * -1 to account for the negative value in resulting set).
    if (curSize == (numValues * -1))
        return true;
    return false;
}

void DisjointSet::printArrayValues(std::ostream &outputStream)
{
    for (int i = 0; i < numValues; i++)
    {
        outputStream << theArray[i] << " ";
    }
    outputStream << std::endl;
}
