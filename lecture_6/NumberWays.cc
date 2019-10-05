
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  using ll = long long;
  int N = 0;
  cin >> N;
  vector<ll> prefix_sum(N, 0);
  vector<ll> second_prefix(N, 0);
  // We will use two different prefix sums. The first one
  // will be the usual one, the second will be trickier.
  for (auto i = 0; i < N; i++) {
    long appo;
    cin >> appo;
    if (i > 0) {
      prefix_sum[i] = prefix_sum[i - 1] + appo;
    } else {
      prefix_sum[i] = appo;
    }
  }
  // The last element in prefix sum is the sum of all elements.
  // If we want to divide, this number must be divisible by 3.
  if (prefix_sum[N - 1] % 3) {
    cout << "0\n";
    return 0;
  }
  const ll division = prefix_sum[N - 1] / 3;
  // Now we look at the prefix sum backwards. A possible second splitting
  // point must have the prefix sum equal to 2/3 * total.
  // We save in second_prefix the number of interesting points found
  // from the end to this point.
  for (auto i = N - 1; i > 0; i--) {
    const ll prec = (i < N - 1) ? second_prefix[i + 1] : 0;
    if (prefix_sum[i - 1] == 2*division) {
      second_prefix[i] = prec + 1;
    } else {
      second_prefix[i] = prec;
    }
  }
  ll how_many = 0;
  // Now, with some attention to indexes, we can get the answer simply noting
  // that if we look at the prefix sum in the original order, for every point
  // in which the sum is the right one (total / 3), we can choose each of the
  // interesting points on the right.
  // We saved this information before, so we can simply access it.
  for (auto i = 0; i < N - 2; i++) {
    if (prefix_sum[i] == division) {
      how_many += second_prefix[i + 2];
    }
  }

  cout << how_many << endl;

  return 0;
}
