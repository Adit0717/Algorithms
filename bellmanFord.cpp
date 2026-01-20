#include <iostream>
#include <vector>

using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>> &edges) {
  // edges = {u, v, wt}
  vector<int> dist(V, 1e9);

  // Relax all edges V-1 times

  for (int i = 0; i < V; i++) {
    for (auto &ele : edges) {
      int u = ele[0];
      int v = ele[1];
      int wt = ele[2];

      if (dist[u] + wt < dist[v]) {
        dist[v] = dist[u] + wt;
      }
    }
  }

  // Check for negative cycle
  for (int i = 0; i < V; i++) {
    for (auto &ele : edges) {
      int u = ele[0];
      int v = ele[1];
      int wt = ele[2];

      if (dist[u] + wt < dist[v]) {
        return {-1};
      }
    }
  }

  return dist;
}
