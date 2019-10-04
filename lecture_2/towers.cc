#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
  int N = 0;
  // I use a map structure because it inserts sorted with O(log n) time
  using pil = pair<int, long>;
  map<int, long> mapp;
  cin >> N;
  int buf;
  // Overall complexity of O(n log n)
  for (auto i = N; i > 0; i--) {
    cin >> buf;
    auto it = mapp.insert(pil(buf, 1));
    if (!it.second) {
      it.first->second += 1;
    }
  }
  // O(n), but this is not the bottleneck.
  auto max = max_element(
      mapp.begin(), mapp.end(),
      [](const pil& p1, const pil& p2) {
        return p1.second < p2.second;
      });
  cout << max->second << " " <<  mapp.size() << endl;

  return 0;
}
