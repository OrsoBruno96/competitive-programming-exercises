#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int n = 0;
    cin >> n;
    vector<int> A;
    A.reserve(n);
    for (auto i = 0; i < n; i++) {
      int appo = 0;
      cin >> appo;
      A.push_back(appo);
    }

    // I keep items in my stack starting from the "expected minimum"
    // When I go to a left subtree
    // Every time I go to a right subtree
    // I keep track of it's root.
    // At the next iteration if the new element is smaller,
    // the tree is unbalanced


    int root = INT_MIN;
    stack<int> s;
    int result = -1;
    for (const auto& current: A) {
      if (current < root) {
        result = 0; break;
      }
      while (!s.empty()) {
        if (current < s.top()) {
          s.pop();
        } else {
          root = s.top();
          break;
        }
      }
      s.push(current);
      // cout << "Stack: ";
      // for (stack<int> dump = s; !dump.empty(); dump.pop()) {
      //   cout << dump.top() << " ";
      // }
      // cout << "root: " << root <<  "\n";
    }
    result = (result == -1) ? 1 : result;
    cout << result << "\n";
  }
  return 0;
}
