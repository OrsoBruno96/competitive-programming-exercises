
#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using pi = pair<int, int>;
using ppi = pair<int, pi>;
using vppi = vector<ppi>;


// I can use a greedy solution.
// I sort the pairs of (start, end) of the meetings by increasing end
// and I start to scan them from the beginning. I take all the meetings I
// can (so the ones that do not overlap with the last item I took.

// This is optimal because in this sorting each segment disturbs us no
// further as soon as possible.

// Time complexity: O(N log N) (need to sort)
// Space complexity: O(N)

int main() {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    vi starts(N, 0), ends(N, 0);
    vppi couples;
    couples.reserve(N);
    for (int i = 0; i < N; i++) {
      int appo;
      cin >> appo;
      starts[i] = appo;
    }
    for (int i = 0; i < N; i++) {
      int appo;
      cin >> appo;
      ends[i] = appo;
    }
    for (int i = 0; i < N; i++) {
      couples.emplace_back(ppi(i + 1, pi(starts[i], ends[i])));
    }
    sort(couples.begin(), couples.end(), [](const ppi& left, const ppi& right) {
                                           return left.second.second < right.second.second;
                                         });

    vi answers;
    answers.reserve(N);
    int minn = 0;
    for (const auto& it: couples) {
      if (minn <= it.second.first) {
        minn = it.second.second;
        answers.push_back(it.first);
      }
    }
    for (const auto& it: answers) {
      cout << it << " ";
    }
    cout << "\n";
  }
  return 0;
}
