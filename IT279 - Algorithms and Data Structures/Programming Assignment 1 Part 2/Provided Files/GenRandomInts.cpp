// write a number of random integers to standard output
// Mary Elaine Califf
// 1/8/20

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " <number of values> <maximum value> <optional random seed (not zero)>" << endl;
        exit(1);
    }
    int numValues = atoi(argv[1]); // we're not worrying about safety here
    int maxValue = atoi(argv[2]);
    int randomSeed=0;

    // If a random seed is provided, accept it.
    if (argc > 3){
        randomSeed = atoi(argv[3]);
    }

    //No numbers are truly random, so the values are algorithmically generated based off a provided seed value.
    // If we want to use a known random number sequence, we can provide a seed value.
    // If we want to use an arbitrary number sequence, we can give it the current time as a seed instead.
    // Seed values are set through a call to srand(int).
    if (randomSeed)
    {
        // If we are provided with a random seed,
        // use that value instead of the compile time value.
        srand(randomSeed);
    }
    else
    {
        // If we are not provided a seed (or are provided 0),
        // seed our random number generator with current time
        srand(time(nullptr));
    }

    for (int i = 0; i < numValues; i++)
    {
        cout << rand() % maxValue + 1 << '\n';
    }
}