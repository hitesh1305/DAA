#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent, rank;
};

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void KruskalMST(struct Edge edges[], int V, int E) {
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    struct Edge* result = (struct Edge*)malloc((V - 1) * sizeof(struct Edge));
    if(result == NULL) {
        printf("Memory allocation failed.\n");
        free(subsets);
        return;
    }
    int e = 0, i = 0;

    while (e < V - 1 && i < E) {
        struct Edge next = edges[i++];
        int x = find(subsets, next.src);
        int y = find(subsets, next.dest);

        if (x != y) {
            result[e++] = next;
            Union(subsets, x, y);
        }
    }

    printf("\nKruskal's MST:\n");
    int minCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }
    printf("Minimum Cost = %d\n", minCost);

    free(subsets);
    free(result);
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

    struct Edge* edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    if (edges == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter edges in the format: src dest weight\n");
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

    KruskalMST(edges, V, E);

    free(edges);
    return 0;
}
