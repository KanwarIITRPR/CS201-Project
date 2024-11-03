#include "mapGenerator.h"

// File paths for storing map data
char* hospital_storage = "Data/hospital_location.txt";
char* house_storage = "Data/house_location.txt";
char* map_parameters = "Data/map_parameters.txt";

// Map parameters
int map_size;           // Size of the map
int num_hospitals;      // Number of hospitals on the map
int num_houses;         // Number of houses on the map

// Arrays to store hospital and house locations as Point structures
struct Point* hospitals = NULL;
struct Point* houses = NULL;

// Reads map parameters from a file and stores them in global variables
void extractMapParameters() {
    FILE* file = fopen(map_parameters, "r");   // Open map parameters file in read mode

    // Read map size, number of hospitals, and number of houses
    fscanf(file, "%d", &map_size);
    fscanf(file, "%d", &num_hospitals);
    fscanf(file, "%d", &num_houses);

    fclose(file);   // Close the file after reading
}

// Generates a random point within the map boundaries
struct Point* generateRandomMapPoint() {
    double coordinates[DIMENSIONS];            // Array to hold coordinates
    int float_factor = pow(10, PRECISION);     // Factor to adjust for decimal precision

    // Generate a random coordinate for each dimension
    for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
        coordinates[dimension] = (double) (rand() % ((map_size * float_factor) + 1)) / float_factor;
    }

    return createPoint(coordinates);  // Return a dynamically allocated Point with generated coordinates
}

// Generates random locations for houses and stores them in the global 'houses' array
void generateHouses() {
    houses = (struct Point*) calloc(num_houses, sizeof(struct Point));  // Allocate memory for house locations

    // Generate a random point for each house
    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        houses[house_idx] = *generateRandomMapPoint();
    }
}

// Generates random locations for hospitals and stores them in the global 'hospitals' array
void generateHospitals() {
    hospitals = (struct Point*) calloc(num_hospitals, sizeof(struct Point));  // Allocate memory for hospital locations

    // Generate a random point for each hospital
    for (int hospital_idx = 0; hospital_idx < num_hospitals; hospital_idx++) {
        hospitals[hospital_idx] = *generateRandomMapPoint();
    }
}

// Saves the generated house locations to the specified file
void storeHouses() {
    FILE* file = fopen(house_storage, "w");  // Open file in write mode

    // Write each house's coordinates to the file
    for (int house_idx = 0; house_idx < num_houses; house_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", houses[house_idx].coordinates[dimension]);
        }
        fprintf(file, "%c", '\n');  // Newline after each house's coordinates
    }

    fclose(file);   // Close the file after writing
}

// Saves the generated hospital locations to the specified file
void storeHospitals() {
    FILE* file = fopen(hospital_storage, "w");  // Open file in write mode

    // Write each hospital's coordinates to the file
    for (int hospital_idx = 0; hospital_idx < num_hospitals; hospital_idx++) {
        for (int dimension = 0; dimension < DIMENSIONS; dimension++) {
            fprintf(file, "%f ", hospitals[hospital_idx].coordinates[dimension]);
        }
        fprintf(file, "%c", '\n');  // Newline after each hospital's coordinates
    }

    fclose(file);   // Close the file after writing
}

// Initializes the map by generating and storing locations for hospitals and houses
void initializeMap() {
    srand(time(0));              // Seed the random number generator for randomness
    extractMapParameters();      // Read map size and number of entities from file

    generateHospitals();         // Generate hospital locations
    storeHospitals();            // Save hospital locations to file

    generateHouses();            // Generate house locations
    storeHouses();               // Save house locations to file
}
