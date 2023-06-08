#include <iostream>
#include <string>
#include<fstream>
#include <vector> // Used for sorting
#include <algorithm> // Used for sorting
#include <sstream> // Used to read word by word
using namespace std;

class HashTable
{
private:
    struct HashEntry
    {
        std::string* data;
        bool flag = false; // If filled, returns true. If empty, returns false.

        HashEntry(std::string* theData = nullptr, bool f = false) : data(theData), flag(f) {}
        
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
    int numEntries;

public:
    //TESTING FUNCTIONS. SHOULD BE DELETED
    void printSize(ostream& outputStream);
    
    // PUBLIC METHODS GO HERE LIKE ADD ENTRY, IS EMPTY, PRINT DICTIONARY, ETC>
    HashTable() // Default Constructor
    {
        hashArray = new HashEntry[currentSize]{nullptr};
        numEntries = 0;
    };

    void addEntry(string* key); // BASICALLY ADD ENTRY
    bool isEmpty() const; // IS EMPTY
    bool findEntry(const string& key) const;
private:
    //FUNCTIONS THAT WILL GO LIVE
    unsigned int hash( const string &key, int tableSize) const;
    void rehash(); // Determines if we hash or rehash
    void insert(string* key, HashEntry*& entry, HashEntry* array, bool doRehash);
    bool checkIndex(string* key, HashEntry*& entry, int index, HashEntry* array);
    int findIndex(string* key, HashEntry*& entry, int index, HashEntry* array);
    void sort(HashEntry* array);

};

string makeLowerCase(string& s);

int main()
{
    HashTable test;
    ifstream infile("smalldict.txt");
    ofstream outfile("outfile.txt");
    if (infile.fail())
    {
        cerr << "Could not open for input" << endl;
       exit(1);
    }

    string curWord = "";
    string curLine; // Keeps track of the line and words respectively
    istringstream iss; // Used to keep track of words

    getline(infile, curLine); // Gets the current line and assigns it to string line
    while (!infile.eof())
    {
        iss.clear(); // Clears out the iss
        iss.str(curLine); // Copies the current line to read from

        while (iss >> curWord) // Iterates through each word in the line
        {
            string word; // Keeps track of our edited word
            for (char c: curWord) // Iterate through each word in the text file
            {
                if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) // only include characters which are >= 'a' && <='z' and every other character would be considered a separator
                {
                    word += c; // Adds the character to the word string
                }
            }
            //cout << word << endl;
            test.addEntry(new string((word)));
        }
        getline(infile, curLine); // Iterates to the next line
    }

    //cout << "Added all of the words. Now printing the hash table..." << endl;
    test.printSize(outfile);
}
string makeLowerCase(string& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

// PRIVATE METHODS
void HashTable::printSize(ostream& outputStream)
{
    //cout << "Current table size is: " << currentSize << endl;

    //cout << "50 percent of our table size is: " << (currentSize/2) << endl;

    //cout << "numEntries is: " << numEntries << endl;

    int sum = 0;
    for (int i = 0; i < currentSize; i++)
    {
        if (hashArray[i].flag)
        {
            outputStream << i << ": " << *hashArray[i].data << endl;
            sum++;
        }
        else
            outputStream << i << ": " << endl;
    }
    //cout << "We have a total of: " << sum << " element(s) in the table." << endl;
}

void HashTable::addEntry(string* anEntry)
{
    //cout << "\nWe are adding -" << *anEntry << "- to the table!" << endl;
    rehash(); // Calls rehash. Checks if we need to rehash and if so, we will rehash.

    //cout << "Now calling the insert method!" << endl;
    insert(anEntry, entry, hashArray, false);
}

void HashTable::rehash()
{
    if (!isEmpty())
    {
        //cout << "Num entries is currently " << numEntries <<" . Do we need to rehash? " << (numEntries >= (currentSize / 2)) << endl;
        if (numEntries >= (currentSize / 2)) // If at least 50% full, rehash table
        {
            //cout <<"\n\nDoing Rehash\n\n" << endl;
            //cout << "Currently this is our table: " << endl;
            //printSize();

            // Create a new array at the new size
            int oldSize = currentSize; // Size of the old table
            rehashCounter++; // Used to iterate to the next index in our array
            currentSize = singleHashPrimes[rehashCounter];
            //cout << "\n\nAccessing " << currentSize << endl;
            HashEntry* temp = new HashEntry[currentSize];
            
            //cout << "Doing rehash" << endl;
            // Goes through the old array and insert each item into the new array
            for (int i = 0; i < oldSize; i++) 
            {
                if (hashArray[i].flag) // If there's a value at the index, we will insert it into the new table
                {
                    //cout << "\nAt index " << i << " : value is " << *hashArray[i].data << endl;
                    insert(hashArray[i].data, entry, temp, true); // Inserts the value at the index
                }
            }

            delete [] hashArray; // Deletes the old array

            // Set variables to use the new array
            hashArray = temp;

            //cout << "Hash Table's new size is: " << currentSize << endl;
            
        }
    }
}

void HashTable::insert(string* key, HashEntry*& entry, HashEntry* array, bool doRehash)
{
    //cout << "CURRENT SIZE IS: " << currentSize << endl;
    int index = hash(*key, currentSize); // Gets the index we will be looking at
    //cout << "Our computed index is: " << index << endl;

    while (!checkIndex(key, entry, index, array)) // if index is not taken, we will insert the value to that index.
    {
        index = findIndex(key, entry, index, array);
    }
    if (!doRehash) 
        numEntries++;// increases the number of entries
}

unsigned int HashTable::hash( const string &key, int tableSize) const
{
    unsigned int hashVal = 0;
    for (char ch : key) // Iterates through each character in the string key
    {
        //cout << "HashVal before computation for char " << ch << ": " << hashVal << endl;
        hashVal = 37 * hashVal + ch; // Computes value we will be using for the hash function
        //cout << "HashVal after computation for char " << ch << ": " << hashVal << "\n" << endl;
    }
    
    if (tableSize == currentSize)
        return hashVal % currentSize; // Hash function 1
    else
        return (hashVal % tableSize) + 1; // Hash function 2
}

bool HashTable::checkIndex(string* key, HashEntry*& entry, int index, HashEntry* array)
{
    //cout << "Is this index currently filled? " << array[index].flag << endl;

    if (!array[index].flag) // if index isn't taken
    {
        //cout << "Index is free! Adding " << *key << " to index " << index << endl;
        array[index].data = key;
        array[index].flag = true;
        return true;
    }
    return false;
}

bool HashTable::isEmpty() const
{
    return (numEntries == 0);
}

bool HashTable::findEntry(const string& key) const
{
    int index = hash(key, currentSize); // Gets the initial index of the key

    //cout << "Index is : " << index << endl;
    //cout << "Value at this index is: " << *hashArray[index].data << endl; // THIS WILL BE A CORE DUMP IF THIS IS INDEX IS EMPTY.
    while (true) // We want to keep looping until we return a boolean. This will break when we return a bool.
    {
        if (!hashArray[index].flag) // No element at this position which means this key cannot be here.
        {
            //cout << "Empty bucket. Key is not in this table" << endl;
            return false;
        }
        else
        {
            //cout << "Is " << key << " = " << *hashArray[index].data << " ? " << (key == *hashArray[index].data) << endl;
            if (key == *hashArray[index].data)
            {
                return true;
            }
        }
    }
}

int HashTable::findIndex(string* key, HashEntry*& entry, int index, HashEntry* array)
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

void HashTable::sort(HashEntry* array)
{
    
}

/*
califf should be at index 34
elaine should be at index 81
mary should be at index 87
hrabak should be at index 1
hartman should be at index 42
zant should be at index 4
chrisman should be at index 45
goodwin should be at index 38
illinois should be at index 51
a should be at index 97
accent should be at index 100
an should be at index 63
as should be at index 68
away should be at index 66
believe should be at index 32
brain should be at index 89
but should be at index 35
cannot should be at index 58
child should be at index 22
clouds should be at index 48
come should be at index 45
decided should be at index 63
doubt should be at index 2
doubtful should be at index 52
eager should be at index 18
encouraging should be at index 21
encouragingly should be at index 47
expect should be at index 2
fact should be at index 72
first should be at index 60
from should be at index 47
girl should be at index 8
gravely should be at index 68
he should be at index 10
hers should be at index 45
him should be at index 21
his should be at index 27
i should be at index 4
imaginative should be at index 42
impulse should be at index 54
is should be at index 61
it should be at index 62
know should be at index 93
lady should be at index 22
merely should be at index 11
must should be at index 27
next should be at index 75
not should be at index 81
of should be at index 68
over should be at index 71
overly should be at index 13
own  should be at index 75
reprimand should be at index 92
roll should be at index 88
rolled should be at index 79
said should be at index 45
sane  should be at index 95
sanity should be at index 100
she should be at index 87
shot should be at index 69
speaking should be at index 97
that should be at index 7
the should be at index 42
then should be at index 48
to should be at index 60
truth should be at index 84
us should be at index 0
was should be at index 66
with should be at index 1
you should be at index 92
*/