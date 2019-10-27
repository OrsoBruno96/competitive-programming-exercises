
#include <bits/stdc++.h>
#include "LazySegmentTree.h"

using namespace std;


int main() {
  {
    LazySegmentTree<int, LazySegmentTypeAdd<int>> test(8);
    cout << "dbg" << endl;
    print_all(cout, test) << endl;
    test.add(2, 4);
    print_all(cout, test) << endl;
    test.add(3, 4);
    print_all(cout, test) << endl;
    test.add(1, 5);
    print_all(cout, test) << endl;
    cout << "expected: 13: " << test.range_query(1, 3) << endl;
    cout << "expected: 9: " << test.range_query(1, 2) << endl;
    cout << "expected: 0: " << test.range_query(5, 7) << endl;
    cout << "expected: 4: " << test.range_query(3, 3) << endl;
    test.add(1, 8);
    print_all(cout, test) << endl;
    cout << "expected: 21: " << test.range_query(1, 3) << endl;
    test.range_add(1, 3, 2);
    print_all(cout, test) << endl;
    cout << "expected: 27: " << test.range_query(1, 3) << endl;
    print_all(cout, test) << endl;
    cout << "expected: 15: " << test.range_query(1, 1) << endl;
    print_all(cout, test) << endl;
  }
  {
    LazySegmentTree<int, LazySegmentTypeMax<int>> test(8);
    cout << "dbg" << endl;
    print_all(cout, test) << endl;
    test.add(2, 4);
    print_all(cout, test) << endl;
    test.add(3, 4);
    print_all(cout, test) << endl;
    test.add(1, 5);
    print_all(cout, test) << endl;
    cout << "expected: 5: " << test.range_query(1, 3) << endl;
    cout << "expected: 5: " << test.range_query(1, 2) << endl;
    cout << "expected: 0: " << test.range_query(5, 7) << endl;
    cout << "expected: 4: " << test.range_query(3, 3) << endl;
    test.add(1, 8);
    print_all(cout, test) << endl;
    cout << "expected: 13: " << test.range_query(1, 3) << endl;
    test.range_add(1, 3, 5);
    print_all(cout, test) << endl;
    cout << "expected: 18: " << test.range_query(1, 3) << endl;
  }
  {
    LazySegmentTree<int, LazySegmentTypeMin<int>> test(8);
    cout << "dbg" << endl;
    print_all(cout, test) << endl;
    test.add(2, 4);
    print_all(cout, test) << endl;
    test.add(3, 4);
    print_all(cout, test) << endl;
    test.add(1, 5);
    print_all(cout, test) << endl;
    cout << "expected: 4: " << test.range_query(1, 3) << endl;
    cout << "expected: 4: " << test.range_query(1, 2) << endl;
    cout << "expected: 0: " << test.range_query(5, 7) << endl;
    cout << "expected: 4: " << test.range_query(3, 3) << endl;
    test.add(1, 8);
    print_all(cout, test) << endl;
    cout << "expected: 4: " << test.range_query(1, 3) << endl;
  }
  return 0;
}
