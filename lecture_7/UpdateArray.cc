

#include <bits/stdc++.h>
#include "Fenwick.h"

using namespace std;

int main(int argc, char* argv[]) {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int n = 0, u = 0;
    cin >> n >> u;
    Fenwick<int> ft(n);
    // I exploit the fact that a FT gives as an answer the prefix
    // sum of a vector with a good complexity (O(log n)), and admits
    // updates with complexity O(log n)

    // u iterations, each with O(log n) complexity
    for (auto i = 0; i < u; i++) {
      int l = 0, r = 0, v = 0;
      cin >> l >> r >> v;
      ft.add(l, v);
      if (r < n - 1) {
        ft.add(r + 1, -v);
      }
    }
    int q = 0;
    cin >> q;
    // each query is O(log n) and there are q queries.
    for (int i = 0; i < q; i++) {
      int appo;
      cin >> appo;
      cout << ft.sum(appo) << "\n";
    }
    // Space complexity is good because with a fenwick tree
    // I do not need to store the original array, i can use only
    // this data structure, so the space complexity is linear with
    // the size of the array.
  }
  return 0;
}
