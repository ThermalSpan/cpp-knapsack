//
// dynamic.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/26/16.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT license
//

#include <iostream>
#include "dynamic.h"

using namespace std;

void dynamicSolve (ItemVec &vec, int capacity) {
    int x, y, index, doNotTake, doTake;
    int rowSize = capacity + 1;
    int columnSize = vec.size () + 1;
    int arraySize = columnSize * rowSize;
    int *sumArray = new int[arraySize];

    // Here, x refers to [0, capacity]
    //       y refers to [0, n]
    for (x = 0; x < rowSize; x++) {
        sumArray[x] = 0;
    }

    for (y = 1; y < columnSize; y++) {
        for (x = 0; x < rowSize; x++) {
            index = y * rowSize + x;
            if (vec[y-1].s_weight <= x) {
                doNotTake = sumArray[ (y-1) * rowSize + x];
                doTake = sumArray[ (y-1) * rowSize + (x - vec[y-1].s_weight)] + vec[y-1].s_value;
                sumArray[index] = max (doNotTake, doTake);
            }  else {
                sumArray[index] = sumArray[ (y-1) * rowSize + x];
            }
        }
    }

    cout << sumArray[arraySize - 1] << endl;

    char *decision = (char *) malloc (vec.size () * sizeof (char) + 1);
    decision[vec.size ()] = '\0';
    x = capacity;
    for (y = vec.size (); y > 0; y--) {
        if (sumArray[y * rowSize + x] == sumArray[ (y-1) * rowSize + x]) {
            decision[y-1] = '0';
        } else {
            decision[y-1] = '1';
            x -= vec[y-1].s_weight;
        }
    }

    string d (decision);
    cout << d << endl;

    delete (sumArray);
    free (decision);
}
