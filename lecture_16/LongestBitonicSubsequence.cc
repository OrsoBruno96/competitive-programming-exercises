
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;


// I am combining the computation of two Longest Increasing
// Subsequence algorithm.
// To be more specific, I want an increasing and a decreasing subsequence
// If I look at the sequence backwards, a decreasing subsequence
// becomes increasing.
// If I compute LIS[j] for the sequence and its reverse, with the O(n^2)
// algorithm used before, I can combine the result in linear time to get
// the answer I want.
// Actually, I only need to sum LIS[j] with LDS[N - j - 1] for each j in the
// range and get the maximum of these values (minus one, because the number j is
// being taken twice).

// Time complexity: O(n^2)
// Space complexity: O(n)


// compare = true: the sequence is increasing
// compare = false: the sequence is decreasing
void compute(const vi& sequence, vi& LIS, const bool compare) {
  const int N = sequence.size();
  for (int i = 1; i < N; i++) {
    int maxx = 1;
    bool found = false;
    for (int j = 0; j < i; j++) {
      bool compared = compare ? sequence[j] < sequence[i] : sequence[j] > sequence[i];
      if (compared) {
        found = true;
        maxx = std::max(LIS[j], maxx);
      }
    }
    if (found) {
      LIS[i] = maxx + 1;
    }
  }
}


int main() {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    vi sequence(N, 0), reversed_sequence(N, 0);
    for (int i = 0; i < N; i++) {
      int appo = 0;
      cin >> appo;
      sequence[i] = appo;
      reversed_sequence[N - i - 1] = appo;
    }
    vi LIS(N, 1);
    compute(sequence, LIS, true);
    vi LDS(N, 1);
    compute(reversed_sequence, LDS, true);

    int maxx = 0;
    for (auto i = 0; i < N; i++) {
      maxx = std::max(LIS[i] + LDS[N - i - 1] - 1, maxx);
    }
    cout << maxx << "\n";
  }
  return 0;
}
