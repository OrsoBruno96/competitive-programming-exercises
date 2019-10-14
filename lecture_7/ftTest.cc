

#include "Fenwick.h"
#include <iostream>

using namespace std;


// Test for the fenwick tree.
int main() {
  Fenwick<int> foo(3);

  foo.add(0, 2);
  foo.add(1, 3);
  foo.add(1, 3);
  foo.add(2, 7);

  // Expected:
  // 2 6 7
  for (int i = 0; i < 3; i++) {
    cout << foo[i] << " ";
  }
  cout << endl;
  // Expected:
  // 2 8 7
  for (int i = 0; i < 3; i++) {
    cout << foo.get(i) << " ";
  }
  cout << endl;


  return 0;
}
