#include<iostream>
#define inf 999999
#define MAX 10
using namespace std;

int G[MAX][MAX], S[MAX][MAX], n;

int prims() {
   int C[MAX][MAX];
   int u, v, min_dist, dist[MAX], from[MAX];
   int visited[MAX], edges_left, i, j, min_cost;

   for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
         if(G[i][j]==0)
            C[i][j]=inf;
         else
            C[i][j]=G[i][j];
         S[i][j]=0;
      }
   }

   dist[0]=0;
   visited[0]=1;
   for(i=1; i<n; i++) {
      dist[i] = C[0][i];
      from[i] = 0;
      visited[i] = 0;
   }

   min_cost = 0;
   edges_left = n-1;

   while(edges_left > 0) {
      min_dist = inf;
      for(i=1; i<n; i++) {
         if(!visited[i] && dist[i] < min_dist) {
            v = i;
            min_dist = dist[i];
         }
      }
      u = from[v];

      S[u][v] = dist[v];
      S[v][u] = dist[v];

      edges_left--;
      visited[v]=1;

      for(i=1; i<n; i++) {
         if(!visited[i] && C[i][v] < dist[i]) {
            dist[i] = C[i][v];
            from[i] = v;
         }
      }
      min_cost += C[u][v];
   }

   return min_cost;
}

int main() {
   int i, j, cost;

   cout << "Enter number of vertices: ";
   cin >> n;

   cout << "Enter adjacency matrix (0 if no edge):\n";
   for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
         cin >> G[i][j];
      }
   }

   cost = prims();

   cout << "\nSpanning tree (Adjacency Matrix):\n";
   for(i=0; i<n; i++) {
      for(j=0; j<n; j++)
         cout << S[i][j] << " ";
      cout << endl;
   }

   cout << "\nEdges in MST:\n";
   for(i=0; i<n; i++) {
      for(j=i+1; j<n; j++) {
         if(S[i][j] != 0)
            cout << i << " -- " << j << " == " << S[i][j] << endl;
      }
   }

   cout << "Minimum cost = " << cost << endl;

   return 0;
}
