
#include <bits/stdc++.h>

using namespace std;

constexpr int NUM_LETTERS = 26;

using vi = vector<int>;
using li = long unsigned int;


// The problem can be recasted in a form that gives a solution in term
// of standard graph algorithms.
// First of all, using the comparison of only neighbours
// (string and its successor)
// it's necessary and sufficient because lexycographical ordering
// is a good ordering.
// We can build a directed graph from the comparison conditions
// between each string
// and its successor (for example if I compare "fox" and "wolf",
// I will have a graph with all the letters of the alphabet as vertices
// and an edge connecting f to w)

// Finding an order that satisfies our problem question is equivalent
// to finding a topological order on this graph. The topological order exists
// only if the graph is acyclic, so we have to 2 two standard things:
// 1. Check whether if the graph is acyclic or not
// 2. If it is a DAG, find the topological order.


// We can do this with only one dfs. If we find a back edge, we have a cycle
// and we can stop.
// We put on a stack the vertexes every time we finish the visit.
// The answer is the stack in reversed order.

// Time and space complexity: O(|E| + |V|)


bool dfs(const int& i, vector<int>& visited,
         const vector<vi>& adj_list,
         vi& stack, li& counter) {
  if (visited[i] == 1) {
    return true;
  } else if (visited[i] == 0) {
    return false;
  }
  visited[i] = 0;
  for (auto& it: adj_list[i]) {
    auto appo = dfs(it, visited, adj_list, stack, counter);
    if (!appo) {
      return appo;
    }
  }
  stack.push_back(i);
  visited[i] = 1;
  counter++;
  return true;
}



bool topological_sort(const vector<vi>& adj_list,
                      vi& answer) {
  const auto size = adj_list.size();

  // -1 not visited
  // 0 visiting
  // 1 visited
  vector<int> visited(size, -1);
  answer.reserve(size);

  li counter = 0;
  bool finished = true;
  while (counter < size) {
    const auto first = std::distance(visited.begin(),
                                     std::find(visited.begin(),
                                               visited.end(), -1));
    auto appo = dfs(first, visited, adj_list, answer, counter);
    if (!appo) {
      finished = false;
      break;
    }
  }
  std::reverse(answer.begin(), answer.end());
  return finished;
}



int main() {
  int n = 0;
  cin >> n;
  vector<string> words;
  words.reserve(n);
  for (int i = 0; i < n; i++) {
    string appo;
    cin >> appo;
    words.emplace_back(appo);
  }
  vector<vi> adj_list(NUM_LETTERS, vi());

  for (int i = 0; i < n - 1; i++) {
    li cursor = 0;
    auto size1 = words[i].size(), size2 = words[i + 1].size();
    while (cursor < size1 && cursor < size2 &&
           words[i].at(cursor) == words[i + 1].at(cursor)) {
      cursor++;
    }
    if (cursor == size2) {
      cout << "Impossible\n";
      return 0;
    }
    if (cursor == size1) {
      continue;
    }
    adj_list[words[i][cursor] - 'a'].push_back(words[i + 1][cursor] - 'a');
  }

  vector<int> answer;
  answer.reserve(NUM_LETTERS);
  bool done = topological_sort(adj_list, answer);
  if (!done) {
    cout << "Impossible\n";
  } else {
    for (const auto& it: answer) {
      cout << string(1, 'a' + it);
    }
    cout << "\n";
  }
  return 0;
}
