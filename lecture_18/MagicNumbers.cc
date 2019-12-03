
#include <bits/stdc++.h>

using namespace std;

// Simple algorithm:
// I scan the figures backwards:
// If I get something different from 1 or 4 the number is not magic
// It is never a problem to have a 1
// I cannot have more than 2 4s in a row, so I keep a counter that
// I reset when I encounter a 1.
// I cannot have a number starting with 4.


// Time complexity: O(N)

int main() {
  string magic_number;
  cin >> magic_number;
  bool magic = true;
  int carry = 0;
  for (int i = magic_number.size() - 1; i >= 0; i--) {
    if (magic_number.at(i) != '1' && magic_number.at(i) != '4') {
      magic = false;
      break;
    }
    if (magic_number.at(i) == '1') {
      carry = 0;
    }
    if (magic_number.at(i) == '4') {
      carry++;
      if (carry > 2) {
        magic = false;
        break;
      }
    }
  }
  if (carry > 0) {
    magic = false;
  }
  if (magic) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }

  return 0;
}
