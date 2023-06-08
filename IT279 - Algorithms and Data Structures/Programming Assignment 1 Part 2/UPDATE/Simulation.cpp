/* Simulation file for Queue implementation
Author: Fernando Payan
Class: IT 279
*/
#include "Register.h"
#include "Queue.h"

// Multiple Queue's Max Line Value declared here so it can be called in assignCustomerToRegister method
int multi_MaxLineLength = 0;

// Methods defined in the file
void getRandomSeed(int randomSeed);
void assignCustomerToRegister(CustomerData customer, Queue &multiple_Queue1, Queue &multiple_Queue2, Queue &multiple_Queue3, ofstream &txtfile);
void computeTime(Queue &theQueue, double &averageWaitTime, int &maxWaitTime, int index);
bool checkRegisters(Register &reg1, Register &reg2, Register &reg3, CustomerData customer, int index, ofstream &txtfile);
void checkService(Register &theRegister, Queue &theQueue, double &averageWait, int &maxWait, int index, int registerNum, ofstream &txtfile);

int main(int argc, char **argv)
{
    if (argc < 3) // Ensures the proper number of arguments was passed
    {
        cout << "Usage: " << argv[0] << " <maximum time between Customers> <maximum service time per customer> <random seed>" << endl;
        exit(1);
    }
    int maxArrivalInterval = atoi(argv[1]);
    int maxServTime = atoi(argv[2]);
    int randomSeed = atoi(argv[3]);
    getRandomSeed(randomSeed);

    // Allows us to write to the files
    ofstream singleFile;
    singleFile.open("singleline.txt");
    ofstream multipleFile;
    multipleFile.open("multiplelines.txt");

    // Queues
    Queue single_Queue;
    Queue multiple_Queue1;
    Queue multiple_Queue2;
    Queue multiple_Queue3;

    // Registers for Single Queue Simulation
    Register single_Reg1;
    Register single_Reg2;
    Register single_Reg3;

    // Registers for Multi Queue Simulation
    Register multi_Reg1;
    Register multi_Reg2;
    Register multi_Reg3;

    // Universal variables that will be used in both simulations
    int arrivalTime = (rand() % maxArrivalInterval + 1); // Generate the arrival time of the first customer

    // Customer Variables
    int customerNumber = 1;
    int custArrival = arrivalTime;

    // Single Queue values that will be printed at the end
    double single_AverageWaitTime = 0;
    int single_MaxWaitTime = 0;
    int single_MaxLineLength = 0;

    // Multi Queue values that will be printed at the end
    double multi_AverageWaitTime = 0;
    int multi_MaxWaitTime = 0;

    // For loop that starts at that arrival time and ends at 720
    for (int i = arrivalTime; i <= 720; i++) // i will be used to check if serviceTime ends
    {
        // SIMULATION 1: If service has completed at any cash register
        checkService(single_Reg1, single_Queue, single_AverageWaitTime, single_MaxWaitTime, i, 1, singleFile);
        checkService(single_Reg2, single_Queue, single_AverageWaitTime, single_MaxWaitTime, i, 2, singleFile);
        checkService(single_Reg3, single_Queue, single_AverageWaitTime, single_MaxWaitTime, i, 3, singleFile);

        // SIMULATION 2: If service has completed at any cash register
        checkService(multi_Reg1, multiple_Queue1, multi_AverageWaitTime, multi_MaxWaitTime, i, 1, multipleFile);
        checkService(multi_Reg2, multiple_Queue2, multi_AverageWaitTime, multi_MaxWaitTime, i, 2, multipleFile);
        checkService(multi_Reg3, multiple_Queue3, multi_AverageWaitTime, multi_MaxWaitTime, i, 3, multipleFile);

        // If a customer has arrived
        if (custArrival == i)
        {
            // Creates a customer
            CustomerData customer(customerNumber, custArrival, rand() % maxServTime + 1); // Generates the customer's service time.
            customerNumber++;

            // Generate the next customer's arrival time
            custArrival = arrivalTime += (rand() % maxArrivalInterval + 1);

            singleFile << "Customer " << customer.customerNumber << " arrived at " << customer.arrivalTime << "\n";   // For Single File
            multipleFile << "Customer " << customer.customerNumber << " arrived at " << customer.arrivalTime << "\n"; // For Multiple File

            // SIMULATION 1: If there is a cash register that is not currently serving a customer
            if (!checkRegisters(single_Reg1, single_Reg2, single_Reg3, customer, i, singleFile))
            {
                // Single Queue
                single_Queue.enqueue(customer);

                if (single_MaxLineLength < single_Queue.getSize())
                {
                    single_MaxLineLength = single_Queue.getSize();
                }
            }

            // SIMULATION 2: If there is a cash register that is not currently serving a customer
            if(!checkRegisters(multi_Reg1, multi_Reg2, multi_Reg3, customer, i, multipleFile))
            {
                // Multi Queue
                assignCustomerToRegister(customer, multiple_Queue1, multiple_Queue2, multiple_Queue3, multipleFile); // The customer will join the shortest queue (compare sizes and do min size)
            }
        }
    } // End of Simulation

    // Single Queue Results
    singleFile << "\nAverage wait time: " << fixed << setprecision(1) << (single_AverageWaitTime / (customerNumber - 1));
    singleFile << "\nMaximum wait time: " << single_MaxWaitTime;
    singleFile << "\nMaximum line length: " << single_MaxLineLength << "\n";

    // Multi Queue Results
    multipleFile << "\nAverage wait time: " << fixed << setprecision(1) << (multi_AverageWaitTime / (customerNumber - 1));
    multipleFile << "\nMaximum wait time: " << multi_MaxWaitTime;
    multipleFile << "\nMaximum line length: " << multi_MaxLineLength << "\n";
}

void getRandomSeed(int randomSeed) // This gets the random seed
{
    if (randomSeed != 0)
    {
        // Random seed is used with srand() to initialize the random number sequence to match a sample run
        srand(randomSeed);
    }
    else
    {
        // If random seed is 0, it will use the current time to initialize the random number sequence with srand().
        srand(time(nullptr));
    }
}

void assignCustomerToRegister(CustomerData customer, Queue &multiple_Queue1, Queue &multiple_Queue2, Queue &multiple_Queue3, ofstream &txtfile) // Assigns a customer to a register depending on the size
{
    if (multiple_Queue1.isEmpty() || (multiple_Queue1.getSize() <= multiple_Queue2.getSize() && multiple_Queue1.getSize() <= multiple_Queue3.getSize()))
    {
        multiple_Queue1.enqueue(customer);
    }
    else if (multiple_Queue2.isEmpty() || (multiple_Queue2.getSize() <= multiple_Queue3.getSize() && multiple_Queue2.getSize() < multiple_Queue1.getSize()))
    {
        multiple_Queue2.enqueue(customer);
    }
    else
    {
        multiple_Queue3.enqueue(customer);
    }

    if (multi_MaxLineLength < (multiple_Queue1.getSize() + multiple_Queue2.getSize() + multiple_Queue3.getSize()))
    {
        multi_MaxLineLength = multiple_Queue1.getSize() + multiple_Queue2.getSize() + multiple_Queue3.getSize();
    }
}

void computeTime(Queue &theQueue, double &averageWaitTime, int &maxWaitTime, int index) // Computes the average wait time and the max wait time
{
    int waitTime = (index - theQueue.front().arrivalTime);
    averageWaitTime += waitTime; // Adds to the wait time

    if (maxWaitTime < waitTime) // Gets the max wait time
    {
        maxWaitTime = waitTime;
    }
}

bool checkRegisters(Register &reg1, Register &reg2, Register &reg3, CustomerData customer, int index, ofstream &txtfile) // Checks the availability of registers in the Single Queue Simulation
{
    if (reg1.isOpen())
    {
        // Cash register will begin serving this customer
        reg1.doService(customer, 1, index, txtfile);
        return true;
    }
    else if (reg2.isOpen())
    {
        // Cash register will begin serving this customer
        reg2.doService(customer, 2, index, txtfile);
        return true;
    }
    else if (reg3.isOpen())
    {
        // Cash register will begin serving this customer
        reg3.doService(customer, 3, index, txtfile);
        return true;
    }

    return false; // Registers are not available
}

void checkService(Register &theRegister, Queue &theQueue, double &averageWait, int &maxWait, int index, int registerNum, ofstream &txtfile) // Checks if service has completed at the cash register
{
    if (theRegister.doCheckout(index, txtfile))
    {
        // If the queue has any customers, it will remove that customer from the queue and begin service for that customer
        if (!theQueue.isEmpty())
        {
            computeTime(theQueue, averageWait, maxWait, index);

            theRegister.doService(theQueue.dequeue(), registerNum, index, txtfile); // Dequeues customer from queue and sends to register
        }
    } 
}