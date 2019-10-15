

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
    for (int i = 0; i < q; i++) {
      int appo;
      cin >> appo;
      cout << ft.sum(appo) << "\n";
    }
  }
  return 0;
}
