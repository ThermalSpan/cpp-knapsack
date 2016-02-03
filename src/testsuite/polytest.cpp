//
// polytest.cpp
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
    cout << "Usage: polytest [OPTIONS...] testDirectory" << endl;
    cout << endl;
    cout << "Description:" << endl;
    cout << "\tRuns the knapsack solver on a directory of tests" << endl;
    cout << endl;
    cout << "General Options" << endl;
    cout << "\t-t\t\tProvide the number of test cases, defaults to 10" << endl;
    cout << endl;
    cout << "Algorithm Options" << endl;
    cout << "\t--recurrence\tUse a naive recurrence to solve" << endl;
    cout << "\t--branchbound\tUse a naive branch and bound algorithm" << endl;
    cout << "\t--dynamic\tUse a dynamic programming algorithm" << endl;
    cout << "\t--minknap\tNot done..." << endl;
}

int main (int argc, char *argv[]) {
    // Print help menu?
    if (cmdOptionExists (argv, argv + argc, "-h")) {
        printHelp ();
        return 0;
    }

    // Get the user's test count
    int testCount = 10;
    char *testInput = getCmdOption (argv, argv + argc, "-t");
    if (testInput != nullptr) {
        testCount = atoi (testInput);
        if (testCount == 0) {
            cout << "Invalid test count option" << endl;
            return 1;
        }
    }

    string command ("(time ./knapsack ");
    string type;

    // Figure out what type of set we will generate
    if (cmdOptionExists (argv, argv + argc, "--recurrence ")) {
        command += "--recurrence ";
        type.assign ("recurrence ");
    } else if (cmdOptionExists (argv, argv + argc, "--branchbound ")) {
        command += "--branchbound ";
        type.assign ("branchbound");
    } else if (cmdOptionExists (argv, argv + argc, "--dynamic ")) {
        command += "--dynamic ";
        type.assign ("dynamic");
    } else if (cmdOptionExists (argv, argv + argc, "--minknap ")) {
        command += "--minknap ";
        type.assign ("minknap");
    }

    // Get the director name
    string inputDirectory;
    if (argc > 1) {
        inputDirectory.assign (argv[argc - 1]); // inputDirectory should be the last option supplied
    } else {
        cout << "No inputDirectory given" << endl;
        return 1;
    }

    // Generate the test cases
    for (int i = 0; i < testCount; i++) {
        string testCommand (command + inputDirectory + "/case" + to_string (i) + ".txt ");
        testCommand += ") &> " + inputDirectory + "/output_" + type + to_string (i) + ".txt";
        cout << testCommand << endl;
        system (command.c_str ());
    }

    return 0;
}
