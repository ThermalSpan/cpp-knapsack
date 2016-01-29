//
// minknap.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/27/16.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include "minknap.h"

using namespace std;

void minKnapSolve (ItemVec &vec, int capacity) {
    // First, sort and find the break item
    sortItemVecByValue (ItemVec& vec);
    int spaceUsed = 0;
    int index = 0;
    while (index < vec.size ()) {
        int newSpaceUsed = vec[index].s_weight + spaceUsed;
        if (newSpaceUsed <= capacity) {
            spaceUsed = newSpaceUsed;
            index++;
        } else {
            break;
        }
    }

    // Iterativley adjust the core
}


