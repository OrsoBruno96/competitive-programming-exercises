
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

// I use dynamic programming with a O(n^2) table of state that can be fillen in
// constant time for each entry, so O(n^2) time complexity.

// The subproblems can be identified in "do the same problem but for
// prefix strings". For convenience I start with the empty string, so our table
// will actually be (len1 + 1)*(len2 + 1).
// The recursion is the following:
// EDIT(i, j) = {
//      i   if j == 0
//      j   if i == 0
//      EDIT(i - 1, j - 1) if I am adding an equal char to both,
//                         which means if s1[i] == s2[j]
//      1 + min(
//          EDIT(i - 1, j - 1),  // with replace operation
//          EDIT(i - 1, j)       // with insert operation
//          EDIT(i, j - 1)       // with delete operation
// }
// Actually the last two can be swapped, it depends on which string you want to
// modify, but the edit distance is symmetric in the arguments.


int main() {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int len1 = 0, len2 = 0;
    cin >> len1 >> len2;
    string s1, s2;
    cin >> s1 >> s2;
    vvi cache;
    cache.reserve(len1 + 1);
    for (int i = 0; i < len1 + 1; i++) {
      cache.emplace_back(vi(len2 + 1, 0));
    }
    for (int i = 1; i < len1 + 1; i++) {
      cache[i][0] = i;
    }
    for (int i = 1; i < len2 + 1; i++) {
      cache[0][i] = i;
    }
    for (auto i = 1; i < len1 + 1; i++) {
      for (auto j = 1; j < len2 + 1; j++) {
        if (s1[i - 1] == s2[j - 1]) {
          cache[i][j] = cache[i - 1][j - 1];
        } else {
          const auto minn = std::min(std::min(cache[i - 1][j], cache[i][j - 1]), cache[i - 1][j - 1]);
          cache[i][j] = minn + 1;
        }
      }
    }


    cout << cache[len1][len2] << "\n";
  }
  return 0;
}
