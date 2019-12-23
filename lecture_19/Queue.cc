
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;


using psi = pair<string, int>;
using vpsi = vector<psi>;


// The solution to this problem is greedy.
// First of all, we sort our people by increasing number of
// people in front of them.
// It it obvious that if a_i > i, then the solution does not exist.

// We are going to construct a solution if this is not the case.
// If all the values a_i were different, the solution would be trivial
// because we can simply use these values as "inverse height" (height = N - a_i)
// If there are equal a_i, the situation is a bit more difficult.

// The idea is the following. Without loss of generality, we say that
// the heights are a permutation of [1, ..n]. In this way, we can
// produce heights simply giving an order to the people in the
// queue.
// The following idea is to put greedily a person with a_n in position
// a_n if a_n is not repeated and to "fill the holes" if there are repetitions.


// Time complexity: O(N^2)
// space complexity: O(N)


int main() {
  int N = 0;
  cin >> N;
  vpsi people;
  people.reserve(N);
  for (int i = 0; i < N; i++) {
    string s;
    int appo;
    cin >> s >> appo;
    people.emplace_back(s, appo);
  }

  sort(people.begin(), people.end(), [](const psi& l, const psi& r) {
                                        return l.second < r.second;
                                      });
  // Check if the solution exists
  for (int i = 0; i < N; i++) {
    if (people[i].second > i) {
      cout << "-1\n";
      return 0;
    }
  }

  // Now compute the solution
  vpsi answers(N, psi("", 0));

  int i = N - 1;
  int heigth = 1;
  while (i >= 0) {
    int a_i = people[i].second;
    int j = i;
    // We look for a value change
    while (people[j].second == a_i && j >= 0) {
      j--;
    }
    // Insert people with a_k = a_i
    int free_idx = a_i;
    for (int k = j + 1; k < i + 1; k++) {
      // Look for a free place to put him
      while (answers[free_idx].second != 0 && free_idx < N) {
        free_idx++;
      }
      answers[free_idx] = psi(people[k].first, heigth);
      heigth++;
    }
    i = j;
  }


  for (int i = 0; i < N; i++) {
    cout << answers[i].first << " " << answers[i].second << "\n";
  }
  return 0;
}
