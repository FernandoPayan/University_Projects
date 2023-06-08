/* Implementation file for the Register class
// Fernando Payan
// IT 279
*/
#include "Register.h"

    Register::Register(){} // Default Constructor

bool Register::isOpen()
    {
        return isFree;
    }

void Register::doService(CustomerData cust, int registerNum, int updatedArrivalTime, ofstream &txtfile) // Register is working with a customer
    {
        customer = cust;
        regNum = registerNum;
        departTime = updatedArrivalTime + customer.serviceTime;
        isFree = false;
        txtfile << "Customer " << customer.customerNumber << " served by " << regNum << " starting at " << updatedArrivalTime << "\n";
    }

bool Register::doCheckout(int counter, ofstream &txtfile) // Register checks out Customer
    {
        if (departTime == counter)
        {
            
            txtfile << "Customer " << customer.customerNumber << " departed at " << departTime << "\n";
            return isFree = true;
        } else
            return false;
    }