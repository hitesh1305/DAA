#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int** graph, int V) {
    int minCost = 0;
    printf("\nPrim's MST:\n");
    for (int i = 1; i < V; i++) {
        printf("%d -- %d == %d\n", parent[i], i, graph[i][parent[i]]);
        minCost += graph[i][parent[i]];
    }
    printf("Minimum Cost = %d\n", minCost);
}

void primMST(int** graph, int V) {
    int* parent = (int*)malloc(V * sizeof(int));
    int* key = (int*)malloc(V * sizeof(int));
    int* mstSet = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    printMST(parent, graph, V);

    free(parent);
    free(key);
    free(mstSet);
}

int main() {
    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    if (V <= 0) {
        printf("Number of vertices must be positive.\n");
        return 1;
    }

    int** graph = (int**)malloc(V * sizeof(int*));
    if (!graph) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter adjacency matrix (enter 0 if no edge):\n");
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
        if (!graph[i]) {
            printf("Memory allocation failed.\n");
            for (int k = 0; k < i; k++) free(graph[k]);
            free(graph);
            return 1;
        }
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, V);

    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
