/* File: hy_hello.c
 
 Hybrid parallel program with OpenMP and MPI
 
 compile with:
 mpicc  -g -Wall -fopenmp -o hy_hello hy_hello.c
 export OMP_NUM_THREADS=6
 run with:
 mpiexec -n 2 ./hy_hello

 IT 388 
*/

#include <stdio.h>
#include "mpi.h"
#include <omp.h>

int main(int argc, char *argv[]) {
  int nproc, rank, namesize;
  char processor_Name[MPI_MAX_PROCESSOR_NAME];
  int threadID = 0, numThreads = 1;

  /* MPI starts here, no MPI calls before this*/
  MPI_Init(&argc, &argv);
    
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  MPI_Get_processor_name(processor_Name, &namesize);
  
    /* Each MPI process will execute this omp parallel directive */
  #pragma omp parallel private(threadID, numThreads)
  {
    numThreads = omp_get_num_threads();
    threadID = omp_get_thread_num();
    printf("Hello! I am thread %d out of %d threads from process %d out of %d on %s\n",
           threadID, numThreads, rank, nproc, processor_Name);
  }

  MPI_Finalize();
    /*NO MPI call after this*/
    return 0;
}

