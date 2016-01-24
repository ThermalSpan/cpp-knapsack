//
// search.h
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/22/16.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#pragma once

#include "../utility/knapsack.h"

using namespace std;

struct Node {
    int s_depth;        // Which Item are we choosing?
    int s_value;        // Value of items in sack so far
    int s_capacity;     // Capacity left
    int s_upperBound;   // Upperbound on total value for sack
};

bool operator< (const Node &n1, const Node &n2);

int greedyEstimate (const ItemVec &vector, int capacity, int depth);

void search (ItemVec &vector, int capacity);

