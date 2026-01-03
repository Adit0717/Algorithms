#include <iostream>
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

int main() {
  DisjointSet ds(7);
  ds.unionBySize(1, 2);
  ds.unionBySize(2, 3);
  ds.unionBySize(4, 5);
  ds.unionBySize(6, 7);
  ds.unionBySize(5, 6);

  if (ds.find(3) == ds.find(7)) {
    cout << "Same" << endl;
  } else {
    cout << "Not Same" << endl;
  }

  ds.unionBySize(3, 7);

  if (ds.find(3) == ds.find(7)) {
    cout << "Same" << endl;
  } else {
    cout << "Not Same" << endl;
  }
}
