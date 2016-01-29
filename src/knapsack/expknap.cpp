//
// expknap.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/28/16.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include <iostream>
#include <math.h>
#include "expknap.h"

using namespace std;

void expKnapSolve (ItemVec &vec, int capacity) {
    // Get greedy estimate and find break item
    sortItemVecByRatio (vec);
    int greedyEstimate = 0;
    int spaceUsed = 0;
    int index = 0;
    int breakIndex = -1;
    while (index < vec.size ()) {
        int newSpaceUsed = vec[index].s_weight + spaceUsed;
        if (newSpaceUsed < capacity) {
            greedyEstimate += vec[index].s_value;
            spaceUsed = newSpaceUsed;
            index++;
        } else {
            breakIndex = index;
            int spaceLeft = capacity - spaceUsed;
            float spaceFraction = (float) spaceLeft / (float) vec[index].s_weight;
            float valueFraction = spaceFraction * (float) vec[index].s_value;
            int breakValue = (int) ceil (valueFraction);
            greedyEstimate += breakValue;
            break;
        }
    }

    // If we fit all items then we are done...
    if (breakIndex == -1) {
        cout << "Fit all items: " << greedyEstimate << endl;
    }





}
