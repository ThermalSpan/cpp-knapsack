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
    int s_value;
    int s_capacity;
    int s_depth;
};

void search (ItemVec& vector, int capacity);


