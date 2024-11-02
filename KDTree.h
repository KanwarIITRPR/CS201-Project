#include <stdio.h>
#include <stdlib.h>
#include "point.h"

struct KDNode {
    struct Point point;
    struct KDNode* left;
    struct KDNode* right;
};

extern struct KDNode* KDRoot;

struct KDNode* createKDNode(struct Point point);

struct KDNode* insertKDRecursive(struct Point point, struct KDNode* node, int depth);
void insertKDNode(struct Point point);

void nearestKDNode(struct Point target, struct KDNode* node, int depth, struct KDNode** neighbour);
struct Point nearestKDPoint(struct Point target);

void freeKDTree(struct KDNode* node);