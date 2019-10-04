#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0, K = 0;
    cin >> N >> K;
    // max_q is a double-ended queue of indexes. It is sorted
    // in a way such that the front is always the maximum index.
    // I keep only the necessary indexes of the last K values.
    // If I encounter a new value, bigger than its predecessor, I can safely
    // discard that predecessor, and so on until the end of the queue.
    deque<int> max_q;
    vector<int> all_values;
    // I save the max_list values in a vector because outputting
    // on every iteration is really time consuming.
    vector<int> max_list;
    all_values.reserve(N);
    max_list.reserve(N - K + 1);
    for (auto i = 0; i < N; i++) {
      int appo;
      cin >> appo;
      all_values.push_back(appo);
      while (!max_q.empty() && max_q.back() <= i - K) {
        max_q.pop_back();
      }
      while (!max_q.empty() && all_values[max_q.front()] <= appo) {
        max_q.pop_front();
      }
      max_q.push_front(i);
      if (i > K - 2) {
        max_list.push_back(all_values[max_q.back()]);
      }
    }
    for (const auto& it: max_list) {
      cout << it << " ";
    }
    cout << "\n";
  }
}
