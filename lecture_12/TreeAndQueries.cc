

// First of all I produce a linearized version of my tree.
// I save in auxiliary vectors a dfs of the tree
// and pointers to the dfs that for each vertex point to
// the beginning and the end of its subtree.

// then i sort the queries as in Mo's algorithm,
// using the dfs as segment and the pointers as start and
// end of the query.

// Done that, I simply apply Mo's algorithm to obtain the answer.




#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using vpii = vector<pii>;
using ppi = pair<int, pii>;
using vppi = vector<ppi>;
using vi = vector<int>;


inline void add(int i, const vi& colors, vi& color_counter,
         vi& greater_than) {
  color_counter[colors[i]]++;
  greater_than[color_counter[colors[i]]]++;
}


inline void remove(int i, const vi& colors, vi& color_counter,
            vi& greater_than) {
  greater_than[color_counter[colors[i]]]--;
  color_counter[colors[i]]--;
}


void solve(const vppi& queries, const vi& visit, const vi& colors,
           vi& answers, const vpii& terminals) {
  int curr_i = 0, curr_j = 0;
  const int n = colors.size();
  vi color_counter(n, 0);
  vi greater_than(n + 2, 0);

  add(0, colors, color_counter, greater_than);
  for (const auto& it: queries) {
    const auto query = it.second;
    const auto v_i = query.first;
    const auto k_i = query.second;

    if (k_i > n + 1) {
      answers[it.first] = 0;
      continue;
    }

    while (curr_j > terminals[v_i].second) {
      remove(visit[curr_j], colors, color_counter, greater_than);
      curr_j--;
    }
    while (curr_j < terminals[v_i].second) {
      curr_j++;
      add(visit[curr_j], colors, color_counter, greater_than);
    }
    while (curr_i < terminals[v_i].first) {
      remove(visit[curr_i], colors, color_counter, greater_than);
      curr_i++;
    }
    while (curr_i > terminals[v_i].first) {
      curr_i--;
      add(visit[curr_i], colors, color_counter, greater_than);
    }
    auto ans = 0;
    if (k_i >= 0) {
      ans = greater_than[k_i];
    } else {
      ans = n;
    }
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
    query_groups[group].emplace_back(ppi(i, pii(appo1, appo2)));
  }

  for (auto& it: query_groups) {
    std::sort(it.begin(), it.end(),
              [&terminals](const ppi& left, const ppi& right) {
                return terminals[left.second.first].second <
                  terminals[right.second.first].second;
              });
  }
  for (const auto& it: query_groups) {
    for (const auto& jt: it) {
      all_sorted_queries.push_back(jt);
    }
  }
}


void dfs(const int vertex, const vector<vi>& adj_list,
         vi& visit, vector<bool>& visited,
         vpii& terminals) {
  if (visited[vertex]) { return; }
  visited[vertex] = true;
  terminals[vertex].first = visit.size();
  visit.push_back(vertex);
  for (const auto& it: adj_list[vertex]) {
    dfs(it, adj_list, visit, visited, terminals);
  }
  terminals[vertex].second = visit.size() - 1;
}



void produce_visit(const int n, const vector<vi>& adj_list,
                        vi& visit, vpii& terminals) {
  vector<bool> visited(n + 1, false);
  dfs(0, adj_list, visit, visited, terminals);
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
  vi visit;
  // Pair of values. For every node n in the tree
  // terminals[n] is a pair of indexes in visit
  // that point to the beginning and to the end of the
  // subtree.
  vpii terminals(n, pii(-1, -1));
  visit.reserve(n);
  terminals.reserve(n);
  for (auto i = 0; i < n; i++) {
    cin >> colors[i];
  }
  remap_colors(colors);

  for (auto i = 0; i < n - 1; i++) {
    int appo1 = 0, appo2 = 0;
    cin >> appo1 >> appo2;
    appo1--; appo2--;
    adj_list[appo1].push_back(appo2); adj_list[appo2].push_back(appo1);
  }
  produce_visit(n, adj_list, visit, terminals);

  vppi queries;
  vector<int> answers(m, 0);
  queries.reserve(m);
  const int division = std::sqrt(n) + 1;
  get_sorted_queries(division, m, queries, terminals);


  solve(queries, visit, colors, answers, terminals);
  for (const auto& it: answers) {
    cout << it << "\n";
  }
  return 0;
}
