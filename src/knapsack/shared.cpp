//
// shared.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/22/15.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include <algorithm>
#include <iostream>
#include "shared.h"

using namespace std;

void printItemVec (const ItemVec &vector) {
    cout << "Val\tWght\tratio" << endl;
    for (int i = 0; i < vector.size (); i++) {
        cout << vector[i].s_value << "\t" << vector[i].s_weight << "\t" << vector[i].s_ratio << endl;
    }
}

bool itemValueComp (const Item &i1, const Item &i2) {
    return i1.s_value < i2.s_value;
}

bool itemWeightComp (const Item &i1, const Item &i2) {
    return i1.s_weight < i2.s_weight;
}

bool itemRatioComp (const Item &i1, const Item &i2) {
    if (i1.s_ratio == i2.s_ratio) {
        return i1.s_value > i2.s_value;
    } else {
        return i1.s_ratio > i2.s_ratio;
    }
}

void sortItemVecByValue (ItemVec &vector) {
    sort (vector.begin (), vector.end (), itemValueComp);
}

void sortItemVecByWeight (ItemVec &vector) {
    sort (vector.begin (), vector.end (), itemWeightComp);
}

void sortItemVecByRatio (ItemVec &vector) {
    sort (vector.begin (), vector.end (), itemRatioComp);
}

