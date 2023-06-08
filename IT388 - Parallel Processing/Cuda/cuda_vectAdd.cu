/* FILE: cuda_vectAdd.cu
Compile and run in Expanse cluster
1) Load module:
	module load cuda
2) Compile
nvcc -o cuda_vectAdd cuda_vectAdd.cu

3) a) Submit job
	sbatch jobCuda.jb

Name: Fernando Payan
IT 388

TODO: Implement add vectors using cuda.
*/
#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<math.h>

/* Function that adds two vectors */
__global__ void addVectors(double *x, double *y, double*z, int n){
    //global thread ID
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    //make sure is not out of bounds
    if (index < n){
        z[index] = x[index] + y[index];
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
    int blockSize = 256;
    int numBlocks = ceil((double)n / blockSize);

    cudaMallocManaged(&x, n * sizeof(double));
    cudaMallocManaged(&y, n * sizeof(double));
    cudaMallocManaged(&z, n * sizeof(double));

    // generate vectors
    for (i=0;i<n;i++){
        x[i]=sin(i)*sin(i);
        y[i]=cos(i)*cos(i);
    }
    start = getTime();
    addVectors<<<numBlocks, blockSize>>>(x, y, z, n);
    cudaDeviceSynchronize();

    elapsed = getTime() - start;
    printf("\nN=%d; Elapsed time:%f\n",n,elapsed);
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
    cudaFree(x);
    cudaFree(y);
    cudaFree(z);

    return 0;
}  /* main */
