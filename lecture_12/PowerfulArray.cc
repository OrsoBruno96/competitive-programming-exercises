
#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;

using ppi = pair<int, pi>;
using vppi = vector<ppi>;
using vvppi = vector<vppi>;
using ll = long long;
using vl = vector<ll>;



// I am going to use Mo's algorithm, which is known to have
// O((n + t)sqrt(n)) complexity.

// The idea is to process the queries together, trying to
// avoid to do the same calculations too many times.
// I keep two pointers to the original list, curr_i, curr_j.
// I store in a local variable the answer to the query on the
// interval (curr_i, curr_j). I need to define how to change
// the query result if I move one of the two pointers and this is
// done via the add and remove functions.

// For now, it is only a different way of approaching the problem,
// the complexity is the same. The interesting point is ordering
// the queries in a way that reduces the overall complexity.
// If I only sort them for one of the endpoints, I do not improve
// much my situation because in the worst case scenario the other
// extreme will oscillate back and forth
// through the whole initial vector at each iteration.
// Mo's idea is to divide the query in groups of size sqrt(n)
// and sort them inside the group division.
// This means that for each group one of the extremes may move through the
// whole initial vector (but only once, because it's sorted),
// but the other one is confined in a smaller (sqrt(n)) segment. The
// latter one can go back and forth at will in the worst case scenario,
// but it is confined in a smaller region, and this gives an improvement.

// The overall time complexity is
// \[ \sum_{i \in G} [ {# of queries in group i} \cdot \sqrt(n) + n] = \sqrt(n) (t + n) \]


void add(const int i, const vi& original, vi& counter, ll& ans) {
  ans += (2*counter[original[i]] + 1)*original[i];
  counter[original[i]]++;
}

void remove(const int i, const vi& original, vi& counter, ll& ans) {
  ans += (1 - 2*counter[original[i]])*original[i];
  counter[original[i]]--;
}

void solve(const vppi& queries, const vi& original, vl& answers) {
  int curr_i = 0, curr_j = 0;
  ll ans = 0;
  vi counter(1000*1000 + 1, 0);
  for (const auto& it: queries) {
    const auto query = it.second;
    const auto i = query.first;
    const auto j = query.second;
    while (curr_i < i) {
      remove(curr_i, original, counter, ans);
      curr_i++;
    }
    while (curr_i > i) {
      curr_i--;
      add(curr_i, original, counter, ans);
    }
    while (curr_j > j) {
      remove(curr_j, original, counter, ans);
      curr_j--;
    }
    while (curr_j < j) {
      curr_j++;
      add(curr_j, original, counter, ans);
    }

    answers[it.first] = ans;
  }
}



// This block gets input and sorts queries in Mo's algorithm order.
// The result is saved in all_sorted_queries
void get_sorted_queries(const int division, const int t, vppi& all_sorted_queries) {
  vvppi query_groups(division, vppi());
  for (int i = 0; i < t; i++) {
    int appo1 = 0, appo2 = 0;
    cin >> appo1 >> appo2;
    // queries.emplace_back(pi(appo1, appo2));
    query_groups[appo1 / division].emplace_back(ppi(i, pi(appo1, appo2)));
  }
  for (auto& it: query_groups) {
    std::sort(it.begin(), it.end(), [](const ppi& left, const ppi& right) {
                                      return left.second.second < right.second.second;
                                    });
  }
  for (const auto& it: query_groups) {
    for (const auto& jt: it) {
      all_sorted_queries.push_back(jt);
    }
  }
}


int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n = 0, t = 0;
  cin >> n >> t;
  vi original(n + 1, 0);
  vector<ll> answers(t, 0);
  vppi all_sorted_queries;
  all_sorted_queries.reserve(t);
  int division = std::sqrt(n) + 1;  // just to avoid errors due to roundoff
  for (int i = 1; i < n + 1; i++) {
    int appo = 0;
    cin >> appo;
    original[i] = appo;
  }
  get_sorted_queries(division, t, all_sorted_queries);
  solve(all_sorted_queries, original, answers);

  for (int i = 0; i < t; i++) {
    cout << answers[i] << "\n";
  }

  return 0;
}
