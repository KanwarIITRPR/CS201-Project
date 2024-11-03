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

char* kd_storage = "Data/KD_divisions.txt";
char* balls_storage = "Data/BT_balls.txt";

struct KDNode* nodes;
int* node_depths;
int nodes_count;

struct BTBall* balls;
int* ball_depths;
int balls_count;

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

void TraverseNodes(struct KDNode* node, int depth) {
    if (!node) {
        return;
    }

    nodes[nodes_count] = *node;
    node_depths[nodes_count] = depth;
    nodes_count++;

    TraverseNodes(node -> left, depth + 1);
    TraverseNodes(node -> right, depth + 1);
}

void TraverseBalls(struct BTBall* ball, int depth) {
    if (!ball) {
        return;
    }

    balls[balls_count] = *ball;
    ball_depths[balls_count] = depth;
    balls_count++;

    TraverseBalls(ball -> left, depth + 1);
    TraverseBalls(ball -> right, depth + 1);
}

void storeDivisionsData() {
    FILE* file = fopen(kd_storage, "w");

    nodes_count = 0;
    TraverseNodes(KDRoot, 0);

    for (int node_idx = 0; node_idx < nodes_count; node_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", nodes[node_idx].point.coordinates[dimension]);
        }
        fprintf(file, "%d\n", node_depths[node_idx]);
    }

    fclose(file);
}

void storeBallsData() {
    FILE* file = fopen(balls_storage, "w");

    balls_count = 0;
    TraverseBalls(BTRoot, 0);

    for (int ball_idx = 0; ball_idx < balls_count; ball_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", balls[ball_idx].center.coordinates[dimension]);
        }
        fprintf(file, "%f ", balls[ball_idx].radius);
        fprintf(file, "%d\n", ball_depths[ball_idx]);
    }

    fclose(file);
}

int main() {
    initializeMap();
    printf("MAP GENERATED!\n");

    for (int hospital_idx = 0; hospital_idx < num_hospitals; hospital_idx++) {
        insertKDNode(hospitals[hospital_idx]);
    }
    printf("KD TREE GENERATED!\n");

    buildBTBall(hospitals, num_hospitals);
    printf("BALL TREE GENERATED!\n\n");

    results_KD = (struct Point*) calloc(num_houses, sizeof(struct Point));
    results_BT = (struct Point*) calloc(num_houses, sizeof(struct Point));
    nodes = (struct KDNode*) calloc(num_hospitals, sizeof(struct KDNode));
    node_depths = (int*) calloc(num_hospitals, sizeof(int));
    balls = (struct BTBall*) calloc(2 * num_hospitals, sizeof(struct BTBall));
    ball_depths = (int*) calloc(2 * num_hospitals, sizeof(int));
    
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

    storeKDResults();
    storeBTResults();

    storeDivisionsData();
    storeBallsData();

    free(results_KD);
    free(results_BT);
    free(results_KD_storage);
    free(results_BT_storage);

    free(balls);
    free(balls_storage);

    freeKDTree(KDRoot);
    freeBallTree(BTRoot);

    return 0;
}