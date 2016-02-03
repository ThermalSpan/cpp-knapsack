//
// branchbound.cpp
// knapsack
//
// Created by Russell Wilhelm Bentley on 1/22/16
// Copyright (c) 2015 Russell Wilhelm Bentley.
// Distributed under the MIT License
//

#include <math.h>
#include <iostream>
#include <queue>
#include "branchbound.h"

struct Node {
    int s_depth;        // Which Item are we choosing?
    int s_value;        // Value of items in sack so far
    int s_capacity;     // Capacity left
    int s_upperBound;   // Upperbound on total value for sack
    int s_addedBy;
    char *s_d;
};

bool operator< (const Node &n1, const Node &n2) {
    return n1.s_upperBound < n2.s_upperBound;
}

int upperEstimate (const ItemPtrVec &vec, int capacity, int depth) {
    int index = depth;
    int spaceLeft = capacity;
    int valueEst = 0;
    // We will add as much as we can...
    while (index < vec.size ()) {
        int newSpaceLeft = spaceLeft - vec[index]->s_weight;
        // If there's room we add it
        if (newSpaceLeft > 0) {
            spaceLeft = newSpaceLeft;
            valueEst += vec[index]->s_value;
            index++;
            // Otherwise we add a fraction of it, and we're done
        } else {
            float fraction = (float) spaceLeft / (float) vec[index]->s_weight;
            fraction = fraction * (float) vec[index]->s_value;
            valueEst += (int) ceil (fraction);
            break;
        }
    }

    return valueEst;
}

int lowerEstimate (const ItemPtrVec &vec, int capacity, char *d) {
    int index = 0;
    int spaceLeft = capacity;
    int valueEst = 0;
    // We will add as much as we can...
    while (index < vec.size ()) {
        int newSpaceLeft = spaceLeft - vec[index]->s_weight;
        // If there's room we add it
        if (newSpaceLeft > 0) {
            spaceLeft = newSpaceLeft;
            valueEst += vec[index]->s_value;
            d[vec[index]->s_id - 1] = '1';
        }
        index++;
    }

    return valueEst;
}

char *makeD (int n) {
    char *result = (char *) malloc ((n+1) * sizeof (char));
    for (int i = 0; i < n; i++) {
        result[i] = '0';
    }
    result[n] = '\0';
    return result;
}

char *copyD (int n, char *src) {
    char *result = (char *) malloc ((n+1) * sizeof (char));
    memcpy (result, src, (n+1) * sizeof (char));
    return result;
}

void branchBoundSolve (ItemVec &vec, int capacity) {
    int n = vec.size ();
    // First we need a vector of pointers
    ItemPtrVec ptrVec (vec.size ());
    for (int i = 0; i < vec.size (); i++) {
        ptrVec[i] = &vec[i];
    }

    // This method assumes the items are sorted by ratio, with value as the tie breake
    sortItemPtrVecByRatio (ptrVec, 0, ptrVec.size ());

    // The priority queue will give us the node with the best upper bound
    priority_queue <Node> frontierQueue;
    char *charD = makeD (n);
    int lowerBound = lowerEstimate (ptrVec, capacity, charD);
    int nodeCount = 0;

    // The root node has yet to make a decision on the first item
    Node root;
    root.s_depth = 0;
    root.s_value = 0;
    root.s_capacity = capacity;
    root.s_upperBound = upperEstimate (ptrVec, capacity, 0);
    root.s_addedBy = -1;
    root.s_d = makeD (n);
    frontierQueue.push (root);

    // Expand the node with the most promising upper bound
    while (!frontierQueue.empty ()) {
        Node cnode = frontierQueue.top ();
        frontierQueue.pop ();
        int depth = cnode.s_depth;

        // Have we bottomed out? If so, update lowerBound accordingly
        if (depth == ptrVec.size ()) {
            if (cnode.s_value > lowerBound) {
                lowerBound = cnode.s_value;
                free (charD);
                charD = copyD (n, cnode.s_d);
            }
            free (cnode.s_d);
            continue;
        }

        // Is there room to add the next item? If so, add it
        if (cnode.s_capacity >= ptrVec[depth]->s_weight) {
            Node lnode;
            lnode.s_depth = depth + 1;
            lnode.s_value = cnode.s_value + ptrVec[depth]->s_value;
            lnode.s_capacity = cnode.s_capacity - ptrVec[depth]->s_weight;
            lnode.s_upperBound = lnode.s_value + upperEstimate (ptrVec, lnode.s_capacity, depth + 1);
            lnode.s_addedBy = nodeCount;
            lnode.s_d = copyD (n, cnode.s_d);
            lnode.s_d[ptrVec[depth]->s_id - 1] = '1';
            frontierQueue.push (lnode);
        }

        // Or, we could not add, but then we have to check for bounding
        Node rnode = cnode;
        rnode.s_depth++;
        rnode.s_upperBound = upperEstimate (ptrVec, rnode.s_capacity, depth + 1);
        rnode.s_addedBy = nodeCount;
        if (rnode.s_upperBound > lowerBound) {
            frontierQueue.push (rnode);
        } else {
            free (cnode.s_d);
        }

        nodeCount++;
    }

    cout << lowerBound << endl;
    for (int i = 0; i < n; i++) {
        cout << charD[i];
    }
    cout << endl;
    cout << "node count: " << nodeCount << endl;
    free (charD);
}

