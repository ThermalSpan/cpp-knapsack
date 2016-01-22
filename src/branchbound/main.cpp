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
#include "../utility/knapsack.h"

using namespace std;

void printHelp () {
    cout << "Usage: branchbound [OPTIONS...] inputFile" << endl;
    cout << endl;
    cout << "Description:" << endl;
    cout << "\tOptimally solves the knapsack problem with a branch and bound algorithm." << endl;
    cout << endl;
    cout << "General Options" << endl;
    cout << "\t-h\t\tPrint the help / options menu and exit" << endl;
    cout << "\t-o\t\tSave solution to provided file name" << endl;
    cout << "\t--verbose\tPrint extra information about runtime information" << endl;
}

int main (int argc, char* argv[]) {
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
        cout << "branchbound: opening: " << inputName << endl;
    } else {
        cout << "branchbound: no outputName given" << endl;
        return 1;
    }
    ifstream inputFileStream (inputName);
    if (!inputFileStream.is_open ()) {
        cout << "branchbound: There was an error opening the file stream" << endl;
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

    // Sort
    sortItemVecByRatio (itemVec);

    // Print
    printItemVec (itemVec);


    inputFileStream.close ();
    return 0;
}
