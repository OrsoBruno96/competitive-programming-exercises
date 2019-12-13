
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using ll = long long int;

void end_dfs(const int& i, vector<bool>& visited,
             const vector<vi>& adj_list, unsigned long& counter, vi& end_time) {
  if (visited[i]) {
    return;
  }
  visited[i] = true;
  for (const auto& it: adj_list[i]) {
    end_dfs(it, visited, adj_list, counter, end_time);
  }
  end_time[i] = counter;
  counter++;
  return;
}


void sorted_dfs(const int& i, vector<bool>& visited,
                const vector<vi>& adj_list, unsigned long& counter, vi& component) {
  if (visited[i]) {
    return;
  }
  visited[i] = true;
  for (const auto& it: adj_list[i]) {
    sorted_dfs(it, visited, adj_list, counter, component);
  }
  counter++;
  component.push_back(i);
  return;
}


void find_strongly_connected(vector<vi>& scc, const vector<vi>& adj_list) {
  vector<vi> transposed;
  const auto size = adj_list.size();
  vector<int> end_time(size, 0);

  // cout << "adj list" << endl;
  // for (const auto it: adj_list) {
  //   for (const auto jt: it) {
  //     cout << jt << " ";
  //   }
  //   cout << endl;
  // }

  {  // first dfs
    unsigned long int counter = 0;
    vector<bool> visited(size, false);
    while (counter < size) {
      auto first = std::distance(visited.begin(),
                                 std::find(visited.begin(),
                                           visited.end(), false));
      // cout << "first: " << first << endl;
      end_dfs(first, visited, adj_list, counter, end_time);
    }
  }

  {  // Reversed sorted dfs
    vector<vi> transposed(size, vi());
    vi order(size, 0);
    vi right_order(size, 0);
    for (unsigned long int i = 0; i < size; i++) {
      order[i] = i;
    }
    for (unsigned long int i = 0; i < size; i++) {
      for (const auto& it: adj_list[i]) {
        transposed[it].push_back(i);
      }
    }
    for (auto& it: transposed) {
      sort(it.begin(), it.end(), [&](const auto& l, const auto& r) {
                                   return end_time[l] > end_time[r];
                                 });
    }
    sort(order.begin(), order.end(), [&]( const auto& l, const auto& r) {
                                       return end_time[l] > end_time[r];
                                     });
    for (int i = 0; i < (int) size; i++) {
      right_order[order[i]] = i;
    }

    unsigned long int counter = 0;
    vector<bool> visited(size, false);
    int scanner = 0;
    while (counter < size) {
      while ((scanner < (int) size) && visited[right_order[scanner]]) {
        scanner++;
      }
      int first = right_order[scanner];
      // cout << "Scanner: " << scanner << " First: " << first << endl;
      vi conn_component;
      sorted_dfs(first, visited, transposed, counter, conn_component);
      scc.push_back(conn_component);  // Fare con move syntax
    }
  }
}




int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  constexpr int MODULO = 1000000007;
  int n = 0, m = 0;
  cin >> n;
  vector<int> costs(n, 0);
  for (int i = 0; i < n; i++) {
    cin >> costs[i];
  }
  cin >> m;
  vector<vi> adj_list(n, vi());
  for (int i = 0; i < m; i++) {
    int appo1 = 0, appo2 = 0;
    cin >> appo1 >> appo2;
    adj_list[appo1 - 1].push_back(appo2 - 1);
  }

  vector<vi> scc;  // strongly connected components
  find_strongly_connected(scc, adj_list);
  ll total_minimum = 0;
  ll ways = 1;
  // cout << "Quante scc: " << scc.size() << endl;
  for (const auto& it: scc) {
    int min = INT_MAX;
    std::multimap<int, int> values;
    for (const auto& jt: it) {
      values.emplace(costs[jt], jt);
      min = std::min(min, costs[jt]);
    }
    total_minimum += min;
    auto counted = values.count(min);
    counted %= MODULO;
    ways %= MODULO;
    ways *= values.count(min);
    ways %= MODULO;
  }

  cout << total_minimum << " " << ways << "\n";

  return 0;
}
