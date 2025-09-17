#include<iostream>
#define MAX 20
using namespace std;

int parent[MAX];

int find_set(int v) {
    if (parent[v] != v)
        parent[v] = find_set(parent[v]);
    return parent[v];
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}

int main() {
    int n;
    int G[MAX][MAX];

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter adjacency matrix (0 if no edge):\n";
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin >> G[i][j];
        }
    }

    int edges[MAX*MAX][3];
    int edge_count = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(G[i][j] != 0) {
                edges[edge_count][0] = i;
                edges[edge_count][1] = j;
                edges[edge_count][2] = G[i][j];
                edge_count++;
            }
        }
    }

    for(int i=0; i<edge_count-1; i++) {
        for(int j=0; j<edge_count-i-1; j++) {
            if(edges[j][2] > edges[j+1][2]) {
                int t0 = edges[j][0], t1 = edges[j][1], t2 = edges[j][2];
                edges[j][0] = edges[j+1][0]; edges[j][1] = edges[j+1][1]; edges[j][2] = edges[j+1][2];
                edges[j+1][0] = t0; edges[j+1][1] = t1; edges[j+1][2] = t2;
            }
        }
    }

    for(int i=0; i<n; i++)
        parent[i] = i;

    int mst_cost = 0;
    int mst_edges = 0;

    cout << "\nEdges in MST (Kruskal's):\n";
    for(int i=0; i<edge_count && mst_edges < n-1; i++) {
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        if(find_set(u) != find_set(v)) {
            cout << u << " -- " << v << " == " << w << endl;
            mst_cost += w;
            union_sets(u, v);
            mst_edges++;
        }
    }

    cout << "Total weight of MST = " << mst_cost << endl;
    return 0;
}
