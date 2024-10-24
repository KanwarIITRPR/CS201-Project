#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Dimensions of the K-D Trees and Ball Trees
#define DIMENSIONS 2

// Structing a point in a Hyperspace with "DIMENSIONS" dimensions
struct Point {
    double coordinates[DIMENSIONS];
};

// Structuring K-Dimensional Trees using essential attributes
struct KDNode {
    struct Point point;
    struct KDNode* left;
    struct KDNode* right;
};

struct KDNode* KDRoot = NULL;

struct Point* createPoint(double coordinates[]) {
    struct Point* point = (struct Point*) malloc(sizeof(struct Point));
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        point -> coordinates[dimension] = coordinates[dimension];
    }

    return point;
}

int arePointsSame(struct Point point1, struct Point point2) {
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        if (point1.coordinates[dimension] != point2.coordinates[dimension]) {
            return 0;
        }
    }
    return 1;
}


struct KDNode* createKDNode(double coordinates[]) {
    struct Point* node_point = createPoint(coordinates);
    struct KDNode* node = (struct KDNode*) malloc(sizeof(struct KDNode));

    node -> point = *node_point;
    node -> left = node -> right = NULL;
    return node;
}

struct KDNode* insertKDRecursive(double coordinates[], struct KDNode* currentNode, int currentDepth) {
    if (!currentNode) {
        return createKDNode(coordinates);
    }

    int comparedDimension = currentDepth % DIMENSIONS;
    if (coordinates[comparedDimension] < currentNode -> point.coordinates[comparedDimension]) {
        currentNode -> left = insertKDRecursive(currentNode -> left, coordinates, currentDepth + 1);
    } else {
        currentNode -> right = insertKDRecursive(currentNode -> right, coordinates, currentDepth + 1);
    }

    return currentNode;
}

void insertKDNode(double coordinates[]) {
    KDRoot = insertKDRecursive(coordinates, KDRoot, 0);
}

struct KDNode* searchKDRecursive(double coordinates[], struct KDNode* currentNode, int currentDepth) {
    if (!currentNode) {
        return NULL;
    }

    if (arePointsSame(currentNode -> point, *createPoint(coordinates))) {
        return currentNode;
    }

    int comparedDimension = currentDepth % DIMENSIONS;
    if (coordinates[comparedDimension] < currentNode -> point.coordinates[comparedDimension]) {
        return searchKDRecursive(currentNode -> left, coordinates, currentDepth + 1);
    } else {
        return searchKDRecursive(currentNode -> right, coordinates, currentDepth + 1);
    }
}

struct KDNode* searchKDNode(double coordinates[]) {
    return searchKDRecursive(coordinates, KDRoot, 0);
}


struct BTBall {
    struct Point center;
    double radius;
    struct BTBall* left;
    struct BTBall* right;
};

struct BTBall* BTRoot = NULL;

double euclideanDistance(struct Point point1, struct Point point2) {
    double distance = 0;
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        distance += pow(point1.coordinates[dimension] - point2.coordinates[dimension], 2);
    }

    return sqrt(distance);
}

struct Point* subtractPoints(struct Point point1, struct Point point2) {
    struct Point* resultant = (struct Point*) malloc(sizeof(struct Point));
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        resultant -> coordinates[dimension] = point1.coordinates[dimension] - point2.coordinates[dimension];
    }

    return resultant;
}

double dotProduct(struct Point point1, struct Point point2) {
    double resultant = 0;
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        resultant += point1.coordinates[dimension] * point2.coordinates[dimension];
    }

    return resultant;
}


struct Point* getCentroid(struct Point points[], int numPoints) {
    struct Point* centroid = (struct Point*) malloc(sizeof(struct Point));
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        centroid -> coordinates[dimension] = 0;
        for (int pointIndex = 0; pointIndex < numPoints; pointIndex++) {
            centroid -> coordinates[dimension] += points[pointIndex].coordinates[dimension];
        }
    }

    return centroid;
}

struct Point getRadiusEndpoint(struct Point center, struct Point points[], int numPoints) {
    struct Point radiusEndpoint;
    double maximumDistance = 0;

    for (int pointIndex = 0; pointIndex < numPoints; pointIndex++) {
        double currentDistance = euclideanDistance(center, points[pointIndex]);
        if (currentDistance > maximumDistance) {
            maximumDistance = currentDistance;
            radiusEndpoint = points[pointIndex];
        }
    }

    return radiusEndpoint;
}

struct BTBall* createBTBall(double coordinates[], double radius) {
    struct Point* node_point = createPoint(coordinates);
    struct BTBall* node = (struct BTBall*) malloc(sizeof(struct BTBall));

    node -> center = *node_point;
    node -> radius = radius;
    node -> left = node -> right = NULL;
}

struct BTBall* buildRecursive(struct Point points[], int numPoints) {
    if (!numPoints) { return NULL; }

    struct Point centroid = *getCentroid(points, numPoints);
    struct Point radiusEndpoint = getRadiusEndpoint(centroid, points, numPoints);
    struct BTBall* new_ball = createBTBall(centroid.coordinates, euclideanDistance(centroid, radiusEndpoint));

    struct Point centerPlaneNormal = *subtractPoints(centroid, radiusEndpoint);
    struct Point leftPoints[numPoints], rightPoints[numPoints];
    int leftCount = 0, rightCount = 0;

    for (int pointIndex = 0; pointIndex < numPoints; pointIndex++) {
        if (dotProduct(*subtractPoints(points[pointIndex], new_ball -> center), centerPlaneNormal) < 0) {
            leftPoints[leftCount++] = points[pointIndex];
        } else {
            rightPoints[rightCount++] = points[pointIndex];
        }
    }

    new_ball -> left = buildRecursive(leftPoints, leftCount);
    new_ball -> right = buildRecursive(rightPoints, rightCount);

    return new_ball;
}

void buildBTBall(struct Point points[], int numPoints) {
    BTRoot = buildRecursive(points, numPoints);
}


int main() {
    return 0;
}