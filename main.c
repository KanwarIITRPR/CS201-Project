#include <stdio.h>
#include <stdlib.h>

#define K 2  // Dimensionality, here 2D for simplicity

// Structure to represent a node in the K-D Tree
struct KDNode {
    int point[K];  // Array to store k-dimensional point
    struct KDNode* left;
    struct KDNode* right;
};

// Function to create a new K-D Tree node
struct KDNode* createNode(int point[]) {
    struct KDNode* node = (struct KDNode*)malloc(sizeof(struct KDNode));
    for (int i = 0; i < K; i++)
        node->point[i] = point[i];
    node->left = node->right = NULL;
    return node;
}
// Inserts a new point into the KD Tree. Dimension indicates the axis (0 or 1 in 2D)
struct KDNode* insertRec(struct KDNode* root, int point[], unsigned depth) {
    // Base case: Empty tree
    if (root == NULL)
        return createNode(point);

    // Current dimension to compare with
    unsigned cd = depth % K;

    // Compare the point with the root based on the cd (current dimension) and insert accordingly
    if (point[cd] < root->point[cd])
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

// Function to insert a point into the K-D Tree
struct KDNode* insert(struct KDNode* root, int point[]) {
    return insertRec(root, point, 0);
}
// A utility function to check if two points are the same
int arePointsSame(int point1[], int point2[]) {
    for (int i = 0; i < K; ++i)
        if (point1[i] != point2[i])
            return 0;
    return 1;
}

// Function to search a point in the K-D Tree
int searchRec(struct KDNode* root, int point[], unsigned depth) {
    // Base case: tree is empty or the point is found
    if (root == NULL)
        return 0;
    if (arePointsSame(root->point, point))
        return 1;

    // Current dimension to compare with
    unsigned cd = depth % K;

    // Compare the point with root and recursively search in the left or right subtree
    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);
    return searchRec(root->right, point, depth + 1);
}

// Function to search a point in the K-D Tree
int search(struct KDNode* root, int point[]) {
    return searchRec(root, point, 0);
}

#define DIM 2  // Number of dimensions (2D in this case)

// Structure to represent a point in space
typedef struct Point {
    double coords[DIM];  // Coordinates of the point
} Point;

// Structure to represent a node in the Ball Tree
typedef struct BallTreeNode {
    Point center;       // Center of the ball
    double radius;      // Radius of the ball
    struct BallTreeNode *left;  // Left subtree
    struct BallTreeNode *right; // Right subtree
    Point *points;      // Points stored in this node (for leaf nodes)
    int numPoints;      // Number of points stored (for leaf nodes)
} BallTreeNode;

// Function to calculate the Euclidean distance between two points
double euclideanDistance(Point *p1, Point *p2) {
    double sum = 0.0;
    for (int i = 0; i < DIM; i++) {
        sum += (p1->coords[i] - p2->coords[i]) * (p1->coords[i] - p2->coords[i]);
    }
    return sqrt(sum);
}

// Function to calculate the centroid (center) of a set of points
Point calculateCentroid(Point *points, int numPoints) {
    Point centroid = {{0.0}};
    for (int i = 0; i < numPoints; i++) {
        for (int j = 0; j < DIM; j++) {
            centroid.coords[j] += points[i].coords[j];
        }
    }
    for (int j = 0; j < DIM; j++) {
        centroid.coords[j] /= numPoints;
    }
    return centroid;
}

// Function to calculate the radius of the ball (maximum distance from center)
double calculateRadius(Point *center, Point *points, int numPoints) {
    double maxDist = 0.0;
    for (int i = 0; i < numPoints; i++) {
        double dist = euclideanDistance(center, &points[i]);
        if (dist > maxDist) {
            maxDist = dist;
        }
    }
    return maxDist;
}

// Function to build a Ball Tree recursively
BallTreeNode* buildBallTree(Point *points, int numPoints) {
    if (numPoints == 0) return NULL;

    BallTreeNode *node = (BallTreeNode*)malloc(sizeof(BallTreeNode));

    // Calculate the center (centroid) and radius for the current node
    node->center = calculateCentroid(points, numPoints);
    node->radius = calculateRadius(&node->center, points, numPoints);

    if (numPoints <= 2) {  // Base case: if the node has 1 or 2 points, make it a leaf node
        node->points = points;
        node->numPoints = numPoints;
        node->left = node->right = NULL;
    } else {
        // Split the points into two groups based on their distance from the centroid
        Point *leftPoints = (Point*)malloc(sizeof(Point) * numPoints);
        Point *rightPoints = (Point*)malloc(sizeof(Point) * numPoints);
        int leftCount = 0, rightCount = 0;

        for (int i = 0; i < numPoints; i++) {
            if (euclideanDistance(&node->center, &points[i]) < node->radius / 2) {
                leftPoints[leftCount++] = points[i];
            } else {
                rightPoints[rightCount++] = points[i];
            }
        }

        // Recursively build the left and right subtrees
        node->left = buildBallTree(leftPoints, leftCount);
        node->right = buildBallTree(rightPoints, rightCount);
        node->points = NULL;  // This is not a leaf node
        node->numPoints = 0;
    }

    return node;
}

// Function to print a Ball Tree (for debugging)
void printBallTree(BallTreeNode *node, int depth) {
    if (node == NULL) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Node: Center (%.2f, %.2f), Radius: %.2f\n", node->center.coords[0], node->center.coords[1], node->radius);

    if (node->left == NULL && node->right == NULL) {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("Leaf: %d points\n", node->numPoints);
        for (int i = 0; i < node->numPoints; i++) {
            for (int j = 0; j < DIM; j++) {
                printf(" %.2f", node->points[i].coords[j]);
            }
            printf("\n");
        }
    } else {
        printBallTree(node->left, depth + 1);
        printBallTree(node->right, depth + 1);
    }
}

int main() {
    struct KDNode* root = NULL;

    // Points to be inserted in the K-D Tree
    int points[][K] = {{3, 6}, {17, 15}, {13, 15}, {6, 12},
                       {9, 1}, {2, 7}, {10, 19}};

    int n = sizeof(points) / sizeof(points[0]);

    // Insert points into the tree
    for (int i = 0; i < n; i++)
        root = insert(root, points[i]);

    // Search for a point in the tree
    int point[] = {10, 19};
    if (search(root, point))
        printf("Point found.\n");
    else
        printf("Point not found.\n");

    return 0;
}
