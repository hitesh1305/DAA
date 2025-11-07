#include<iostream>
using namespace std;

#define N 7
#define INF 999999

int final_path[N + 1];
bool visited[N];
int final_res = INF;

void copyToFinal(int curr_path[]) {
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
