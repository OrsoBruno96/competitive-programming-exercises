#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);
  using ll = long long int;
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    stack<int> tbf;  // to be found (the next one)
    vector<ll> all_values;
    vector<ll> greaters(N, 0);
    all_values.reserve(N);
    for (int i = 0; i < N; i++) {
      ll appo = 0;
      cin >> appo;
      all_values.push_back(appo);
      while (!tbf.empty() && (appo > all_values[tbf.top()])) {
        greaters[tbf.top()] = appo;
        tbf.pop();
      }
      tbf.push(i);
    }
    while (!tbf.empty()) {
      greaters[tbf.top()] = -1;
      tbf.pop();
    }
    for (const auto& it: greaters) {
      cout << it << " ";
    }
    cout << "\n";
  }
  return 0;
}
