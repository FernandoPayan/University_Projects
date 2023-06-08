#include <iostream>
#include <fstream> // Allows to write to file
using namespace std;

int main() {
    int customerNumber = 1;
    int currentMinuteCounter = 10;
    int cashRegisterNumber = 2;
    ofstream file1;
    ofstream file2;
    file1.open("single.txt");
    file2.open("multiple.txt");
    // Service Completed
    file1 << "Customer " << customerNumber << " departed at " << currentMinuteCounter << "\n";
    file2 << "Customer " << customerNumber << " departed at " << currentMinuteCounter << "\n";

    // Customer Served
    file1 << "Customer " << customerNumber << " served by " << cashRegisterNumber << " starting at " << currentMinuteCounter << "\n";
    file2 << "Customer " << customerNumber << " served by " << cashRegisterNumber << " starting at " << currentMinuteCounter << "\n";

    // Customer Arrives
    file1 << "Customer " << customerNumber << " served by " << cashRegisterNumber << " starting at " << currentMinuteCounter << "\n";
    file2 << "Customer " << customerNumber << " served by " << cashRegisterNumber << " starting at " << currentMinuteCounter << "\n";
    
    file1.close();
    file1.close();

}