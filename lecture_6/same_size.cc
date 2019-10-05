
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  using ll = long long;
  int N = 0;
  cin >> N;
  vector<ll> prefix_sum(N, 0);
  vector<ll> second_prefix(N, 0);
  for (auto i = 0; i < N; i++) {
    long appo;
    cin >> appo;
    if (i > 0) {
      prefix_sum[i] = prefix_sum[i - 1] + appo;
    } else {
      prefix_sum[i] = appo;
    }
  }
  if (prefix_sum[N - 1] % 3) {
    cout << "0\n";
    return 0;
  }
  const ll division = prefix_sum[N - 1] / 3;
  for (auto i = N - 1; i > 0; i--) {
    const ll prec = (i < N - 1) ? second_prefix[i + 1] : 0;
    if (prefix_sum[i - 1] == 2*division) {
      second_prefix[i] = prec + 1;
    } else {
      second_prefix[i] = prec;
    }
  }
  ll how_many = 0;
  for (auto i = 0; i < N - 2; i++) {
    if (prefix_sum[i] == division) {
      how_many += second_prefix[i + 2];
    }
  }

  // for (const auto& it: prefix_sum) {
  //   cout << it << " ";
  // }
  // cout << "\n";
  // for (const auto& it: second_prefix) {
  //   cout << it << " ";
  // }
  // cout << "\n";
  cout << how_many << endl;

  return 0;
}
