#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRECISION 2
#define DIMENSIONS 2

#ifndef POINT_H

#define POINT_H
struct Point {
    double coordinates[DIMENSIONS];
};

#endif

struct Point* createPoint(double coordinates[]);
double euclideanDistance(struct Point point1, struct Point point2);
struct Point* subtractPoints(struct Point point1, struct Point point2);
double dotProduct(struct Point point1, struct Point point2);

void printPoint(struct Point point);