#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int src, dest, weight;
};

void bellmanFord(struct Edge edges[], int V, int E, int src) {
    int dist[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printf("Vertex Distance from Source %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d \t\t INF\n", i);
        else
            printf("%d \t\t %d\n", i, dist[i]);
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    if (V <= 0 || E <= 0) {
        printf("Number of vertices and edges must be positive.\n");
        return 1;
    }

    struct Edge *edges = (struct Edge *)malloc(E * sizeof(struct Edge));
    if (edges == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter edges in format: src dest weight\n");
    printf("Vertices should be between 0 and %d\n", V - 1);
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        if (edges[i].src < 0 || edges[i].src >= V || edges[i].dest < 0 || edges[i].dest >= V) {
            printf("Invalid edge vertices. Please enter vertices in range 0 to %d.\n", V - 1);
            free(edges);
            return 1;
        }
    }

    int src;
    printf("Enter source vertex: ");
    scanf("%d", &src);
    if (src < 0 || src >= V) {
        printf("Invalid source vertex.\n");
        free(edges);
        return 1;
    }

    bellmanFord(edges, V, E, src);

    free(edges);
    return 0;
}
