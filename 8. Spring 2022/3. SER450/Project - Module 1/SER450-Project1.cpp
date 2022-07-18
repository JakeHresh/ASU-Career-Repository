/*
    This file contains an implementation of the Sieve of Eratosthenes method of
    calculating the first X prime numbers. This calculation is timed.

    To run, first compile the cpp file.
    e.g. g++ SER450-Project1.cpp
    This will result in an executable called a.exe. Run this executable while passing
    in an integer, which will represent the upper bound that the sieve will work on.
    e.g. a.exe 100000
*/

#include <string.h>
#include <iostream>
#include <tgmath.h>
#include <chrono>
using namespace std;

// Below code for the function runEratosthenesSieve from the following site:
// https://www.algolist.net/Algorithms/Number_theoretic/Sieve_of_Eratosthenes

void runEratosthenesSieve(int upperBound) {

    int upperBoundSquareRoot = (int)sqrt((double)upperBound);

    bool *isComposite = new bool[upperBound + 1];

    memset(isComposite, 0, sizeof(bool) * (upperBound + 1));
    // Beginning to track the time it takes to calculate primes.
    auto begin = chrono::high_resolution_clock::now();
    for (int m = 2; m <= upperBoundSquareRoot; m++) {
        if (!isComposite[m]) {
            // The printing has been commented out to avoid unnecessary overhead.
            //cout << m << " ";
            for (int k = m * m; k <= upperBound; k += m)
                isComposite[k] = true;
        }
    }
    // Time tracked after prime calculation.
    auto end = chrono::high_resolution_clock::now();
    // Finding the difference between times to determine duration of time elapsed.
    chrono::duration<float> duration = end - begin;
    cout << duration.count() << endl;
    // The below loop was commented out since there are no calculations happening.
    /*
    for (int m = upperBoundSquareRoot; m <= upperBound; m++)
        if (!isComposite[m])
            cout << m << " ";
    */
    delete [] isComposite;
}

// The below function is the main method. When running the program,
// simply pass in an integer number. This will represent the upper bound,
// that the sieve will run on.
// e.g. SER450-Project1.exe 100000

int main(int argc, char *argv[]) {
    cout << "---------- WELCOME TO ERATOSTHENES SIEVE BENCHMARKING! ----------\n";
    cout << "------------- Jacob Hreshchyshyn SER450 - Project 1 -------------\n\n";
    int num = stoi(argv[1]);
    runEratosthenesSieve(num);
    return 0;
}