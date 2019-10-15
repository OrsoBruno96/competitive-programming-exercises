
#include <bits/stdc++.h>
#include "Fenwick.h"

using namespace std;

using pii = pair<int, int>;
using piii = pair<int, pii>;
using vpii = vector<pii>;
using vpiii = vector<piii>;

int main(int argc, char* argv[]) {
  int N = 0;
  cin >> N;

  vpiii segments;
  vpii lefts;
  lefts.reserve(N);
  segments.reserve(N);
  for (int i = 0; i < N; i++) {
    int l, r;
    cin >> l >> r;
    segments.emplace_back(i, pii(l, r));
    lefts.emplace_back(i, l);
  }
  // rielaborare l
  sort(lefts.begin(), lefts.end(),
       [](const auto& left, const auto& right) {
         return left.second < right.second;
       });
  for (int i = 0; i < N; i++) {
    // Questo rimappa in 0, N - 1 i valori di sinistra.
    segments[lefts[i].first].second.first = i;
  }
  sort(segments.begin(), segments.end(),
       [](const auto& left, const auto& right) {
         return left.second.second < right.second.second;
       });
  Fenwick<int> ft(10*N);
  vector<int> contents(N, 0);
  // for (const auto& it: segments) {
  //   cout << it.second.first << " " << it.second.second << "\n";
  // }

  for (int i = 0; i < N; i++) {
    contents[segments[i].first] = i - ft.sum(segments[i].second.first);
    ft.add(segments[i].second.first, 1);
  }
  for (const auto& it: contents) {
    cout << it << "\n";
  }
  return 0;
}
