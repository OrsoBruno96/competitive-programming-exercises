
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char* argv[]) {
  int N = 0;
  cin >> N;

  deque<int> queue;
  for (auto i = 0; i < N; i++) {
    int appo = 0;
    cin >> appo;
    queue.push_back(appo);
  }
  // Be careful to limits
  if (queue.size() == 1) {
    cout << "1 0\n";
    return 0;
  }
  // I keep track of the time remaining to finish the chocolate
  int atime, btime;
  // eat the first
  int acount = 1, bcount = 1;
  atime = queue.front();
  queue.pop_front();
  btime = queue.back();
  queue.pop_back();
  // Now race :)
  // Every operation is done in constant time and
  // I iterate once, so the overall complexity is linear.
  while (!queue.empty()) {
    // This is because Alice wins in draw case.
    if (atime <= btime) {
      btime -= atime;
      atime = queue.front();
      queue.pop_front();
      acount++;
    } else {
      atime -= btime;
      btime = queue.back();
      queue.pop_back();
      bcount++;
    }
  }
  cout << acount << " " << bcount << "\n";
  return 0;
}
