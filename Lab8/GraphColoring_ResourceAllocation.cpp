#include <iostream>
using namespace std;

const int MAX = 10;
int n, m;
int graph[MAX][MAX];
int allowed[MAX][MAX];
int numAllowed[MAX];
int color[MAX];

bool isValid(int task, int col) {
    bool allowedColor = false;
    for (int i = 0; i < numAllowed[task]; i++)
        if (allowed[task][i] == col)
            allowedColor = true;
    if (!allowedColor)
        return false;
    for (int i = 0; i < n; i++)
        if (graph[task][i] && color[i] == col)
            return false;
    return true;
}

bool assignColor(int task) {
    if (task == n)
        return true;
    for (int i = 0; i < numAllowed[task]; i++) {
        int col = allowed[task][i];
        if (isValid(task, col)) {
            color[task] = col;
            if (assignColor(task + 1))
                return true;
            color[task] = -1;
        }
    }
    return false;
}

int main() {
    cout << "Enter number of tasks: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;
    cout << "Enter conflict adjacency matrix (" << n << "x" << n << "):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];
    for (int i = 0; i < n; i++) {
        cout << "Enter number of allowed resources for Task " << i << ": ";
        cin >> numAllowed[i];
        cout << "Enter allowed resources: ";
        for (int j = 0; j < numAllowed[i]; j++)
            cin >> allowed[i][j];
    }
    for (int i = 0; i < n; i++)
        color[i] = -1;
    if (assignColor(0)) {
        cout << "Resource Allocation (Task -> Resource):" << endl;
        for (int i = 0; i < n; i++)
            cout << "Task " << i << " -> Resource " << color[i] << endl;
    } else
        cout << "No valid resource allocation possible" << endl;
    return 0;
}
