#include "point.h"

struct Point* createPoint(double coordinates[]) {
    struct Point* point = (struct Point*) malloc(sizeof(struct Point));
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        point -> coordinates[dimension] = coordinates[dimension];
    }

    return point;
}

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

void printPoint(struct Point point) {
    printf("(");
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        printf("%f", point.coordinates[dimension]);
        if (dimension != DIMENSIONS - 1) printf(", ");
    }
    printf(")");
}