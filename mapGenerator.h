#include <stdio.h>
#include <time.h>
#include "point.h"

#ifndef STORAGE_FILES

#define STORAGE_FILES
extern char* hospital_storage;
extern char* house_storage;

#endif

#ifndef MAP_PARAMETERS

#define MAP_PARAMETERS
extern int map_size;
extern int num_hospitals;
extern int num_houses;

#endif

struct Point* hospitals;
struct Point* houses;

struct Point* generateRandomMapPoint();

void generateHospitals();
void generateHouses();

void storeHospitals();
void storeHouses();

void initializeMap();