# Nearest Neighbor Search with KD-Tree and Ball Tree

This project implements an efficient nearest neighbor search in C using **KD-Tree** and **Ball Tree** data structures. Designed for applications that involve spatial or multi-dimensional data, the program calculates the nearest hospital to each house on a 2D map and compares the results between KD-Tree and Ball Tree methods. This project provides insights into both data structures and highlights their efficiency in various dimensional spaces.

## Project Structure
📁 Project
- ```main.c``` includes all the files together and compiles them for output
- ```point.h/point.c``` includes all the declarations and definitions for the function related to points. Points are essential to locate the places which we'll be applying the Data Structure on.
- ```mapGenerator.h/mapGenerator.c``` includes all the declarations and definitions for generating a map containting houses and hospitals
- ```KDTree.h/KDTree.c``` includes all the declarations and definitions for using and implementing a KD Tree
- ```BallTree.h/BallTree.c``` includes all the declarations and definitions for using and implementing a Ball Tree
- ```storeData.h/storeData.c``` includes all the declarations and definitions for storing the data into text files, which will later be accessed for plotting
- ```mapPlotter.py``` is a Python file, used solely for the purpose of making plots (as allowed by our mentor)
- 📁 **Plot** stores all the plots made for nearest neighbors found while the visualizations of tree's structures
- 📁 **Data** stores all the data of the trees and nearest neighbors found when running the function

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

Ball Trees are an alternative to KD-Trees, particularly suited for higher-dimensional data. Ball Trees organize points into "balls" or clusters, based on distance metrics. Each ball can be recursively divided into sub-balls, allowing efficient partitioning for nearest neighbor searches.

## Dependencies

- **C Standard Libraries**: Includes `<stdio.h>`, `<stdlib.h>`, and `<math.h>`.
- **Make**: For building the project with `make`.

## Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/KanwarIITRPR/CS201-Project.git
   cd nearest_neighbor_search

2. **Run the proect in the terminal**
   ```bash
   gcc main.c point.c mapGenerator.c KDTree.c BallTree.c storeData.c -o a
   ./a/exe
   
## Input
No explicit user input is required during execution. The program generates a random map of houses and hospitals within the initializeMap() function (located in mapGenerator.h).

Map Parameters
To adjust the map parameters, modify the following variables in the source code:

- map_size - The size of the map.
- num_houses - The number of house points in the map.
- num_hospitals - The number of hospital points in the map.

The number of dimensions is set by the DIMENSIONS macro (set to 2 by default), meaning each point will have an x and y coordinate.

Output
The program outputs the results to the console and writes data to two files. Here’s what to expect:

Console Output
The program will print:

- The coordinates of each hospital as it’s added to the KD-Tree.
- The coordinates of the nearest hospital for each house as found by both KD-Tree and Ball Tree.
- Whether or not the KD-Tree and Ball Tree produced the same result for each house.
- A summary of how many times the two methods produced the same results.

**Example console output:**
```
Nearest Hospital to (3.23, 5.11) is:
(4.56, 5.23) using K-Dimensional Trees
(4.56, 5.23) using Ball Trees
Result from K-Dimensional Trees and Ball Trees is same

K-Dimensional Trees and Ball Trees produce same results 95/100 times
```
**Output Files**
```Data/results_KD.txt``` - Contains coordinates of the nearest hospitals found for each house using the KD-Tree. Each line represents the coordinates of the nearest hospital for a house.
```Data/results_BT.txt``` - Contains coordinates of the nearest hospitals found for each house using the Ball Tree. Each line represents the coordinates of the nearest hospital for a house.

**Example content for Data/results_KD.txt:**
```4.56 5.23
6.78 8.12
3.34 2.15```
...