#include <iostream>
using namespace std;

const int MAX = 10;
int n;
int graph[MAX][MAX];
int path[MAX];

bool isSafe(int v, int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return false;
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
    return true;
}

bool hamCycleUtil(int pos) {
    if (pos == n) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        return false;
    }
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamCycleUtil(pos + 1))
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

void hamCycle() {
    for (int i = 0; i < n; i++)
        path[i] = -1;
    path[0] = 0;
    if (hamCycleUtil(1)) {
        cout << "Hamiltonian Circuit: ";
        for (int i = 0; i < n; i++)
            cout << path[i] << " ";
        cout << path[0] << endl;
    } else
        cout << "No Hamiltonian Circuit exists" << endl;
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;
    cout << "Enter adjacency matrix (" << n << "x" << n << "):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];
    hamCycle();
    return 0;
}
