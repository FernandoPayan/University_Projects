/* Sections example
 * IT 388 - ISU
 * Compile:  gcc -g -Wall -fopenmp -o sections omp_sections.c
 * Run:      ./sections <number of threads>
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    
    /* Get number of threads from command line */
    omp_set_num_threads(atoi(argv[1]));
    
#pragma omp parallel sections
    {
#pragma omp section
        {
            printf ("thread %d is working on section 1 \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf ("thread %d is working on section 2 \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf ("thread %d is working on section 3 \n", omp_get_thread_num());
        }
    }
    
    return 0;
}  /* main */



