/* File: omp_mv.c
 * Purpose: Computes a parallel matrix-vector product with openMP
 * Linux Servers:
 *  Compile:  gcc -g -Wall -fopenmp -o omp_mv omp_mv.c
 *  Run: ./omp_mv <thread_count> <matrix dimension m=n>
 * Expanse Cluster:
 *  1) load intel compiler 
        module load intel mvapich2
    2) compile code with 
        icc -o mv omp_mv.c -qopenmp
    3) submit job script:
        sbatch ompScript.sb
 *
 * IT 388 - Illinois State University
 Name:

 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* Parallel function */
/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
    double start, finish, elapsed;
    int i, j, k, nThreads;
    int     m, n;
    double* A;
    double* x;
    double* y;
    
    /* Get number of threads from command line */
    nThreads = atoi(argv[1]);
    omp_set_num_threads(nThreads);
    m=n=atoi(argv[2]); // get matrix dimension
    
    A = malloc(m*n*sizeof(double));
    x = malloc(n*sizeof(double));
    y = malloc(m*sizeof(double));
    
    start = omp_get_wtime();
    
    #pragma omp parallel private(i,j,k) shared(A,x,y,n)
    {
        // generate matrix
        #pragma omp for
        for (i=0;i<m;i++){
            for (j=0;j<n;j++){
                A[i*n + j] = (i+j)%6;
            }
        }
    

        // Generate vector
        #pragma omp for
        for (k=0;k<n;k++){
            x[k] = k%6-1;
        }


        // Matrix-vector multiplication
        for (i = 0; i <= m; i++) {
            y[i] = 0.0;
            for (j = 0; j < n; j++){
                y[i] += A[i*n+j]*x[j];
            }
        }
    }
    finish = omp_get_wtime();
    elapsed = finish - start;
    
    
    printf("A[%d,%d] x[%d], #threads: %d Elapsed time: %f\n",m,n,n,nThreads,elapsed);
    
    free(A);
    free(x);
    free(y);
    return 0;
}  /* main */