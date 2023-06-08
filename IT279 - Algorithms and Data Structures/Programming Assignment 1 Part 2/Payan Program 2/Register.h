/* Header file for the Register class
// Fernando Payan
// IT 279
*/
#ifndef REGISTER_H
#define REGISTER_H
#include "CustomerData.h"
#include <fstream> // Allows to write to file
#include <iomanip> // Does the rounding process
#include <iostream>
using namespace std;

class Register
{
    // Variables
    private:
        CustomerData customer;
        int regNum;
        int departTime;
        bool isFree = true;

    public:
        Register(); // Default Constructor

        bool isOpen(); // Checks if the register is free

        void doService(CustomerData cust, int registerNum, int updatedArrivalTime, ofstream &txtfile); // Register is working with a customer

        bool doCheckout(int counter, ofstream &txtfile); // Register checks out Customer
};

#endif