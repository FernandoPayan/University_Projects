/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of queues
 */
// Modifications:
//    8/20/2003 Mary Elaine Califf
//        Changed to ANSI C++
// Revised 12/25/2020
// _____ and Mary Elaine Califf S2021
//Implementation of a queue of CustomerData objects

#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue() // constructor
{
  frontIndex = -1;
  backIndex = -1;
  size = 0;
}

bool Queue::enqueue(CustomerData newValue) // add newValue to queue
{
  if (size == MAX_QUEUE_SIZE) // queue too large -- failure case
    return false;

  if (size == 0) // empty queue
  {
    frontIndex = backIndex = 0;
    size = 1;
    queueArr[0] = newValue;
  }
  else // standard insert logic
  {
    size++;
    backIndex = (backIndex + 1) % MAX_QUEUE_SIZE;
    queueArr[backIndex] = newValue;
  }
  return true;
}

CustomerData Queue::dequeue()
{
  CustomerData retVal = queueArr[frontIndex];
  size--;
  frontIndex = (frontIndex + 1) % MAX_QUEUE_SIZE;
  return retVal;
}
