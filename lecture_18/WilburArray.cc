
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// The greedy solution works.
// Every time I use the "modify(i)" operation,
// I can only change the numbers in position above i.
// For example, I can modify item in position 0 only with the
// "modify(0)" operations. I need at least abs(0 - wanted) operations
// to get to the desired value.
// Once I move to position 1, I can iterate this argument and
// proceed by induction.

// time complexity: O(N)
// space complexity: O(1)


int main() {
  int N = 0;
  cin >> N;
  ll nec = 0;
  ll prec = 0;
  for (int i = 0; i < N; i++) {
    ll appo = 0;
    cin >> appo;
    nec += std::abs(prec - appo);
    prec = appo;
  }
  cout << nec << "\n";
  return 0;
}
