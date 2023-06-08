/* Simulation file for Queue implementation
Author: Fernando Payan 
Class: IT 279
*/
#include <iostream>
#include <fstream> // Allows to write to file
#include "Queue.cpp"
using namespace std;

struct Register
{
    // Variables
private: // check if this is ok?
    CustomerData customer;
    int regNum;
    int departTime;
    bool isFree = true;

public:
    Register() {}; // Default Constructor

    bool isOpen()
    {
        return isFree;
    }

    void doService(CustomerData cust, int registerNum, int updatedArrivalTime, ofstream &txtfile) // Register is working with a customer
    {
        customer = cust;
        regNum = registerNum;
        departTime = updatedArrivalTime + customer.serviceTime;
        isFree = false;
        txtfile << "Customer " << customer.customerNumber << " served by " << regNum << " starting at " << updatedArrivalTime << "\n";
    }

    bool doCheckout(int counter, ofstream &txtfile) // Register checks out Customer
    {
        if (departTime == counter)
        {
            
            txtfile << "Customer " << customer.customerNumber << " departed at " << departTime << "\n";
            return isFree = true;
        } else
            return false;
    }

};


void getRandomSeed(int randomSeed);
void assignCustomerToRegister(CustomerData customer, Queue &reg1, Queue &reg2, Queue &reg3);

int main(int argc, char **argv)
{
    if (argc < 3) // Ensures the proper number of arguments was passed
    {
        cout << "Usage: " << argv[0] << " <maximum time between Customers> <maximum service time per customer> <random seed>" << endl;
        exit(1);
    }
    int maxArrivalInterval = atoi(argv[1]);
    int maxServTime = atoi(argv[2]);
    int randomSeed= atoi(argv[3]);
    getRandomSeed(randomSeed);

    // Allows us to write to the files
    ofstream singleFile; singleFile.open("singlefile.txt");
    ofstream multipleFile; multipleFile.open("singlefile.txt");
    
    
    // Queues
    Queue single_Queue;
    Queue multiple_Queue1;
    Queue multiple_Queue2;
    Queue multiple_Queue3;

    // Registers
    Register reg1;
    Register reg2;
    Register reg3;


    // Generate the arrival time of the first customer
    int arrivalTime = (rand() % maxArrivalInterval + 1); // Customer arrive in random integer intervals of 1 to maxArrivalInterval

    // Customer Variables
    float customerNumber = 1;
    int custArrival = arrivalTime;
    
    // Values that will be printed at the end
    float averageWaitTime = 0;
    int maxWaitTime = 0;
    int maxLineLength = 0;

    //For loop that starts at that arrival time and ends at 720 (not before 720, but at 720)
    for (int i = arrivalTime; i <= 720; i++) // i will be used to check if serviceTime ends
    {
        // Adds wait time if someone is waiting in the queue
        if (!single_Queue.isEmpty())
        {
            averageWaitTime++;
        }


        // If service has completed at any cash register
        if (reg1.doCheckout(i, singleFile))
        {
            //cout << "DOING REG 1 CHECKOUT" << endl;
            // Write a line to a output file with the message:
                //singleFile << "Customer " << customer.customerNumber << " departed at " << (i + customer.serviceTime) << "\n"; DO THIS IN DOCHECKOUT METHOD.
                
    
            // If the queue has any customers, it will remove that customer from the queue and begin service for that customer
            if (!single_Queue.isEmpty())
            {
                reg1.doService(single_Queue.dequeue(), 1, i, singleFile);
            }

                // You will need to do any wait time computations
                // wait time does NOT include service time

                // You will also write the following message to the appropriate output file
                    // "Customer " << customerNumber << " served by " << cashRegisterNumber << " starting at " << currentMinuteCounter
                    //assignCustomerToRegister(customer, register1, register2, register3);
        } if (reg2.doCheckout(i, singleFile)) 
        {
            //cout << "DOING REG 2 CHECKOUT" << endl;
            // same as above

            // If the queue has any customers, it will remove that customer from the queue and begin service for that customer
            if (!single_Queue.isEmpty())
            {
                reg2.doService(single_Queue.dequeue(), 2, i, singleFile);
            }
        } if (reg3.doCheckout(i, singleFile))
        {
            //cout << "DOING REG 3 CHECKOUT" << endl;
            // same as above

            // If the queue has any customers, it will remove that customer from the queue and begin service for that customer
            if (!single_Queue.isEmpty())
            {
                reg3.doService(single_Queue.dequeue(), 3, i, singleFile);
            }
        }

        // If a customer has arrived
        if (custArrival == i)
        {
            // Creates a customer
            CustomerData customer(customerNumber, custArrival, rand() % maxServTime + 1); // Generates the customer's service time.
            customerNumber++;

            // Generate the customer's service time. THIS IS ALREADY DONE. LOOK ABOVE
            // Generate the next customer's arrival time
            custArrival = arrivalTime += (rand() % maxArrivalInterval + 1);
        
            // For each simulation:
                // Write a line to each of the output files with this message:
                     singleFile << "Customer " << customer.customerNumber << " arrived at " << customer.arrivalTime << "\n"; // For Single File
                     // multipleFile << "Customer " << customer.customerNumber << " arrived at " << customer.arrivalTime << "\n"; // For Single File

                // If there is a cash register that is not currently serving a customer
                if (reg1.isOpen())
                {
                    // Cash register will begin serving this customer
                    reg1.doService(customer, 1, i, singleFile);

                    //multiple_Queue1.enqueue(customer);
                        // Consider this as a 0 in your average wait time
                        // Print the service message to appropriate output file
                            // "Customer " << customerNumber << " served by " << cashRegisterNumber << " starting at " << currentMinuteCounter
                } else if (reg2.isOpen())
                {
                    // Cash register will begin serving this customer
                    reg2.doService(customer, 2, i, singleFile);

                    //multiple_Queue2.enqueue(customer);
                        // Consider this as a 0 in your average wait time
                        // Print the service message to appropriate output file
                            // "Customer " << customerNumber << " served by " << cashRegisterNumber << " starting at " << currentMinuteCounter
                } else if (reg3.isOpen())
                {
                    // Cash register will begin serving this customer
                    reg3.doService(customer, 3, i, singleFile);

                    //multiple_Queue3.enqueue(customer);
                        // Consider this as a 0 in your average wait time
                        // Print the service message to appropriate output file
                            // "Customer " << customerNumber << " served by " << cashRegisterNumber << " starting at " << currentMinuteCounter
                } else // Else add the customer to a queue
                {
                    // Single Queue
                    single_Queue.enqueue(customer);
                    averageWaitTime++;
                    // For multiple queue scenario, the customer will join the shortest queue (compare sizes and do min size)
                    //assignCustomerToRegister(customer, multiple_Queue1, multiple_Queue2, multiple_Queue3);

                    // In case of ties, you will prefer the first to the second to the third. THIS IS DONE IS ASSIGNCUSTOMERTOREGISTER FOR MULTI QUEUE.
    
                    // When a customer has been added, update the maximum line length if appropriate
                    // if (queue.getSize() > maxLineLength): maxLineLength = queue.getSize() {};
                }
        }
    }  // End of Simulation

    //Print out a blank line and then the following summary to each file:
    cout << averageWaitTime << " | " << customerNumber << endl;
    cout << "Average wait time: " << (averageWaitTime / customerNumber) << endl;
    // "Maximum wait time: " << maxWaitTime
        // Wait time does NOT include service time
    // "Maximum line length: " << maxLineLength
        // For multiple line case, maxLineLength includes customers in all of the queues.
            //This means that customers currently being served are NOT in line and should NOT be in any queue.


}

void getRandomSeed(int randomSeed) // This gets the random seed
{
    if (randomSeed != 0) 
    {
        //Random seed is used with srand() to initialize the random number sequence to match a sample run
        srand(randomSeed);
    } else
    {
        // If random seed is 0, it will use the current time to initialize the random number sequence with srand().
        srand(time(nullptr));
    }
}

void assignCustomerToRegister(CustomerData customer, Queue &multiple_Queue1, Queue &multiple_Queue2, Queue &multiple_Queue3, ofstream &txtfile) // Assigns a customer to a register depending on the size
{
    // Sets the ID of each Queue
    int q1 = 1; int q2 = 2; int q3 = 3;

    if ((multiple_Queue1.isEmpty() || multiple_Queue1.getSize() < multiple_Queue2.getSize()))
    {
        multiple_Queue1.enqueue(customer); // Adds the customer to reg1's queue
        txtfile << "Customer " << customer.customerNumber << " served by " << q1 << " starting at " << customer.arrivalTime << "\n"; // Prints message of customer being served
    } else if (multiple_Queue2.getSize() == 0 || multiple_Queue2.getSize() < multiple_Queue3.getSize())
    {
        multiple_Queue2.enqueue(customer); // Adds the customer to reg2's queue
        txtfile << "Customer " << customer.customerNumber << " served by " << q2 << " starting at " << customer.arrivalTime << "\n"; // Prints message of customer being served
    } else
    {
        multiple_Queue3.enqueue(customer); // Adds the customer to reg2's queue
        txtfile << "Customer " << customer.customerNumber << " served by " << q3 << " starting at " << customer.arrivalTime << "\n"; // Prints message of customer being served
    }
}