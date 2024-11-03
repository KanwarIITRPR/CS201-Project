# Nearest Neighbor Search with KD-Tree and Ball Tree

This project implements an efficient nearest neighbor search in C using **KD-Tree** and **Ball Tree** data structures. Designed for applications that involve spatial or multi-dimensional data, the program calculates the nearest hospital to each house on a 2D map and compares the results between KD-Tree and Ball Tree methods. This project provides insights into both data structures and highlights their efficiency in various dimensional spaces.

## project structure
.
├── main.c                 # Main program file
├── point.h                # Header for Point structure and related functions
├── KDTree.h               # Header for KD-Tree implementation
├── BallTree.h             # Header for Ball Tree implementation
├── mapGenerator.h         # Header for map generation functions
├── Data/
│   ├── results_KD.txt     # Stores nearest hospital coordinates found using KD-Tree
│   ├── results_BT.txt     # Stores nearest hospital coordinates found using Ball Tree
└── README.md              # Project documentation


## Table of Contents
- [Overview](#overview)
- [Background](#background)
  - [KD-Tree](#kd-tree)
  - [Ball Tree](#ball-tree)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Input&Output](#Input&Output)
- [License](#license)

## Overview

The goal of this project is to simulate and evaluate nearest neighbor search algorithms for a set of points. Specifically, it:
1. **Generates Random Coordinates**: Creates a map with points representing houses and hospitals.
2. **Builds Data Structures**: Constructs KD-Tree and Ball Tree structures from hospital coordinates.
3. **Finds Nearest Neighbors**: Uses both KD-Tree and Ball Tree to find the closest hospital for each house.
4. **Compares Results**: Compares the accuracy and efficiency of KD-Tree and Ball Tree results, storing these in text files for further analysis.

This program is useful in fields such as geographic information systems (GIS), computer vision, and machine learning where efficient high-dimensional spatial queries are essential.

## Background

### KD-Tree

A KD-Tree (K-dimensional tree) is a binary tree in which each node is a k-dimensional point. KD-Trees are widely used for range searches and nearest neighbor searches, especially in low-dimensional data. Nodes are divided by alternating dimensions at each level, allowing for efficient spatial partitioning.

### Ball Tree

Ball Trees are an alternative to KD-Trees, particularly suited for higher-dimensional data. Ball Trees organize points into "balls," or clusters, based on distance metrics. Each ball can be recursively divided into sub-balls, allowing efficient partitioning for nearest neighbor searches.

## Project Structure


Here’s an expanded version of the README.md file that goes into more detail for each section.

markdown
Copy code
# Nearest Neighbor Search with KD-Tree and Ball Tree

This project implements an efficient nearest neighbor search in C using **KD-Tree** and **Ball Tree** data structures. Designed for applications that involve spatial or multi-dimensional data, the program calculates the nearest hospital to each house on a 2D map and compares the results between KD-Tree and Ball Tree methods. This project provides insights into both data structures and highlights their efficiency in various dimensional spaces.

## Table of Contents
- [Overview](#overview)
- [Background](#background)
  - [KD-Tree](#kd-tree)
  - [Ball Tree](#ball-tree)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [License](#license)

## Overview

The goal of this project is to simulate and evaluate nearest neighbor search algorithms for a set of points. Specifically, it:
1. **Generates Random Coordinates**: Creates a map with points representing houses and hospitals.
2. **Builds Data Structures**: Constructs KD-Tree and Ball Tree structures from hospital coordinates.
3. **Finds Nearest Neighbors**: Uses both KD-Tree and Ball Tree to find the closest hospital for each house.
4. **Compares Results**: Compares the accuracy and efficiency of KD-Tree and Ball Tree results, storing these in text files for further analysis.

This program is useful in fields such as geographic information systems (GIS), computer vision, and machine learning where efficient high-dimensional spatial queries are essential.

## Background

### KD-Tree

A KD-Tree (K-dimensional tree) is a binary tree in which each node is a k-dimensional point. KD-Trees are widely used for range searches and nearest neighbor searches, especially in low-dimensional data. Nodes are divided by alternating dimensions at each level, allowing for efficient spatial partitioning.

### Ball Tree

Ball Trees are an alternative to KD-Trees, particularly suited for higher-dimensional data. Ball Trees organize points into "balls," or clusters, based on distance metrics. Each ball can be recursively divided into sub-balls, allowing efficient partitioning for nearest neighbor searches.

## Project Structure

nearest_neighbor_search ├── src │ ├── main.c # Main program with nearest neighbor search logic │ ├── KDTree.c # KD-Tree implementation │ ├── BallTree.c # Ball Tree implementation │ ├── point.c # Point structure and operations │ ├── mapGenerator.c # Generates random points for houses and hospitals ├── include │ ├── KDTree.h # KD-Tree function declarations │ ├── BallTree.h # Ball Tree function declarations │ ├── point.h # Point structure and utility functions │ ├── mapGenerator.h # Map generator function declarations ├── Data │ ├── results_KD.txt # Output file for KD-Tree results │ ├── results_BT.txt # Output file for Ball Tree results ├── README.md # Project documentation └── Makefile # Makefile for building and running the project


## Dependencies

- **C Standard Libraries**: Includes `<stdio.h>`, `<stdlib.h>`, and `<math.h>`.
- **Make**: For building the project with `make`.

## Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/nearest_neighbor_search.git
   cd nearest_neighbor_search

## Input&Output
No explicit user input is required during execution. The program generates a random map of houses and hospitals within the initializeMap() function (located in mapGenerator.h).

Map Parameters
To adjust the map parameters, modify the following variables in the source code:

num_houses - The number of house points in the map.
num_hospitals - The number of hospital points in the map.
Coordinate Dimensions
The number of dimensions is set by the DIMENSIONS macro (set to 2 by default), meaning each point will have an x and y coordinate.

Output
The program outputs the results to the console and writes data to two files. Here’s what to expect:

Console Output
The program will print:

The coordinates of each hospital as it’s added to the KD-Tree.
The coordinates of the nearest hospital for each house as found by both KD-Tree and Ball Tree.
Whether or not the KD-Tree and Ball Tree produced the same result for each house.
A summary of how many times the two methods produced the same results.
Example console output:
MAP GENERATED!
KD TREE GENERATED!
BALL TREE GENERATED!
Nearest Hospital to (3.23, 5.11) is:
(4.56, 5.23) using K-Dimensional Trees
(4.56, 5.23) using Ball Trees
Result from K-Dimensional Trees and Ball Trees is same

K-Dimensional Trees and Ball Trees produce same results 95/100 times

Output Files
Data/results_KD.txt - Contains coordinates of the nearest hospitals found for each house using the KD-Tree. Each line represents the coordinates of the nearest hospital for a house.
Data/results_BT.txt - Contains coordinates of the nearest hospitals found for each house using the Ball Tree. Each line represents the coordinates of the nearest hospital for a house.
Example content for Data/results_KD.txt:
4.56 5.23
6.78 8.12
3.34 2.15
...

## license 

This version of the `README.md` includes a more comprehensive overview of each section, additional context on each data structure, and more detail in the time complexity and future improvements sections. Adjust specific project details like repository links as needed.


