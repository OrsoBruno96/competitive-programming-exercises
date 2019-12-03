
#include <bits/stdc++.h>

using namespace std;

// A simple observation solves the problem:
// The number of changes switching a contiguous segment of
// numbers can only add at most 2 to the number of switches and this is
// because if a and b are boolean and a != b, not a != not b, so I can only
// affect the border of the problem. But I can change it only if I
// have some equal adjacent numbers.

// time complexity: O(N)



int main() {
  int N = 0;
  cin >> N;
  string results;
  cin >> results;
  N = results.size();
  auto prec = results.at(0);
  int changes = 0, equals = 0;
  for (int i = 1; i < N; i++) {
    auto next = results.at(i);
    if (next != prec) {
      changes++;
    } else {
      equals++;
    }
    prec = next;
  }
  cout << 1 + changes + std::min(equals, 2) << "\n";

  return 0;
}
