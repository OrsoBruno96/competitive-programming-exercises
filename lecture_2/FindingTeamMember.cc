
#include <bits/stdc++.h>

using namespace std;

// We define a class to store the data
class Team {
 public:
  Team(const int a, const int b, const int strength) :
    a_(a), b_(b), strength_(strength) {}

  int a_;
  int b_;
  int strength_;
};


int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int N = 0;
  cin >> N;
  const int nteams = N;
  vector<Team> all_teams;
  all_teams.reserve(nteams*(nteams - 1)/2);
  {
    int appo = 0;
    for (int i = 1; i < 2*nteams; i++) {
      for (int j = 0; j < i; j++) {
        cin >> appo;
        all_teams.emplace_back(i, j, appo);
      }
    }
  }
  // We sort teams by decreasing strength
  std::sort(all_teams.begin(), all_teams.end(),
            [](const Team& a, const Team& b) {
              return a.strength_ > b.strength_;
            });
  vector<int> tm(nteams*2, -1);  // teammate
  int counter = 0;
  // And we select them greedily.
  // Overall complexity dominated by sorting algorithm
  // O(n log n)
  for (const auto& it: all_teams) {
    if ((tm[it.a_] == -1) && (tm[it.b_] == -1)) {
      tm[it.a_] = it.b_;
      tm[it.b_] = it.a_;
      counter++;
      if (counter == nteams) {
        break;
      }
    }
  }

  for (const auto& it: tm) {
    // Off by one
    cout << it + 1 << " ";
  }
  cout << "\n";
  return 0;
}
