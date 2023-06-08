/* File: mpi_array.c
 Processing array using point-to-point communication.
 
 Complete items 1 through 9.
 
 IT 388 - Fall 2022
 */
#include <stdio.h>
#include <mpi.h>


void printArray(int [],int size);

int main(int argc, char* argv[]){
    
    /* global variables*/
    int N = 12; // array length
    int array[N], array_new[N];
    for (int i=0; i<N; i++){array[i]=0; array_new[i]=0;}
    
    int my_rank, nproc; /* Process rank and number of processes*/
    int offset, work, dest, source;
    
    /* Start MPI*/
    MPI_Init(&argc,&argv);
    MPI_Comm comm; MPI_Status status; comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nproc); //Returns number of Processors
    MPI_Comm_rank(comm, &my_rank); // Returns rank of calling process
    // Get the name of the processor
    char proc_name[MPI_MAX_PROCESSOR_NAME];
    int len;
    MPI_Get_processor_name(proc_name, &len);

    /* 1. Define local amount of items each processor will work on (i.e the work)*/
    work = N / nproc;
   
    if (my_rank == 0)
    {
        /* 2.1 Manager initializing array */
       for (int i = 0; i < sizeof(array); i++)
       {
            array[i] = i * 2;
       }
        /* 2.2 Manager prints initial array*/
        printf("Initial array = ");
        printArray(array,N);
        
        /* 2.3 manager sends subarrays to each process */
       for (dest = 1; dest < nproc; dest++) // This is where the fatal error is occuring
       {
            offset = work * dest; // Doing this because the offset is respective to the destination
            printf("DESTINATION VALUE: %d\n", dest);
            MPI_Send(&array[offset], work, MPI_INT, dest, 13, MPI_COMM_WORLD); // check message tag and comm?
       }
    
        /* 2.4. manager works on its part */
        for (int i = 0; i < work; i++)
        {
            array_new[i] = array[i] + 1;
        }
        
        /* 2.5.  manager receives calculations from workers */
        for (source = 1; source < nproc; source++)
        {
            offset = work * source;
            MPI_Recv(&array_new[offset], work, MPI_INT, source, 15, MPI_COMM_WORLD, &status);
        }

        /* 2.6. manager prints the processed array */
        printf("Final array = "); 
        printArray(array_new,N);
    } else
    {
        /* 3.0 Workers receive offset, and its portion of the data. Does not need a for loop*/
        offset = my_rank * work;
        MPI_Recv(&array[offset], work, MPI_INT, 0, 13, MPI_COMM_WORLD, &status);

        /* 3.1 Worker prints processor name, its rank and received array*/
        printf("Name: %s rank = %d: received on subarray", proc_name, my_rank);
        printArray(array,N);

        /* 3.2. Worker works on array, doing some calculation on it. For loop. Subtract num, add num, etc. and then send it back to manager. */
       for (dest = offset; dest < offset + work; dest++){
            array_new[dest] = array[dest] + 1;
       } 
        
        /* 3.3. Workers send their work back to manager */
        MPI_Send(&array_new[offset], work, MPI_INT, 0, 15, MPI_COMM_WORLD);
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