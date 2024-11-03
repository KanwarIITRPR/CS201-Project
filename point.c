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

int arePointsSame(struct Point point1, struct Point point2) {
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        if (point1.coordinates[dimension] != point2.coordinates[dimension]) {
            return 0;
        }
    }
    return 1;
}

void printPoint(struct Point point) {
    printf("(");
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        printf("%f", point.coordinates[dimension]);
        if (dimension != DIMENSIONS - 1) printf(", ");
    }
    printf(")");
}