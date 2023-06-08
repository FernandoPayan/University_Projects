/* File:    omp_trap_critical.c
 * Purpose: Estimate definite integral (or area under curve) using trapezoidal 
 *          rule. Each thread explicitly computes the integral
 *       over its assigned subinterval, a critical directive is used
 *       for the global sum. This version assumes that n is evenly divisible by the 
 *       number of threads.
 *
 * Input:   a, b, n
 * Output:  estimate of integral from a to b of f(x)=x*x
 *          using n trapezoids.
 *
 * Compile: gcc -g -Wall -fopenmp -o critical omp_trap_critical.c
 * Usage:   ./critical <number of threads>
 *
 * IT388 - Example: using omp critical.
 * Todo: Measure elapsed time, and print to screen
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);
double f(double x);    /* Function we're integrating */
void Trap(double a, double b, int n, double* global_result_p);

int main(int argc, char* argv[]) {
   double  global_result = 0.0;  /* Store result in global_result */
   double  a, b;                 /* Left and right endpoints      */
   int     n;                    /* Total number of trapezoids    */
   int     nThreads;
   double startTime, elapsed;
    
   if (argc != 2) Usage(argv[0]);
   
   nThreads = strtol(argv[1], NULL, 10);
   printf("Enter a, b, and n\n");
   scanf("%lf %lf %d", &a, &b, &n);
   if (n % nThreads != 0) Usage(argv[0]);
    
    /* 1. Mesure intial time */
    
#  pragma omp parallel num_threads(nThreads)
   Trap(a, b, n, &global_result);
    
    /* 2. Measure elapsed time */
    
   printf("With n = %d trapezoids, our estimate\n", n);
   printf("of the integral from %1.2f to %1.2f = %.6e\n",
      a, b, global_result);
    /* 3. Print "Critical approach" number of threads and elapsed time */

   return 0;
}  /* main */

/*------------------------------------------------------------------
 * Function:    Trap
 * Purpose:     Use trapezoidal rule to estimate definite integral
 * Input args:
 *    a: left endpoint
 *    b: right endpoint
 *    n: number of trapezoids
 * Output arg:
 *    integral:  estimate of integral from a to b of f(x)
 */
void Trap(double a, double b, int n, double* global_result_p) {
    double  h, x, my_result;
    double  local_a, local_b;
    int  i, local_n;
    int my_rank = omp_get_thread_num();
    int nThreads = omp_get_num_threads();
    
    h = (b-a)/n;
    local_n = n/nThreads;
    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;
    my_result = (f(local_a) + f(local_b))/2.0;
    for (i = 1; i <= local_n-1; i++) {
        x = local_a + i*h;
        my_result += f(x);
    }
    my_result = my_result*h;
    
// 1. Protect critical section
   # pragma omp critical
    *global_result_p += my_result;
    
}  /* Trap */

/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 */
void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   fprintf(stderr, "   number of trapezoids must be evenly divisible by\n");
   fprintf(stderr, "   number of threads\n");
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 */
double f(double x) {
   return x*x;
}  /* f */

