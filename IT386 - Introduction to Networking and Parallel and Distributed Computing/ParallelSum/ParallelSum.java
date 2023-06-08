/**  File: ParallelSum.java
 *  A team of threads adds up the numbers of an array
 * Name:
 * Date:
 * Compile with: javac ParallelSum
 * Run with: java ParallelSum <#threads> <Array Dimension N>
 *
 * ToDo:  Divide the work among the threads
 * IT 386
  */
import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

public class ParallelSum {
    // shared variables
    static int nThreads, N;
    static int arrayA[];
    static int totalSum=0;
    private int counter = 0;
    public static void main(String[] args) throws InterruptedException {
        /*Get user input from command line*/
        if (args.length > 0) {
            nThreads = Integer.parseInt(args[0]);
            N = Integer.parseInt(args[1]);
        }else{
            System.out.println("Usage: java className <number of Threads> < N > ");
            System.exit(1);
        }
        /*Generate array*/
        arrayA = new int[N];
        for ( int i = 0; i<N;i++){
            arrayA[i] = i+1;
        }
        /* Main thread prints initial array if array lenght < 20*/
        if (N<20){
            System.out.println(Thread.currentThread().getName() +": "
            + Arrays.toString(arrayA));
        }
        /* Create array to hold team of threads */
        Thread[] workers = new Thread[nThreads];
        /* 1. Amount of work each thread will do */
        int work = N/nThreads;
        for (int i = 0; i<nThreads;i++){
          /* 2. Starting and ending index each thread will work on */
            int low =work*i;
            int high = low + work;
            Runnable obj = new Worker(low,high);
            workers[i] = new Thread(obj);
            workers[i].start();
        }
        for (int i = 0; i<nThreads; i++) {
            workers[i].join();
        }
        System.out.println(Thread.currentThread().getName()+": Sequential Sum "
         + seqSum() + ", Parallel Sum " + totalSum);
    } /*main*/

  /** Worker class that implements Runnable */
    public static class Worker implements Runnable {
        private int low, high;
        public Worker(int low, int high){
            this.low = low;
            this.high = high;
        }
        /* Thread work */
        @Override
        public void run(){
            int localSum = 0;
            for (int i = low; i< high; i++){
                localSum += arrayA[i];
            }
            //totalSum += localSum;
            increment(localSum);
        }

        private synchronized void increment(int localSum)
        {
            totalSum += localSum;
        }
    }
/*Sequential Sum */
    public static int seqSum(){
        int sum = 0;
        for (int i = 0; i<N; i++ ){
            sum += arrayA[i];
        }
        return sum;
    }

}
