#include <stdio.h>

#define MAX 10
#define INF 99999

int main() {
    int V, i, j, u, v;
    int graph[MAX][MAX];
    int key[MAX], parent[MAX], mstSet[MAX];
    int min, total_cost = 0;

    printf("Enter number of neighbourhoods (vertices): ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix (use 0 if no direct road):\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0)
                graph[i][j] = INF;
        }
    }

    for (i = 0; i < V; i++) {
        key[i] = INF;
        parent[i] = -1;
        mstSet[i] = 0;
    }

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        min = INF;
        u = -1;
        for (i = 0; i < V; i++) {
            if (mstSet[i] == 0 && key[i] < min) {
                min = key[i];
                u = i;
            }
        }

        mstSet[u] = 1;

        for (v = 0; v < V; v++) {
            if (graph[u][v] != INF && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\nEdges in the constructed Minimum Spanning Tree:\n");
    for (i = 1; i < V; i++) {
        printf("%d - %d  (Cost: %d)\n", parent[i], i, graph[i][parent[i]]);
        total_cost += graph[i][parent[i]];
    }

    printf("Total Minimum Cost = %d\n", total_cost);

    return 0;
}
