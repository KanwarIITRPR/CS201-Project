#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define constants for precision and dimensions
#define PRECISION 2
#define DIMENSIONS 2

// Include guard to prevent multiple inclusions of this header file
#ifndef POINT_H
#define POINT_H

// Structure to represent a point in a multi-dimensional space
struct Point {
    double coordinates[DIMENSIONS]; // Array to hold coordinates of the point
};

#endif // End of the include guard

// Function prototypes for operations on Points
struct Point* createPoint(double coordinates[]); // Create a new Point from an array of coordinates
double euclideanDistance(struct Point point1, struct Point point2); // Calculate the distance between two Points
int arePointsSame(struct Point point1, struct Point point2); // Check if two Points are the same
void printPoint(struct Point point); // Print the coordinates of a Point
