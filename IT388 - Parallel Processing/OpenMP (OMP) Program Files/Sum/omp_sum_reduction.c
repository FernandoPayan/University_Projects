/* File:     omp_sum.c
 *
 * Purpose:  Simple parallel program in openMP that adds up the threads rank
 *
 * Compile:  gcc -g -Wall -fopenmp -o sum omp_sum.c
 * Run:      ./sum <number of threads>
 * Run several times: for i in {1..10}; do ./sum 10; done
 * Input:    number of threads
 * Output:   A message from each thread
 *
 * ToDo: Identify and protect the critical section
 */
#include <stdio.h>
#include <stdlib.h>
#ifndef _OPENMP
#include <omp.h>
#endif
void Usage(char* prog_name);
int computeNumber(int rank); /* Thread function generates a number in terms of rank*/
/*-----------------------------------------------------------------*/
int main(int argc, char* argv[]) {
    int totalSum=0; /* Stores global sum */
    if (argc != 2) Usage(argv[0]);
    int nThreads = strtol(argv[1], NULL, 10);  /* input # of threads */
   // omp_set_num_threads(nThreads);
    
#  pragma omp parallel num_threads(nThreads) reduction(+: totalSum)
    {
      int rank = omp_get_thread_num();
      int  myNumber = computeNumber(rank);
      totalSum += myNumber;
    }
    /* Main thread prints totalSum */
    printf("nThreads: %d, Correct sum: %d, Calculated sum: %d\n",nThreads,nThreads*(nThreads+1)/2, totalSum);
    return 0;
}  /* main */

/** Compute number function*/
int computeNumber(int rank){
    return rank + 1;
}

void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */
