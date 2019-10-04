

#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    vector<int> columns;
    columns.reserve(N);
    // Get all values to be used later.
    for (auto i = N; i > 0; i--) {
      int appo;
      cin >> appo;
      columns.push_back(appo);
    }
    int volume = 0;

    // The tallest water level will be in the "middle",
    // Meaning that there exist a point x, between 0 and N - 1
    // where if I go from 0 to x or from N - 1 to x, the water level
    // is always increasing.
    // This is useful because I can simply keep track of the max for the
    // two sides while advancing to the middle.
    // Every time I find a new tallest, the water level (height_(s|d)x)
    // will rise.
    auto sx = columns.begin();
    auto dx = columns.end() - 1;
    int height_sx = 0, height_dx = 0;
    while (sx != dx) {
      if (*sx < *dx) {
        height_sx = max(*sx, height_sx);
        volume += height_sx - *sx;
        sx++;
      } else {
        height_dx = max(*dx, height_dx);
        volume += height_dx - *dx;
        dx--;
      }
      // cout << *sx << ", " << *dx << ", (" << height_sx << ", " <<
      //   height_dx << ")\n";
    }
    cout << volume << "\n";
  }
  return 0;
}
