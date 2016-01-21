//
// main.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/19/16.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "../utility/utilities.h"
#include "genFunctions.h"

using namespace std;

void printHelp () {
    cout << "Usage: generate [OPTIONS...] outputName" << endl;
    cout << endl;
    cout << "Description:" << endl;
    cout << "\tGenerate a set of n weights within range, and correlate weights as specified" << endl;
    cout << endl;
    cout << "General Options" << endl;
    cout << "\t-n\t\tProvide the number of items, defaults to 50" << endl;
    cout << "\t-r\t\tProvide the range for the weights, defaults to 1000" << endl;
    cout << "\t-c\t\tProvide the capacity of the knapsack, defaults to the range" << endl;
    cout << "\t-s\t\tProvide an integer seed for the random number generator" << endl;
    cout << endl;
    cout << "Attribute Correlation Options" << endl;
    cout << "\t--uncor\tUncorrelated attributes" << endl;
    cout << "\t--weakcor\tWeakly correlated attributes" << endl;
    cout << "\t--strcor\tValue is equal to weight, with positive fixed charge" << endl;
    cout << "\t--invstrcor\tValue is equal to weight, with a negative fixed charge" << endl;
    cout << "\t--subsum\tValue is equal to weight" << endl;
    cout << "\t--almstrcor\tApproximately strongly correlated attributes" << endl;
}

int main (int argc, char* argv[]) {
    // Print help menu?
    if (cmdOptionExists (argv, argv + argc, "-h")) {
        printHelp ();
        return 0;
    }

    // Get the user's item count
    int itemCount = 50;
    char* countInput = getCmdOption (argv, argv + argc, "-n");
    if (countInput != nullptr) {
        itemCount = atoi (countInput);
        if (itemCount == 0) {
            cout << "Invalid item count option" << endl;
            return 1;
        }
    }

    // Get the user's range
    int range = 100;
    char* rangeInput = getCmdOption (argv, argv + argc, "-r");
    if (rangeInput != nullptr) {
        range = atoi (rangeInput);
        if (range == 0) {
            cout << "Invalid range option" << endl;
            return 1;
        }
    }

    // Get the user's capacity
    int capacity = range;
    char* capacityInput = getCmdOption (argv, argv + argc, "-c");
    if (capacityInput != nullptr) {
        capacity = atoi (capacityInput);
        if (capacity == 0) {
            cout << "Invalid capacity option" << endl;
            return 1;
        }
    }

    // Get the user's seed number
    int seed = time (nullptr);
    char* seedInput = getCmdOption (argv, argv + argc, "-s");
    if (seedInput != nullptr) {
        seed = atoi (seedInput);
        cout << "Seed used: " << seed << endl;
    }
    srand (seed);

    // Open output file stream
    string outputName;
    if (argc > 1) {
        outputName.assign (argv[argc - 1]); // outputName should be the last option supplied
    } else {
        cout << "No outputName given" << endl;
        return 1;
    }
    ofstream outputFile (outputName);
    if (!outputFile.is_open ()) {
        cout << "There was an error opening the output file stream" << endl;
        return 1;
    }

    // Write out the item count
    outputFile << itemCount << endl;

    // Figure out what type of set we will generate
    if (cmdOptionExists (argv, argv + argc, "--uncor")) {
        genUnCor (itemCount, range, outputFile);
    } else if (cmdOptionExists (argv, argv + argc, "--weakcor")) {
        genWeakCor (itemCount, range, outputFile);
    } else if (cmdOptionExists (argv, argv + argc, "--strcor")) {
        genStrCor (itemCount, range, outputFile);
    } else if (cmdOptionExists (argv, argv + argc, "--invstrcor")) {
        genInvStrCor (itemCount, range, outputFile);
    } else if (cmdOptionExists (argv, argv + argc, "--almstrcor")) {
        genAlmStrCor (itemCount, range, outputFile);
    } else if (cmdOptionExists (argv, argv + argc, "--subsum")) {
        genSubSum (itemCount, range, outputFile);
    } else {
        // Not the greatest, but wan't to leave the default case easy to modify
        genUnCor (itemCount, range, outputFile);
    }

    // Write out the capacity and close
    outputFile << capacity << endl;
    if (outputFile.is_open ()) {
        outputFile.close ();
    }
    return 0;
}
