/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of a queue of integers which may have length of up to 100
 *
 * Revised 10/15/2022
 */
 // Fernando Payan and Mary Elaine Califf S2021
 //Header file for a queue of CustomerData objects

#ifndef QUEUE_H
#define QUEUE_H
#include "CustomerData.h"

class Queue
{
private:
  int size = 0;

  struct Node
  {
    CustomerData dataVal;
    Node *next;
    Node(CustomerData data, Node *nextPtr) : dataVal(data), next(nextPtr) {} // ?
  };
    Node *head;
    Node *tail;

  void deleteQueue(); // Deletes the queue
  void makeCopy(const Queue& rhs); // Makes a copy of the Queue

public:
  // constructor
  Queue();

  // copy constructor
  Queue(const Queue& rhs);

  // assignment constructor
  Queue& operator=(const Queue& rhs);

  // getter for size
  int getSize() { return size; }

  // is the queue empty
  bool isEmpty() { return (size == 0); }

  // adds a new value to the queue
  // fails and returns false if the queue is full
  bool enqueue(CustomerData newValue);

  // removes a value from the queue and returns it
  // Precondition: queue must not be empty
  CustomerData dequeue();

  // return item at the front of the queue without removing it
  // Precondtion: queue must not be empty
  CustomerData front() { return head->dataVal; }

  // destructor
  ~Queue();
};

#endif