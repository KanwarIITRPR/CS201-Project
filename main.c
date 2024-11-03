#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"           // Definitions related to Point structure and related functions
#include "mapGenerator.h"    // Functionality for map generation
#include "KDTree.h"          // KD-Tree structure and function declarations
#include "BallTree.h"        // Ball Tree structure and function declarations
#include "storeData.h"       // Data storage and memory management functions

int main() {
    // Step 1: Generate the map with hospitals and houses
    initializeMap();
    printf("MAP GENERATED!\n");

    // Step 2: Insert each hospital location into the KD-Tree
    for (int hospital_idx = 0; hospital_idx < num_hospitals; hospital_idx++) {
        insertKDNode(hospitals[hospital_idx]);
    }
    printf("KD TREE GENERATED!\n");

    // Step 3: Build the Ball Tree using the hospital locations
    buildBTBall(hospitals, num_hospitals);
    printf("BALL TREE GENERATED!\n\n");

    // Step 4: Initialize storage pointers for storing nearest points
    initializeStoragePointers();

    // Step 5: Find the nearest hospital for each house using both KD-Tree and Ball Tree
    int sameCount = 0;
    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        struct Point query_point = houses[house_idx]; // Current house location

        // Find the nearest hospital using the KD-Tree
        struct Point nearestKD = nearestKDPoint(query_point);

        // Find the nearest hospital using the Ball Tree
        struct Point nearestBT = nearestBTPoint(query_point);

        // Store the results for each house
        results_KD[house_idx] = nearestKD;
        results_BT[house_idx] = nearestBT;

        // Check if both methods returned the same nearest hospital
        int same = euclideanDistance(nearestKD, nearestBT) == 0;
        sameCount += same; // Count how many times the results match
    }

    // Display the number of times KD-Tree and Ball Tree produced the same results
    printf("K-Dimensional Trees and Ball Trees produce same results %d/%d times\n\n", sameCount, num_houses);

    // Step 6: Store results data to an external file or memory
    storeData();
    freeStoragePointers(); // Free memory for storage pointers

    // Step 7: Free memory allocated for KD-Tree and Ball Tree structures
    freeKDTree(KDRoot);
    freeBallTree(BTRoot);

    return 0;
}
