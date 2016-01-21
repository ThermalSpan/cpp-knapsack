//
// knapsack.h
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/20/15.
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

struct item {
    int weight;
    int value;
    float ratio;
};

bool itemRatioComp (const item& i1, const item& i2) {
    return i1.ratio < i2.ratio;
}


