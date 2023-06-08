//Fernando Payan IT279
//Implementation file for double array list

// Inheriting from the header class
#include "DoubleList.h"

// Default Constructor
DoubleList::DoubleList() {
    numDoubles = 0;
    capacity = 10;
    theArray = new double[capacity];
};

// Copy Constructor
DoubleList::DoubleList(const DoubleList& rhs) {
    makeDeepCopy(rhs); 
};

//Assignment Constructor
DoubleList &DoubleList:: operator=(const DoubleList& rhs) {
    if (this != &rhs)
    {
        deleteArray(); 
        makeDeepCopy(rhs); 
    }
    return *this;
};

// addDouble method
void DoubleList::addDouble(double toAdd) {
    if (numDoubles == capacity)
    {
        updateArray();
    }
    theArray[numDoubles] = toAdd;
    numDoubles++;
};

//Removes the last double from the list.
void DoubleList::removeDouble() {
    numDoubles = numDoubles - 1;
}

//Retrieves the double at the specified index.
double DoubleList::getDouble(int index) const {
    return theArray[index];
}

//Returns the number of doubles in the List.
int DoubleList::getNumDoubles() const {
    return numDoubles;
}

//Destructor, to clean up dynamic memory.
DoubleList::~DoubleList() {
    deleteArray();
}

void DoubleList::updateArray() { // If max capacity size has been reached, we allocate space by creating a new array with +10 of the capacity size.
    capacity = capacity + 10;
    double* temp = new double[capacity];
    for (int i = 0; i < numDoubles; i++)
    {
        temp[i] = theArray[i];
        
    }
    delete [] theArray;
    theArray = temp;
 }

 void DoubleList::makeDeepCopy(const DoubleList& rhs) { // This method makes a deep copy of the array which updates this object's variables with rhs's variabsles. 
    double* freshArray = new double[rhs.capacity];
    for (int i = 0; i < rhs.numDoubles; i++)
    {
        freshArray[i] = rhs.theArray[i];
    }
    theArray = freshArray;
    numDoubles=rhs.numDoubles;
    capacity = rhs.capacity;
 }

 void DoubleList::deleteArray() // Deletes theArray. Also called in the destructor.
 {
    delete [] theArray;
 }