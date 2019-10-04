

#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;  // <height, horizontal position>

struct order_compare {
  bool operator() (const pii& a, const pii& b) const {
    return a.first > b.first;
  }
};

int main(int argc, char* argv[]) {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    vector<pii> columns;
    columns.reserve(N);
    {
      int prec = -1, count = 0;
      for (auto i = N; i > 0; i--) {
        int appo;
        cin >> appo;
        if (prec != appo) {
          columns.push_back(pii(appo, count));
          prec = appo;
          count++;
        }
      }
    }
    // This problems admits a greedy solution.
    // If I sort all the columns by height, i can loop
    // over them in descending order and fill a rectangle with
    // height of the second.
    const order_compare cusumano;
    stable_sort(columns.begin(), columns.end(), cusumano);
    int counter =
      (columns[0].second == 0
       || columns[0].second == (columns.size() - 1)) ?
      1 : 0;
    int volume = 0, i = 1;
    for (const auto& i: columns) {
      cout << "(" << i.second << ", " << i.first << ") ";
    }
    cout << '\n';
    // Sorted in reverse order, i need to start from the end.
    // Actually not the end but the one before the end.
    auto prec = columns[0];
    auto precprec = columns[0];
    while (counter < 2) {
      const int horiz = (abs(columns[i].second - prec.second) - 1);
      if (horiz == 0) {
        if ( ) {
          volume -= columns[i].first;
        }
      } else {
        precprec = prec;
        prec = columns[i];
        volume += columns[i].first * horiz;
      }
      if (columns[i].second == 0 || columns[i].second == (columns.size() - 1)) {
        counter++;
      }
      i++;
    }
    while (i < columns.size()) {
      volume -= columns[i].first;
      i++;
    }
    cout << volume << "\n";
  }
  return 0;
}
