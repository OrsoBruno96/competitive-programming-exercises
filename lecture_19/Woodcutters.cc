
#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
using pvi = vector<pi>;


// Problem is simple once you understand that it's never useful to
// skip cutting a tree to "save stuff for later", because it's not useful.


// First you can always cut the first and last tree.
// Now you can simply scan the trees. If you can fit it to the left,
// you won't disturb the next trees and this is optimal for sure.
// If you can cut it to the right, you should cut it either.

// This can be proven by a simple swap argument on the optimal solution.


int main() {
  int N = 0;
  cin >> N;
  if (N < 2) {
    cout << N << "\n";
    return 0;
  }
  pvi trees;
  trees.reserve(N);
  for (int i = 0; i < N; i++) {
    auto pos = 0, heigth = 0;
    cin >> pos >> heigth;
    trees.emplace_back(pi(pos, heigth));
  }
  int counter = 2;
  for (int i = 1; i < N - 1; i++) {
    if (trees[i].first - trees[i - 1].first > trees[i].second) {
      counter++;
      continue;
    }
    if (trees[i + 1].first - trees[i].first > trees[i].second) {
      counter++;
      trees[i].first += trees[i].second;
      continue;
    }
  }
  cout << counter << "\n";

  return 0;
}
