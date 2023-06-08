/** FILE: mpi_mm.c
 * HOMEWORK #3 - Matrix-Matrix Multiplication
 * DESCRIPTION: MPI code that will perform matrix multiplication
 * Author: Fernando Payan
 * Compile:
 *      mpicc -o mm mpi_mm.c
 * Execution:
 *      mpiexec -n <NUM_OF_PROCESSORS> ./mpi_mm <N, M, Q>
 * 
 * IT 388 Fall 2022
 * Illinois State University
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Fills in the values of Matrix A
void fill_A_Matrix(long r, long c, long matrix[r][c]);

// Fills in the values of Matrix A
void fill_B_Matrix(long r, long c, long matrix[r][c]);

// Converts a matrix from a 2D array to a 1D array representation.
void convertMatrix(long r, long c, long size, long matrix[r][c], long newMatrix[size]);

// Prints the array
void printArray(long r, long c, long size, long matrix[size]);

int main(int argc, char* argv[])
{
    int rank, nproc; // Rank and Num of processors
    long N, M, Q; // Values of N, M, Q.
    double startTime, elapsed; // Stores the time the program took. Elapsed is calculated by subtracting the MPI_Wtime() - startTime.
    
    // MPI
    MPI_Init(&argc, &argv);
    MPI_Comm comm; comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nproc);
    MPI_Comm_rank(comm, &rank);

    // Gets the user inputted value for N, M, and Q respectively
    N = atoi(argv[1]); 
    M = atoi(argv[2]); 
    Q = atoi(argv[3]);

    // Creates the 2D and 1D arrays of A and B based on the values of N, M, and Q
    long matrixA[N][M]; 
    long arrayA[(N * M)];
    long matrixB[M][Q]; 
    long arrayB[(M * Q)];

    /**
     *  Calculates how many rows a processor will calculate
     *  EX: If we have N = 4 and nproc = 2, A_local = 2. This means each processor will calculate two rows each.
     */
    long A_local = N / nproc; 

    /**
     *  Calulates the size of the return array 
     *  EX: If we have 3 elements per row and we're calculating 2 rows per processor, we do 2 * 3 = size 6 for this array
     *  [A, B, C, D, E, F] where A - C is row 1, D-F is row 2.
     */
    long C_local = A_local * Q; 
    
    // Where the scattered values of matrixA will be stored for each processor
    long arrayA_local[A_local * M]; 

    // Where the values of matrixC will be stored for each processor and returned to the manager core. 
    long arrayC_local[C_local];

    // Where Matrix C's values is gathered to
    long result[(N * Q)]; 

    if (rank  == 0) // Manager Core
    {
        // Checks if N is a multiple of the number of processors. If not, the program prints a message and terminates.
        if ( (N % nproc) != 0 )
        {
            printf("%ld is not a multiple of %d. Terminating program...\n", N, nproc);
            MPI_Abort(comm, 1);
        }
        // Manager core constructs matrix A and B, using 1D representation for the 2D arrays.

        // Fills the values for Matrix A
        fill_A_Matrix(N, M, matrixA);
        fill_B_Matrix(M, Q, matrixB);

        // Storing elements in 1-D array
        convertMatrix(N, M, (M * Q), matrixA, arrayA);
        convertMatrix(M, Q, (M * Q), matrixB, arrayB);
    }

    // Start time computation for scatter, broadcast, multiplication, and gather operations
    MPI_Barrier(comm);
    startTime = MPI_Wtime();
    MPI_Bcast(matrixB, (M * Q), MPI_LONG, 0, comm); // Sending the matrixB to all processors
    MPI_Scatter(arrayA, (A_local * M), MPI_LONG, arrayA_local, (A_local * M), MPI_LONG, 0, comm); // Splits arrayA into (A_local * M) across nproc processors.

    // Sets default values of arrayC_local
    for (int i = 0; i < C_local; i++)
    {
        arrayC_local[i] = 0;
    }

    // Multiplication
    int arrayA_counter = 0; // Used to keep track of which index we're at in arrayA_local
    for (int k = 0; k < A_local; k++) // Num of Rows each processor needs to calculate
    {
        int counter = k * Q; // Keeps track of which position we're at in our arrayC_local
        for (int i = 0; i < M; i++) // Iterates through the num of rows in B 
        {
            for (int j = 0; j < Q; j++) // Iterates through the num of columns in B
            {
                arrayC_local[counter] += (arrayA_local[arrayA_counter] * matrixB[i][j]); // Computes value from arrayA_local * matrixB[i][j] and adds it to arrayC_local
                counter++;
            }
            counter = k * Q; // Resets back to counter based on the value of k. 
            arrayA_counter++;
        }
    }

    // Gathers the computed work from each processor and sends it to the manager core
    MPI_Gather(arrayC_local, C_local, MPI_LONG, result, C_local, MPI_LONG, 0, comm);

    // Closes the barrier and computes the elapsed time
    MPI_Barrier(comm);
    elapsed = MPI_Wtime() - startTime;

    // Prints the results
    if (rank == 0)
    {
        printf("\nMatrix Multiplication: C[%ldx%ld] = A[%ldx%ld]*B[%ldx%ld], nproc: %d, Elapsed time: %f secs\n", N, Q, N, M, M, Q, nproc, elapsed);
        if (N < 20 && M < 20 && Q < 20)
        {
            // Matrix A
            printf("A[%ldx%ld]:\n", N, M);
            printArray(N, M, (N * M), arrayA);

            // Matrix B
            printf("B[%ldx%ld]:\n", M, Q);
            printArray(M, Q, (M * Q), arrayB);

            // Matrix C
            printf("C[%ldx%ld]:\n", N, Q);
            printArray(N, Q, (N * Q), result);
        }
    }
    MPI_Finalize();
}

void fill_A_Matrix(long r, long c, long matrix[r][c]){
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            matrix[i][j] = j % 3;
            
        }
    }
}

void fill_B_Matrix(long r, long c, long matrix[r][c]){
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            matrix[i][j] = i % 3;
        }
    }
}

void convertMatrix(long r, long c, long size, long matrix[r][c], long newMatrix[size])
{
    for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                int k = i * c + j;
                newMatrix[k] = matrix[i][j];
                k++;
            }
        }
}

void printArray(long r, long c, long size, long matrix[size])
{
    for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                printf("%ld ", *(matrix + i*c + j));
            }
            printf("\n");
        }
}