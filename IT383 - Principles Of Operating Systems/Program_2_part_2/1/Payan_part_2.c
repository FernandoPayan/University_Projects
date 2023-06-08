/* author: fpayan
** A parallel program that finds the median and mode given a large array of integers
** Compile: gcc -o part_2 Payan_part_2.c -lm -pthread
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* Used for threads */
#include <math.h> /* Used to round */
#include <limits.h> /* Used for final sort */

void findMedian(int* array); /* Find the median of the values */
void findMode(int* array); /* Find the mode of the values */
int comparator(const void *p1, const void *p2); /* Comparator function used for quicksort */
void sortArray(void *arg); /* Method each thread will run to apply quicksort to their portion of the array */

/* Global Variables */
int *values; /* Array to store the values in the text file */
int numLines; /* Tells us how many numbers (or lines) are in the text file */
int num_threads; /* Stores the number of threads we're working with */

int main(int argc, char* argv[])
{
    /* Check if the user passed the correct number of parameters*/
    if (argc != 3)
    {
        fprintf(stderr, "Error: Incorrect number of arguments. Usage: %s num_threads inputFile.txt\n", argv[0]);
        exit(1);
    }

    /* Set the number of threads we're working with */
    num_threads = atoi(argv[1]);

    /* Input file */
    FILE *input_file = fopen(argv[2], "r");

    /* If the file doesn't exist, exit the program */
    if (input_file == NULL)
    {
        fprintf(stderr, "File doesn't exist. Please make sure to execute program in the following manner: ./mt_medianmode_finder number_of_childthreads inputFile.txt\n");
        exit(1);
    }

    /* Read each line in the file */
    char buffer[1024];
    int index = 0; /* Used to keep track of which index we need to put the value in */

    /* While loop to read in the values and store them into an array of integers */
    while (fgets(buffer, sizeof(buffer), input_file))
    {
        /* Check if we're reading in the first line*/
        if (strstr(buffer, "% "))
        {
            /* Parse the string so we only get the number and store it into numLines */
            sscanf(buffer, "%% %d", &numLines);

            /* Set the size of the array based on how many values we're reading */
            values = malloc(numLines * sizeof(int)); 
        }
        else
        {
            /* Convert the string to an integer and store it into our array */
            values[index] = atoi(buffer);

            /* Move to the next index */
            index++;
        }
    }

    /* Parallel */
    pthread_t *threads = (pthread_t*) malloc (num_threads * sizeof(pthread_t));
    int work = round((double) numLines / (double) num_threads);
        
    /* Call the threads to work on the subarrays */
    for (int i = 0; i < num_threads; i++)
        pthread_create(&threads[i], NULL, sortArray, (void*) i);
    
    /* Join the threads together */
    for (int j = 0; j < num_threads; j++)
        pthread_join(threads[j], NULL);

    /* Now we need to sort everything into a second array*/

    /* Our second array that stores the sorted values */
    int* sortedArr = malloc(numLines * sizeof(int));
    
    /* Stores the indexes we are looking at */
    int* temp = malloc(num_threads * sizeof(int));

    /* Calculate the indexes we will need to look at*/
    int start_index = 0;
    for (int i = 0; i < num_threads; i++)
    {
        /* Set the end index */
        int end_index = start_index + work - 1;

        /* Remainder check for last thread */
        if (i == num_threads - 1)
            end_index = numLines - 1;
        
        /* Store the index to our temp array */
        temp[i] = start_index;

        /* Move to the next index */
        start_index = end_index + 1;
    }

    /* Sort the array */
    for (int i = 0; i < numLines; i++)
    {
        int minVal = values[temp[0]];
        int curIndex = temp[0];
        int tempIndex = 0;

        /* Find the minVal at the thread's index */
        for (int j = 1; j < num_threads; j++)
        {
            /* Check if it's less than the current min val */
            if (values[temp[j]] <= minVal)
            {
                minVal = values[temp[j]];
                curIndex = temp[j];
                tempIndex = j;
            }
        }

        values[curIndex] = INT_MAX; /* This value is already inserted so we do not care for it anymore. Making it the max value. */
        sortedArr[i] = minVal; /* Insert the min val into the array */

        /* Increment to the next index */
        if (curIndex != numLines - 1)
            temp[tempIndex] = curIndex + 1;
    }

    /* Calcualate the median and mode */
    findMedian(sortedArr);

    findMode(sortedArr);

    /* Free the arrays */
    free(values);
    free(temp);
    free(sortedArr);
    free(threads);
}


void findMedian(int* array)
{
    /* Get the middle index of the file */
    int median = round(numLines / 2.0) - 1;

    /* If the number of elements in the file is odd, then the median is the number of elements / 2 */
    if (numLines % 2 != 0)
        fprintf(stderr, "The median is %d\n", array[median]);
    else /* If the number of elements in the file is even, return the average of the two elements in the middle */
    {
        median = (array[median] + array[median + 1]) / 2;
        fprintf(stderr, "The median is %d\n", median);
    }
}

void findMode(int* array)
{
    /* Variables used to calculate the mode */
    int mode = array[0];
    int curVal = array[0];
    int modeCount = 1;
    int localCount = 1;

    // Iterate through the array
    for (int i = 1; i < numLines; i++)
    {
        /* Increment count if same number */
        if (array[i] == curVal)
            localCount++;
        else
        {
            /* Check if localCount has a higher count than the modeCount */
            if (localCount > modeCount)
            {
                modeCount = localCount;
                mode = curVal;
            }

            /* Reset the current value and count */
            curVal = array[i];
            localCount = 1;
        }
    }

    /* Check if localCount has a higher count than the modeCount */
    if (localCount > modeCount)
        mode = curVal;

    fprintf(stderr, "The mode is %d and it appeared %d times\n", mode, modeCount);
}


int comparator(const void *p1, const void *p2)
{
    return (*(int*)p1 - *(int*)p2);
}

void sortArray(void* arg)
{
    int work = round((double) numLines / (double) num_threads); /* Calculate the work */
    int thread_id = (int) arg; /* Get the rank of the thread*/

    int start_index = work * thread_id; /* Starting Index for the thread to work on */
    int last_index = start_index + work - 1; /* Last index for the thread to work up to */

    /* If statement to check if there's a remainder
    ** In case the work was not evenly divisible, we need to consider the work that the 
    ** last thread will work on
    */
    if (thread_id == num_threads - 1) 
        last_index = numLines - 1;

    /* Perform QuickSort on the subarray section */
    qsort(&values[start_index], last_index - start_index + 1, sizeof(int), comparator);
}