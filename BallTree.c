#include "BallTree.h"

struct BTBall* BTRoot = NULL;

struct Point getCentroid(struct Point points[], int numPoints) {
    double centroid_coordinates[DIMENSIONS];
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        centroid_coordinates[dimension] = 0;
        for (int point_idx = 0; point_idx < numPoints; point_idx++) {
            centroid_coordinates[dimension] += points[point_idx].coordinates[dimension];
        }
        centroid_coordinates[dimension] /= numPoints;
    }

    return *createPoint(centroid_coordinates);
}

double getRadius(struct Point center, struct Point points[], int numPoints) {
    double maximumDistance = 0;
    for (int point_idx = 0; point_idx < numPoints; point_idx++) {
        double currentDistance = euclideanDistance(center, points[point_idx]);
        if (currentDistance > maximumDistance) {
            maximumDistance = currentDistance;
        }
    }
    return maximumDistance;
}

struct BTBall* createBTBall(struct Point* points, int numPoints) {
    struct BTBall* ball = (struct BTBall*) malloc(sizeof(struct BTBall));
    ball -> center = getCentroid(points, numPoints);
    ball -> radius = getRadius(ball -> center, points, numPoints);
    ball -> left = ball -> right = NULL;

    ball -> points = points;
    ball -> numPoints = numPoints;
}

struct BTBall* buildBTRecursive(struct Point* points, int numPoints) {
    if (numPoints == 0) {
        return NULL;
    }

    struct BTBall* ball = createBTBall(points, numPoints);
    if (numPoints <= BALL_CAPACITY) {
        return ball;
    }

    int midPoint = numPoints / 2;
    struct Point* left_points = points;
    struct Point* right_points = points + midPoint;
    
    ball -> left = buildBTRecursive(left_points, midPoint);
    ball -> right = buildBTRecursive(right_points, numPoints - midPoint);
    
    return ball;
}

void buildBTBall(struct Point* points, int numPoints) {
    BTRoot = buildBTRecursive(points, numPoints);
}

void nearestBTRecursive(struct Point target, struct BTBall* node, struct BTBall* neighbour) {
    if (!node) {
        return;
    }

    double minimumDistance = euclideanDistance(target, neighbour -> center);
    double currentBallDistance = euclideanDistance(target, node -> center);

    if (currentBallDistance - node -> radius > minimumDistance) {
        return;
    }

    if (!node -> left && !node -> right) {
        return;
    }

    nearestBTRecursive(target, node -> left, neighbour);
    nearestBTRecursive(target, node -> right, neighbour);
}

struct Point nearestBTPoint(struct Point target) {
    struct BTBall* neighbourBall = BTRoot;
    nearestBTRecursive(target, BTRoot, neighbourBall);
    
    struct Point neighbour = neighbourBall -> points[0];
    double minimumDistance = euclideanDistance(target, neighbour);
    for (int point_idx = 1; point_idx < neighbourBall -> numPoints; point_idx++) {
        double currentDistance = euclideanDistance(target, neighbourBall -> points[point_idx]);
        if (currentDistance < minimumDistance) {
            minimumDistance = currentDistance;
            neighbour = neighbourBall -> points[point_idx];
        }
    }

    return neighbour;
}

void freeBallTree(struct BTBall* node) {
    if (!node) {
        return;
    }

    if (node -> numPoints > BALL_CAPACITY) {
        freeBallTree(node -> left);
        freeBallTree(node -> right);
    } else {
        for (int point_idx = 0; point_idx < node -> numPoints; point_idx++) {
            free(node -> points);
        }
    }

    free(node);
}