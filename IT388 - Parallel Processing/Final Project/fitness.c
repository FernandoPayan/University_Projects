// IT 388, Conversion of 8-queen-fitness program into c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Boolean Library
#include <time.h> // For Random Values
#include <string.h>

const int populationSize = 500;
int codeLength;
char* code;



int* geneticAlgorithm(char population[populationSize][codeLength]);
int fitness(char initial[]);
char * reproduce(char x[], char y[]);
char* mutate(char child[]);
void assignNewPopulationAtIndex(char population[populationSize][codeLength], char crackedCodeNumber, int position);
void generateEntirelyNewPopulation(char population[populationSize][codeLength]);


int main(int argc, char argv[])
{
    srand((unsigned)(time(0)));

    int generation = 0; 
    

    /*if (argc != 2)
    {
        printf("Usage incorrect");
        exit(1);
    }*/
    //int populationSize = argv[2];
    code = (char*)malloc(sizeof(char) * populationSize);


    printf("Please enter the length of the code you want us to break: ");
    scanf("%d", &codeLength);
    for (int i = 0; i < codeLength; i++)
    {
        printf("Please enter in each individual number for the code: ");
        scanf("%d", &code[i]);

    }
    char population[populationSize][codeLength];

    for (int i = 0; i < codeLength; i++)
    {
        printf("%d\n", code[i]);
    }

    /*
        MPI Portion incoming
    */
    for (int row = 0; row < populationSize; row++)
    {
        for (int column = 0; column < codeLength; column++)
        {
            population[row][column] = ((rand() % 9) + 1) % 10;
        }

    }
    int *p;

    p = geneticAlgorithm(population);
    // OPEN MPI Incoming
    printf("Cracked code\n");

    for (int i = 0; i < codeLength; i++)
    {
        printf("%d\n", *(p + i));
    }
}

int* geneticAlgorithm(char population[populationSize][codeLength])
{

    char *child = malloc(codeLength);

    bool flag = true;
    srand(time(NULL));



    while (flag)
    {
        int numberOfCrackedCodes = 0;
        int numberOfTries = 0;

        for (int i = 0; i < codeLength; i++)
        {
            char x[codeLength];
            memcpy(x, population[rand() % populationSize], sizeof(x));

            char y[codeLength];
            memcpy(y, population[rand() % populationSize], sizeof(y));


            memcpy(child, reproduce(x, y), sizeof(reproduce(x, y)));

            float mutate_chance = (float)rand()/RAND_MAX;

            if (mutate_chance > 0.998)
            {
                memcpy(child, mutate(child), sizeof(mutate(child)));
            }

            if (fitness(child) == codeLength)
            {
                flag = false;
                break;
            } else {
                if (fitness(child) != numberOfCrackedCodes)
                {
                    for (int i = 0; i < codeLength; i++)
                    {
                        char g = child[i];
                        char a = code[i];
                        if (a == g)
                        {
                            assignNewPopulationAtIndex(population, child[i], i);        
                            numberOfCrackedCodes++;                   
                        }   
                    }
                } else {
                    if (numberOfTries > 2000)
                    {
                        generateEntirelyNewPopulation(population);
                        numberOfCrackedCodes = 0;
                        numberOfTries = -1;
                    }

                    numberOfTries++;
                    
                }
            }
        }
    }

    int *crackedCode = malloc(codeLength);

    for (int i = 0; i < codeLength; i++)
    {
        crackedCode[i] = (int)child[i];
    }


    return crackedCode;
}

int fitness(char guess[])
{
    int fitness = 0;
    char g;
    char a;

    for (int i = 0; i < codeLength; i++)
    {
        g = guess[i];
        a =  code[i];
        if (g == a) 
        {
            fitness += 1;
        }   
    }

    return fitness;

}

char* reproduce(char x[], char y[]) {
    int c = rand() % populationSize;
    
    static char child[sizeof populationSize];

    for (int i = 0; i <= c; i++)
    {
        child[i] = x[i];
    }

    for (int j = c + 1; j < populationSize; j++)
    {
        child[j] = y[j];
    }

    return child;
}

char* mutate(char child[])
{ 
    
    int index = child[rand() % (populationSize + 1 -0) + 0] % 10;

    child[index] = rand() % (populationSize + 1 - 0) + 0;

    return child;
}

void assignNewPopulationAtIndex(char population[populationSize][codeLength], char crackedCodeNumber, int position)
{
    char newPopulation[populationSize][codeLength];
    memcpy(newPopulation, population, sizeof(newPopulation));
    for (int row = 0; row < populationSize; row++)
    {
        for (int column = 0; column < codeLength; column++)
        {
            if (column == position)
            {
                newPopulation[row][column] = crackedCodeNumber;
            }                 
        }
    }
    memcpy(population, newPopulation, populationSize);
}

void generateEntirelyNewPopulation(char population[populationSize][codeLength])
{
    for (int row = 0; row < populationSize; row++)
    {
        for (int column = 0; column < codeLength; column++)
        {
            population[row][column] = ((rand() % 9) + 1) % 10;
        }

    }

}