#include <stdio.h>
#include <stdlib.h>
#include "point.h"          // Include the header for Point struct and related functions
#include "mapGenerator.h"   // Include the header for map generation functions
#include "KDTree.h"         // Include the header for KD-Tree data structure and functions
#include "BallTree.h"       // Include the header for Ball-Tree data structure and functions

// Define macro to prevent multiple inclusions of this header file
#ifndef DATA_FILES
#define DATA_FILES

// File paths for storing KD-tree and Ball-tree results
char* results_KD_storage; // Path for storing KD results
char* results_BT_storage; // Path for storing Ball-tree results
char* kd_storage;         // Path for storing KD-tree divisions
char* balls_storage;      // Path for storing Ball-tree balls

#endif // DATA_FILES

// Declare external variables for KD-tree and Ball-tree results
extern struct Point* results_KD; // Array of points for KD-tree results
extern struct Point* results_BT;  // Array of points for Ball-tree results

// Define macro to hold KD-tree nodes and related data
#ifndef NODES_DATA
#define NODES_DATA

// Arrays and variables to store KD-tree nodes and their constraints
struct KDNode* nodes;               // Array to hold nodes of the KD-tree
struct Point* lower_constraints;     // Array to hold lower constraint points for nodes
struct Point* upper_constraints;     // Array to hold upper constraint points for nodes
int* node_depths;                   // Array to hold depth levels of each node
int nodes_count;                    // Count of nodes processed in the KD-tree

#endif // NODES_DATA

// Define macro to hold Ball-tree balls and related data
#ifndef BALLS_DATA
#define BALLS_DATA

// Arrays and variables to store Ball-tree balls and their depths
struct BTBall* balls;               // Array to hold balls in the Ball-tree
int* ball_depths;                   // Array to hold depth levels of each ball
int balls_count;                    // Count of balls processed in the Ball-tree

#endif // BALLS_DATA

// Function prototypes for storing results and traversing data structures
void storeKDResults();               // Function to store KD-tree results in a file
void storeBTResults();               // Function to store Ball-tree results in a file

// Function prototypes for traversing and gathering data from trees
void getConstraints(struct KDNode* target, struct KDNode* node, int depth, struct Point* lower, struct Point* upper);
void TraverseNodesData(struct KDNode* node, int depth); // Function to traverse KD-tree and gather node data
void TraverseBallsData(struct BTBall* ball, int depth);   // Function to traverse Ball-tree and gather ball data

// Function prototypes for storing divisions and ball data
void storeDivisionsData();           // Function to store KD-tree divisions in a file
void storeBallsData();               // Function to store Ball-tree balls in a file

// Function prototypes for initializing storage and freeing resources
void initializeStoragePointers();     // Function to allocate memory for data structures
void storeData();                     // Function to store all results
void freeStoragePointers();            // Function to free allocated memory
