/* File:    omp_trap_for.c
 * Purpose: Estimate definite integral (or area under curve) using the
 *          trapezoidal rule.  This version uses a parallel for directive
 *
 * Input:   a, b, n
 * Output:  estimate of integral from a to b of f(x)=x*x
 *          using n trapezoids.
 *
 * Compile: gcc -g -Wall -fopenmp -o trapfor omp_trap_for.c
 * Usage:   ./trapfor <number of threads>
 *
 *
 IT388 -
 TODO: use parallel for and reduction clause to parallelize the Trap function to estimate the integral. Also measure time and print elapsed time
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);
double f(double x);    /* Function we're integrating */
double Trap(double a, double b, int n, int nThreads);

int main(int argc, char* argv[]) {
   double  global_result = 0.0;  /* Store result in global_result */
   double  a, b;                 /* Left and right endpoints      */
   int     n;                    /* Total number of trapezoids    */
   int     nThreads;

   if (argc != 2) Usage(argv[0]);
   nThreads = strtol(argv[1], NULL, 10);
   printf("Enter a, b, and n\n");
   scanf("%lf %lf %d", &a, &b, &n);

    /* Mesure intial time */
   double startTime = omp_get_wtime();

   global_result = Trap(a, b, n, nThreads); // Parallelize Trap function
    
    /* Measure elapsed time */
   double elapsed = omp_get_wtime() - startTime;
    
   printf("With n = %d trapezoids, our estimate\n", n);
   printf("of the integral from %1.2f to %1.2f = %.6f\n",
      a, b, global_result);
    /* Print "Parallel for approach" number of threads and elapsed time */
   printf("Parallel for approach %d: %f\n", nThreads, elapsed);
   return 0;
}  /* main */
/*------------------------------------------------------------------
 * Function:    Trap
 * Purpose:     Use trapezoidal rule to estimate definite integral
 */
double Trap(double a, double b, int n, int nThreads) {
    // TODO: Finish implenting the Trap rule, follow the sequential algorithm we discuss in class and use the parallel for pragma to parallelize this algorithm.
    double h = (b - a) / n;
    double approx = (f(a) + f(b)) / 2.0;
#pragma omp parallel for reduction(+: approx) num_threads(nThreads)
   for (int i = 1; i <= n - 1; i++)
   {
      double x_i = a + i * h;
      approx += f(x_i);
   }
   approx = h*approx;
    
   return approx;
    
}  /* Trap */

/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 */
void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 */
double f(double x) {
   return x*x;
}  /* f */

