// 
// genFunctions.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/21/16.
// Copyright (c) 2016 Russell Wilhelm Bentley
// Distributed under the MIT License
//

#pragma once

#include <stdlib.h>
#include <fstream>

using namespace std;

void genUnCor (int itemCount, int range, ofstream &outputFile);

void genWeakCor (int itemCount, int range, ofstream &outputFile);

void genStrCor (int itemCount, int range, ofstream &outputFile);

void genInvStrCor (int itemCount, int range, ofstream &outputFile);

void genAlmStrCor (int itemCount, int range, ofstream &outputFile);

void genSubSum (int itemCount, int range, ofstream &outputFile);
