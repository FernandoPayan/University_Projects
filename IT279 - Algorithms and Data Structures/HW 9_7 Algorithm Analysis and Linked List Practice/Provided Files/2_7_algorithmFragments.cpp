//Nick Dunne IT279 S2021
//Algorithms in exercise 2.7
//Data Structures & Algorithm Analysis in C++, Weiss
#include <iostream>
using namespace std;


//The six different algorithms that are being evaluated
int alg1(int n);
int alg2(int n);
int alg3(int n);
int alg4(int n);
int alg5(int n);
int alg6(int n);


int main(int argc, char* argv[]){
    //Validate command line arguments
    if (argc != 3){
        cerr << "Correct Usage: " << argv[0] << "<algorithm selection [1-6]> <n value>" << endl;
        exit(1);
    }

    int algChoice = atoi(argv[1]);
    int n = atoi(argv[2]);
    int result = 0;

    switch (algChoice){
        case 1:
            result = alg1(n);
            break;
        case 2:
            result = alg2(n);
            break;
        case 3:
            result = alg3(n);
            break;
        case 4:
            result = alg4(n);
            break;
        case 5:
            result = alg5(n);
            break;
        case 6:
            result = alg6(n);
            break;
    }

    cout << "Algorithm: " << algChoice
         << "\n  N: " << n
         << "\n  Sum: " << result
         << endl;
    return 0;
}

int alg1(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i )
        ++sum;
    return sum;
}

int alg2(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i )
        for(int j = 0; j < n; ++j )
            ++sum;
    return sum;
}

int alg3(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i )
        for(int j = 0; j < n * n; ++j ) 
            ++sum;
    return sum;
}

int alg4(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i )
        for(int j = 0; j < i; ++j )
        ++sum;
    return sum;
}

int alg5(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i )
        for(int j = 0; j < i*i; ++j )
            for(int k = 0; k < j; ++k )
                ++sum;
    return sum;
}

int alg6(int n){
    int sum = 0;
    for(int i = 1; i < n; ++i )
        for(int j = 1; j < i*i; ++j )
            if (j % i == 0)
                for(int k = 0; k < j; ++k )
                    ++sum;
    return sum;
}