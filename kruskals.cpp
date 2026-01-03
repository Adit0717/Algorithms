#include <vector>

using namespace std;

class DisjointSet {
private:
  vector<int> parent;
  vector<int> rank;
  vector<int> size;

public:
  DisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    size.resize(n, 1);

    for (int i = 0; i < parent.size(); i++) {
      parent[i] = i;
    }
  }

  int find(int ele) {
    if (ele == parent[ele])
      return ele;

    return parent[ele] = find(parent[ele]);
  }

  void unionByRank(int ele1, int ele2) {
    int parentOfEle1 = find(ele1);
    int parentOfEle2 = find(ele2);

    if (parentOfEle1 == parentOfEle2)
      return;

    if (rank[parentOfEle1] < rank[parentOfEle2]) {
      parent[parentOfEle1] = parentOfEle2;
    } else if (rank[parentOfEle1] > rank[parentOfEle2]) {
      parent[parentOfEle2] = parentOfEle1;
    } else {
      parent[parentOfEle2] = parentOfEle1;
      rank[parentOfEle1]++;
    }
  }

  void unionBySize(int ele1, int ele2) {
    int parentOfEle1 = find(ele1);
    int parentOfEle2 = find(ele2);

    if (parentOfEle1 == parentOfEle2)
      return;

    if (size[parentOfEle1] < size[parentOfEle2]) {
      parent[parentOfEle1] = parentOfEle2;
      size[parentOfEle2] += size[parentOfEle1];
    } else if (size[parentOfEle1] > size[parentOfEle2]) {
      parent[parentOfEle2] = parentOfEle1;
      size[parentOfEle1] += size[parentOfEle2];
    } else {
      parent[parentOfEle2] = parentOfEle1;
      size[parentOfEle1] += size[parentOfEle2];
    }
  }
};

/*
Input should be in the form of edges = {{wt, {u, v}}} and sort them according to
the weight in ascending order
*/

int kruskals(int V, vector<pair<int, pair<int, int>>> &edges,
             vector<pair<int, int>> &result) {
  int weight = 0;
  DisjointSet ds(V);

  sort(edges.begin(), edges.end());

  for (auto &edge : edges) {
    int u = edge.second.first;
    int v = edge.second.second;
    int wt = edge.first;

    if (ds.find(u) != ds.find(v)) {
      weight += wt;
      result.push_back({u, v});
      ds.unionBySize(u, v);
    }
  }
  return weight;
}