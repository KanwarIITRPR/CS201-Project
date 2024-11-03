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


This version of the `README.md` includes a more comprehensive overview of each section, additional context on each data structure, and more detail in the time complexity and future improvements sections. Adjust specific project details like repository links as needed.


