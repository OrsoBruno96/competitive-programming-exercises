
#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
using pvi = vector<pi>;

// I use a kind of greedy algorithm.
// I can see the problem as equivalent to covering an interval
// with the minimum number of segments.
// At each iteration I try to get the segment that I can reach that
// goes the furthest.
// This is optimal and can be proven by a simple swap argument.

// The overall complexity is linear because I only need to scan all the
// entries once. (actually twice but it's only because it was faster to write)


int main() {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    pvi all;
    all.reserve(N);
    for (int i = 0; i < N; i++) {
      int appo = 0;
      cin >> appo;
      all.emplace_back(pi(i, i + appo));
    }
    int avanti = all[0].second;
    if (avanti == 0) {
      cout << "-1\n";
      continue;
    } else if (avanti >= N - 1) {
      cout << "1\n";
      continue;
    }
    int new_max = avanti;
    bool ok = false;
    int how_many = 1;
    for (int i = 1; i < N; i++) {
      new_max = std::max(new_max, all[i].second);
      if (new_max == i) { break; }
      if (new_max >= N - 1) {
        how_many++;
        ok = true;
        break;
      }
      if (i >= avanti) {
        avanti = new_max;
        how_many++;
      }
    }
    if (ok) {
      cout << how_many << "\n";
    } else {
      cout << "-1\n";
    }
  }

  return 0;
}
