#include "point.h"

// Function to create a Point object from an array of coordinates
struct Point* createPoint(double coordinates[]) {
    // Allocate memory for a new Point struct
    struct Point* point = (struct Point*) malloc(sizeof(struct Point));
    // Assign coordinates to the Point struct
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        point->coordinates[dimension] = coordinates[dimension];
    }

    return point; // Return the newly created Point
}

// Function to calculate the Euclidean distance between two Points
double euclideanDistance(struct Point point1, struct Point point2) {
    double distance = 0; // Initialize distance to zero
    // Iterate through each dimension to compute the squared differences
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        distance += pow(point1.coordinates[dimension] - point2.coordinates[dimension], 2);
    }

    return sqrt(distance); // Return the square root of the total distance
}

// Function to check if two Points are the same
int arePointsSame(struct Point point1, struct Point point2) {
    // Iterate through each dimension to compare coordinates
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        // If any coordinate differs, return 0 (false)
        if (point1.coordinates[dimension] != point2.coordinates[dimension]) {
            return 0; // Points are not the same
        }
    }
    return 1; // Points are the same
}

// Function to print the coordinates of a Point
void printPoint(struct Point point) {
    printf("("); // Start of the point representation
    // Iterate through each dimension to print coordinates
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        printf("%f", point.coordinates[dimension]); // Print each coordinate
        if (dimension != DIMENSIONS - 1) printf(", "); // Add a comma if not the last dimension
    }
    printf(")"); // End of the point representation
}
