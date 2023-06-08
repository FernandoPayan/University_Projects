// program to do a test of the disjoint set class
// By Mary Elaine Califf

#include "DisjointSet.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream outputFile("tester.txt");

    DisjointSet mySet(16);

    outputFile << "original array" << endl;
    mySet.printArrayValues(outputFile);
    outputFile << endl;

    mySet.doUnion(2, 3);
    mySet.doUnion(4, 5);
    mySet.doUnion(2, 5);

    outputFile << "after first 3 doUnions " << endl;
    mySet.printArrayValues(outputFile);
    outputFile << endl;

    mySet.doUnion(13, 15);
    mySet.doUnion(14, 0);
    mySet.doUnion(1, 7);
    mySet.doUnion(1, 0);
    mySet.doUnion(9, 15);

    outputFile << "after 9,15" << endl;
    mySet.printArrayValues(outputFile);
    outputFile << endl;

    mySet.doUnion(6, 11);
    mySet.doUnion(11, 13);

    outputFile << "after 11,13" << endl;
    mySet.printArrayValues(outputFile);
    outputFile << endl;

    outputFile << "0 set label: " << mySet.find(0) << endl;
    outputFile << "11 set label: " << mySet.find(11) << endl;
    outputFile << "5 set label: " << mySet.find(5) << endl;

    outputFile << "result of 14,2 "<<mySet.doUnion(14, 2)<<endl;
    outputFile << "result of 10,12 "<<mySet.doUnion(10, 12)<<endl;
    outputFile << "result of 8,12 "<<mySet.doUnion(8, 12)<<endl;

    outputFile << "after 8,12" << endl;
    mySet.printArrayValues(outputFile);
    outputFile << endl;

    outputFile << "result of 5,8 " << mySet.doUnion(5, 8) << endl;
    outputFile << "result of 15,0 " << mySet.doUnion(15, 0) << endl;

    outputFile << "\nFinal version" << endl;
    mySet.printArrayValues(outputFile);
}
