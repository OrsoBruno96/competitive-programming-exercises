#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  using ll = long long int;
  int TC = 0;
  cin >> TC;
  while (TC--) {
    // I save in an array the number of occurencies of every
    // digit.
    array<int, 10> occurrencies({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    string s;
    cin >> s;
    for (const auto& c: s) {
      int i = ((int) c) - ((int) '0');
      occurrencies[i] += 1;
    }
    // This will save the smallest even number.
    int smallest = -1;
    for (auto i = 0; i < 9; i += 2) {
      if (occurrencies[i]) {
        smallest = i;
        break;
      }
    }
    // Print all digits in descending order.
    // But do it one time less if the digit is the smallest even digit.
    // That digit will be printed at the end.
    for (auto i = 9; i > 0; i--) {
      auto times = (i == smallest) ? occurrencies[i] - 1 : occurrencies[i];
      for (auto j = 0; j < times; j++) {
        cout << i;
      }
    }
    // Now if the number contains an even digit, print it
    if (smallest != -1) {
      cout << smallest;
    }
    cout << "\n";
  }
  return 0;
}
