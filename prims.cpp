#include <queue>
#include <vector>

using namespace std;

int weight(int V, vector<pair<int, pair<int, int>>> &edges,
           vector<pair<int, int>> &result) {
  int weight = 0;

  vector<int> visited(V, 0);
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      pq;

  pq.push({0, {0, -1}});

  while (!pq.empty()) {
    int wt = pq.top().first;
    int node = pq.top().second.first;
    int parent = pq.top().second.second;

    pq.pop();

    if (visited[node] == 1)
      continue;

    visited[node] = 1;
    weight += wt;
    result.push_back({node, parent});

    for (auto &edge : edges) {
      int adjNode = edge.second.first;
      int wt = edge.second.second;

      if (visited[adjNode] == 0)
        pq.push({wt, {adjNode, node}});
    }
  }

  return weight;
}