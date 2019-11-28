
#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;
using pvi = vector<pi>;
using ppvi = vector<pair<int, pi>>;


// Actually this does not look a lot like DP,
// it's more divide and conquer, but maybe I'm wrong.
// Basically I'm doing a DFS in the tree. For each vertex I save
// a pair of numbers, (take, not_take), that are the minimum
// number of items I have to take (in the sense defined by the problem,
// having all edges touching a node in the subset)
// to touch all the subtree rooted at the vertex in two cases:
// take if I take also the vertex I'm looking at,
// not_take if I do not take it.
// I can combine the results easily: if I do not take
// the vertex, I'm forced to take the children.
// If I take it, I can always choose the minimum of the 2.

// space complexity: O(N)
// time complexity: O(N)



pi dfs(const vvi& children_list, vector<bool>& visited, int vertex) {
  visited[vertex] = true;
  int take = 0, not_take = 0;
  bool at_least_once = false;
  for (const auto& it: children_list[vertex]) {
    if (visited[it]) { continue; }
    at_least_once = true;
    visited[it] = true;
    auto appo = dfs(children_list, visited, it);
    not_take += appo.first;
    take += std::min(appo.first, appo.second);
  }
  if (!at_least_once) {
      return pi(1, 0);
  }
  take += 1;
  return pi(take, not_take);
}


int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N = 0;
  cin >> N;
  pvi edge_list;
  edge_list.reserve(N);
  vvi children_list;
  children_list.reserve(N + 1);
  for (int i = 0; i < N + 1; i++) {
    children_list.emplace_back(vi());
  }

  for (int i = 0; i < N - 1; i++) {
    int appo1 = 0, appo2 = 0;
    cin >> appo1 >> appo2;
    edge_list.emplace_back(pi(appo1, appo2));
    children_list[appo1].push_back(appo2);
    children_list[appo2].push_back(appo1);
  }

  vector<bool> visited(N + 1, false);
  auto result = dfs(children_list, visited, 1);
  cout << std::min(result.first, result.second) << "\n";

  return 0;
}
