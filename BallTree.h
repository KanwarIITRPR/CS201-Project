#include <stdio.h>
#include <stdlib.h>
#include "point.h"  // Include point structure and related functions

#define BALL_CAPACITY 2  // Maximum number of points per ball (leaf node)

// Structure definition for a ball in the Ball Tree
#ifndef BTBALL_DEFINITION
#define BTBALL_DEFINITION

struct BTBall {
    struct Point center;     // Center of the ball
    double radius;           // Radius of the ball
    struct BTBall* left;     // Pointer to the left child (sub-ball)
    struct BTBall* right;    // Pointer to the right child (sub-ball)

    struct Point* points;    // Array of points contained within the ball (if it's a leaf node)
    int numPoints;           // Number of points in the ball
};

#endif

// Declaration of the root of the Ball Tree, defined in another file
extern struct BTBall* BTRoot;

// Function declarations for Ball Tree operations

// Calculates the centroid of a given set of points
struct Point getCentroid(struct Point points[], int numPoints);

// Calculates the radius of a ball to cover all points from the center
double getRadius(struct Point center, struct Point points[], int numPoints);

// Creates a new ball (BTBall) structure from a set of points
struct BTBall* createBTBall(struct Point* points, int numPoints);

// Recursively builds the Ball Tree from a given set of points
struct BTBall* buildBTRecursive(struct Point* points, int numPoints);

// Initializes the Ball Tree construction and sets the root
void buildBTBall(struct Point* points, int numPoints);

// Recursively finds the nearest neighbor for a target point within a ball
void nearestBTRecursive(struct Point target, struct BTBall* node, struct BTBall* neighbour);

// Finds the nearest point to a target point in the Ball Tree
struct Point nearestBTPoint(struct Point target);

// Frees the memory allocated for the Ball Tree nodes and their points
void freeBallTree(struct BTBall* node);
