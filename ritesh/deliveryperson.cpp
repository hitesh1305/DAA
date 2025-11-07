#include <iostream>
using namespace std;

#define MAX 10

bool isSafe(int v, int graph[MAX][MAX], int path[], int pos, int n) {
    if (graph[path[pos - 1]][v] == 0)
        return false;
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
    return true;
}

bool hamCycleUtil(int graph[MAX][MAX], int path[], int pos, int n) {
    if (pos == n) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        return false;
    }
    for (int v = 1; v < n; v++) {
        if (isSafe(v, graph, path, pos, n)) {
            path[pos] = v;
            if (hamCycleUtil(graph, path, pos + 1, n))
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

void hamCycle(int graph[MAX][MAX], int n) {
    int path[MAX];
    for (int i = 0; i < n; i++)
        path[i] = -1;
    path[0] = 0;
    if (!hamCycleUtil(graph, path, 1, n)) {
        cout << "No Hamiltonian Circuit exists" << endl;
        return;
    }
    cout << "Hamiltonian Circuit found: ";
    for (int i = 0; i < n; i++)
        cout << path[i] << " -> ";
    cout << path[0] << endl;
}

int main() {
    int n;
    int graph[MAX][MAX];
    cout << "Enter number of vertices (max 10): ";
    cin >> n;
    cout << "Enter adjacency matrix (" << n << "x" << n << "):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];
    hamCycle(graph, n);
    return 0;
}
