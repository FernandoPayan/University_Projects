/** FILE: mpi_sendrec.c
 *  Description: First MPI program, prints greetings from each process.
 *  Compile:
 *    mpicc -g -Wall  -o mpi_sendrec mpi_sendrec.c
 *  Execution:
 *    mpiexec -n<number of processes> ./mpi_sendrec
 *
 *  IT 388 Fall 2022
 *  Illinois State Univerity
 */
#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {

   int rank;               /* Process rank */
   int nproc;           /* Number of processes */
   int source = 0;
   int dest = 1;
   int data = 0;
   int count = 1;

   MPI_Init (&argc, &argv); /* intialize MPI*/
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nproc);
    MPI_Comm_rank(comm, &rank);
    MPI_Status status;

    if (rank == 0)
    {
        data = 16;
        for (dest = 1; dest < nproc; dest++)
        {
            MPI_Send(&data, count, MPI_INT, dest, 13, MPI_COMM_WORLD);
        }
    } else // rank != 0
    {
        printf("rank %d, before receive data= %d \n", rank, data);
        MPI_Recv(&data, count, MPI_INT, source, 13, MPI_COMM_WORLD, &status); //You could also put MPI_STATUS_IGNORE
        printf("rank %d, after receive data= %d \n", rank, data);
    } // If n > 2, the program gets stuck because for every send, there needs to be a receive. The MPI_Recv is just waiting for something to be sent to it.
    
   MPI_Finalize(); /*Finalize MPI*/

    return 0;
}

/* DEADLOCK EXAMPLE
  if (rank == 0)
    {
        data = 16;
        MPI_Send(&data, count, MPI_INT, dest, 13, MPI_COMM_WORLD);
    } else
    {
        printf("rank %d, before receive data= %d \n", rank, data);
        MPI_Recv(&data, count, MPI_INT, source, 13, MPI_COMM_WORLD, &status); //You could also put MPI_STATUS_IGNORE
        printf("rank %d, after receive data= %d \n", rank, data);
    } // If n > 2, the program gets stuck because for every send, there needs to be a receive. The MPI_Recv is just waiting for something to be sent to it.
*/