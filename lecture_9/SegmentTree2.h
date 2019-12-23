

#include <vector>
#include <iostream>




template<typename T>
class SegmentTree {
 public:
  explicit SegmentTree(const int N) : _original_size(N) {
    const int msb = MSB(N);
    _tree_size = (msb == N) ? 2*msb : 4*msb;
    _segment_tree.assign(_tree_size, 0);
  }
  explicit SegmentTree(const std::vector<T>& v);

  T range_query(const int i, const int j) const {
    return recursive_range_query(1, i, j, 0, _original_size - 1);
  }
  void add(const int pos, const T& value) {
    return recursive_add(1, pos, value, 0, _original_size - 1);
  }
  T operator[](int i) const;


  void print_all() {
    for (auto it: _segment_tree) {
      std::cout << it << " ";
    }
    std::cout << std::endl;
  }

 private:
  inline int MSB(int a) {
    int counter = -1;
    while (a) {
      a >>= 1;
      counter++;
    }
    return 1 << counter;
  }

  int left(const int p) const {
    return p << 1;
  }
  int right(const int p) const {
    return (p << 1) + 1;
  }

  T recursive_range_query(const int pos, const int i, const int j,
                            const int L, const int R) const {
    if (i > R || j < L) {
      return 0;
    }
    if (L >= i && R <= j) {
      return _segment_tree[pos];
    }
    T l = recursive_range_query(left(pos), i, j, L, (L + R)/2);
    T r = recursive_range_query(right(pos), i, j, (L + R)/2 + 1, R);
    return l + r;
  }

  void recursive_add(int pos, int range, const T& value, int L, int R) {
    if (L == range && R == range) {
      _segment_tree[pos] += value;
      return;
    }
    int left_extreme = (L + R)/2;
    if (range > left_extreme) {
      recursive_add(right(pos), range, value, (L + R)/2 + 1, R);
    } else {
      recursive_add(left(pos), range, value, L, (L + R)/2);
    }
    _segment_tree[pos] = _segment_tree[right(pos)] + _segment_tree[left(pos)];
  }


  std::vector<T> _segment_tree;
  int _original_size;
  int _tree_size;
};
