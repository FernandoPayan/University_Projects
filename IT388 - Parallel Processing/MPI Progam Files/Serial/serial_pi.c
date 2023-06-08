/******************************************************************************
 * FILE: serial_pi
 * DESCRIPTION:nSerial Example - Compute pi
 *  - Using trapezoid rule
 *      Compile: gcc -o serialPi serial_pi.c
 *          run: ./serialPi 
 ****************************************************************************/
#include <stdio.h>
#include <math.h>
#define PI25DT 3.141592653589793238462643

/* Function we're integrating */
double f(double xi);

int main (int argc, char *argv[])
{
    int N = 10000; // Number of trapezoids we are using
    double x=0.0,integral=0.0, a=0.0, b=1.0;
    double dx=(b-a)/N;
    double pi;
    
    integral = (f(a)+f(b))/2;
    for (int i=1; i<N; i++){
        x=a+dx*i;
        integral = integral + f(x);
    }
    pi=4*dx*integral;
   
    printf("With n = %d trapezoids, our estimate\n", N);
    printf("Serial: pi~= %.15lf \n",pi);
    printf(" Error : %.15lf\n", fabs(pi-PI25DT));
}   /* end of main */
/*------------------------------------------------------------------
 * Function:  Compute value of function to be integrated
 */
double f(double xi){
    return sqrt(1.0-xi*xi);
}
