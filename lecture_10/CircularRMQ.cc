

#include <bits/stdc++.h>

#include "LazySegmentTree.h"


// This problem can be solved easily using a segment tree
// with lazy propagation, that allows to make range updates
// in O(log n) time.

// if the requested range is circular (the second is smaller than
// the first) we can simply split it in 2 intervals in the right order,
// one from the beginning to the second, and the other from the first
// to the end.

// Time complexity: O(q log n)
// Space complexity: O(n)



using namespace std;
using ll = long long;



int main(int argc, char* argv[]) {
  int n = 0;
  cin >> n;
  using ll = long long int;
  vector<ll> initial(n, 0);
  for (auto i = 0; i < n; i++) {
    cin >> initial[i];
  }
  LazySegmentTree<ll> tree(initial);


  int q = 0;
  cin >> q;
  vector<ll> ans;
  ans.reserve(q);
  for (int i = 0; i < q + 1; i++) {
    int a = 0, b = 0, c = 0;
    string appo;
    getline(cin, appo);
    if (i == 0) {
      continue;
    }
    stringstream ss(appo);
    ss >> a >> b;
    if (ss >> c) {
      if (b >= a) {
        tree.range_add(a, b, c);
      } else {
        tree.range_add(0, b, c);
        tree.range_add(a, n - 1, c);
      }
    } else {
      if (b >= a) {
        ans.push_back(tree.range_query(a, b));
      } else {
        auto appo = std::min(tree.range_query(0, b),
                             tree.range_query(a, n - 1));
        ans.push_back(appo);
      }
    }
  }
  for (const auto& it: ans) {
    cout << it << "\n";
  }
  return 0;
}
