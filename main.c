# include<stdio.h>
# include<stdlib.h>

typedef struct {
    int* vector;
} Point;

int dimensions;

int main() {
    prnitf("Enter the dimensions for the vectors: ");
    scanf("%d", &dimensions);

    return 0;
}