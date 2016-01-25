//
// search.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/22/16
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include <math.h>
#include <iostream>
#include <queue>
#include "search.h"
#include "../utility/knapsack.h"

bool operator< (const Node& n1, const Node& n2) {
    return n1.s_upperBound < n2.s_upperBound;
}

int greedyEstimate (const ItemVec& vector, int capacity, int depth) {
    int index = depth;
    int spaceLeft = capacity;
    int valueEst = 0;
    // We will add as much as we can...
    while (index < vector.size ()) {
        int t = spaceLeft - vector[index].s_weight;
        // If there's room we add it
        if (t > 0) {
            spaceLeft = t;
            valueEst += vector[index].s_value;
            index++;
            // Otherwise we add a fraction of it, and we're done
        } else {
            float fraction = (float) spaceLeft / (float) vector[index].s_weight;
            fraction = fraction * (float) vector[index].s_value;
            valueEst += (int) ceil (fraction);
            break;
        }
    }

    return valueEst;
}

void search (ItemVec& vector, int capacity) {
    // This method assumes the items are sorted by ratio, with value as the tie breaker
    sortItemVecByRatio (vector);

    printItemVec (vector);
    cout << "Greedy estimate " << greedyEstimate (vector, capacity, 0) << endl;

    // The priority queue will give us the node with the best upper bound
    priority_queue <Node> frontierQueue;
    int lowerBound = 0;
    int nodeCount = 0;

    // The root node has yet to make a decision on the first item
    Node root;
    root.s_depth = 0;
    root.s_value = 0;
    root.s_capacity = capacity;
    root.s_upperBound = greedyEstimate (vector, capacity, 0);
    root.s_addedBy = -1;
    frontierQueue.push (root);

    // Expand the node with the most promising upper bound
    while (!frontierQueue.empty ()) {
        Node cnode = frontierQueue.top ();
        frontierQueue.pop ();
        int depth = cnode.s_depth;


        cout << "Exploring Node: " << nodeCount << endl;
        cout << "\tdepth\t" << cnode.s_depth << endl;
        cout << "\tvalue\t" << cnode.s_value << endl;
        cout << "\tcapac\t" << cnode.s_capacity << endl;
        cout << "\tUpper\t" << cnode.s_upperBound << endl;
        cout << "\tadded\t" << cnode.s_addedBy << endl;
        if (depth == vector.size ()) {
            cout << "\tBottom!" << endl;
        }
        cout << endl;

        // Have we bottomed out? If so, update lowerBound accordingly
        if (depth == vector.size ()) {
            if (cnode.s_value > lowerBound) {
                lowerBound = cnode.s_value;
            }
            continue;
        }

        // Is there room to add the next item? If so, add it
        if (cnode.s_capacity >= vector[depth].s_weight) {
            Node lnode;
            lnode.s_depth = depth + 1;
            lnode.s_value = cnode.s_value + vector[depth].s_value;
            lnode.s_capacity = cnode.s_capacity - vector [depth].s_value;
            lnode.s_upperBound = lnode.s_value + greedyEstimate (vector, lnode.s_capacity, depth + 1);
            lnode.s_addedBy = nodeCount;
            frontierQueue.push (lnode);
        }

        // Or, we could not add, but then we have to check for bounding
        Node rnode = cnode;
        rnode.s_depth++;
        rnode.s_upperBound = greedyEstimate (vector, rnode.s_capacity, depth + 1);
        rnode.s_addedBy = nodeCount;
        if (rnode.s_upperBound > lowerBound) {
            frontierQueue.push (rnode);
        }

        nodeCount++;
    }

    cout << lowerBound << endl;
}

