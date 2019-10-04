#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  string s;
  cin >> s;
  vector<int> queries(s.size(), 0);
  // We can solve in linear time preprocessing the string.
  // We keep an array with a prefix sum of the
  // elements which have the an equal successor.
  for (auto i = 0; i < s.size() - 1; i++) {
    const int prec = (i >= 0) ? queries[i] : 0;
    if (s[i] == s[i + 1]) {
      queries[i + 1] = prec + 1;
    } else {
      queries[i + 1] = prec;
    }
  }
  int n = 0;
  cin >> n;
  vector<int> answers;
  for (auto i = 0; i < n; i++) {
    int init, end;
    cin >> init >> end;
    answers.push_back(queries[end - 1] - queries[init - 1]);
  }
  for (auto const& it: answers) {
    cout << it << " ";
  }
  cout << "\n";
  return 0;
}
