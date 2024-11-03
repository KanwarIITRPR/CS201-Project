#include <stdio.h>
#include <time.h>
#include <math.h>
#include "point.h"  // Header file for Point structure and related functions

// External variables for storing file paths and map parameters
extern char* hospital_storage;  // Path for hospital location data
extern char* house_storage;     // Path for house location data

// External variables for map size and counts of hospitals and houses
extern int map_size;           // Size of the map
extern int num_hospitals;      // Number of hospitals in the map
extern int num_houses;         // Number of houses in the map

// Definition for the Point arrays to hold hospital and house locations
#ifndef MAP_POINTS
#define MAP_POINTS
struct Point* hospitals;   // Array of Point structures for hospitals
struct Point* houses;      // Array of Point structures for houses
#endif

// Function prototypes
struct Point* generateRandomMapPoint();  // Generates a random point within the map

void generateHospitals();   // Function to generate hospital locations
void generateHouses();      // Function to generate house locations

void storeHospitals();       // Function to save hospital locations to a file
void storeHouses();          // Function to save house locations to a file

void initializeMap();        // Function to initialize the map with hospitals and houses
