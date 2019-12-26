

#include <bits/stdc++.h>
#include "Fenwick.h"
using namespace std;

using pii = pair<int, int>;
using vpii = vector<pii>;
using ppi = pair<int, pii>;
using vppi = vector<ppi>;
using vi = vector<int>;


void add(int i, const vi& colors, vi& color_counter,
         Fenwick<int>& greater_than) {
  const auto old = color_counter[colors[i]];
  // cout << "Aggiungo vertice " << i << " di colore " << colors[i] << endl;
  // cout << "Prima c'era " << old << " volte\n\n" << endl;
  color_counter[colors[i]]++;
  if (old >= 0) {
    greater_than.add(old, -1);
  }
  if (old >= -1) {
    greater_than.add(old + 1, 1);
  }
}


void remove(int i, const vi& colors, vi& color_counter,
            Fenwick<int>& greater_than) {
  const auto old = color_counter[colors[i]];
  // cout << "Tolgo vertice " << i << " di colore " << colors[i] << endl;
  // cout << "Prima c'era " << old << " volte\n\n" << endl;
  color_counter[colors[i]]--;
  if (old >= 0) {
    greater_than.add(old, -1);
  }
  if (old > 0) {
    greater_than.add(old - 1, 1);
  }
}


void solve(const vppi& queries, const vi& euler_tour, const vi& colors,
           vi& answers, const vpii& terminals) {
  int curr_i = 0, curr_j = 0;
  const int n = colors.size();
  vi color_counter(n + 1, 0);
  Fenwick<int> greater_than(2*n);
  greater_than.add(0, n);

  add(0, colors, color_counter, greater_than);
  for (const auto& it: queries) {
    const auto query = it.second;
    const auto v_i = query.first;
    const auto k_i = query.second;
    // cout << "Query: subtree di " << v_i << " " << k_i << " volte" << endl;
    // cout << "Voglio raggiungere a sx " << terminals[v_i].first <<
    //   " e a dx " << terminals[v_i].second << endl;

    while (curr_j > terminals[v_i].second) {
      remove(euler_tour[curr_j], colors, color_counter, greater_than);
      curr_j--;
    }
    while (curr_j < terminals[v_i].second) {
      curr_j++;
      add(euler_tour[curr_j], colors, color_counter, greater_than);
    }
    while (curr_i < terminals[v_i].first) {
      remove(euler_tour[curr_i], colors, color_counter, greater_than);
      curr_i++;
    }
    while (curr_i > terminals[v_i].first) {
      curr_i--;
      add(euler_tour[curr_i], colors, color_counter, greater_than);
    }
    auto ans = 0;
    if (k_i > 0) {
      if (k_i < n + 2) {
        ans = n - greater_than.sum(k_i - 1);
      } else {
        ans = 0;
      }
    } else {
      ans = n;
    }
    // cout << "Sono arrivato in posizione corretta. Dumpo i colori" << endl;
    // for (auto it: color_counter) {
    //   cout << it << " ";
    // }
    // cout << endl;
    // cout << "Quelli che sono piú piccoli di " << k_i - 1 << " sono " <<
    //   greater_than.sum(k_i - 1) << endl;
    // cout << "Risposta a questa query: " << ans << endl;
    // cout << "Dumpo il FT "  << endl;
    // for (int i = 0; i < n; i++) {
    //   cout << greater_than[i] << " ";
    // }
    // cout << endl;
    answers[it.first] = ans;
  }
}



void get_sorted_queries(const int division, const int t,
                        vppi& all_sorted_queries,
                        const vpii& terminals) {
  vector<vppi> query_groups(division, vppi());

  vpii vertex_start;
  const int n = terminals.size();
  vi groups(n, 0);
  vertex_start.reserve(n);
  for (int i = 0; i < n; i++) {
    vertex_start.emplace_back(i, terminals[i].first);
  }
  sort(vertex_start.begin(), vertex_start.end(),
       [](const auto& left, const auto& right) {
         return left.second < right.second;
       });
  for (int i = 0; i < n; i++) {
    groups[vertex_start[i].first] = i / division;
  }

  for (int i = 0; i < t; i++) {
    int appo1 = 0, appo2 = 0;
    cin >> appo1 >> appo2;
    appo1--;  // We want zero indexed values
    int group = groups[appo1];
    // cout << "Putting query for " << terminals[appo1].first << ", " <<
    //   terminals[appo1].second << "in group " << group << endl;
    query_groups[group].emplace_back(ppi(i, pii(appo1, appo2)));
  }
  for (auto& it: query_groups) {
    std::sort(it.begin(), it.end(),
              [&terminals](const ppi& left, const ppi& right) {
                return terminals[left.second.first] <
                  terminals[right.second.first];
              });
  }
  for (const auto& it: query_groups) {
    for (const auto& jt: it) {
      all_sorted_queries.push_back(jt);
    }
  }
}


void dfs(const int vertex, const vector<vi>& adj_list,
         vi& euler_tour, vector<bool>& visited,
         vpii& terminals) {
  if (visited[vertex]) { return; }
  visited[vertex] = true;
  terminals[vertex].first = euler_tour.size();
  euler_tour.push_back(vertex);
  for (const auto& it: adj_list[vertex]) {
    dfs(it, adj_list, euler_tour, visited, terminals);
  }
  terminals[vertex].second = euler_tour.size() - 1;
  // euler_tour.push_back(vertex);
}



void produce_euler_tour(const int n, const vector<vi>& adj_list,
                        vi& euler_tour, vpii& terminals) {
  vector<bool> visited(n + 1, false);
  dfs(0, adj_list, euler_tour, visited, terminals);
}


// This function remaps the colors in the range [0, n-1] for
// later convenience
void remap_colors(vi& colors) {
  map<int, int> color_map;
  int counter = 0;
  auto size = colors.size();
  for (unsigned int i = 0; i < size; i++) {
    auto right_color = color_map.find(colors[i]);
    if (right_color == color_map.end()) {
      color_map[colors[i]] = counter;
      counter++;
    }
  }
  for (unsigned int i = 0; i < size; i++) {
    colors[i] = color_map[colors[i]];
  }
}



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n = 0, m = 0;
  cin >> n >> m;
  vi colors(n);
  vector<vi> adj_list(n, vi());
  vi euler_tour;
  // Pair of values. For every node n in the tree
  // terminals[n] is a pair of indexes in euler_tour
  // that point to the beginning and to the end of the
  // subtree.
  vpii terminals(n, pii(-1, -1));
  euler_tour.reserve(n);
  terminals.reserve(n);
  for (auto i = 0; i < n; i++) {
    cin >> colors[i];
  }
  remap_colors(colors);

  for (auto i = 0; i < n - 1; i++) {
    int appo1 = 0, appo2 = 0;
    cin >> appo1 >> appo2;
    appo1--;
    appo2--;
    adj_list[appo1].push_back(appo2);
    adj_list[appo2].push_back(appo1);
  }
  produce_euler_tour(n, adj_list, euler_tour, terminals);
  // for (int i = 0; i < adj_list.size(); i++) {
  //   cout << "Vertex " << i + 1 << ": ";
  //   for (auto it: adj_list[i]) {
  //     cout << it + 1 << " ";
  //   }
  //   cout << endl;
  // }
  // cout << "Euler tour: " << endl;
  // for (auto it: euler_tour) {
  //   cout << it + 1 << " ";
  // }
  // cout << endl;
  // cout << "Terminals: " << endl;
  // for (auto it: terminals) {
  //   cout << "(" << it.first << ", " << it.second << ") ";
  // }
  // cout << endl;
  // for (int i = 0; i < colors.size(); i++) {
  //   cout << colors[i] << " ";
  // }
  // cout << endl;


  vppi queries;
  vector<int> answers(m, 0);
  queries.reserve(m);
  const int division = std::sqrt(n) + 1;
  get_sorted_queries(division, m, queries, terminals);

  // cout << "Debugging query order" << endl;
  // for (auto it: queries) {
  //   cout << "(" << it.second.first << ", " << it.second.second << ") ";
  // }
  // cout << endl;

  solve(queries, euler_tour, colors, answers, terminals);
  for (const auto& it: answers) {
    cout << it << "\n";
  }
  return 0;
}
