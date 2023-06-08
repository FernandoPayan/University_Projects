/* File:vectAdd.c
 Compile:
    gcc -o add vectAdd.c -lm
 Run:
    ./add <vector dimension>
 
 */

#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<math.h>

/* Function that adds two vectors */
void addVectors(double *x, double *y, double*z, int n){
    int j=0;
    for (j=0;j<n;j++){
        z[j] = x[j] + y[j];
    }
}

/*--------------------------------
 Function to Print Vectors
 --------------------------------*/
void printVectors(double *a, double *b, double*c, int n) {
    int k = 0;
    for(k=0;k<n;k++)
    printf("\n %f + %f  = %f",  a[k] , b[k], c[k]);
}

/*--------------------------------
 Function to measure run time
 --------------------------------*/
double getTime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec/1000000.0;
    
}

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
    
    double start, elapsed;
    double* z; double* x; double* y;
    int n;
    int i;
    int numBlocks = 2;
    int blockSize = 4;
    n=atoi(argv[1]); // get vector dimension
    cudaMallocManaged(&x, n*sizeof(double));
    cudaMallocManaged(&y, n*sizeof(double));
    cudaMallocManaged(&z, n*sizeof(double));
    
    // generate vectors
    for (i=0;i<n;i++){
        x[i]=sin(i)*sin(i);
        y[i]=cos(i)*cos(i);
    }
    start = getTime();
    addVectors<<<numBlocks,blockSize>>>(x,y,z,n);
    cudaDeviceSynchronize();
    elapsed = getTime() - start;
    printf("\nN=%d; Elapsed time:%f\nthe numBlocks is %d and the blockSize is %d",n,elapsed, numBlocks, blockSize);
    // Print vectors
    if (n<21){
        printVectors(x, y, z,  n);
    }
    // Check if vector z is correct, this should equal 1
    double sum = 0;
    for(i=0; i<n; i++){
        sum += z[i];
    }
    printf("final result: %f\n", sum/n);
    cudaFree(x); cudaFree(y); cudaFree(z);
    return 0;
}  /* main */



