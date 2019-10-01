
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    // Keep maximum value and current sum
    int max; int current;
    // Initialize max to a small value
    max = INT_MIN;
    current = 0;
    // alop = at least one positive
    bool alop = false;
    for (auto i = N; i > 0; i--) {
      int appo;
      cin >> appo;
      // The problem is when I start with a lot of negative numbers
      // I cannot sum naively because starting from a positive is
      // better than adding a positive to a negative
      if (alop || max == INT_MIN) {
        current += appo;
      } else {
        current = (appo > current) ? appo : current;
      }
      alop = alop || (appo > 0);
      if (current > max) {
        max = current;
      }
      // if i get to a negative value from a positive i can start again
      if (current < 0 && max > 0) {
        current = 0;
      }
    }
    cout << max << "\n";
  }

  return 0;
}
