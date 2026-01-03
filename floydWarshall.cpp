#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> floydWarshall(int V, vector<vector<int>> &edges) {
  vector<vector<int>> dist(V, vector<int>(V, 1e9));

  for (int i = 0; i < V; i++) {
    dist[i][i] = 0;
  }

  for (auto &edge : edges) {
    int u = edge[0];
    int v = edge[1];
    int wt = edge[2];

    dist[u][v] = wt;

    // For undirected graph
    // dist[v][u] = wt;
  }

  for (int k = 0; k < V; k++) {
    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
        if (dist[i][k] != 1e9 && dist[k][j] != 1e9) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }

  return dist;
}