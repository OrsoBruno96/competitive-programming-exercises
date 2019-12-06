
// C++ program to find out whether a given graph is Bipartite or not.
// It works for disconnected graph also.
#include <bits/stdc++.h>
using namespace std;
const int MAX = 100;
bool isBipartite(int G[][MAX],int V);
int main()
{
  int t;
  cin >> t;
  int g[MAX][MAX];
  while (t--) {
    memset(g,0,sizeof (g));
    int n;
    cin >> n;

    for (int i=0;i<n;i++) {
      for (int j=0;j<n;j++) {
        cin>>g[i][j];
      }
    }

    cout<<isBipartite(g,n)<<endl;
  }
  return 0;
}



// This is the code submitted to GFG
// The idea is simple. If a graph is bipartite, then I can divide in exactly
// two groups the node, and each node will be included in only one of the two.
// In particular, each node will be connected with only nodes of
// the other group.

// To make this check I can perform a BFS on the graph.
// I store in the queue not only the vertex number but also the
// group it should belong to.
// If a vertex has already been visited and it belongs to a group
// that is different from the group it should belong to,
// then the result is false. In the other case, we can continue.

// We also have 2 tricky corner cases for the |V| = 2 case.

// Time complexity: O(|E| + |V|)
// Space complexity: O(|E|)


using namespace std;
using pi = pair<int, int>;



bool isBipartite(int G[][MAX], int V) {
  vector<vector<int>> adj_list(V, vector<int>());
  for (auto i = 0; i < MAX; i++) {
    for (auto j = 0; j < MAX; j++) {
      if (G[i][j] == 1) {
        adj_list[i].push_back(j);
      }
    }
  }

  vector<set<int>> groups;
  groups.push_back(set<int>());
  groups.push_back(set<int>());

  queue<pi> q;
  vector<bool> visited(V, false);
  int counter = 0;
  int connected_components = 0;
  while (counter < V) {
    // becca il primo non falso
    int non_false = std::distance(visited.begin(),
                                  std::find(visited.begin(),
                                            visited.end(), false));
    q.emplace(non_false, connected_components);
    groups[connected_components].insert(non_false);
    while (!q.empty()) {
      const auto new_element = q.front();
      q.pop();
      const auto group = new_element.second;
      const auto i = new_element.first;
      const auto other_group = (group == 0) ? 1 : 0;
      visited[i] = true;
      counter++;
      for (const auto& it: adj_list[i]) {
        if (visited[it]) {
          auto found = groups[group].find(it);
          if (found != groups[group].end()) {
            return false;
          }
        } else {
          q.emplace(it, other_group);
          groups[other_group].insert(it);
        }
      }
    }
    connected_components++;
    if (connected_components > 2) {
      return false;
    }
  }
  if (V == 2 && counter == 1) {
    return true;
  }
  if (counter < V) {
    return false;
  }
  return true;
}
