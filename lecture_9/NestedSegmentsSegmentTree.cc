
#include <bits/stdc++.h>
#include "SegmentTree.h"

using namespace std;

using pii = pair<int, int>;
using piii = pair<int, pii>;
using vpii = vector<pii>;
using vpiii = vector<piii>;

// Time complexity:
// I have to sort an array of length N and work with a Fenwick tree N times,
// so complexity is O(N log N)

// Space complexity:
// I need an extra array to remap my values, but nothing that scales worse
// than O(N) where N is the size of the array


int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N = 0;
  cin >> N;

  vpiii segments;
  segments.reserve(N); {
  vpii lefts;
  lefts.reserve(N);
  for (int i = 0; i < N; i++) {
    int l, r;
    cin >> l >> r;
    segments.emplace_back(i, pii(l, r));
    lefts.emplace_back(i, l);
  }
  // I want to use a Fenwick tree, but to do so I
  // need to remap my values from generic signed integers
  // to values that are a permutaion of (1, ..., n)
  // The following lines do exactly this to the left end
  // of the segments.
  sort(lefts.begin(), lefts.end(),
       [](const auto& left, const auto& right) {
         return left.second < right.second;
       });
  for (int i = 0; i < N; i++) {
    segments[lefts[i].first].second.first = i;
  }
  }
  // Now I sort my segments by increasing right end.
  sort(segments.begin(), segments.end(),
       [](const auto& left, const auto& right) {
         return left.second.second < right.second.second;
       });
  SegmentTree<int> ft(N);
  vector<int> contents(N, 0);
  // for (const auto& it: segments) {
  //   cout << it.second.first << " " << it.second.second << "\n";
  // }

  // Now I iterate through the segments, sorted as before.
  // Every segment that I didn't elaborate cannot be included in
  // the one I'm elaborating now because it's right end
  // is after the right end of the current one.
  // So I can concentrate on the ones already seen.

  // I use a fenwick tree because I want to keep track dynamically
  // of the places where a segment starts.
  // If a segment is not started yet at the position where the current
  // left end is, it means that that segment is inside the current one.

  // With the fenwick tree I keep track of the number of left ends I
  // have already seen in position i, so if I want the ones that did not
  // start yet, I can simply take the complementary (total is i, i subtract
  // the value in FT)
  for (int i = 0; i < N; i++) {
    contents[segments[i].first] = i - ft.range_query(0, segments[i].second.first - 1);
    ft.add(segments[i].second.first, 1);
  }
  for (const auto& it: contents) {
    cout << it << "\n";
  }
  return 0;
}
