//
// shared.h
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/20/15.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#pragma once

#include <vector>

using namespace std;

struct Item {
    int s_value;
    int s_weight;
    float s_ratio;
};

typedef vector <Item> ItemVec;

//
// Print Vector
//
void printItemVec (const ItemVec &vec);

//
// Comparators
//
bool itemValueComp (const Item &i1, const Item &i2);

bool itemWeightComp (const Item &i1, const Item &i2);

bool itemRatioComp (const Item &i1, const Item &i2);

//
// Sort Vectors
//
void sortItemVecByValue (ItemVec &vec);

void sortItemVecByWeight (ItemVec &vec);

void sortItemVecByRatio (ItemVec &vec);

