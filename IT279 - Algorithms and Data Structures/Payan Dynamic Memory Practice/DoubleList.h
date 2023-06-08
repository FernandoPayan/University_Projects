//Fernando Payan IT279
//Header file for double array list
#include <iostream>
using namespace std;

// DoubleList class
class DoubleList {
private:
    double* theArray;
    int numDoubles;
    int capacity;
public:
    //Standard constructor for an empty List
    DoubleList();

    //Copy constructor for the List class
    DoubleList(const DoubleList& rhs);

    //Assignment operator, which will replace the contents of this object, with rhs's contents.
    DoubleList& operator=(const DoubleList& rhs);

    //Adds the given double to the end of the List, and expand if needed.
    void addDouble(double toAdd);

    //Removes the last double from the list.
    void removeDouble();

    //Retrieves the double at the specified index.
    double getDouble(int index) const;

    //Returns the number of doubles in the List.
    int getNumDoubles() const;

    //Destructor, to clean up dynamic memory.
    ~DoubleList();

private:
    // add private methods here
    // Method to do the copying
    // Method to do the other stuff
    void updateArray();
    void makeDeepCopy(const DoubleList& rhs);
    void deleteArray();
};