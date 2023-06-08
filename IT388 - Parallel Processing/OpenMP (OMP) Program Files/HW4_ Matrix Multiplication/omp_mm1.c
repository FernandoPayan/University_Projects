/** FILE: omp_mm1.c
 * HOMEWORK #4 - Matrix-Matrix Multiplication with openMP
 * DESCRIPTION: OpenMP code that will perform matrix multiplication. Parallelizing the outermost loop.
 * Author: Fernando Payan
 * Compile:
 *      gcc -g -Wall -fopenmp -o mm1 omp_mm1.c
 * Execution:
 *      ./mm1 <NUM_OF_THREADS> <MATRIX_SIZE>
 *
 * IT 388 Fall 2022
 * Illinois State University
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Fills in the values of Matrix A
void fill_A_Matrix(long r, long c, long matrix[r][c]);

// Fills in the values of Matrix A
void fill_B_Matrix(long r, long c, long matrix[r][c]);

// Prints the matrix
void printMatrix(long size, long matrix[size][size]);

int main(int argc, char *argv[])
{
    int M, i, j, k, numThreads;    // M represents the Matrix Dimension. i, j, and k are used for the loops.
    double start, elapsed, finish; // Stores the time the program took.
    int sum = 0;

    if (argc < 3) // Checks if the number of arguments passed is correct.
    {
        printf("Not enough arguments passed. Restart program");
        exit(1);
    }

    // Gets the user inputted value for M
    numThreads = atoi(argv[1]);
    M = atoi(argv[2]);

    // Creates the Matices of A and B based on the values of M
    long matrixA[M][M];

    long matrixB[M][M];

    long matrixC[M][M];

    // Fills the values for Matrix A and B
    fill_A_Matrix(M, M, matrixA);
    fill_B_Matrix(M, M, matrixB);

    // Sequential Multiplication

    // Start time
    start = omp_get_wtime();
    
    // Matrix Multiplication
    for (i = 0; i < M; i++) // Num of Rows each processor needs to calculate
    {
        for (j = 0; j < M; j++) // Iterates through the num of rows
        {
            sum = 0;
            for (k = 0; k < M; k++) // Iterates through the num of columns
                sum += (matrixA[i][k] * matrixB[k][j]);
            matrixC[i][j] = sum;
        }
    }

    // Calculates the elapsed time
    finish = omp_get_wtime();
    elapsed = finish - start;

    // Prints the elapsed time for the Sequential Multiplication
    printf(" Sequential Multiplication: Matrix C[%d][%d], #threads: %d Elapsed time: %f\n", M, M, numThreads, elapsed);

    // Parallel Multiplicaiton

    // Start time
    start = omp_get_wtime();

    // Matrix Multiplication
    #pragma omp parallel for num_threads(numThreads) private(i, sum)
    for (int i = 0; i < M; i++) // Num of Rows each processor needs to calculate
    {
        for (int j = 0; j < M; j++) // Iterates through the num of rows
        {
            sum = 0;
            for (int k = 0; k < M; k++) // Iterates through the num of columns
                sum += (matrixA[i][k] * matrixB[k][j]);
            matrixC[i][j] = sum;
        }
    }

    // Calculates the elapsed time
    finish = omp_get_wtime();
    elapsed = finish - start;

    // Prints the elapsed time for the Parallel Multiplication
    printf(" Parallel Multiplication: Matrix C[%d][%d], #threads: %d Elapsed time: %f\n", M, M, numThreads, elapsed);
}

void fill_A_Matrix(long r, long c, long matrix[r][c])
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            matrix[i][j] = j % 3;
        }
    }
}

void fill_B_Matrix(long r, long c, long matrix[r][c])
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            matrix[i][j] = i % 3;
        }
    }
}

void printMatrix(long size, long matrix[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%ld ", matrix[i][j]);
        }
        printf("\n");
    }
}

void multiplyMatrix(long size, long matrixA[size][size], long matrixB[size][size], long matrixC[size][size])
{
    
}