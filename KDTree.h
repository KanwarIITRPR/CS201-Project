#include <stdio.h>
#include <stdlib.h>
#include "point.h"  // Include point structure and related definitions

// Structure definition for a KD-Tree node
#ifndef KDNODE_DEFINITION
#define KDNODE_DEFINITION

struct KDNode {
    struct Point point;         // Point data stored in the node
    struct KDNode* left;        // Pointer to the left child
    struct KDNode* right;       // Pointer to the right child
};

#endif

// Declaration of the root of the KD-Tree, defined elsewhere in the program
extern struct KDNode* KDRoot;

// Function declarations for KD-Tree operations

// Creates a new KD-Tree node with a given point
struct KDNode* createKDNode(struct Point point);

// Recursive function to insert a point into the KD-Tree
struct KDNode* insertKDRecursive(struct Point point, struct KDNode* node, int depth);

// Wrapper function to start insertion from the root
void insertKDNode(struct Point point);

// Recursive function to find the nearest neighbor to a target point in the KD-Tree
void nearestKDNode(struct Point target, struct KDNode* node, int depth, struct KDNode** neighbour);

// Finds and returns the nearest point to a target in the KD-Tree
struct Point nearestKDPoint(struct Point target);

// Recursively frees all nodes in the KD-Tree
void freeKDTree(struct KDNode* node);
