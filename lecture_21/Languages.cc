

#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

// The idea is the following:
// I build an implicit graph where the edges connect people that can speak
// the same language.
// Finding the connected components in this graph is very close to the solution.
// The reason is that every person can communicate with the people in
// his connected component.
// Obs 1: every connected component has a set of languages that can be used.
// For each couple of connected components, these sets are disjoint. The reason is
// simple and done by contradiction. If they share a language, than they can communicate
// and they are in the same connected component.

// So, we can simply choose one of the two and make an employee learn a
// language from the other group.
// In this way, we just connected 2 disconnected components, and we can
// continue in this way.
// The answer to the problem is the number of connected components minus 1

// There only is a corner case where every employee doesn't know any language.


// Time complexity: the complexity of a dfs.


void dfs(const int employee, const vector<vi>& employees,
         const vector<vi>& languages, int& counter,
         vector<bool>& visited) {
  if (visited[employee]) {
    return;
  }
  visited[employee] = true;
  counter++;
  for (auto lan: employees[employee]) {
    for (auto collegue: languages[lan]) {
      dfs(collegue, employees, languages, counter, visited);
    }
  }
  return;
}

int main() {
  int n = 0, m = 0;
  cin >> n >> m;
  vector<vi> adj_list(n, vi());
  vector<vi> employees(n, vi());
  vector<vi> languages(m, vi());
  bool all_disconnected = true;
  for (int i = 0; i < n; i++) {
    int num = 0;
    cin >> num;
    if (num != 0) {
      all_disconnected = false;
    }
    employees[i].reserve(num);
    for (int j = 0; j < num; j++) {
      int appo;
      cin >> appo;
      employees[i].emplace_back(appo - 1);
      languages[appo - 1].emplace_back(i);
    }
  }
  vector<bool> visited(n, false);
  int counter = 0;
  int group_counter = 0;
  while (counter < n) {
    auto first = std::distance(visited.begin(), std::find(visited.begin(), visited.end(), false));
    dfs(first, employees, languages, counter, visited);
    group_counter++;
  }
  int extra = 0;
  if (all_disconnected) {
    extra = 1;
  }
  cout << group_counter + extra - 1 << "\n";

  return 0;
}
