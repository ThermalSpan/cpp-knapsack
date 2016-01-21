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

using namespace std;

int main (int argc, char* argv[]) {

    // Get the file name
    string fileName;
    if (argc > 1) {
        fileName.assign (argv[argc - 1]);
        cout << "Input: " << fileName << endl;
    } else {
        cerr << "No input file given." << endl;
        return 1;
    }

    // Open a file stream, and an int iterator
    fstream inputFileStream (fileName);
    istream_iterator <int> intIterator (inputFileStream);

    // Read in vector of items
    int itemCount = *intIterator;




    inputFileStream.close ();
    return 0;
}
