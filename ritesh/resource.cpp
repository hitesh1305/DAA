#include <iostream>
using namespace std;

#define MAX 10

bool is_valid(int task, int col, int graph[MAX][MAX], int colors[MAX], int allowed[MAX][MAX], int allowed_count[MAX], int n) {
    for (int neighbour = 0; neighbour < n; neighbour++)
        if (graph[task][neighbour] == 1 && colors[neighbour] == col)
            return false;
    for (int i = 0; i < allowed_count[task]; i++)
        if (allowed[task][i] == col)
            return true;
    return false;
}

bool assign_task(int task, int graph[MAX][MAX], int colors[MAX], int allowed[MAX][MAX], int allowed_count[MAX], int n) {
    if (task == n)
        return true;
    for (int i = 0; i < allowed_count[task]; i++) {
        int col = allowed[task][i];
        if (is_valid(task, col, graph, colors, allowed, allowed_count, n)) {
            colors[task] = col;
            if (assign_task(task + 1, graph, colors, allowed, allowed_count, n))
                return true;
            colors[task] = -1;
        }
    }
    return false;
}

void solve_resource_allocation(int graph[MAX][MAX], int allowed[MAX][MAX], int allowed_count[MAX], int n) {
    int colors[MAX];
    for (int i = 0; i < n; i++)
        colors[i] = -1;
    if (assign_task(0, graph, colors, allowed, allowed_count, n)) {
        cout << "Task -> Resource assignment:\n";
        for (int i = 0; i < n; i++)
            cout << "Task " << i << " -> Resource M" << colors[i] << endl;
    } else {
        cout << "No valid assignment found.\n";
    }
}

int main() {
    int n = 6;
    int graph[MAX][MAX] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 1},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    int allowed[MAX][MAX] = {
        {0, 1, 2, 3},
        {0, 1, 2, -1},
        {1, 2, 3, -1},
        {0, 2, 3, -1},
        {1, 3, -1, -1},
        {0, 2, -1, -1}
    };

    int allowed_count[MAX] = {4, 3, 3, 3, 2, 2};

    solve_resource_allocation(graph, allowed, allowed_count, n);
    return 0;
}
