/** FILE: mpi_sum.c
 * HOMEWORK #2 - Simple MPI
 * Description: MPI code that will compute the sum of the first N integer numbers using multiple processors
 * Author: Fernando Payan
 * Compile:
 *    mpicc -o sum mpi_sum.c
 * Execution:
 *    mpiexec -n <number of processes> ./sum <N value>
 *
 * IT 388 Fall 2022
 * Illinois State Univerity
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) 
{
    int my_rank, nproc, source; // Rank, # of Processors, and Source
    int sum = 0, calculated_sum; // Sum will store the total sum, and calculated_sum stores the sum a processor calculated.
    

    MPI_Init(&argc, &argv);
    MPI_Comm comm; comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nproc);
    MPI_Comm_rank(comm, &my_rank);
    MPI_Status status;

    if (argc <= 1) // If user did not pass enough arguments, it will abort the program.
    {
        printf("Argument was not passed. Please try executing the file again in this format: mpiexec -n <number of processes> ./sum <N value>\n");
        MPI_Abort(comm, 1);
    }

    int N = atoi(argv[1]); // User Input
    sum = 0; 
    
    // Calculates how much work each core will do
    int nproc_start_val = N * my_rank / nproc + 1; // Gets the starting value for each core
    int nproc_end_val = N * (my_rank + 1) / nproc; // Gets the ending value for each core

    // All of the cores have to calculate the sum
    for (int i = nproc_start_val; i <= nproc_end_val; ++i)
    {
        sum = sum + i;
    }
    printf("Rank %d's starting value is: %d and it's ending value is: %d\n", my_rank, nproc_start_val, nproc_end_val);

    if (my_rank == 0)
    {
        printf("\nRank %d: Sum currently is: %d\n", my_rank, sum);

        // Receives the value of sum from the other processes and adds them
        for (int source = 1; source < nproc; source++)
        {
            MPI_Recv(&calculated_sum, 1, MPI_INT, source, 1, comm, &status);
            sum = sum + calculated_sum;
            printf("Rank: %d Calculated Sum: %d Sum is now: %d\n", source, calculated_sum, sum);
        }
    }
    else
    {
        MPI_Send(&sum, 1, MPI_INT, 0, 1, comm);
    }
    if (my_rank == 0)
        printf("The sum from 1 to %d is %d \n\n", N, sum);

    MPI_Finalize();
}