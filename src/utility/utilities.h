//
//  utilities.h
//  knapsack
//
//  Created by Russell Wilhelm Bentley on 1/19/16.
//  Copyright (c) 2016 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include <stdlib.h>
#include <iostream>
//#include "knapsack.h"

using namespace std;

//
// Returns the option next to a flag
// src: http://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
//
char* getCmdOption (char** begin, char** end, const string& option);

//
// Returns whether or not a flag is there
// src: http://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
//
bool cmdOptionExists (char** begin, char** end, const string& option);

