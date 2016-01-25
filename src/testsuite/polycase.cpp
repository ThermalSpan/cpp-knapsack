//
// polycase.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/25/16
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "../utility/utilities.h"

using namespace std;

void printHelp () {
    cout << "Usage: polycase [OPTIONS...] directory" << endl;
    cout << endl;
    cout << "Description:" << endl;
    cout << "\tWraps the generator, builds a number of cases" << endl;
    cout << endl;
    cout << "General Options" << endl;
    cout << "\t-t\t\tProvide the number of test cases, defaulst to 10" << endl;
    cout << "\t-n\t\tProvide the number of items, defaults to 50" << endl;
    cout << "\t-r\t\tProvide the range for the weights, defaults to 1000" << endl;
    cout << "\t-c\t\tProvide the capacity of the knapsack, defaults to the range" << endl;
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

    // Get the user's test count
    int testCount = 10;
    char* testInput = getCmdOption (argv, argv + argc, "-t");
    if (testInput != nullptr) {
        testCount = atoi (testInput);
        if (testCount == 0) {
            cout << "Invalid test count option" << endl;
            return 1;
        }
    }

    string command ("./generator ");

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
    command += "-n ";
    command += to_string (itemCount) + " ";

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
    command += "-r ";
    command += to_string (range) + " ";

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
    command += "-c ";
    command += to_string (capacity) + " ";

    // Figure out what type of set we will generate
    if (cmdOptionExists (argv, argv + argc, "--uncor")) {
        command += "--uncor ";
    } else if (cmdOptionExists (argv, argv + argc, "--weakcor")) {
        command += "--weakcor ";
    } else if (cmdOptionExists (argv, argv + argc, "--strcor")) {
        command += "--strcor ";
    } else if (cmdOptionExists (argv, argv + argc, "--invstrcor")) {
        command += "--invstrcor ";
    } else if (cmdOptionExists (argv, argv + argc, "--almstrcor")) {
        command += "--almstrcor ";
    } else if (cmdOptionExists (argv, argv + argc, "--subsum")) {
        command += "--subsum ";
    } else {
        // Not the greatest, but wan't to leave the default case easy to modify
        command += "--uncor ";
    }

    // Get the director name
    string outputDirectory;
    if (argc > 1) {
        outputDirectory.assign (argv[argc - 1]); // outputDirectory should be the last option supplied
    } else {
        cout << "No outputDirectory given" << endl;
        return 1;
    }

    // Generate the test cases
    for (int i = 0; i < testCount; i++) {
        string caseCommand = command + "-s " + to_string (i) + " ";
        caseCommand += outputDirectory + "/case" + to_string (i) + ".txt";
        system (caseCommand.c_str ());
    }

    return 0;
}
