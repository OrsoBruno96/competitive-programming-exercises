
#include <bits/stdc++.h>

using namespace std;


// The idea is simple, I can build an implicit graph from the table structure
// given by the problem and find its connected components.

// To do so, I do a simple DFS of the graph. I color the vertices
// when I visit them and I visit all the subbraph before moving to
// the next one.

// Then I count the connected components.

// Time complexity: I have to visit each element in the matrix at least once
// but actually I can do it 4 times. every visit has constant time.
// O(NM)

// Space complexity: O(NM)


int dfs(const int i, const int j, const int N, const int M,
        const vector<string>& matrix, vector<vector<bool>>& visited) {
  if (visited[i][j]) {
    return 0;
  }
  visited[i][j] = true;
  vector<pair<int, int>> targets;
  targets.reserve(4);
  if (i > 0) {
    targets.emplace_back(i - 1, j);
  }
  if (i < N - 1) {
    targets.emplace_back(i + 1, j);
  }
  if (j > 0) {
    targets.emplace_back(i, j - 1);
  }
  if (j < M - 1) {
    targets.emplace_back(i, j + 1);
  }
  for (const auto& it: targets) {
    if (matrix[it.first].at(it.second) == 'X') {
      dfs(it.first, it.second, N, M, matrix, visited);
    }
  }

  return 1;
}



int main() {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0, M = 0;
    cin >> N >> M;
    vector<string> matrix(N);
    for (int i = 0; i < N; i++) {
      string appo;
      cin >> appo;
      matrix[i] = appo;
    }
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    int connected_components = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (matrix[i].at(j) == 'O') {
          continue;
        }
        connected_components += dfs(i, j, N, M, matrix, visited);
      }
    }

    cout << connected_components << "\n";
  }
  return 0;
}
