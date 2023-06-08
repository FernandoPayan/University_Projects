/* File: mpi_array_coll.c
 * Process an array using collective communication in mpi.
 IT 388 - Fall 2022
 
 Your Name: Fernando Payan
 Date: 9/20/2022
 
 Compile: mpicc -o array mpi_array_coll.c
 Execute: mpiexec -n 3 ./array SIZE_OF_ARRAY
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void printArray(int [],int size);

int main(int argc, char* argv[]){
    int N, n_local, rank, nproc;
    int *array;
    int *array_new;
    MPI_Init(&argc,&argv);
    MPI_Comm comm; comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nproc);
    MPI_Comm_rank(comm, &rank);
    
    // 1. Manager processor scans input (array size), initializes array, computes n_local, and prints initial array
    if (rank == 0)
    {
        // User Array Size
        if (argc <= 1)
        {
            printf("Not enough arguments\n");
            MPI_Abort(comm, 1);
        }
        N = atoi(argv[1]); // Reads input (You need to check for errors for HW here. do MPI Abort)
        array = malloc(N*sizeof(int));
        array_new = malloc(N*sizeof(int));
        for (int i = 0; i < N; i++)
        {
            array[i]=i*2;
        }
        n_local = N / nproc; // Work
        printArray(array, N);
    }
    // 2. Make n_local available to all processors
    MPI_Bcast(&n_local, 1, MPI_INT, 0, comm);

    // 3. Declare local subarray that will receive scattered array from manager
    int *array_local = malloc(n_local*sizeof(int));

    // 4. Scatter parts of the array (subarrays) to all processors
    MPI_Scatter(array, n_local, MPI_INT, array_local, n_local, MPI_INT, 0, comm);
        
    // 4.1 Add a printing statement that prints, the rank, and the array_local after the scatter.
    printf("\nrank: %d, local subarray:", rank); printArray(array_local, n_local);
        
    // 5. Each processor works on its part of the subarray ( multiply by or add a number for example )
    for (int j = 0; j < n_local; j++)
    {
        array_local[j] = array_local[j] + 1;
    }
    

    // 6. Gather all new subarrays into manager processors 0
    MPI_Gather(array_local, n_local, MPI_INT, array_new, n_local, MPI_INT, 0, comm);
    
    // 7.  Manager processor prints out the final processed array
    if (rank == 0)
    {
        printf("Final Array:"); printArray(array_new, N);
    }

    MPI_Finalize();
}

/*--------------------
 Print array to screen
 */
void printArray(int a[], int N){
    printf("[");
    for (int i=0; i<N-1; i++){
        printf("%d,",a[i]);
    }
    printf("%d]\n",a[N-1]);
    
}
