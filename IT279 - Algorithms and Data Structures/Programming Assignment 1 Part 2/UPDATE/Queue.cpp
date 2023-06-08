/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of queues
 */
// Modifications:
//    8/20/2003 Mary Elaine Califf
//        Changed to ANSI C++
// Revised 10/15/2022
// Fernando Payan and Mary Elaine Califf S2021
//Implementation of a queue of CustomerData objects

#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue() // constructor
{
  size = 0;
  head = tail = nullptr;
}

Queue::Queue(const Queue& rhs) // copy constructor
{
  makeCopy(rhs);
}

Queue &Queue:: operator=(const Queue& rhs) // assignment constructor
{
  if (this != &rhs)
  {
    deleteQueue();
    makeCopy(rhs);
  }
  return *this;
}

bool Queue::enqueue(CustomerData newValue) // add newValue to queue
{
  if (size == 0) // empty queue
  {
    head = tail = new Node(newValue, nullptr); // Creates a new node at head with the customer value
    size++;  // Increments the size by 1
  }
  else // standard insert logic
  {
    tail->next = new Node(newValue, nullptr); // Creates a new node at tail->next
    tail = tail->next; // Points tail to tail->next (i.e. the end of the queue)
    size++; // Increments the size by 1
  }
  return true;
}

CustomerData Queue::dequeue() // removes a value from the queue and returns it
{
  CustomerData retVal = head->dataVal; // Gets the CustomerData value at head (i.e. the front of the queue)

  // Updates the queue to the next value
  Node *temp = head;
  head = head->next;
  delete temp; // absolutely neceesary
  size--; // Decrements the size by 1

  if (head == nullptr) // Checks if head became nullptr after removing the item from the queue
  {
    head = tail = nullptr;
  }

  return retVal;
}

Queue::~Queue() // destructor
{
  deleteQueue();
}

void Queue::deleteQueue()
{
  Node *temp;
  while (head != nullptr)
  {
    temp = head;
    head = head->next;
    delete temp;
  }
  head = nullptr;
  tail = nullptr;
}

void Queue::makeCopy(const Queue& rhs)
{
  if (rhs.size != 0) // Checks if the copied queue is not empty
  {
    Node *tempHead; // Keeps track of the nodes in Queue rhs
    tempHead = rhs.head; // Sets tempHead to be the head in Queue rhs
    head = tail = new Node(tempHead->dataVal, nullptr); // Sets this queue's head and tail to the head in Queue rhs
    size = 1;
    
    Node *prev; // Keeps track of the previous node
    prev = head; // Points to this queue's head

    tempHead = tempHead->next; // Iterates to the next node in Queue rhs
    while (tempHead != nullptr) // While loop that will iterate through every node in Queue rhs
    {
      tail = new Node(tempHead->dataVal, nullptr); // Updates the tail to the last node
      //Updates prev node
      prev->next = tail;
      prev = tail;
      //Moves onto the next node
      tempHead = tempHead->next;
      //Increments size by one
      size++;
    }
  } else // If the copied queue is empty
  {
    head = tail = rhs.head; // same as setting to nullptr. Maybe write that instead?
  }
}