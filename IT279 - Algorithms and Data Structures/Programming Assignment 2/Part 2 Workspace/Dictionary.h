// An dictionary created using a hash table
// By Mary Elaine Califf and Fernando Payan
#include <string>

#ifndef DICTIONARY_H 
#define DICTIONARY_H  

class Dictionary
{
private:
    struct HashEntry
    {
        std::string* data; // Contains the string data
        bool flag; // Used to indicate whether the position is filled or empty

        HashEntry(std::string* theData = nullptr, bool f = false) : data(theData), flag(f) {} // Constructor
        
    };

        const int singleHashPrimes[14] = // An array that keeps track of the single hash prime sizes
    {
        101, 211, 431, 863, 1733, 3469, 6947,
        13901, 27803, 55609, 111227, 222461, 444929, 889871
    };

    const int doubleHashprimes[14] = // An array that keeps track of the double hash prime sizes
    {
        97, 199, 421, 859, 1723, 3467, 6917,
        13883, 27799, 55603, 111217, 222436, 444901, 889829
    };

    HashEntry* entry; // Entry objects that will be stored in the array
    HashEntry* hashArray; // Hash Table Array
    int rehashCounter = 0; // Used to keep track of the next size we will set our hash table to
    int currentSize = singleHashPrimes[rehashCounter]; // Stores the current size of the array
    int numEntries; // Keeps track of how many entries are in the hash table

public:
    // Constructor
    Dictionary();

    // Copy constructor
    Dictionary(const Dictionary& orig);

    // Destructor
    ~Dictionary() { clear(); }

    // Assignment operator
    Dictionary& operator=(const Dictionary& rhs);

    // Check to see if the Dictionary isEmpty
    bool isEmpty() const { return (numEntries == 0); }

    // Add an entry
    // Precondition: the dictionary must not have the identical string already stored in the dictionary
    // Postcondition: the string has been added to the dictionary
    void addEntry(std::string* anEntry);

    // Determine whether the string is in the dictionary
    // Returns true if the string is stored in the dictionary and false otherwise
    bool findEntry(const std::string& key) const;

    // Print entries in order
    void printDictionaryInOrder(std::ostream& outputStream) const;

    // Prints the dictionary keys only, demonstrating the dictionary structure
    void printDictionaryKeys(std::ostream& outputStream) const;

private:
    // Clears the hash table and deletes the array
    void clear();

    // Copies hash table
    void copy(const Dictionary& orig);

    // Inserts the value to the hash table
    void insert(std::string* key, HashEntry* curPtr, HashEntry* array, bool doRehash);

    // My Private Methods

    // Hashing method that will either do the first or second hash function based on the passed table size
    unsigned int hash( const std::string& key, int tableSize) const; // Add const to end?

    // Rehashing method that will increase the hash table's size to the next array if necessary
    void rehash();

    // Finds the next available index
    int findIndex(const std::string* key, const HashEntry* entry, int index, HashEntry* array) const;

    // Checks if the index is available. Returns true if empty - false if filled
    bool checkIndex(std::string* key, const HashEntry* entry, int index, HashEntry* array);

};

#endif