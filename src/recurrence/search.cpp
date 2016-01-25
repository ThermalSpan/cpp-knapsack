//
// search.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/25/16
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include <math.h>
#include <iostream>
#include <queue>
#include "search.h"
#include "../utility/knapsack.h"

using namespace std;

void search (ItemVec& vector, int capacity) {
    queue <Node> nodeQueue;
    int best = 0;
    int nodeCount = 0;

    Node root;
    root.s_value = 0;
    root.s_capacity = capacity;
    root.s_depth = 0;
    nodeQueue.push (root);

    while (!nodeQueue.empty ()) {
        nodeCount++;
        Node cnode = nodeQueue.front ();
        nodeQueue.pop ();

        if (cnode.s_depth == vector.size ()) {
            if (cnode.s_value > best) {
                best = cnode.s_value;
            }
            continue;
        }

        if (vector[cnode.s_depth].s_weight <= cnode.s_capacity) {
            Node lnode;
            lnode.s_value = cnode.s_value + vector[cnode.s_depth].s_value;
            lnode.s_capacity = cnode.s_capacity - vector[cnode.s_depth].s_weight;
            lnode.s_depth = cnode.s_depth + 1;
            nodeQueue.push (lnode);
        }

        Node rnode;
        rnode.s_value = cnode.s_value;
        rnode.s_capacity = cnode.s_capacity;
        rnode.s_depth = cnode.s_depth + 1;
        nodeQueue.push (rnode);
    }

    cout << "Best: " << best << "\tnode count: " << nodeCount << endl;
}


