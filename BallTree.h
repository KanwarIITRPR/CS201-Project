#include <stdio.h>
#include <stdlib.h>
#include "point.h"

#define BALL_CAPACITY 2

#ifndef BTBALL_DEFINITION

#define BTBALL_DEFINITION
struct BTBall {
    struct Point center;
    double radius;
    struct BTBall* left;
    struct BTBall* right;

    struct Point* points;
    int numPoints;
};

#endif

extern struct BTBall* BTRoot;

struct Point getCentroid(struct Point points[], int numPoints);
double getRadius(struct Point center, struct Point points[], int numPoints);
struct BTBall* createBTBall(struct Point* points, int numPoints);

struct BTBall* buildBTRecursive(struct Point* points, int numPoints);
void buildBTBall(struct Point* points, int numPoints);

void nearestBTRecursive(struct Point target, struct BTBall* node, struct BTBall* neighbour);
struct Point nearestBTPoint(struct Point target);

void freeBallTree(struct BTBall* node);