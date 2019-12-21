
#include "UnionFind.h"

#include <bits/stdc++.h>


// For this problem I use Kruskal's algorithm
// I keep all the edges stored in an edge list.
// I sort them by increasing weigth and select them greedily.
// I only have to check not to create loops. To do so
// I can choose to use an efficient data structure, the
// Union find disjoint set, which creates a forest of trees that
// can be merged very efficiently.

// Time complexity: O(N log M)
// Space complexity: O(M) (M > N)



using namespace std;
using pi = pair<int, int>;
using ppi = pair<int, pi>;

int main() {
  int N = 0, M = 0;
  cin >> N >> M;
  vector<ppi> edge_list;  // weight, i, j
  edge_list.reserve(M);
  for (int k = 0; k < M; k++) {
    int w = 0, i = 0, j = 0;
    cin >> i >> j >> w;
    edge_list.emplace_back(w, pi(i, j));
  }

  sort(edge_list.begin(), edge_list.end());
  UnionFind uf(N);
  int total_weigth = 0;
  for (int i = 0; i < M; i++) {
    if (!uf.is_same_set(edge_list[i].second.first, edge_list[i].second.second)) {
      uf.insert_link(edge_list[i].second.first, edge_list[i].second.second);
      total_weigth += edge_list[i].first;
    }
    if (uf.connected_components() == 1) {
      break;
    }
  }
  cout << total_weigth << "\n";

  return 0;
}
