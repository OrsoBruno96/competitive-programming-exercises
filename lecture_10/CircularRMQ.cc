

#include <bits/stdc++.h>
#include "LazySegmentTree.h"

using namespace std;

int main(int argc, char* argv[]) {
  int n = 0;
  cin >> n;
  using ll = long long int;
  LazySegmentTree<ll, LazySegmentTypeMin<ll>> tree(n);

  for (auto i = 0; i < n; i++) {
    int appo;
    cin >> appo;
    tree.add(i + 1, appo);
  }
  int q = 0;
  cin >> q;
  vector<int> ans;
  ans.reserve(q);
  // int cusumano = 0;
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
      a++; b++;
      if (b >= a) {
        tree.range_add(a, b, c);
      } else {
        tree.range_add(1, b, c);
        tree.range_add(a, n, c);
      }
    } else {
      a++; b++;
      // cout << cusumano << endl;
      // cusumano++;
      if (b >= a) {
        ans.push_back(tree.range_query(a, b));
      } else {
        auto appo = std::min(tree.range_query(1, b), tree.range_query(a, n));
        ans.push_back(appo);
      }
    }
    // cout << "a: " << a << " b: " << b << " c: " << c << endl;
    // print_all(cout, tree) << endl << endl << endl;
  }
  for (const auto& it: ans) {
    cout << it << "\n";
  }
  return 0;
}
