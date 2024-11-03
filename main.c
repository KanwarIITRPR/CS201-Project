#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"
#include "mapGenerator.h"
#include "KDTree.h"
#include "BallTree.h"
#include "storeData.h"

int main() {
    initializeMap();
    printf("MAP GENERATED!\n");

    for (int hospital_idx = 0; hospital_idx < num_hospitals; hospital_idx++) {
        insertKDNode(hospitals[hospital_idx]);
    }
    printf("KD TREE GENERATED!\n");

    buildBTBall(hospitals, num_hospitals);
    printf("BALL TREE GENERATED!\n\n");

    initializeStoragePointers();
    
    int sameCount = 0;
    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        struct Point query_point = houses[house_idx];

        struct Point nearestKD = nearestKDPoint(query_point);
        struct Point nearestBT = nearestBTPoint(query_point);

        results_KD[house_idx] = nearestKD;
        results_BT[house_idx] = nearestBT;

        int same = euclideanDistance(nearestKD, nearestBT) == 0;
        sameCount += same;
    }

    printf("K-Dimensional Trees and Ball Trees produce same results %d/%d times\n\n", sameCount, num_houses);

    storeData();
    freeStoragePointers();

    freeKDTree(KDRoot);
    freeBallTree(BTRoot);

    return 0;
}