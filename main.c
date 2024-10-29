#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// ----------------------------- Helper Structures & Functions -----------------------------

// Point structure for both KD and Ball Trees
typedef struct Point {
    double *coords;  // Array of coordinates for each dimension
    int dim;         // Dimension of the point
} Point;

// Function to create a Point with given coordinates and dimension
Point createPoint(double *coords, int dim) {
    Point p;
    p.coords = (double *)malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++) {
        p.coords[i] = coords[i];
    }
    p.dim = dim;
    return p;
}

// Calculate Euclidean distance between two points in any dimension
double euclideanDistance(Point *p1, Point *p2) {
    double sum = 0.0;
    for (int i = 0; i < p1->dim; i++) {
        sum += (p1->coords[i] - p2->coords[i]) * (p1->coords[i] - p2->coords[i]);
    }
    return sqrt(sum);
}

// Free memory for a dynamically allocated point
void freePoint(Point *p) {
    free(p->coords);
    p->coords = NULL;
}

// ----------------------------- KD Tree Section -----------------------------

// Structure for a KD Tree node
typedef struct KDNode {
    Point point;               // Point stored at this node
    struct KDNode *left;       // Left subtree
    struct KDNode *right;      // Right subtree
} KDNode;

// Function to create a new KD Tree node with a given point
KDNode* createKDNode(Point point) {
    KDNode* node = (KDNode*)malloc(sizeof(KDNode));
    node->point = point;
    node->left = node->right = NULL;
    return node;
}

// Insert a point into the KD Tree recursively, using depth to alternate dimensions
KDNode* insertKDTree(KDNode *root, Point point, int depth) {
    // Base case: create a new node if we're at an empty spot in the tree
    if (root == NULL) {
        return createKDNode(point);
    }

    // Calculate the current dimension (cycling through dimensions by depth)
    int cd = depth % point.dim;

    // Recursively insert based on the current dimension
    if (point.coords[cd] < root->point.coords[cd]) {
        root->left = insertKDTree(root->left, point, depth + 1);
    } else {
        root->right = insertKDTree(root->right, point, depth + 1);
    }

    return root;
}

// Recursive nearest neighbor search for KD Tree
void nearestNeighborKD(KDNode *root, Point *target, int depth, KDNode **best, double *bestDist) {
    if (root == NULL) return;

    // Calculate distance to the current node's point
    double d = euclideanDistance(&root->point, target);

    // Update the best point if we found a closer one
    if (d < *bestDist) {
        *bestDist = d;
        *best = root;
    }

    // Determine dimension to compare based on depth
    int cd = depth % target->dim;
    KDNode *next = NULL, *other = NULL;

    // Determine which side of the tree to search based on the target coordinate
    if (target->coords[cd] < root->point.coords[cd]) {
        next = root->left;
        other = root->right;
    } else {
        next = root->right;
        other = root->left;
    }

    // Search the next subtree
    nearestNeighborKD(next, target, depth + 1, best, bestDist);

    // Check the other subtree if needed (within best distance)
    if (fabs(root->point.coords[cd] - target->coords[cd]) < *bestDist) {
        nearestNeighborKD(other, target, depth + 1, best, bestDist);
    }
}

// Wrapper function to find the nearest neighbor in the KD Tree
Point findNearestNeighborKD(KDNode *root, Point target) {
    KDNode *best = NULL;
    double bestDist = DBL_MAX;

    nearestNeighborKD(root, &target, 0, &best, &bestDist);

    if (best != NULL) {
        return best->point;
    } else {
        Point nullPoint = {NULL, 0};
        return nullPoint;
    }
}

// Recursive function to free KD Tree nodes
void freeKDTree(KDNode *root) {
    if (root != NULL) {
        freePoint(&root->point);
        freeKDTree(root->left);
        freeKDTree(root->right);
        free(root);
    }
}

// ----------------------------- Ball Tree Section -----------------------------

// Ball Tree node structure
typedef struct BallTreeNode {
    Point center;            // Center of the ball
    double radius;           // Radius of the ball
    struct BallTreeNode *left;   // Left child (sub-ball)
    struct BallTreeNode *right;  // Right child (sub-ball)
    Point *points;           // Points stored if this is a leaf node
    int num_points;          // Number of points in the leaf node
} BallTreeNode;

// Calculate the centroid of a set of points (average of each coordinate)
Point calculateCentroid(Point *points, int num_points, int dim) {
    double *sum = (double *)calloc(dim, sizeof(double));
    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < dim; j++) {
            sum[j] += points[i].coords[j];
        }
    }

    for (int j = 0; j < dim; j++) {
        sum[j] /= num_points;
    }

    Point centroid = createPoint(sum, dim);
    free(sum);
    return centroid;
}

// Calculate the radius of a ball given its center and contained points
double calculateRadius(Point *center, Point *points, int num_points) {
    double max_distance = 0.0;
    for (int i = 0; i < num_points; i++) {
        double dist = euclideanDistance(center, &points[i]);
        if (dist > max_distance) {
            max_distance = dist;
        }
    }
    return max_distance;
}

// Recursively build the Ball Tree with a center point and radius
BallTreeNode* buildBallTree(Point *points, int num_points, int dim) {
    if (num_points == 0) {
        return NULL;
    }

    BallTreeNode *node = (BallTreeNode *)malloc(sizeof(BallTreeNode));
    node->center = calculateCentroid(points, num_points, dim);
    node->radius = calculateRadius(&node->center, points, num_points);
    node->points = points;
    node->num_points = num_points;
    node->left = node->right = NULL;

    if (num_points <= 1) {
        return node;  // Leaf node with single point
    }

    int mid = num_points / 2;
    Point *left_points = points;
    Point *right_points = points + mid;
    
    node->left = buildBallTree(left_points, mid, dim);
    node->right = buildBallTree(right_points, num_points - mid, dim);
    
    return node;
}

// Nearest neighbor search in Ball Tree
void nearestNeighborBall(BallTreeNode *node, Point *target, Point *best, double *bestDist) {
    if (node == NULL) return;

    double dist_to_center = euclideanDistance(target, &node->center);

    if (dist_to_center - node->radius > *bestDist) {
        return;  // Ball is too far, no closer points here
    }

    if (node->left == NULL && node->right == NULL) {
        for (int i = 0; i < node->num_points; i++) {
            double dist = euclideanDistance(target, &node->points[i]);
            if (dist < *bestDist) {
                *bestDist = dist;
                *best = node->points[i];
            }
        }
        return;
    }

    nearestNeighborBall(node->left, target, best, bestDist);
    nearestNeighborBall(node->right, target, best, bestDist);
}

// Wrapper function to find the nearest neighbor in Ball Tree
Point findNearestNeighborBall(BallTreeNode *root, Point target) {
    Point best = target;
    double bestDist = DBL_MAX;
    nearestNeighborBall(root, &target, &best, &bestDist);
    return best;
}

// Free Ball Tree memory recursively
void freeBallTree(BallTreeNode *node) {
    if (node == NULL) return;
    if (node->num_points > 1) {
        freeBallTree(node->left);
        freeBallTree(node->right);
    }
    free(node->center.coords);
    if (node->num_points <= 1) {
        for (int i = 0; i < node->num_points; i++) {
            free(node->points[i].coords);
        }
    }
    free(node);
}

// ----------------------------- Main Function -----------------------------

int main() {
    int dim = 3;  // Example dimension

    // Define some example points
    double coords1[] = {1.0, 2.0, 3.0};
    double coords2[] = {4.0, 5.0, 6.0};
    double coords3[] = {7.0, 8.0, 9.0};
    Point points[] = {createPoint(coords1, dim), createPoint(coords2, dim), createPoint(coords3, dim)};
    int num_points = sizeof(points) / sizeof(Point);

    // Build KD Tree
    KDNode *kdRoot = NULL;
    for (int i = 0; i < num_points; i++) {
        kdRoot = insertKDTree(kdRoot, points[i], 0);
    }

    // Query point for nearest neighbor search
    double query_coords[] = {5.0, 5.0, 5.0};
    Point query_point = createPoint(query_coords, dim);

    // Find nearest in KD Tree
    Point nearestKD = findNearestNeighborKD(kdRoot, query_point);
    printf("Nearest in KD Tree: (%.2f, %.2f, %.2f)\n", nearestKD.coords[0], nearestKD.coords[1], nearestKD.coords[2]);

    // Build Ball Tree and find nearest
    BallTreeNode *ballRoot = buildBallTree(points, num_points, dim);
    Point nearestBall = findNearestNeighborBall(ballRoot, query_point);
    printf("Nearest in Ball Tree: (%.2f, %.2f, %.2f)\n", nearestBall.coords[0], nearestBall.coords[1], nearestBall.coords[2]);

    // Cleanup
    freeKDTree(kdRoot);
    freeBallTree(ballRoot);
    freePoint(&query_point);
    
    return 0;
}
