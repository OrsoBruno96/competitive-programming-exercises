

#include <bits/stdc++.h>
#include "SegmentTree.h"

using namespace std;


int main() {
  {
    SegmentTree<int, SegmentTypeAdd<int>> test(8);
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
    cout << "expected: 21: " << test.range_query(1, 3) << endl;
  }
  {
    SegmentTree<int, SegmentTypeMax<int>> test(8);
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
  }
  {
    SegmentTree<int, SegmentTypeMin<int>> test(8);
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
