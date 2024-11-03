#include "BallTree.h"

// Root of the Ball Tree
struct BTBall* BTRoot = NULL;

// Function to calculate the centroid of a set of points
struct Point getCentroid(struct Point points[], int numPoints) {
    double centroid_coordinates[DIMENSIONS];
    // Initialize centroid coordinates to zero for each dimension
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        centroid_coordinates[dimension] = 0;
        // Sum the coordinates for the current dimension across all points
        for (int point_idx = 0; point_idx < numPoints; point_idx++) {
            centroid_coordinates[dimension] += points[point_idx].coordinates[dimension];
        }
        // Calculate the average for the dimension
        centroid_coordinates[dimension] /= numPoints;
    }

    // Return the centroid as a Point structure
    return *createPoint(centroid_coordinates);
}

// Function to calculate the radius of a ball centered at 'center' covering 'points'
double getRadius(struct Point center, struct Point points[], int numPoints) {
    double maximumDistance = 0;
    // Iterate through each point to find the maximum distance from the center
    for (int point_idx = 0; point_idx < numPoints; point_idx++) {
        double currentDistance = euclideanDistance(center, points[point_idx]);
        if (currentDistance > maximumDistance) {
            maximumDistance = currentDistance;
        }
    }
    return maximumDistance;
}

// Function to create a ball with a center, radius, and points
struct BTBall* createBTBall(struct Point* points, int numPoints) {
    struct BTBall* ball = (struct BTBall*) malloc(sizeof(struct BTBall));
    // Set ball center and radius based on provided points
    ball -> center = getCentroid(points, numPoints);
    ball -> radius = getRadius(ball -> center, points, numPoints);
    // Initialize children pointers to NULL
    ball -> left = ball -> right = NULL;

    // Assign points and their count to the ball
    ball -> points = points;
    ball -> numPoints = numPoints;
}

// Recursive function to build the Ball Tree
struct BTBall* buildBTRecursive(struct Point* points, int numPoints) {
    // Base case: return NULL if there are no points
    if (numPoints == 0) {
        return NULL;
    }

    // Create a ball for the current set of points
    struct BTBall* ball = createBTBall(points, numPoints);
    // If the number of points is within the ball capacity, return the ball as a leaf node
    if (numPoints <= BALL_CAPACITY) {
        return ball;
    }

    // Split the points into two halves
    int midPoint = numPoints / 2;
    struct Point* left_points = points;
    struct Point* right_points = points + midPoint;
    
    // Recursively build the left and right subtrees
    ball -> left = buildBTRecursive(left_points, midPoint);
    ball -> right = buildBTRecursive(right_points, numPoints - midPoint);
    
    return ball;
}

// Function to initialize the construction of the Ball Tree
void buildBTBall(struct Point* points, int numPoints) {
    BTRoot = buildBTRecursive(points, numPoints);
}

// Recursive function to find the nearest neighbor in the Ball Tree
void nearestBTRecursive(struct Point target, struct BTBall* node, struct BTBall* neighbour) {
    // Base case: if node is NULL, return
    if (!node) {
        return;
    }

    // Calculate minimum distance to the current nearest neighbor
    double minimumDistance = euclideanDistance(target, neighbour -> center);
    // Calculate distance to the center of the current ball
    double currentBallDistance = euclideanDistance(target, node -> center);

    // If the current ball is further than the nearest neighbor, skip recursion
    if (currentBallDistance - node -> radius > minimumDistance) {
        return;
    }

    // If the node is a leaf (no children), return
    if (!node -> left && !node -> right) {
        return;
    }

    // Recursively search in the left and right subtrees
    nearestBTRecursive(target, node -> left, neighbour);
    nearestBTRecursive(target, node -> right, neighbour);
}

// Function to find the nearest point to a target in the Ball Tree
struct Point nearestBTPoint(struct Point target) {
    // Start search with root node as the nearest neighbor
    struct BTBall* neighbourBall = BTRoot;
    nearestBTRecursive(target, BTRoot, neighbourBall);
    
    // Initialize nearest point and minimum distance
    struct Point neighbour = neighbourBall -> points[0];
    double minimumDistance = euclideanDistance(target, neighbour);
    // Iterate through points in the nearest ball to find the closest point
    for (int point_idx = 1; point_idx < neighbourBall -> numPoints; point_idx++) {
        double currentDistance = euclideanDistance(target, neighbourBall -> points[point_idx]);
        if (currentDistance < minimumDistance) {
            minimumDistance = currentDistance;
            neighbour = neighbourBall -> points[point_idx];
        }
    }

    return neighbour;
}

// Function to free the memory allocated for the Ball Tree
void freeBallTree(struct BTBall* node) {
    // Base case: if node is NULL, return
    if (!node) {
        return;
    }

    // If the node is not a leaf, recursively free the children
    if (node -> numPoints > BALL_CAPACITY) {
        freeBallTree(node -> left);
        freeBallTree(node -> right);
    } else {
        // If the node is a leaf, free the points
        for (int point_idx = 0; point_idx < node -> numPoints; point_idx++) {
            free(node -> points);
        }
    }

    // Free the node itself
    free(node);
}
