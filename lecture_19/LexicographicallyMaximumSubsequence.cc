
#include <bits/stdc++.h>

using namespace std;


// To have a maximal sequence I always need to have the
// chars in decreasing order.
// So I need to find the largest char in the sequence
// and start my string with the number of occurrencies
// of that char.
// Let's suppose that the biggest char appears last at position i.
// Then I can repeat the same argument with the substring S[i + 1, N]
// and with the chars that are below the one I just selected.
// I can reach the end of string with the same procedure.

// I can do the same in linear time with the following preprocessing:
// I save in an array the last occurrency of char x for every x in the alphabet
// Then I select chars in the alphabet in decreasing order.
// If the char is in the string, I scan the remaning part of the string until the last position
// to find the number of occurrencies.
// When I reach the last occurrency I switch to the next char.

// Time complexity: O(N)
// Space complexity: O(N)


int main() {
  constexpr auto size = 'z' - 'a' + 1;
  array<int, size> last_pos;
  last_pos.fill(-1);
  array<int, size> how_many;
  how_many.fill(0);
  string original;
  cin >> original;
  int N = original.size();
  for (int i = 0; i < N; i++) {
    const auto c = original.at(i);
    const auto pos = c - 'a';
    last_pos[pos] = i;
  }
  int scan = 0;
  for (int i = size - 1; i >= 0; i--) {
    if (last_pos[i] == -1) {
      continue;
    }
    while (scan <= last_pos[i]) {
      if (original.at(scan) == ('a' + i)) {
        how_many[i]++;
      }
      scan++;
    }
  }
  string answer;
  answer.reserve(N);
  for (int i = size - 1; i >= 0; i--) {
    if (how_many[i] > 0) {
      answer += string(how_many[i], 'a' + i);
    }
  }
  cout << answer << "\n";

  return 0;
}
