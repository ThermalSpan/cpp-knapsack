//
// genFunctions.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/21/16.
// Copyright (c) 2016 Russell Wilhelm Bentley
// Distributed under the MIT License
//

#include "genFunctions.h"

using namespace std;

void genUnCor (int itemCount, int range, ofstream &outputFile) {
    for (int i = 1; i <= itemCount; i++) {
        int weight = (rand () % range) + 1;
        int value = rand () % range + 1;
        outputFile << i << " " << value << " " << weight << endl;
    }
}

void genWeakCor (int itemCount, int range, ofstream &outputFile) {
    int interval = range / 10;
    int priceRange = 2 * interval;
    for (int i = 1; i <= itemCount; i++) {
        int weight = (rand () % range) + 1;
        int value = ((rand () % priceRange) - interval) + weight;
        outputFile << i << " " << value << " " << weight << endl;
    }
}

void genStrCor (int itemCount, int range, ofstream &outputFile) {
    int offset = range / 10;
    for (int i = 1; i <= itemCount; i++) {
        int weight = (rand () % range) + 1;
        outputFile << i << " " << weight + offset << " " << weight << endl;
    }
}

void genInvStrCor (int itemCount, int range, ofstream &outputFile) {
    int offset = range / 10;
    for (int i = 1; i <= itemCount; i++) {
        int weight = (rand () % range) + 1;
        outputFile << i << " " << weight - offset << " " << weight << endl;
    }
}

void genAlmStrCor (int itemCount, int range, ofstream &outputFile) {
    int interval = range / 10;
    int increment = range / 500;
    int priceRange = 2 * increment;
    for (int i = 1; i <= itemCount; i++) {
        int weight = rand () %range + 1;
        int value = ((rand () % priceRange) - increment) + weight + interval;
        outputFile << i << " " << value << " " << weight << endl;
    }
}

void genSubSum (int itemCount, int range, ofstream &outputFile) {
    for (int i = 1; i <= itemCount; i++) {
        int weight = rand () %range + 1;
        outputFile << i << " " << weight << " " << weight << endl;
    }
}
