/* File:    mpi_montecarlo.c
 *
 * Description: MPI implementation of Monte Carlo method to compute value of PI
 * Compile: mpicc -g -Wall -o monte mpi_montecarlo.c
 * Usage:   mpiexec -n 4 ./monte <N>
 *             N:   number of samples
 *
 * Input:   Number of samples for Monte Carlo Method
 * Output:  Estimate of Pi
 *
 * IT 388 - ISU
 
 *  Name:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

#define PI25DT  3.141592653589793238462643

/*-----------------------------------------------------------------*/
int main(int argc, char* argv[]) {
    int  N;
    double x, y, estimate_pi;
    int i, count;
    
    int rank, nproc, count_local,N_local;
    double start, elapsed;
    
    MPI_Init(&argc, &argv);
    MPI_Comm comm; comm = MPI_COMM_WORLD;
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank==0){
        N = atoi(argv[1]); // input number of samples
        N_local=N/nproc;
        if (N%nproc!=0){
            MPI_Abort(MPI_COMM_WORLD,1);
        }
    }
    
    // Barrier and start time
    MPI_Barrier(comm);
    start = MPI_Wtime();
    
    // Make N_local available to all processors
    MPI_Bcast(&N_local, 1, MPI_INT, 0, comm);
    
    // Rand seed;
    srand(time(0)); // rand() seed
    
    // Each process counts number of samples fall inside quarter circle.
    count_local = 0;
    for (i = 0; i < N_local; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if ( (x * x) + (y * y) < 1)
            count_local++;
    }
    
    
    // Sum counts from all processors
    MPI_Reduce(&count_local, &count, 1, MPI_INT, MPI_SUM, 0, comm);
    
    
    // Barrier and elapsed time
    MPI_Barrier(comm);
    elapsed = MPI_Wtime() - start;
    
    
    // Manager process prints results:
    if (rank == 0){
        estimate_pi = 4*(double)count/(double)N;
        printf("\n Samples: %d \n PI ~ %1.15f \n Error: %1.15f\n #proc %d \n time: %f sec \n", N, estimate_pi,fabs(estimate_pi-PI25DT),nproc,elapsed);
    }
    
    MPI_Finalize();
    
    
    return 0;
}  /* main */


