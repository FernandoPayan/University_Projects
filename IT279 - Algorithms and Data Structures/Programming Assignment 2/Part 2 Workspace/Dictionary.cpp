// Implementation file for the Dictionary class
// Stores data in a hash table
// By Mary Elaine Califf and Fernando Payan

#include "Dictionary.h"
#include <iostream>
#include <string>
#include <vector> // Used for sorting
#include <algorithm> // Used for sorting
using namespace std; 

Dictionary::Dictionary() // Default Constructor
{
    hashArray = new HashEntry[currentSize]; // Creates the hash table array
}

Dictionary::Dictionary(const Dictionary& orig) // Copy Constructor
{
    copy(orig); // Calls the copy method
}

Dictionary& Dictionary::operator=(const Dictionary& rhs)
{
    if (this != &rhs)
    {
        clear(); 
        copy(rhs);
    }
    return *this;
}

void Dictionary::addEntry(string* anEntry)
{
    cout << "Calling rehash " << endl;
    rehash(); // Calls rehash. Checks if we need to rehash and if so, we will rehash.

    cout << "Inserting " << *anEntry << " into the hash table" << endl;
    insert(anEntry, entry, hashArray, false);
}

bool Dictionary::findEntry(const string& key) const
{
    int index = hash(key, currentSize); // Gets the initial index of the key

    while (true) // We want to keep looping until we return a boolean. This will break when we return a bool.
    {
        if (!hashArray[index].flag) // No element at this position which means this key cannot be here.
        {
            return false;
        }
        else
        {
            if (key == *hashArray[index].data)
            {
                return true;
            }
        }
    }
}

void Dictionary::printDictionaryInOrder(ostream& outputStream) const
{
    vector<string*> testArray; // Creates a vector of type HashEntry
    
    for (int i = 0; i < currentSize; i++) // Iterates through the size of the hash table array
    {
        if (hashArray[i].flag) // If there is an item at the index
            testArray.push_back(hashArray[i].data);
    }
    sort(testArray.begin(), testArray.end()); // May cause a crash?

    //create a for loop that prints out testarray.at(index)
    for (int j = 0; j < testArray.size(); j++)
        cout << testArray.at(j) << endl; // change cout to outputStream
} 

void Dictionary::printDictionaryKeys(ostream& outputStream) const
{
    for (int i = 0; i < currentSize; i++)
    {
        if (hashArray[i].flag) // If we have an item at the index
        {
            cout << i << ": " << *hashArray[i].data << "\n";
        }
        else
            cout << i << ": " << "\n";
    }
}

void Dictionary::clear()
{
    for (int i = 0; i < currentSize; i++)
    {
        
        if (hashArray[i].flag)
        {
            // Will delete the object at the index
            delete hashArray[i].data;
        }
    }
    delete [] hashArray;
}

void Dictionary::copy(const Dictionary& orig)
{
    this->currentSize = orig.currentSize;
    this->numEntries = orig.numEntries;
    this->rehashCounter = orig.rehashCounter;
    this->hashArray = new HashEntry[currentSize];

    for (int i = 0; i < orig.currentSize; i++)
    {
        if (hashArray[i].flag) // If there is an element at index i
        {
            string* newData = new string(*(hashArray[i].data));
            this->hashArray[i].data = newData;
        }
    }
}

void Dictionary::insert(std::string* key, HashEntry* curPtr, HashEntry* array, bool doRehash)
{
    cout << "CURRENT SIZE IS: " << currentSize << endl;
    int index = hash(*key, currentSize); // Gets the index we will be looking at
    cout << "Our computed index is: " << index << endl;

    while (!checkIndex(key, entry, index, array)) // if index is not taken, we will insert the value to that index.
    {
        index = findIndex(key, entry, index, array);
    }
    if (!doRehash) 
        numEntries++;// increases the number of entries
    
    cout << "Leaving insert method..." << endl;
}

// additional private function implementations go here
void Dictionary::rehash()
{
    if (!isEmpty())
    {
        if (numEntries >= (currentSize / 2)) // If at least 50% full, rehash table
        {
            // Create a new array at the new size
            int oldSize = currentSize; // Size of the old table
            rehashCounter++; // Used to iterate to the next index in our array
            currentSize = singleHashPrimes[rehashCounter];
            HashEntry* temp = new HashEntry[currentSize];
            
            // Goes through the old array and insert each item into the new array
            for (int i = 0; i < oldSize; i++) 
            {
                if (hashArray[i].flag) // If there's a value at the index, we will insert it into the new table
                {
                    insert(hashArray[i].data, entry, temp, true); // Inserts the value at the index
                }
            }

            delete [] hashArray; // Deletes the old array

            // Set variables to use the new array
            hashArray = temp;
        }
    }
}    


unsigned int Dictionary::hash( const std::string& key, int tableSize) const
{
    unsigned int hashVal = 0;
    for (char ch : key) // Iterates through each character in the string key
    {
        hashVal = 37 * hashVal + ch; // Computes value we will be using for the hash function
    }
    
    if (tableSize == currentSize)
        return hashVal % currentSize; // Hash function 1
    else
        return (hashVal % tableSize) + 1; // Hash function 2
}

int Dictionary::findIndex(const std::string* key, const HashEntry* entry, int index, HashEntry* array) const
{
    //cout << "Index " << index << " is currently occupied by " << *array[index].data << ". Doing secondaring hash function..." << endl;
    while (array[index].flag) // Finds next available index
    {
        //int test = hash(*key, doubleHashprimes[rehashCounter]); // DELETE THIS
        //cout << "BEFORE COMPUTATION: " << index  << " KEY: " << *key << " DOING HASH OF " << doubleHashprimes[rehashCounter] <<endl;
        //cout << "DOING " << index << " + " << test << endl;
        index += hash(*key, doubleHashprimes[rehashCounter]); // IF DEBUG: index += test;
        //cout << "Moved to index: " << index << "." << endl;
        if (index > currentSize) // If the index is out of range, it will mod it by current size
        {
            //cout << index << " is out of range. Computing new index position..." << endl;
            index = index % currentSize;
            //cout << "Is it empty? " << array[index].flag << endl;
            //if (array[index].flag)
                //cout << "Not empty. Occupied by: " << *array[index].data << endl;
        }
        
    }

    return index;
}

bool Dictionary::checkIndex(std::string* key, const HashEntry* entry, int index, HashEntry* array)
{
    cout << "Is this index currently filled? " << array[index].flag << endl;

    if (!array[index].flag) // if index isn't taken
    {
        cout << "Index is free! Adding " << *key << " to index " << index << endl;
        array[index].data = key;
        array[index].flag = true;
        return true;
    }
    return false;
}