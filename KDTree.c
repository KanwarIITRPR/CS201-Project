#include "KDTree.h"

// Root of the KD-Tree
struct KDNode* KDRoot = NULL;

// Function to create a new KD-Tree node
struct KDNode* createKDNode(struct Point point) {
    struct KDNode* node = (struct KDNode*) malloc(sizeof(struct KDNode));
    node->point = point;      // Set the point data
    node->left = node->right = NULL;  // Initialize children as NULL
    return node;
}

// Recursive function to insert a point into the KD-Tree
struct KDNode* insertKDRecursive(struct Point point, struct KDNode* node, int depth) {
    // Base case: create a new node if we reach a NULL node
    if (!node) {
        return createKDNode(point);
    }

    // Determine the dimension to compare based on depth
    int comparingDimension = depth % DIMENSIONS;

    // Recursive insertion based on the comparing dimension
    if (point.coordinates[comparingDimension] < node->point.coordinates[comparingDimension]) {
        node->left = insertKDRecursive(point, node->left, depth + 1);
    } else {
        node->right = insertKDRecursive(point, node->right, depth + 1);
    }

    return node;
}

// Wrapper function to start insertion from the root
void insertKDNode(struct Point point) {
    KDRoot = insertKDRecursive(point, KDRoot, 0);
}

// Recursive function to find the nearest neighbor in the KD-Tree
void nearestKDNode(struct Point target, struct KDNode* node, int depth, struct KDNode** neighbour) {
    // Base case: return if the node is NULL
    if (!node) {
        return;
    }

    // Calculate distances to the current nearest neighbor and the current node
    double minimumDistance = euclideanDistance(target, (*neighbour)->point);
    double currentDistance = euclideanDistance(target, node->point);

    // Update the nearest neighbor if the current node is closer
    if (currentDistance < minimumDistance) {
        *neighbour = node;
    }

    // Determine the dimension to compare based on depth
    int comparingDimension = depth % DIMENSIONS;

    // Decide which subtree to search first (nextSearchNode) and the other subtree (otherSearchNode)
    struct KDNode* nextSearchNode = NULL;
    struct KDNode* otherSearchNode = NULL;

    if (target.coordinates[comparingDimension] < node->point.coordinates[comparingDimension]) {
        nextSearchNode = node->left;
        otherSearchNode = node->right;
    } else {
        nextSearchNode = node->right;
        otherSearchNode = node->left;
    }

    // Recursive search in the next subtree
    nearestKDNode(target, nextSearchNode, depth + 1, neighbour);

    // If there's a chance the other subtree has a closer point, search it as well
    if (fabs(node->point.coordinates[comparingDimension] - target.coordinates[comparingDimension]) < minimumDistance) {
        nearestKDNode(target, otherSearchNode, depth + 1, neighbour);
    }
}

// Function to find the nearest point to a target in the KD-Tree
struct Point nearestKDPoint(struct Point target) {
    struct KDNode* neighbour = KDRoot;  // Initialize the nearest neighbor with the root
    nearestKDNode(target, KDRoot, 0, &neighbour);  // Start recursive search
    return neighbour->point;  // Return the nearest point found
}

// Function to free all memory allocated for the KD-Tree
void freeKDTree(struct KDNode* node) {
    if (node) {
        // Recursively free left and right subtrees
        freeKDTree(node->left);
        freeKDTree(node->right);
        // Free the current node
        free(node);
    }
}
