//
//  utilities.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 1/19/16.
//  Copyright (c) 2016 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include <algorithm>
#include "utilities.h"

using namespace std;

char* getCmdOption (char** begin, char** end, const string& option) {
    char** it = find (begin, end, option);
    if (it != end && (it + 1) != end) {
        return * (it + 1);
    } else {
        return nullptr;
    }
}

bool cmdOptionExists (char** begin, char** end, const string& option) {
    return find (begin, end, option) != end;
}
