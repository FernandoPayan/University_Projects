/*
 IT 388 - Parallel Recursive Fibonacci
*/
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void Usage(char *prog_name);
int fib(int n);

int main(int argc, char *argv[])
{
  int n, nThreads;
  int parallelResult;
  double start, elapsed;

  if (argc != 3)
    Usage(argv[0]);
  nThreads = strtol(argv[1], NULL, 10);
  n = strtol(argv[2], NULL, 10);

  omp_set_num_threads(nThreads);
  start = omp_get_wtime();
#pragma omp parallel shared(n)
  {
#pragma omp single
    parallelResult = fib(n);
  }
  elapsed = omp_get_wtime() - start;
  printf("Parallel: %d threads, elapsed: %lf sec\n", nThreads, elapsed);
  printf("fib(%d) = %d\n", n, parallelResult);

  return 0;
}

/*--------------------------------------------------------------------
 * Function:   Parallel Fibonacci
 */
int fib(int n)
{
  int x, y;
  if (n < 2)
    return n;
#pragma omp task shared(x) if (n > 20)
  x = fib(n - 1);
#pragma omp task shared(y) if (n > 20)
  y = fib(n - 2);
#pragma omp taskwait
  return x + y;
}

/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char *prog_name)
{

  fprintf(stderr, "usage: %s <# of threads> <N>\n", prog_name);
  exit(0);
} /* Usage */