

#include <bits/stdc++.h>
#include "LazySegmentTree.h"

using namespace std;

int main(int argc, char* argv[]) {
  int n = 0;
  cin >> n;
  LazySegmentTree<int, SegmentTypeMin<int>> tree(n);

  for (auto i = 0; i < n; i++) {
    int appo;
    cin >> appo;
    tree.add(i, appo);
  }
  int q = 0;
  cin >> q;
  vector<int> ans;
  ans.reserve(q);
  for (int i = 0; i < q; i++) {
    int a = 0, b = 0, c = 0;
    string appo;
    getline(cin, appo);
    stringstream ss(appo);
    ss >> a >> b;
    if (ss >> c) {
      cout << "aggiungo: " << a << " " << b << " " << c << endl;
      if (b >= a) {
        tree.range_add(a, b, c);
      } else {
        tree.range_add(0, b, c);
        tree.range_add(a, n, c);  // ocio
      }
    } else {
      cout << "chiedo: " << a << " " << b << endl;
      if (b >= a) {
        ans.push_back(tree.range_query(a, b));
      } else {
        auto appo = std::min(tree.range_query(0, b), tree.range_query(a, n));  // ocio
        ans.push_back(appo);
      }
    }
    print_all(cout, tree) << endl;
  }
  for (const auto& it: ans) {
    cout << it << "\n";
  }
  return 0;
}
