
#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using vii = vector<vi>;


// Actually this code is copypasted from LCS.cc
// To find the longest palindromic subsequence you can
// simply find the longest common subsequence between a string and its reverse.
// I did some simple optimizations because inserting a line
// with a simple s2 = s1 led to a TLE.


int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int TC = 0;
  cin >> TC;
  while (TC--) {
    int len1 = 0;
    string s1;
    cin >> s1;
    len1 = s1.size();
    vii cache;
    cache.reserve(len1 + 1);
    for (auto i = 0; i < len1 + 1; i++) {
      cache.emplace_back(vi(len1 + 1, 0));
    }
    for (auto i = 1; i < len1 + 1; i++) {
      for (auto j = 1; j < len1 + 1; j++) {
        if (s1[i - 1] == s1[len1 - j]) {
          cache[i][j] = cache[i - 1][j - 1] + 1;
        } else {
          cache[i][j] = std::max(cache[i - 1][j], cache[i][j - 1]);
        }
      }
    }
    cout << cache[len1][len1] << "\n";
  }
  return 0;
}
