/** FILE: mpi_hello.c
 *  Description: First MPI program, prints greetings from each process.
 *  Compile:
 *    mpicc -g -Wall  -o hello mpi_hello.c
 *  Execution:
 *    mpiexec -n<number of processes> ./hello
 *
 *  IT 388 Fall 2022
 *  Illinois State Univerity
 *
 * ToDo: Finish this parallel hello implementation so that each process (core) prints its rank and the number of processors in the comm world.

 */
#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {

   int rank;             /* Process rank */
   int nproc;           /* Number of processes */

   MPI_Init (&argc, &argv); /* Intialize MPI*/
   MPI_Comm_size(MPI_COMM_WORLD, &nproc);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   printf("Hello Parallel World! I am rank %d out of %d\n", rank, nproc);
   MPI_Finalize(); /*Finalize MPI*/

   return 0;
}
// The reason why the order is different each time is because 
//Compile: mpicc -g -Wall -o hello mpi_hello.c
//Execute: mpiexec -n 4 ./hello