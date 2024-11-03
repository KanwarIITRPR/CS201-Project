#include "mapGenerator.h"

char* hospital_storage = "Data/hospital_location.txt";
char* house_storage = "Data/house_location.txt";
char* map_parameters = "Data/map_parameters.txt";

int map_size;
int num_hospitals;
int num_houses;

struct Point* hospitals = NULL;
struct Point* houses = NULL;

void extractMapParameters() {
    FILE* file = fopen(map_parameters, "r");

    fscanf(file, "%d", &map_size);
    fscanf(file, "%d", &num_hospitals);
    fscanf(file, "%d", &num_houses);

    fclose(file);
}

struct Point* generateRandomMapPoint() {
    double coordinates[DIMENSIONS];
    int float_factor = pow(10, PRECISION);
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        coordinates[dimension] = (double) (rand() % ((map_size * float_factor) + 1)) / float_factor;
    }

    return createPoint(coordinates);
}

void generateHouses() {
    houses = (struct Point*) calloc(num_houses, sizeof(struct Point));
    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        houses[house_idx] = *generateRandomMapPoint();
    }
}

void generateHospitals() {
    hospitals = (struct Point*) calloc(num_hospitals, sizeof(struct Point));
    for (int hospital_idx = 0; hospital_idx < num_hospitals; hospital_idx++) {
        hospitals[hospital_idx] = *generateRandomMapPoint();
    }
}

void storeHouses() {
    FILE* file = fopen(house_storage, "w");

    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", houses[house_idx].coordinates[dimension]);
        }
        fprintf(file, "%c", '\n');
    }

    fclose(file);
}

void storeHospitals() {
    FILE* file = fopen(hospital_storage, "w");

    for (int hospital_idx = 0; hospital_idx < num_hospitals; hospital_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", hospitals[hospital_idx].coordinates[dimension]);
        }
        fprintf(file, "%c", '\n');
    }

    fclose(file);
}

void initializeMap() {
    srand(time(0));
    extractMapParameters();

    generateHospitals();
    storeHospitals();

    generateHouses();
    storeHouses();
}