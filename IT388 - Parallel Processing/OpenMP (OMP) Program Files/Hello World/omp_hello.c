/* File:     omp_hello.c
 *
 * Purpose:  A parallel hello, world program that uses OpenMP
 *
 * Compile:  gcc -g -Wall -fopenmp -o hello omp_hello.c
 * Run:      ./hello <number of threads>
 *
 * Input:    number of threads
 * Output:   A message from each thread
 *
 */
#include <stdio.h>
#include <stdlib.h>
// Error Checking
# ifdef _OPENMP
#include <omp.h> 
# endif  

void Hello(int rank, int nThreads); /* Thread function */
/*-----------------------------------------------------------------*/
int main(int argc, char* argv[]) {
    
    // If user did not pass enough arguments, it will abort the program.
    if (argc <= 1) Usage(argv[0]);

    /* Get user inputs number of threads */
    int nThreads = strtol(argv[1], NULL, 10); // same as nproc

    /*1. Set the number of threads */
    #ifdef _OPENMP
    omp_set_num_threads(nThreads);
    #else
    nThreads = 1;
    #endif

    
    /* 2. Create parallel region  */
#  pragma omp parallel
    {
        /* 2.1 Get thread rank */
    # ifdef _OPENMP
        int rank = omp_get_thread_num();
    #else
        int rank = 1;
    # endif
        /* 2.2 Call thread function */
    Hello(rank, nThreads);
    }
    return 0;
}  /* main */

/** Thread function*/
void Hello(int rank, int nThreads){
    printf("Hello from thread %d out of %d threads\n", rank, nThreads);
}

