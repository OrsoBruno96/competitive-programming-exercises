
#include <bits/stdc++.h>

using namespace std;



int main(int argc, char* argv[]) {
  int N = 0, Q = 0;
  cin >> N >> Q;
  vector<int> original, bgn(N, 0), end(N, 0);
  // Key idea of the problem is the following:
  // We try to compute the frequency the positions
  // chosen by a query. When we have this occurrencies vector
  // we can sort both the occurrencies and the original vector
  // and multiply them with scalar product. In this way we will choose
  // the bigger number the most of the times and so on.
  original.reserve(N);
  // Begin of a query interval, end of a query interval
  bgn.reserve(Q); end.reserve(Q);
  for (auto i = 0; i < N; i++) {
    int appo = 0;
    cin >> appo;
    original.push_back(appo);
  }
  for (auto i = 0; i < Q; i++) {
    int appo1, appo2;
    cin >> appo1 >> appo2;
    bgn[appo1 - 1] += 1;
    end[appo2 - 1] += 1;
  }
  vector<int> occurrencies(N, 0);
  // here we compute the occurrencies of each position in the array.
  for (auto i = 0; i < N; i++) {
    const auto pred = (i > 0) ? occurrencies[i - 1] : 0;
    const auto last = (i > 0) ? end[i - 1] : 0;
    occurrencies[i] = pred + bgn[i] - last;
  }
  // Bottleneck of the algorithm. Everyting is linear but the following
  // two lines, which are O(n log n)
  sort(original.begin(), original.end());
  sort(occurrencies.begin(), occurrencies.end());
  long long ans = 0;
  for (auto i = 0; i < N; i++) {
    // cast needed to avoid overflow
    ans += ((long long) occurrencies[i])*((long long) original[i]);
  }
  cout << ans << "\n";
  return 0;
}
