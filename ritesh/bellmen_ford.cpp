#include<iostream>
#include<climits>
using namespace std;

void bellman_ford(int graph[][3], int V, int E, int src) {
    int dist[100]; 
    for(int i=0; i<V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for(int i=0; i<V-1; i++) {
        for(int j=0; j<E; j++) {
            int u = graph[j][0];
            int v = graph[j][1];
            int w = graph[j][2];
            if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for(int j=0; j<E; j++) {
        int u = graph[j][0];
        int v = graph[j][1];
        int w = graph[j][2];
        if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    cout << "\nVertex\tDistance from Source\n";
    for(int i=0; i<V; i++) {
        if(dist[i] == INT_MAX)
            cout << i << "\t" << "INF" << endl;
        else
            cout << i << "\t" << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    int graph[100][3];  

    cout << "Enter edges in format (u v w):\n";
    for(int i=0; i<E; i++) {
        cin >> graph[i][0] >> graph[i][1] >> graph[i][2];
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    cout << "\nBellman-Ford Algorithm\n";
    bellman_ford(graph, V, E, src);

    return 0;
}
