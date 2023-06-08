#include <iostream>
#include "DisjointSet.h"
using namespace std;

int main(int argc, char **argv)
{
    DisjointSet mySet(10);
    
    for (int i = 0; i < 10; i++)
    {
        int a;
        int b;
        cout << i << ": Enter values: ";
        cin >> a >> b;
        mySet.doUnion(a, b);
        mySet.printArrayValues(cout);
        cout << "\n";
    }
    
}