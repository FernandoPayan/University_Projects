#include "DoubleList.h"

int main(){
    DoubleList list1;

    //Add one item
    list1.addDouble(2.5);
    cout << "The double at index 0 is: " << list1.getDouble(0) << endl;
    cout << "The number of doubles in list1 is: " << list1.getNumDoubles() << endl;

    // Add Multiple Items & Increase Array by one size
    for (int i = 0; i < 9 ; i++)
    {
        list1.addDouble(i*2.5);
    }
    cout << "\nThe number of doubles is now: " << list1.getNumDoubles() << endl;

    // Remove all doubles
    while (list1.getNumDoubles() > 0)
    {
        list1.removeDouble();
    }
    cout << "The number of doubles in list1 is now: " << list1.getNumDoubles() << endl;

    //Increase Array Size by multiple sizes (2 times)
    for (int i = 0; i < 25; i++)
    {
        list1.addDouble(i);
    }

    // Copy Constructor
    DoubleList list2(list1); 
    cout << "\nThe number of doubles in list2 is: " << list2.getNumDoubles() << endl;

    //Remove one double
    list2.removeDouble();
    cout << "The number of doubles is now: " << list2.getNumDoubles() << endl;
    while (list2.getNumDoubles() > 0)
    {
        list2.removeDouble();
    }
    cout << "The number of doubles is now: " << list2.getNumDoubles() << endl;
};