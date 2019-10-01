
#include <bits/stdc++.h>


int main(int argc, char* argv[]) {
  using namespace std;
  // TC = Test Cases
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int size = 0;
    cin >> size;
    vector<int> vettore;
    vettore.reserve(size);
    // Save in vector all numbers
    for (auto i = size; i > 0; i--) {
      int appo = 0;
      cin >> appo;
      vettore.push_back(appo);
    }
    vector<int> leaders;
    leaders.reserve(size);
    int max = *vettore.rbegin();
    for (auto it = vettore.rbegin(); it != vettore.rend(); it++) {
      if (*it >= max) {
        max = *it;
        leaders.push_back(max);
      }
    }
    for (int i = leaders.size() - 1; i >= 0; i--) {
      cout << leaders[i];
      if (i != 0) {
        cout << " ";
      }
    }
    cout << "\n";
  }
  
  return 0;
}
