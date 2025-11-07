/* TSP Branch & Bound
   Uses only <stdio.h> (no other headers).
   Max cities = 10. Enter NxN cost matrix (0 on diagonal).
*/

#include <stdio.h>

#define MAX 10
#define INF 1000000000

int N;
int adj[MAX][MAX];
int final_path[MAX + 1];
int curr_path[MAX + 1];
int final_res = INF;

/* find minimum outgoing edge cost for vertex i */
int firstMin(int i) {
    int min = INF;
    int k;
    for (k = 0; k < N; k++) {
        if (i != k && adj[i][k] < min)
            min = adj[i][k];
    }
    return min;
}

/* find second minimum outgoing edge cost for vertex i */
int secondMin(int i) {
    int first = INF, second = INF;
    int j;
    for (j = 0; j < N; j++) {
        if (i == j) continue;
        int val = adj[i][j];
        if (val <= first) {
            second = first;
            first = val;
        } else if (val < second) {
            second = val;
        }
    }
    if (second == INF) second = first;
    return second;
}

/* recursive Branch & Bound */
void TSPRec(int curr_bound, int curr_weight, int level, int visited[]) {
    int i;
    if (level == N) {
        int last = curr_path[level - 1];
        if (adj[last][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[last][curr_path[0]];
            if (curr_res < final_res) {
                final_res = curr_res;
                for (i = 0; i < N; i++) final_path[i] = curr_path[i];
                final_path[N] = curr_path[0];
            }
        }
        return;
    }

    for (i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && visited[i] == 0) {
            int temp_bound = curr_bound;
            int temp_weight = curr_weight;

            curr_weight += adj[curr_path[level - 1]][i];

            /* adjust bound */
            if (level == 1)
                curr_bound -= (firstMin(curr_path[level - 1]) + firstMin(i)) / 2;
            else
                curr_bound -= (secondMin(curr_path[level - 1]) + firstMin(i)) / 2;

            /* promising? */
            if (curr_weight + curr_bound < final_res) {
                curr_path[level] = i;
                visited[i] = 1;
                TSPRec(curr_bound, curr_weight, level + 1, visited);
                visited[i] = 0;
            }

            /* backtrack restore */
            curr_weight = temp_weight;
            curr_bound = temp_bound;
        }
    }
}

/* prepare initial bound and start recursion */
void TSP() {
    int visited[MAX];
    int i;
    for (i = 0; i < N; i++) {
        visited[i] = 0;
        curr_path[i] = -1;
    }

    int curr_bound = 0;
    for (i = 0; i < N; i++)
        curr_bound += (firstMin(i) + secondMin(i));

    /* divide by 2 rounding up */
    curr_bound = (curr_bound + 1) / 2;

    visited[0] = 1;
    curr_path[0] = 0;

    TSPRec(curr_bound, 0, 1, visited);
}

int main() {
    int i, j;

    printf("Enter number of cities (max %d): ", MAX);
    if (scanf("%d", &N) != 1) return 0;
    if (N < 2 || N > MAX) {
        printf("N must be between 2 and %d\n", MAX);
        return 0;
    }

    printf("Enter cost matrix (%dx%d), use 0 for diagonal:\n", N, N);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (scanf("%d", &adj[i][j]) != 1) return 0;
        }
    }

    /* initialize */
    final_res = INF;
    for (i = 0; i <= N; i++) final_path[i] = -1;

    TSP();

    if (final_res == INF) {
        printf("No Hamiltonian cycle found.\n");
    } else {
        printf("Minimum cost: %d\n", final_res);
        printf("Path: ");
        for (i = 0; i <= N; i++) {
            if (i) printf(" -> ");
            printf("%d", final_path[i]);
        }
        printf("\n");
    }

    return 0;
}
