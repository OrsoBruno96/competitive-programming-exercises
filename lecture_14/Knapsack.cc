
#include <bits/stdc++.h>


using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;


// The idea is to use dynamic programming.
// The state of my problem is determined by 2 numbers:
// - the prefix of the objects (the first k objects, so the number k)
// - the space left
// For every pair of values I can store the best result I can achieve with
// that starting point.
// The recursion is now simple and I can fill the entire table.
// At every iteration I can choose to grab or not the following object,
// but only if the space left S is greater or equal than its size.
// Otherwise I don't do anything.


// Time complexity: O(N*S)
// Space complexity: O(N*S)


int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int S = 0, N = 0;
  cin >> S >> N;
  vi sizes(N, 0), values(N, 0);

  for (int i = 0; i < N; i++) {
    int size = 0, val = 0;
    cin >> size >> val;
    sizes[i] = size;
    values[i] = val;
  }
  vvi cache;
  cache.reserve(S + 1);
  for (int i = 0; i < S + 1; i++) {
    cache.emplace_back(vi(N + 1, 0));
  }
  for (int i = 1; i < S + 1; i++) {
    for (int j = 1; j < N + 1; j++) {
      if (sizes[j - 1] <= i) {
        cache[i][j] = std::max(values[j - 1] + cache[i - sizes[j - 1]][j - 1],
                               cache[i][j - 1]);
      } else {
        cache[i][j] = cache[i][j - 1];
      }
    }
  }
  cout << cache[S][N] << endl;

  return 0;
}
