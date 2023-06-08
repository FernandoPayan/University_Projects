/******************************************************************************
 * FILE: mpi_trap.c
 * DESCRIPTION: Compute pi using trapezoid rule with MPI collective communication
 * Output example:
    $ mpicc -o trap mpi_trap.c -lm
    $ mpiexec -n 4 ./trap
    With n = 10000 trapezoids, our estimate
    of pi is 3.141591477611322
    Error : 0.000001175978471
    
    Name:
 *
 * IT 388 - Fall 2022
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define PI25DT 3.141592653589793238462643
double f(double x); /* Function/equation we're integrating */
int main (int argc, char *argv[])
{
    int N = 100; // Number of Trapezoids we are doing
    double xi=0.0, integral_local=0.0, a=0.0, b=1.0;
    double dx=(b-a)/N;
    double pi,pi_local=0.0;
    int nproc, rank, n_local,start_i,end_i;
    
    MPI_Init(&argc,&argv);
    MPI_Comm comm; comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm,&nproc);
    MPI_Comm_rank(comm,&rank);
    int MPI_Barrier(MPI_Comm comm);
    startTime = MPI_Wtime();
    
    MPI_Barrier(comm);
    /* Number of trapezoids each processor will compute*/
    n_local = N / nproc; // work = N / p
    
    /* Set the starting and ending index for each processor to compute */
    start_i = n_local * rank; //Core 0: 0, Core 1: 10, Core 2: 20, ...
    end_i = n_local * start_i; // Core 0: 10, Core 2: 20, Core 3: 30, ...
    
    /* Each processor computes its part of the integral */
    double x0 = a + dx * start_i;
    double xN = a + dx * end_i;

    integral_local = (f(x0)+f(xN)) / 2;
    for (int i = start_i + 1; i < end_i; i++)
    {
        xi = a + i * dx;
        integral_local = integral_local + f(xi);
    }
    pi_local = 4 * (integral_local * dx);

    /* Reduce local Pi calculation */
    MPI_Reduce(&pi_local, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
    MPI_Barrier(comm);
    elapsed = MPI_Wtime() - starttime;
    /* Print the result */
    if (rank == 0)
    {
        printf("N = %d. Pi approximation = %f. PI = %f\n", N, pi, PI25DT);
        printf("Elapsed time: %f seconds\n", elapsed);
    }
    
    MPI_Finalize();
    
    return 0;
}   /* end of main */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x){
    return sqrt(1.0-x*x);
}

