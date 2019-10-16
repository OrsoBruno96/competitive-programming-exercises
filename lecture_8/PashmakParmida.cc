

#include <bits/stdc++.h>
#include "Fenwick.h"

using namespace std;

using vi = vector<int>;
using ll = long long;

// The solution can be divided in the following subproblems:
// First we can compute 2 arrays, which are respectively
// suffix[j] = f(j, n, a_j), using the same notation as the
// original problem
// And then prefix[i] = f(1, i, a_i). This can be done in linear
// time with simple standard tricks.

// Now we have the difficult part: we have 2 arrays of integers
// of the same dimension A[] and B[] and we want to know the
// number of indices i < j such that A[i] > B[j]
// we cannot afford the naive quadratic time because the problem gives us
// up to 10^6 cases and quadratic time would mean TLE.

// We do the following: we keep a prefix sum
// of the occurrencies of B[j] meaning that I scan B and every time
// I find the value v, i add 1 in the prefix sum vector in position v.
// This can be done in a static way.

// Now we can scan A and using the prefix sum we precomputed we always
// know how many times we found a value smaller than A[i] simply
// accessing the prefix sum vector.
// The only caveat is that now we have the constraint i < j so we need
// to update our prefix sum vector at every A scan and remove from it
// the entry we found in A. To do so we need a dynamic prefix sum,
// which can be implemented with a fenwick tree, as done below.

// Time complexity: Overall O(n log n)
// We remap our input to be sure not to have a huge and useless
// fenwick tree. to do so, we have to sort it => O(n log n)
// std::distance is O(1) because vectors have random access it
// (otherwise it would be linear)
// std::lower_bound is O(log n)
// Insertions in fenwick and access are both O(log n)

// Space complexity:
// I need a copy of the original vector, fenwick tree and some
// other copy vectors. Overall O(n)


int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N = 0;
  cin >> N;

  vi original(N);
  vi suffix(N, 0);
  {
    vi copia(N);

    for (int i = 0; i < N; i++) {
      int appo;
      cin >> appo;
      original[i] = appo;
      copia[i] = appo;
    }
    sort(copia.begin(), copia.end());
    auto end = unique(copia.begin(), copia.end());
    auto size = distance(copia.begin(), end);
    copia.resize(size);
    for (auto i = 0; i < N; i++) {
      original[i] = distance(
         copia.begin(),
         lower_bound(copia.begin(), copia.end(), original[i]));
    }
  }
  Fenwick<int> ft(N + 1);
  {
    vi appo(N, 0);
    for (int i = N - 1; i >= 0; i--) {
      appo[original[i]]++;
      suffix[i] = appo[original[i]];
      ft.add(appo[original[i]], 1);
    }
  }
  ll ans = 0;
  {
    vi prefix(N, 0);
    for (int i = 0; i < N; i++) {
      ft.add(suffix[i], -1);
      prefix[original[i]]++;
      ans += ft.sum(prefix[original[i]] - 1);
    }
  }
  cout << ans << "\n";
  return 0;
}
