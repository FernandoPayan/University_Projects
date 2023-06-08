// Intersection and union of sorted lists
// By Mary Elaine Califf and _______

#include <list>
#include <iostream>
using namespace std;

// Function prototypes

// Computes the union of list1 and list 2 and store it in result
// Result must be sorted in ascending order and have no duplicates
// Precondition: list1 and list2 each are sorted in ascending order with no duplicates
//               result is an empty list
// This must be done using NO list methods such add, sort, find, etc. These would lead to inefficient implementations
void doUnion(const list<int>& list1, const list<int>& list2, list<int>& result);

// Computes the intersection of list1 and list 2 and store it in result
// Result must be sorted in ascending order and have no duplicates
// Precondition: list1 and list2 each are sorted in ascending order with no duplicates
//               result is an empty list
// This must be done using NO list methods such add, sort, find, etc. These would lead to inefficient implementations
void doIntersection(const list<int>& list1, const list<int>& list2, list<int>& result);


// Prints a list of integers to the screen
void printList(const list<int>& theList);

int main()
{
    int arr1[] = { 2,4, 6, 8, 10, 12 };
    int arr2[] = { 1, 4, 6, 9, 10, 13 };
    int arr3[] = { 3, 6, 7, 8, 9 };
    int arr4[] = { 3, 7 };
    int arr5[] = { 2, 5, 12 };
    list<int> list1, list2, list3, list4, list5, res1, res2, res3, res4, res5, res6;

    for (int num : arr1)
    {
        list1.push_back(num);
    }
    for (int num : arr2)
    {
        list2.push_back(num);
    }
    for (int num : arr3)
    {
        list3.push_back(num);
    }
    for (int num : arr4)
    {
        list4.push_back(num);
    }
    for (int num : arr5)
    {
        list5.push_back(num);
    }

    cout << "Union of\n";
    printList(list1);
    cout << "and\n";
    printList(list2);
    cout << "Expected: 1 2 4 6 8 9 10 12 13" << endl;
    cout << "Actual:";
    doUnion(list1, list2, res3);
    printList(res3);
    cout << "\nUnion of\n";
    printList(list1);
    cout << "and\n";
    printList(list3);
    cout << "Expected: 2 3 4 6 7 8 9 10 12" << endl;
    cout << "Actual:";
    doUnion(list1, list3, res4);
    printList(res4);
    cout << "\nUnion of\n";
    printList(list1);
    cout << "and\n";
    printList(list5);
    cout << "Expected: 2 4 5 6 8 10 12" << endl;
    cout << "Actual:";
    doUnion(list1, list5, res6);
    printList(res6);

    cout << "\nIntersection of\n";
    printList(list1);
    cout << "and\n";
    printList(list2);
    cout << "Expected: 4 6 10" << endl;
    cout << "Actual:";
    doIntersection(list1, list2, res1);
    printList(res1);
    cout << "\nIntersection of\n";
    printList(list1);
    cout << "and\n";
    printList(list3);
    cout << "Expected: 6 8" << endl;
    cout << "Actual:";
    doIntersection(list1, list3, res2);
    printList(res2);
    cout << "\nIntersection of\n";
    printList(list1);
    cout << "and\n";
    printList(list4);
    cout << "Expected:" << endl;
    cout << "Actual:";
    doIntersection(list1, list4, res5);
    printList(res5);
}

void doUnion(const list<int>& list1, const list<int>& list2, list<int>& result)
{
    list<int>::const_iterator iter1;
    list<int>::const_iterator iter2;
    // your code here -- make sure to read the comment on the prototype before beginning work
    // Remember that you are expected to have an efficient solution: O(m+n), not O(m*n)
}

void doIntersection(const list<int>& list1, const list<int>& list2, list<int>& result)
{
    list<int>::const_iterator iter1;
    list<int>::const_iterator iter2;

    // your code here -- make sure to read the comment on the prototype before beginning work
    // Remember that you are expected to have an efficient solution: O(m+n), not O(m*n)    
    // Note that an efficient answer to this is very closely related to an efficient answer to doUnion
}



void printList(const list<int>& theList)
{
    list<int>::const_iterator iter;
    for (iter = theList.begin(); iter != theList.end(); iter++)
    {
        cout << " " << *iter;
    }
    cout << endl;

}
