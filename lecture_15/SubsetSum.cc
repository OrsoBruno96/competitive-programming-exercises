
#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;


// I use a top down dynamic programming approach.
// I save as state of my problem the number of remaining object that I could use
// and the value that I need to get to the right sum (total divided by 2).

// This table has size O(n*v) where v is the sum of all numbers in the array.
// and can be filled in constant time for each entry.
// If the item I am processing has value less or equal than the sum I need,
// I'm going to process two possibilities. If it is greater, I can skip
// the possibility where I need to take also this item.

// Time complexity: O(n*v)
// Space complexity: O(n*v)


int solve(vvi &cache, const vi& numeri, int robject, int rvalue) {
  if (rvalue == 0) { return 1; }
  if (robject < 0) { return 0; }
  if (cache[robject][rvalue] != -1) { return cache[robject][rvalue]; }
  int appo = -1;
  if (numeri[robject] <= rvalue) {
    int appo1, appo2;
    appo1 = solve(cache, numeri, robject - 1, rvalue);
    appo2 = solve(cache, numeri, robject - 1, rvalue - numeri[robject]);
    appo = (appo1 == 1 || appo2 == 1) ? 1 : 0;
  } else {
    appo = solve(cache, numeri, robject - 1, rvalue);
  }
  cache[robject][rvalue] = appo;
  return appo;
}


int main() {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0, totale = 0;
    cin >> N;
    vi numeri(N, 0);
    for (int i = 0; i < N; i++) {
      int appo;
      cin >> appo;
      totale += appo;
      numeri[i] = appo;
    }
    if (totale % 2) {
      cout << "NO\n";
      continue;
    }
    totale /= 2;
    vvi cache;
    for (int i = 0; i < N; i++) {
      cache.emplace_back(vi(totale + 1, -1));
    }
    auto ans = solve(cache, numeri, N - 1, totale);
    if (ans == 1) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
