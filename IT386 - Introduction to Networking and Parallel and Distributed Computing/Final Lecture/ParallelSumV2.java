
/**  File: ParallelSum.java
 *  A team of threads adds up the numbers of an array
 *    Solution-V2 activity 14
* IT 386 - Spring 2023
  */
import java.util.Arrays;
import java.util.concurrent.locks.ReentrantLock;
import java.lang.System;

public class ParallelSumV2 {
    // shared variables
    static int nThreads, N;
    static int arrayA[];
    static long totalSum = 0;

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
        /* Measure initial time */
        long startTime = System.currentTimeMillis();
        /* Create array to hold team of threads */
        Thread[] workers = new Thread[nThreads];
        int work = N / nThreads; // amount of work each thread will do
        int remainder = N % nThreads;
        int low, high;
        for (int i = 0; i < nThreads; i++) {
            low = i * work;
            high = (i + 1) * work;
            // Option 1: Remainder goes to last thread
            if (remainder != 0 && i == nThreads - 1) {
                high = high + remainder;
            }
            Runnable obj = new Worker(low, high);
            workers[i] = new Thread(obj);
            workers[i].start();
        }
        for (int i = 0; i < nThreads; i++) {
            workers[i].join();
        }
        /* Measure elapsed time: start - current */
        long elapsed = System.currentTimeMillis() - startTime;

        /* Print Array size, number of threads, elapsed time */
        System.out.println("N=" + N + ", # threads = " + nThreads + ", elapsed time = " + elapsed + " msec");
        // System.out.println(Thread.currentThread().getName() + ": Sequential Sum " +
        // seqSum() + ", Parallel Sum " + totalSum);
    } /* main */

    public static class Worker implements Runnable {
        static ReentrantLock mutex = new ReentrantLock();
        private int low, high;

        public Worker(int low, int high) {
            this.low = low;
            this.high = high;
        }

        public void run() {
            mutex.lock();
            try {
                for (int i = low; i < high; i++) {
                    totalSum += arrayA[i];
                }
            } finally {
                mutex.unlock();
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
