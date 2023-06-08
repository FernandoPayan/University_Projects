/** FILE: mpi_hello.c
 *  Description: First MPI program, prints greetings from each process.
 *  Compile:
 *    mpicc -g -Wall  -o mpi_hello mpi_hello.c
 *  Execution:
 *    mpiexec -n<number of processes> ./mpi_hello
 *
 *  IT 388 Fall 2022
 *  Illinois State Univerity
 *
 * 
 */
#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {

   int rank;               /* Process rank */
   int nproc;           /* Number of processes */
   MPI_Init (&argc, &argv); /* intialize MPI*/
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nproc);
    MPI_Comm_rank(comm, &rank);
    
    printf("Hello parallel world, I am core %d out of %d cores in my world\n", rank, nproc);
    
   MPI_Finalize(); /*Finalize MPI*/

    return 0;
}
