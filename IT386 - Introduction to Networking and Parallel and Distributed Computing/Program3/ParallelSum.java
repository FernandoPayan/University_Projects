/**  File: ParallelSum.java
 *  A team of threads adds up the numbers of an array
 * Name: Fernando Payan
 * Date: 05/02/2023
 * Activity 14
 * IT 386
  */
import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

public class ParallelSum {
    // shared variables
    static int nThreads, N;
    static int arrayA[];
    static long totalSum=0;

    public static void main(String[] args) throws InterruptedException {
        if (args.length > 0) {
            nThreads = Integer.parseInt(args[0]);
            N = Integer.parseInt(args[1]);
        } else {
            System.out.println("Usage: java className <number of Threads> < N > ");
            System.exit(1);
        }

        arrayA = new int[N];

        for (int i = 0; i < N; i++) {
            arrayA[i] = i + 1;
        }
        /* Main thread prints initial array */
        if (N < 20) {
            System.out.println(Thread.currentThread().getName() + ": " + Arrays.toString(arrayA));
        }

        /* Set the starting time */
        long start_time = java.lang.System.currentTimeMillis();

        /* Create array to hold team of threads */
        Thread[] workers = new Thread[nThreads];
        int work = N / nThreads; // amount of work each thread will do
        int remainder = N % nThreads;
        for (int i = 0; i < nThreads; i++) {
            int low = i * work;
            int high = (i + 1) * work;

            /* Calculate the work the last thread will work on */
            if (remainder != 0 && i == nThreads - 1)
            {
                high = N;
            }

            Runnable obj = new Worker(low, high);
            workers[i] = new Thread(obj);
            workers[i].start();
        }

        for (int i = 0; i < nThreads; i++) {
            workers[i].join();
        }

        /* Calculate the elapsed time */
        long end_time = java.lang.System.currentTimeMillis() - start_time;

        /* Print statement that prints array size N and number of threads */
        System.out.println("Array size N = " + N + " | Number of Threads = " + nThreads);

        System.out.println("SeqSum " +seqSum() + ", Parallel Sum " + totalSum);

        System.out.println("Elapsed time: " + end_time);


    } /* main */

    public static class Worker implements Runnable {

        private int low, high;
        private long localSum;

        ReentrantLock mutLock = new ReentrantLock();

        public Worker(int low, int high) {
            this.low = low;
            this.high = high;
        }

        public void run() {
            localSum = 0;
            for (int i = low; i < high; i++) {
                localSum += arrayA[i];
            }
            /* Implement the mutex lock to fix the race condition */
            mutLock.lock();
            try 
            {
                totalSum += localSum;
            } finally
            {
                mutLock.unlock();
            }
        }
    }

    public static long seqSum() {
        long sum = 0;
        for (int i = 0; i < N; i++) {
            sum += arrayA[i];
        }
        return sum;
    }

}
