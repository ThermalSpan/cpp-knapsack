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

void lower (ItemPtrVec &ptrVec, int capacity) {
    sortItemPtrVecByRatio (ptrVec, 0, ptrVec.size ());
    int low = 0;
    int spaceUsed = 0;
    int index = 0;
    while (index < ptrVec.size ()) {
        int newSpaceUsed = spaceUsed + ptrVec[index]->s_weight;
        if (newSpaceUsed < capacity) {
            low += ptrVec[index]->s_value;
            spaceUsed = newSpaceUsed;
            index++;
        } else {
            break;
        }
    }
    cout << "lower: " << low << " using: " << spaceUsed << " at: " << index << endl;
}

struct partInterval {
    int lower;
    int upper;
    int weight;
};

void partSort (ItemPtrVec &ptrVec, int leftIndex, int rightIndex, int partialSum, int capacity, partInterval &returnVal) {
    int midIndex;
    int size = rightIndex - leftIndex + 1;

    //First things first! Order items such that I_left < I_mid < I_right
    if (size > 0) {
        midIndex = leftIndex + (rightIndex - leftIndex) / 2;

        // Perform Ordering
        if (ptrVec[leftIndex]->s_ratio < ptrVec[midIndex]->s_ratio) {
            swap (ptrVec[leftIndex], ptrVec[midIndex]);
        }
        if (size > 2) {
            if (ptrVec[midIndex]->s_ratio < ptrVec[rightIndex]->s_ratio) {
                swap (ptrVec[midIndex], ptrVec[rightIndex]);
            }
            if (ptrVec[leftIndex]->s_ratio < ptrVec[midIndex]->s_ratio) {
                swap (ptrVec[leftIndex], ptrVec[midIndex]);
            }
        }
    }

    // Now, do we have the Base case?
    if (size < 3) {
        returnVal.lower = leftIndex;
        returnVal.upper = rightIndex;
        returnVal.weight = partialSum;
        return;
    }

    // If not, we find the the new interval and recur
    float midRatio = ptrVec[midIndex]->s_ratio;
    int newSum = partialSum;
    int leftTemp = leftIndex;
    int rightTemp = rightIndex;

    // Shrink [i,j] to the mid point, tracking sum on lower side
    while (leftTemp <= rightTemp) {
        while (ptrVec[leftTemp]->s_ratio >= midRatio) {
            newSum += ptrVec[leftTemp]->s_weight;
            leftTemp++;
        }
        while (ptrVec[rightTemp]->s_ratio <= midRatio) {
            rightTemp--;
        }
        if (leftTemp < rightTemp) {
            swap (ptrVec[leftTemp], ptrVec[rightTemp]);
        }
    }

    // If the new sum is less greater than capacity, break is in lower side
    if (newSum > capacity) {
        partSort (ptrVec, leftIndex, leftTemp-1, partialSum, capacity, returnVal);
    } else {
        partSort (ptrVec, leftTemp , rightIndex, newSum, capacity, returnVal);
    }
}

void expKnapSolve (ItemVec &vec, int capacity) {
    // First, we will be operating on a vector of Item pointers
    int n = vec.size ();
    ItemPtrVec ptrVec (n);
    auto it = vec.begin ();
    for (int i = 0; i < vec.size (); i++) {
        ptrVec[i] = & (*it);
        it++;
    }


}
