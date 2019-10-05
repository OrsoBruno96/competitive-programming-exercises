
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    // Compute all the expected sum of the numbers
    __int64_t sum = N*(N+1)/2;
    for (auto i = N; i > 1; i--) {
      int appo;
      cin >> appo;
      // I remove every entry I read from stdin
      sum -= appo;
    }
    // The final difference is the result.
    cout << sum << "\n";
  }

  return 0;
}
