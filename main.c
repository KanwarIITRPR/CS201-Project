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
