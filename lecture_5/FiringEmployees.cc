
#include <bits/stdc++.h>

using namespace std;

// Sieve of eratosthenes
vector<bool> generate_primes(size_t n) {
  vector<bool> primes(n, true);
  primes[1] = false;
  primes[0] = false;
  for(uint64_t i = 2; i <= (uint64_t) sqrt(n); ++i) {
    if (primes[i]) {
      uint64_t isquare = i*i;
      for(uint64_t j = isquare; j < n; j+=i)
        primes[j] = false;
    }
  }
  return primes;
}


int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    vector<int> original;
    original.reserve(N);

    for (auto i = 0; i < N; i++) {
      int appo;
      cin >> appo;
      original.push_back(appo);
    }

    // Now I invert the relation.
    // The problem gives me the senior of each worker, now I want to get
    // his juniors.
    // The list in position i is the list of people exactly below the
    // worker with rank i.
    vector<vector<int>> positions(N + 1, vector<int>());
    for (int i = 0; i < N; i++) {
      positions[original[i]].push_back(i + 1);
    }
    // Vector of "how many seniors do the employee with rank i has?"
    vector<int> seniors(N + 1, 0);
    stack<int> s;
    // The first one is mr alfred.
    s.push(positions[0].front());
    for (int i = 0; i < N; i++) {
      // At first I have exactly the ones below mr alfred.
      auto list = positions[s.top()];
      s.pop();
      for (auto pos: list) {
        // For every person below I annotate how many people are above him
        seniors[pos] = 1 + seniors[original[pos - 1]];
        // And put it in the stack, to compute the same quantity for the
        // people below him.
        s.push(pos);
      }
    }
    auto primes = generate_primes(2*(N + 1));

    int fired = 0;
    for (int i = 1; i <= N; i++) {
      if (seniors[i] && primes[seniors[i] + i]) {
        fired++;
      }
    }
    cout << fired << "\n";
  }
  return 0;
}
