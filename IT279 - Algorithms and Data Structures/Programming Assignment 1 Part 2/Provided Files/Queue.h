/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of a queue of integers which may have length of up to 100
 *
 * Revised 12/25/2020
 */
 // _____ and Mary Elaine Califf S2021
 //Header file for a queue of CustomerData objects

#ifndef QUEUE_H
#define QUEUE_H
#include "CustomerData.h"

class Queue
{
public:

  // constructor
  Queue();

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
  CustomerData front() { return queueArr[frontIndex]; }

private:
  static const int MAX_QUEUE_SIZE = 500;
  CustomerData queueArr[MAX_QUEUE_SIZE];
  int frontIndex;
  int backIndex;
  int size;
};

#endif
