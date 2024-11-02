#include "KDTree.h"

struct KDNode* KDRoot = NULL;

struct KDNode* createKDNode(struct Point point) {
    struct KDNode* node = (struct KDNode*) malloc(sizeof(struct KDNode));
    node -> point = point;
    node -> left = node -> right = NULL;
    return node;
}

struct KDNode* insertKDRecursive(struct Point point, struct KDNode* node, int depth) {
    if (!node) {
        return createKDNode(point);
    }

    int comparingDimension = depth % DIMENSIONS;

    if (point.coordinates[comparingDimension] < node -> point.coordinates[comparingDimension]) {
        node -> left = insertKDRecursive(point, node -> left, depth + 1);
    } else {
        node -> right = insertKDRecursive(point, node -> right, depth + 1);
    }

    return node;
}

void insertKDNode(struct Point point) {
    KDRoot = insertKDRecursive(point, KDRoot, 0);
}

void nearestKDNode(struct Point target, struct KDNode* node, int depth, struct KDNode** neighbour) {
    if (!node) {
        return;
    }

    double minimumDistance = euclideanDistance(target, (*neighbour) -> point);
    double currentDistance = euclideanDistance(target, node -> point);

    if (currentDistance < minimumDistance) {
        *neighbour = node;
    }

    int comparingDimension = depth % DIMENSIONS;
    struct KDNode* nextSearchNode = NULL;
    struct KDNode* otherSearchNode = NULL;

    if (target.coordinates[comparingDimension] < node -> point.coordinates[comparingDimension]) {
        nextSearchNode = node -> left;
        otherSearchNode = node -> right;
    } else {
        nextSearchNode = node -> right;
        otherSearchNode = node -> left;
    }

    nearestKDNode(target, nextSearchNode, depth + 1, neighbour);

    if (fabs(node -> point.coordinates[comparingDimension] - target.coordinates[comparingDimension]) < minimumDistance) {
        nearestKDNode(target, otherSearchNode, depth + 1, neighbour);
    }
}

struct Point nearestKDPoint(struct Point target) {
    struct KDNode* neighbour = KDRoot;
    nearestKDNode(target, KDRoot, 0, &neighbour);
    return neighbour -> point;
}

void freeKDTree(struct KDNode* node) {
    if (node) {
        freeKDTree(node -> left);
        freeKDTree(node -> right);
        free(node);
    }
}