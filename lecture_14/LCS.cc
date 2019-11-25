
#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using vii = vector<vi>;

// The idea is to use dynamic programming
// The subproblems are the original problem on
// prefix strings, so we can store our state in an
// len(s1)*len(s2) matrix.
// In each entry we store the length of LCS of the substrings.
// We can combine them in a simple way:
// If we are adding the same char, then we can simply get to the previous
// element on the diagonal and add 1,
// If we are adding a different char we simply can take
// the maximum of the neighbours
// (LCS can never decrease if we make the strings longer)

// Time complexity: O(len1*len2)
// Space complexity: O(len1*len2)

int main() {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int len1 = 0, len2 = 0;
    cin >> len1 >> len2;
    string s1, s2;
    cin >> s1 >> s2;
    vii cache;
    cache.reserve(len1 + 1);
    for (auto i = 0; i < len1 + 1; i++) {
      cache.emplace_back(vi(len2 + 1, 0));
    }
    for (auto i = 1; i < len1 + 1; i++) {
      for (auto j = 1; j < len2 + 1; j++) {
        if (s1[i - 1] == s2[j - 1]) {
          cache[i][j] = cache[i - 1][j - 1] + 1;
        } else {
          cache[i][j] = std::max(cache[i - 1][j], cache[i][j - 1]);
        }
      }
    }
    cout << cache[len1][len2] << "\n";
  }
  return 0;
}
