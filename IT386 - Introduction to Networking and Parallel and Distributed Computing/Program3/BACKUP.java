/**
 * Parallel Sort file
 * Author: Fernando Payan
*/
import java.util.Random;

public class ParallelSort {
    /* Shared Variables */
    static int arr[];

    public static void main(String[] args) throws Exception
    {
        /* Check if the user passed in the correct number of arguments */
        if (args.length != 1) 
        {
            System.err.println("Usage: java ParallelSort <array_size>");
            System.exit(1);
        }

        /* 1. Create the array */
        int N = Integer.parseInt(args[0]);
        arr = new int[N];
        int nThreads = 3;

        /* 2. Generate the array */
        fillArray(arr);

        /* 3. Main thread prints initial array if array length < 20 */
        if (N < 20)
        {
            System.out.println("Before sorting: ");
            printArray(arr);
        }

        /* 4. Split the initial array into two arrays */
        int[] arr1 = new int [N / 2];
        int[] arr2 = new int [ N - (N / 2)];

        /* 4a. Measure the start time */
        long start = java.lang.System.currentTimeMillis();

        /* 4b. Populate the arrays */
        int index = 0;
        for (int i = 0; i < arr.length; i++)
        {
            if (i < arr1.length)
                arr1[i] = arr[i];
            else
            {
                arr2[index] = arr[i];
                index++;
            }
        }

        /* 5. Create array to hold the team of threads */
        Runnable obj;
        Thread[] workers = new Thread[nThreads];

        for (int i = 0; i < nThreads - 1; i++)
        {
            /* 5a. Tells which thread works on which array */
            if (i % 2 != 0)
                obj = new Worker(arr1);
            else
                obj = new Worker(arr2);
            
            /* 5b. Execute the thread */
            workers[i] = new Thread(obj);
            workers[i].start();
        }

        /* 5c. Join the threads */
        for (int j = 0; j < nThreads - 1; j++)
            workers[j].join();

        /* 6. Have the third thread merge to two arrays */
        obj = new Worker(arr1, arr2);
        workers[2] = new Thread(obj);
        workers[2].start();
        workers[2].join();

        /* 7. Calculate the end time */
        long end = java.lang.System.currentTimeMillis() - start;
        /* Print the sorted array */
        if (N < 20)
        {
            System.out.println("\nAfter sorting: ");
            printArray(arr);
            System.out.println("\nElapsed Time: " + end);
        }

        System.out.println("\nIs the array sorted correctly?: " + checkArray(arr));
        
    }

    /* Worker class that implements Runnable */
    public static class Worker implements Runnable
    {
        private int[] array, array2;
        
        /* Constructor for Thread 1 and Thread 2 */
        public Worker(int[] array)
        {
            this.array = array;
        }

        /* Constructor for Thread 3 */
        public Worker(int[] arr1, int[] arr2)
        {
            this.array = arr1;
            this.array2 = arr2;

            System.out.println("\nArray 1 is:");
            printArray(array);
            System.out.println("\nArray 2 is:");
            printArray(array2);
        }

        /* Thread Work */
        @Override
        public void run()
        {   
            /* Work for Thread 1 and Thread 2 */
            if (Thread.currentThread().getId() < 22)
            {
                /* Perform Insertion Sort on the array */
                for(int i = 0; i < array.length; i++)
                {
                    int j = i;

                    while(j > 0 && array[j-1] > array[j])
                    {
                        int temp = array[j-1];
                        array[j-1] = array[j];
                        array[j] = temp;
                        j--;
                    }
                }
            }
            /* Work for Thread 3 */
            else
            {
                int firstIndex = 0;
                int secondIndex = 0;
                int curIndex = 0;

                /* Compare between both arrays and add the min value to the merged array */
                while ( (firstIndex < array.length) && (secondIndex < array2.length) )
                {
                    if (array[firstIndex] <= array2[secondIndex])
                    {
                        arr[curIndex] = array[firstIndex];

                        /* Move to the next index for the first array */
                        firstIndex++;
                    }
                    else
                    {
                        arr[curIndex] = array2[secondIndex];

                        /* Move to the next index for the second array */
                        secondIndex++;
                    }

                    /* Move to the next index for our merged array */
                    curIndex++;
                }

                /* Finish up the rest of the first array, if needed */
                while (firstIndex < array.length)
                {
                    arr[curIndex] = array2[firstIndex];
                    firstIndex++;
                    curIndex++;
                }

                /* Finish up the rest of the second array, if needed */
                while (secondIndex < array2.length)
                {
                    arr[curIndex] = array2[secondIndex];
                    secondIndex++;
                    curIndex++;
                }
            }
        }
    }

    public static class WorkerMerger implements Runnable
    {
        
    }

    /* Helper method to generate the random array of integers */
    private static void fillArray(int[] arr)
    {
        Random rand = new Random();

        for(int i=0;i<arr.length;i++)
            arr[i] = rand.nextInt( (100 - 0 ) + 1)+ 0;
    }

    /* Helper method to check if the final array is sorted correctly */
    private static boolean checkArray(int[] arr)
    {
        boolean isSorted = true;

        for (int i = 1; i < arr.length - 1; i++)
        {
            if (arr[i - 1] > arr[i])
                isSorted = false;
        }

        return isSorted;
    }

    /* Helper method to print the array to the screen */
    private static void printArray(int[] arr)
    {
        for (int i = 0; i < arr.length; i++)
            System.out.print("[" + arr[i] + "] ");
    }
}
