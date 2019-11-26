
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

// I use dynamic programming.
// The idea is to store in an array LIS[j]
// the length of the longest increasing subsequence
// that ends with number in position j.
// I choose to store the LIS that ends there because
// in this case it is simple to define the subproblems and
// it is not if I simply store the maximum length.

// Actually, if I store only the maximum value of LIS
// found before I cannot define the subproblem because
// I do not know if I can extend the sequence.

// The overall complexity is quadratic because I need to scan
// the beginning of the list for every entry in the list.

// Time: O(n^2)
// Space: O(n)



int main() {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    vi sequence(N, 0);
    for (int i = 0; i < N; i++) {
      int appo = 0;
      cin >> appo;
      sequence[i] = appo;
    }
    vi LIS(N, 1);
    int ans = 1;
    for (int i = 1; i < N; i++) {
      int maxx = 1;
      bool found = false;
      for (int j = 0; j < i; j++) {
        if (sequence[j] < sequence[i]) {
          found = true;
          maxx = std::max(LIS[j], maxx);
        }
      }
      if (found) {
        LIS[i] = maxx + 1;
        ans = std::max(ans, LIS[i]);
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
