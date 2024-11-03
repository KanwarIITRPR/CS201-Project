#include "storeData.h"

char* results_KD_storage = "Data/results_KD.txt";
char* results_BT_storage = "Data/results_BT.txt";

struct Point* results_KD;
struct Point* results_BT;

char* kd_storage = "Data/KD_divisions.txt";
char* balls_storage = "Data/BT_balls.txt";

struct KDNode* nodes;
struct Point* lower_constraints;
struct Point* upper_constraints;
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

void TraverseNodesData(struct KDNode* node, int depth, struct Point lower, struct Point upper) {
    if (!node) {
        return;
    }

    int comparingDimension = depth % DIMENSIONS;
    lower.coordinates[comparingDimension] = node -> point.coordinates[comparingDimension];
    upper.coordinates[comparingDimension] = node -> point.coordinates[comparingDimension];

    nodes[nodes_count] = *node;
    lower_constraints[nodes_count] = lower;
    upper_constraints[nodes_count] = upper;
    node_depths[nodes_count] = depth;
    nodes_count++;

    struct Point left_lower = lower, left_upper = upper;
    struct Point right_lower = lower, right_upper = upper;
    left_lower.coordinates[comparingDimension] = 0;
    right_upper.coordinates[comparingDimension] = map_size;

    TraverseNodesData(node -> left, depth + 1, left_lower, left_upper);
    TraverseNodesData(node -> right, depth + 1, right_lower, right_upper);
}

void TraverseBallsData(struct BTBall* ball, int depth) {
    if (!ball) {
        return;
    }

    balls[balls_count] = *ball;
    ball_depths[balls_count] = depth;
    balls_count++;

    TraverseBallsData(ball -> left, depth + 1);
    TraverseBallsData(ball -> right, depth + 1);
}

void storeDivisionsData() {
    FILE* file = fopen(kd_storage, "w");

    struct Point origin, limit;
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        origin.coordinates[dimension] = 0;
        limit.coordinates[dimension] = map_size;
    }

    nodes_count = 0;
    TraverseNodesData(KDRoot, 0, origin, limit);

    for (int node_idx = 0; node_idx < nodes_count; node_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", nodes[node_idx].point.coordinates[dimension]);
        }
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", lower_constraints[node_idx].coordinates[dimension]);
        }
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", upper_constraints[node_idx].coordinates[dimension]);
        }
        fprintf(file, "%d\n", node_depths[node_idx]);
    }

    fclose(file);
}

void storeBallsData() {
    FILE* file = fopen(balls_storage, "w");

    balls_count = 0;
    TraverseBallsData(BTRoot, 0);

    for (int ball_idx = 0; ball_idx < balls_count; ball_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", balls[ball_idx].center.coordinates[dimension]);
        }
        fprintf(file, "%f ", balls[ball_idx].radius);
        fprintf(file, "%d\n", ball_depths[ball_idx]);
    }

    fclose(file);
}

void initializeStoragePointers() {
    results_KD = (struct Point*) calloc(num_houses, sizeof(struct Point));
    results_BT = (struct Point*) calloc(num_houses, sizeof(struct Point));

    nodes = (struct KDNode*) calloc(num_hospitals, sizeof(struct KDNode));
    lower_constraints = (struct Point*) calloc(num_hospitals, sizeof(struct Point));
    upper_constraints = (struct Point*) calloc(num_hospitals, sizeof(struct Point));
    node_depths = (int*) calloc(num_hospitals, sizeof(int));
    
    balls = (struct BTBall*) calloc(2 * num_hospitals, sizeof(struct BTBall));
    ball_depths = (int*) calloc(2 * num_hospitals, sizeof(int));
}

void storeData() {
    storeKDResults();
    storeBTResults();

    storeDivisionsData();
    storeBallsData();
}

void freeStoragePointers() {
    free(results_KD);
    free(results_BT);
    free(results_KD_storage);
    free(results_BT_storage);

    free(nodes);
    free(lower_constraints);
    free(upper_constraints);
    free(node_depths);
    free(kd_storage);

    free(balls);
    free(ball_depths);
    free(balls_storage);
}
