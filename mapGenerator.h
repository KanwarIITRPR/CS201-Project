#include <stdio.h>
#include <time.h>
#include <math.h>
#include "point.h"

extern char* hospital_storage;
extern char* house_storage;

extern int map_size;
extern int num_hospitals;
extern int num_houses;

#ifndef MAP_POINTS

#define MAP_POINTS
struct Point* hospitals;
struct Point* houses;

#endif

struct Point* generateRandomMapPoint();

void generateHospitals();
void generateHouses();

void storeHospitals();
void storeHouses();

void initializeMap();