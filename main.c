#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"
#include "KDTree.h"
#include "BallTree.h"
#include "mapGenerator.h"

char* results_KD_storage = "Data/results_KD.txt";
char* results_BT_storage = "Data/results_BT.txt";

struct Point* results_KD;
struct Point* results_BT;

void storeKDResults() {
    FILE* file = fopen(results_KD_storage, "w");

    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", results_KD[house_idx].coordinates[dimension]);
        }
        fprintf(file, "%c", '\n');
    }

    fclose(file);
}

void storeBTResults() {
    FILE* file = fopen(results_BT_storage, "w");

    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", results_BT[house_idx].coordinates[dimension]);
        }
        fprintf(file, "%c", '\n');
    }

    fclose(file);
}

int main() {
    initializeMap();
    printf("MAP GENERATED!");

    for (int hospital_idx = 0; hospital_idx < num_hospitals; hospital_idx++) {
        insertKDNode(hospitals[hospital_idx]);
        printPoint(hospitals[hospital_idx]);
        printf("\n");
    }
    printf("KD TREE GENERATED!");

    buildBTBall(hospitals, num_hospitals);
    printf("BALL TREE GENERATED!");

    results_KD = (struct Point*) calloc(num_houses, sizeof(struct Point));
    results_BT = (struct Point*) calloc(num_houses, sizeof(struct Point));
    
    int sameCount = 0;
    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        struct Point query_point = houses[house_idx];

        struct Point nearestKD = nearestKDPoint(query_point);
        struct Point nearestBT = nearestBTPoint(query_point);

        printf("Nearest Hospital to ");
        printPoint(query_point);
        printf(" is: \n");

        printPoint(nearestKD);
        printf(" using K-Dimensional Trees\n");
        results_KD[house_idx] = nearestKD;

        printPoint(nearestBT);
        printf(" using Ball Trees\n");
        results_BT[house_idx] = nearestBT;

        int same = euclideanDistance(nearestKD, nearestBT) == 0;
        printf("Result from K-Dimensional Trees and Ball Trees is %s\n\n", same == 1 ? "same" : "not same");
        sameCount += same;
    }

    printf("K-Dimensional Trees and Ball Trees produce same results %d/%d times\n", sameCount, num_houses);

    storeKDResults();
    storeBTResults();

    free(results_KD);
    free(results_BT);
    free(results_KD_storage);
    free(results_BT_storage);

    freeKDTree(KDRoot);
    freeBallTree(BTRoot);

    return 0;
}