
/* File pth_sum.c
 * Description: Computes the sum of the First n Natural Numbers.
 *               1+ 2+ 3+ ... + n = n(n+1) / 2, for n a natural number.
 * Compile:  gcc -g -Wall -o pth_sum pth_sum.c -lm -lpthread
 * Run:      ./pth_sum <number of threads> <n>
 *           ./pth_sum 4 16
 *
 *           n is the number of terms of the series to use.
 *           n should be evenly divisible by the number of threads
 *
 *  Run several times using bash shell:
 *      for i in {1..40}; do ./pth_sum 500 1000; done
 *
 *  This example ilustrates critical section.
 *
 * TO DO: Write missing code to protect critical section
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<sys/time.h>

const int MAX_THREADS = 1024;

/* Global variables - shared */
long     thread_count;
long long n;
double sum;
pthread_mutex_t mutex;

void *thread_sum( void *input );

/* Only executed by main thread */
void Get_args(int argc, char* argv[]);
void Usage(char* prog_name);

// Get time function
double Get_time(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec/1000000.0;
}

int main(int argc, char* argv[]) {
    
    long     index;  /* Use long in case of a 64-bit system */
    pthread_t* threads;
       double elapsed, start;
    pthread_mutex_init(&mutex, NULL);
    /* Get number of threads from command line */
    Get_args(argc, argv);
    threads = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
    
    sum = 0.0;
    /* Create independent threads each of which will execute function */
    for (index = 0; index<thread_count; index++){
        pthread_create(&threads[index], NULL, thread_sum,(void*)index);
    }

    /* Wait for threads to complete */
    for (index = 0; index<thread_count; index++){
        pthread_join(threads[index], NULL);
    }
    
    pthread_mutex_destroy(&mutex);

   printf("Sum = %4.1f",sum);
   printf(", should be  = %lld\n",(n*(n+1))/2);
   free(threads);
    return 0;
}

/*----------------------------------------/
 * Thread function to compute the sum
 */
void *thread_sum( void *input )
{
    long my_rank = (long) input;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n*my_rank+1;
    long long my_last_i = my_first_i + my_n;
    double my_sum = 0.0;
    for (i = my_first_i; i < my_last_i; i++)
    {
        my_sum = my_sum + i;
        //sum = sum + i ; // Don't want this because it will always call the Mutex, making it sequential.
    }
    pthread_mutex_lock(&mutex);
    sum = sum + my_sum;
    pthread_mutex_unlock(&mutex);
    return NULL;

}
/*------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get the command line args
 * In args:     argc, argv
 * Globals out: thread_count, n
 */
void Get_args(int argc, char* argv[]) {
    if (argc != 3) Usage(argv[0]);
    thread_count = strtol(argv[1], NULL, 10);
    if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);
    n = strtoll(argv[2], NULL, 10);
    if (n <= 0) Usage(argv[0]);
}  /* Get_args */

/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print a message explaining how to run the program
 * In arg:    prog_name
 */
void Usage(char* prog_name) {
    fprintf(stderr, "usage: %s <number of threads> <n>\n", prog_name);
    fprintf(stderr, "   n is the number of terms and should be >= 1\n");
    fprintf(stderr, "   n should be evenly divisible by the number of threads\n");
    exit(0);
}  /* Usage */
