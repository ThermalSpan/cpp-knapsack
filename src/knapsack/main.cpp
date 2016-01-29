//
// main.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/19/16.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "../utility/utilities.h"
#include "shared.h"
#include "branchbound.h"
#include "recurrence.h"
#include "dynamic.h"
#include "minknap.h"

using namespace std;

void printHelp () {
    cout << "Usage: knapsack [OPTIONS...] inputFile" << endl;
    cout << endl;
    cout << "Description:" << endl;
    cout << "\tOptimally solves the knapsack problem. " << endl;
    cout << endl;
    cout << "General Options" << endl;
    cout << "\t-h\t\tPrint the help / options menu and exit" << endl;
    cout << "\t-o\t\tSave solution to provided file name" << endl;
    cout << "\t--verbose\tPrint extra information about runtime information" << endl;
    cout << endl;
    cout << "Algorithm Options" << endl;
    cout << "\t--recurrence\tUse the naive recurrence" << endl;
    cout << "\t--branchbound\tUse a branch and bound algorithm" << endl;
    cout << "\t--dynamic\tUse naive dynamic programming approach" << endl;
    cout << "\t--minknap\tUse the minknap algorithm" << endl;
}

int main (int argc, char *argv[]) {
    // Print help menu?
    if (cmdOptionExists (argv, argv + argc, "-h")) {
        printHelp ();
        return 0;
    }

    // Check verbose flag
    bool verbose = false;
    if (cmdOptionExists (argv, argv + argc, "--verbose")) {
        verbose = true;
    }

    // Get input file name, open file stream, and make an int iterator
    string inputName;
    if (argc > 1) {
        inputName.assign (argv[argc - 1]); // outputName should be the last option supplied
        cout << "opening: " << inputName << endl;
    } else {
        cout << "Error: no outputName given" << endl;
        return 1;
    }
    ifstream inputFileStream (inputName);
    if (!inputFileStream.is_open ()) {
        cout << "Error: could no open the file stream" << endl;
        return 1;
    }
    istream_iterator <int> intIterator (inputFileStream);

    // Read in vector of items
    int itemCount = *intIterator;
    ++intIterator;
    ItemVec itemVec (itemCount);
    for (int i = 0; i < itemCount; i++) {
        intIterator++; // First number is an id
        itemVec[i].s_value = *intIterator;
        intIterator++;
        itemVec[i].s_weight = *intIterator;
        intIterator++;
        itemVec[i].s_ratio = (float) itemVec[i].s_value / (float) itemVec[i].s_weight;
    }
    int capacity = *intIterator;

    // Now decide which method to use and run!
    if (cmdOptionExists (argv, argv + argc, "--recurrence")) {
        recurrenceSolve (itemVec, capacity);
    } else if (cmdOptionExists (argv, argv + argc, "--branchbound")) {
        branchBoundSolve (itemVec, capacity);
    } else if (cmdOptionExists (argv, argv + argc, "--dynamic")) {
        dynamicSolve (itemVec, capacity);
    } else if (cmdOptionExists (argv, argv + argc, "--minknap")) {
        minKnapSolve (itemVec, capacity);
    }

    inputFileStream.close ();
    return 0;
}
