#include "storeData.h"

// File paths for storing results and data
char* results_KD_storage = "Data/results_KD.txt";
char* results_BT_storage = "Data/results_BT.txt";

// Arrays to hold results from KD-tree and bounding tree operations
struct Point* results_KD;
struct Point* results_BT;

// File paths for KD-tree divisions and bounding tree balls
char* kd_storage = "Data/KD_divisions.txt";
char* balls_storage = "Data/BT_balls.txt";

// Arrays to hold nodes and constraints for KD-tree
struct KDNode* nodes;
struct Point* lower_constraints;
struct Point* upper_constraints;
int* node_depths; // Array to hold depth of each node
int nodes_count; // Count of nodes processed

// Arrays to hold balls and their depths for bounding tree
struct BTBall* balls;
int* ball_depths; // Array to hold depth of each ball
int balls_count; // Count of balls processed

// Function to store results of KD-tree computations in a file
void storeKDResults() {
    FILE* file = fopen(results_KD_storage, "w"); // Open file for writing

    // Write each house's coordinates to the file
    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", results_KD[house_idx].coordinates[dimension]);
        }
        fprintf(file, "%c", '\n'); // New line after each point
    }

    fclose(file); // Close the file
}

// Function to store results of bounding tree computations in a file
void storeBTResults() {
    FILE* file = fopen(results_BT_storage, "w"); // Open file for writing

    // Write each house's coordinates to the file
    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", results_BT[house_idx].coordinates[dimension]);
        }
        fprintf(file, "%c", '\n'); // New line after each point
    }

    fclose(file); // Close the file
}

// Recursive function to get lower and upper constraints for KD-tree nodes
void getConstraints(struct KDNode* target, struct KDNode* node, int depth, struct Point* lower, struct Point* upper) {
    if (!node) {
        return; // Base case: if the node is null, return
    }

    // If the target point matches the current node, do nothing
    if (arePointsSame(target->point, node->point)) {
        return;
    }

    int comparingDimension = depth % DIMENSIONS; // Determine the current dimension to compare
    if (target->point.coordinates[comparingDimension] < node->point.coordinates[comparingDimension]) {
        // Update the upper constraint
        upper->coordinates[comparingDimension] = node->point.coordinates[comparingDimension];
        getConstraints(target, node->left, depth + 1, lower, upper); // Traverse left
    } else {
        // Update the lower constraint
        lower->coordinates[comparingDimension] = node->point.coordinates[comparingDimension];
        getConstraints(target, node->right, depth + 1, lower, upper); // Traverse right
    }

    return;
}

// Recursive function to traverse the KD-tree and collect node data
void TraverseNodesData(struct KDNode* node, int depth) {
    if (!node) {
        return; // Base case: if the node is null, return
    }

    int comparingDimension = depth % DIMENSIONS; // Determine the current dimension to compare
    // Allocate memory for lower and upper constraints
    struct Point* lower = (struct Point*)malloc(sizeof(struct Point));
    struct Point* upper = (struct Point*)malloc(sizeof(struct Point));
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        lower->coordinates[dimension] = 0; // Initialize lower constraints to zero
        upper->coordinates[dimension] = map_size; // Initialize upper constraints to the map size
    }

    // Get constraints based on the current node
    getConstraints(node, KDRoot, 0, lower, upper);
    lower->coordinates[comparingDimension] = node->point.coordinates[comparingDimension];
    upper->coordinates[comparingDimension] = node->point.coordinates[comparingDimension];

    // Store the current node, constraints, and depth
    nodes[nodes_count] = *node;
    lower_constraints[nodes_count] = *lower;
    upper_constraints[nodes_count] = *upper;
    node_depths[nodes_count] = depth;
    nodes_count++; // Increment the count of nodes processed

    // Recursively traverse left and right children
    TraverseNodesData(node->left, depth + 1);
    TraverseNodesData(node->right, depth + 1);
}

// Recursive function to traverse the bounding tree and collect ball data
void TraverseBallsData(struct BTBall* ball, int depth) {
    if (!ball) {
        return; // Base case: if the ball is null, return
    }

    // Store the current ball and its depth
    balls[balls_count] = *ball;
    ball_depths[balls_count] = depth;
    balls_count++; // Increment the count of balls processed

    // Recursively traverse left and right children
    TraverseBallsData(ball->left, depth + 1);
    TraverseBallsData(ball->right, depth + 1);
}

// Function to store the KD-tree node divisions and constraints in a file
void storeDivisionsData() {
    FILE* file = fopen(kd_storage, "w"); // Open file for writing

    nodes_count = 0; // Reset node count
    TraverseNodesData(KDRoot, 0); // Traverse KD-tree to gather node data

    // Write node data to the file
    for (int node_idx = 0; node_idx < nodes_count; node_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", nodes[node_idx].point.coordinates[dimension]); // Node coordinates
        }
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", lower_constraints[node_idx].coordinates[dimension]); // Lower constraints
        }
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", upper_constraints[node_idx].coordinates[dimension]); // Upper constraints
        }
        fprintf(file, "%d\n", node_depths[node_idx]); // Node depth
    }

    fclose(file); // Close the file
}

// Function to store the bounding tree ball data in a file
void storeBallsData() {
    FILE* file = fopen(balls_storage, "w"); // Open file for writing

    balls_count = 0; // Reset ball count
    TraverseBallsData(BTRoot, 0); // Traverse bounding tree to gather ball data

    // Write ball data to the file
    for (int ball_idx = 0; ball_idx < balls_count; ball_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", balls[ball_idx].center.coordinates[dimension]); // Ball center coordinates
        }
        fprintf(file, "%f ", balls[ball_idx].radius); // Ball radius
        fprintf(file, "%d\n", ball_depths[ball_idx]); // Ball depth
    }

    fclose(file); // Close the file
}

// Function to allocate memory for all necessary data structures
void initializeStoragePointers() {
    results_KD = (struct Point*)calloc(num_houses, sizeof(struct Point)); // Allocate for KD results
    results_BT = (struct Point*)calloc(num_houses, sizeof(struct Point)); // Allocate for BT results

    // Allocate memory for KD-tree nodes and constraints
    nodes = (struct KDNode*)calloc(num_hospitals, sizeof(struct KDNode));
    lower_constraints = (struct Point*)calloc(num_hospitals, sizeof(struct Point));
    upper_constraints = (struct Point*)calloc(num_hospitals, sizeof(struct Point));
    node_depths = (int*)calloc(num_hospitals, sizeof(int));
    
    // Allocate memory for balls in the bounding tree
    balls = (struct BTBall*)calloc(2 * num_hospitals, sizeof(struct BTBall)); // Allow for multiple balls per node
    ball_depths = (int*)calloc(2 * num_hospitals, sizeof(int)); // Allow for depth storage
}

// Function to store all results by calling individual storage functions
void storeData() {
    storeKDResults(); // Store KD results
    storeBTResults(); // Store BT results
    storeDivisionsData(); // Store KD divisions data
    storeBallsData(); // Store balls data
}

// Function to free all allocated memory to avoid memory leaks
void freeStoragePointers() {
    free(results_KD); // Free KD results
    free(results_BT); // Free BT results
    // Note: Do not free results_KD_storage and results_BT_storage since they are string literals

    free(nodes); // Free KD-tree nodes
    free(lower_constraints); // Free lower constraints
    free(upper_constraints); // Free upper constraints
    free(node_depths); // Free node depths

    free(balls); // Free bounding tree balls
    free(ball_depths); // Free ball depths
    // Note: Do not free balls_storage since it is a string literal
}
