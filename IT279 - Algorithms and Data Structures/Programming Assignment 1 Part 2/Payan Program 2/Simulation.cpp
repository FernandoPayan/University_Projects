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
    ofstream multipleFile; multipleFile.open("multiplefile.txt");
    
    
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

    //Universal variables that will be used in both simulations
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

    //For loop that starts at that arrival time and ends at 720 
    for (int i = arrivalTime; i <= 720; i++) // i will be used to check if serviceTime ends
    {
        // SIMULATION 1: If service has completed at any cash register
        if (single_Reg1.doCheckout(i, singleFile))
        {
            // If the queue has any customers, it will remove that customer from the queue and begin service for that customer
            if (!single_Queue.isEmpty())
            {
                single_AverageWaitTime += (i - single_Queue.front().arrivalTime); // Adds to the wait time

                if (single_MaxWaitTime < (i - single_Queue.front().arrivalTime)) // Gets the max wait time
                {
                    single_MaxWaitTime = (i - single_Queue.front().arrivalTime);
                }

                single_Reg1.doService(single_Queue.dequeue(), 1, i, singleFile); // Dequeues customer from queue and sends to register              
            }

        } if (single_Reg2.doCheckout(i, singleFile)) 
        {
            // If the queue has any customers, it will remove that customer from the queue and begin service for that customer
            if (!single_Queue.isEmpty())
            {
                single_AverageWaitTime += (i - single_Queue.front().arrivalTime); // Adds to the wait time

                if (single_MaxWaitTime < (i - single_Queue.front().arrivalTime)) // Gets the max wait time
                {
                    single_MaxWaitTime = (i - single_Queue.front().arrivalTime);
                }

                single_Reg2.doService(single_Queue.dequeue(), 2, i, singleFile); // Dequeues customer from queue and sends to register  
            }
        } if (single_Reg3.doCheckout(i, singleFile))
        {
            // If the queue has any customers, it will remove that customer from the queue and begin service for that customer
            if (!single_Queue.isEmpty())
            {
                single_AverageWaitTime += (i - single_Queue.front().arrivalTime); // Adds to the wait time
                
                if (single_MaxWaitTime < (i - single_Queue.front().arrivalTime)) // Gets the max wait time
                {
                    single_MaxWaitTime = (i - single_Queue.front().arrivalTime);
                }

                single_Reg3.doService(single_Queue.dequeue(), 3, i, singleFile); // Dequeues customer from queue and sends to register  
            }
        }

        // SIMULATION 2: If service has completed at any cash register
        if (multi_Reg1.doCheckout(i, multipleFile))
        {
            // If the queue has any customers, it will remove that customer from the queue and begin service for that customer
            if (!multiple_Queue1.isEmpty())
            {
                multi_AverageWaitTime += (i - multiple_Queue1.front().arrivalTime); // Adds to the wait time

                if (multi_MaxWaitTime < (i - multiple_Queue1.front().arrivalTime)) // Gets the max wait time
                {
                    multi_MaxWaitTime = (i - multiple_Queue1.front().arrivalTime);
                }

                multi_Reg1.doService(multiple_Queue1.dequeue(), 1, i, multipleFile); // Dequeues customer from queue and sends to register               
            }
        } if (multi_Reg2.doCheckout(i, multipleFile)) 
        {
            if (!multiple_Queue2.isEmpty())
            {
                multi_AverageWaitTime += (i - multiple_Queue2.front().arrivalTime); // Adds to the wait time

                if (multi_MaxWaitTime < (i - multiple_Queue2.front().arrivalTime)) // Gets the max wait time
                {
                    multi_MaxWaitTime = (i - multiple_Queue2.front().arrivalTime);
                }

                multi_Reg2.doService(multiple_Queue2.dequeue(), 2, i, multipleFile); // Dequeues customer from queue and sends to register             
            }
        } if (multi_Reg3.doCheckout(i, multipleFile))
        {
            if (!multiple_Queue3.isEmpty())
            {
                multi_AverageWaitTime += (i - multiple_Queue3.front().arrivalTime); // Adds to the wait time

                if (multi_MaxWaitTime < (i - multiple_Queue3.front().arrivalTime)) // Gets the max wait time
                {
                    multi_MaxWaitTime = (i - multiple_Queue3.front().arrivalTime);
                }

                multi_Reg3.doService(multiple_Queue3.dequeue(), 3, i, multipleFile); // Dequeues customer from queue and sends to register            
            }
        }


        // If a customer has arrived
        if (custArrival == i)
        {
            // Creates a customer
            CustomerData customer(customerNumber, custArrival, rand() % maxServTime + 1); // Generates the customer's service time.
            customerNumber++;

            // Generate the next customer's arrival time
            custArrival = arrivalTime += (rand() % maxArrivalInterval + 1);
        
            singleFile << "Customer " << customer.customerNumber << " arrived at " << customer.arrivalTime << "\n"; // For Single File
            multipleFile << "Customer " << customer.customerNumber << " arrived at " << customer.arrivalTime << "\n"; // For Multiple File

                // SIMULATION 1: If there is a cash register that is not currently serving a customer
                if (single_Reg1.isOpen())
                {
                    // Cash register will begin serving this customer
                    single_Reg1.doService(customer, 1, i, singleFile);

                } else if (single_Reg2.isOpen())
                {
                    // Cash register will begin serving this customer
                    single_Reg2.doService(customer, 2, i, singleFile);

                } else if (single_Reg3.isOpen())
                {
                    // Cash register will begin serving this customer
                    single_Reg3.doService(customer, 3, i, singleFile);

                } else // Else add the customer to a queue
                {
                    // Single Queue
                    single_Queue.enqueue(customer);

                    if (single_MaxLineLength < single_Queue.getSize())
                    {
                        single_MaxLineLength = single_Queue.getSize();
                    }
                }

                // SIMULATION 2: If there is a cash register that is not currently serving a customer
                if (multi_Reg1.isOpen())
                {
    
                    multi_Reg1.doService(customer, 1, i, multipleFile); // Cash register will begin serving this customer

                } else if (multi_Reg2.isOpen())
                {
                    // Cash register will begin serving this customer
                    multi_Reg2.doService(customer, 2, i, multipleFile);

                } else if (multi_Reg3.isOpen())
                {
                    // Cash register will begin serving this customer
                    multi_Reg3.doService(customer, 3, i, multipleFile);

                } else // Else add the customer to a queue
                {
                    // Multi Queue
                    assignCustomerToRegister(customer, multiple_Queue1, multiple_Queue2, multiple_Queue3, multipleFile); // The customer will join the shortest queue (compare sizes and do min size)
                }
        }
    }  // End of Simulation

    //Single Queue Results
    singleFile << "\nAverage wait time: " << fixed << setprecision(1) << (single_AverageWaitTime / (customerNumber - 1));
    singleFile << "\nMaximum wait time: " << single_MaxWaitTime;
    singleFile << "\nMaximum line length: " << single_MaxLineLength << "\n";


    //Multi Queue Results
    multipleFile << "\nAverage wait time: " << fixed << setprecision(1) << (multi_AverageWaitTime / (customerNumber - 1));
    multipleFile << "\nMaximum wait time: " << multi_MaxWaitTime;
    multipleFile << "\nMaximum line length: " << multi_MaxLineLength << "\n";


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
    if (multiple_Queue1.isEmpty() || (multiple_Queue1.getSize() <= multiple_Queue2.getSize() && multiple_Queue1.getSize() <= multiple_Queue3.getSize()))
    {
        multiple_Queue1.enqueue(customer);
    } else if (multiple_Queue2.isEmpty() || (multiple_Queue2.getSize() <= multiple_Queue3.getSize() && multiple_Queue2.getSize() < multiple_Queue1.getSize()))
    {
        multiple_Queue2.enqueue(customer);
    } else
    {
        multiple_Queue3.enqueue(customer);
    } 

    if (multi_MaxLineLength < (multiple_Queue1.getSize() + multiple_Queue2.getSize() + multiple_Queue3.getSize()))
    {
        multi_MaxLineLength = multiple_Queue1.getSize() + multiple_Queue2.getSize() + multiple_Queue3.getSize();
    }
}