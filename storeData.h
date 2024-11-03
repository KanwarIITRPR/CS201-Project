#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "mapGenerator.h"
#include "KDTree.h"
#include "BallTree.h"

#ifndef DATA_FILES

#define DATA_FILES
char* results_KD_storage;
char* results_BT_storage;
char* kd_storage;
char* balls_storage;

#endif

extern struct Point* results_KD;
extern struct Point* results_BT;

#ifndef NODES_DATA

#define NODES_DATA
struct KDNode* nodes;
struct Point* lower_constraints;
struct Point* upper_constraints;
int* node_depths;
int nodes_count;

#endif

#ifndef BALLS_DATA

#define BALLS_DATA
struct BTBall* balls;
int* ball_depths;
int balls_count;

#endif

void storeKDResults();
void storeBTResults();

void getConstraints(struct KDNode* target, struct KDNode* node, int depth, struct Point* lower, struct Point* upper);
void TraverseNodesData(struct KDNode* node, int depth);
void TraverseBallsData(struct BTBall* ball, int depth);

void storeDivisionsData();
void storeBallsData();

void initializeStoragePointers();
void storeData();
void freeStoragePointers();