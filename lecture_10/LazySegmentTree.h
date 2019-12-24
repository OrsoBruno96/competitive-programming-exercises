

#ifndef __LAZY_SEGMENT_TREE_H__
#define __LAZY_SEGMENT_TREE_H__


#include <vector>


template<typename T>
class LazySegmentTree {
 public:
  // Build the segment tree given 0-indexed initial
  LazySegmentTree(const std::vector<T>& initial) {
    _size = initial.size();
    _segment_tree.assign(initial.size() * 4, 0);
    lazy.assign(initial.size() * 4, 0);
    build(0, 0, _size - 1, initial);
  }


  // Adds value v to all elements in range [i, j]
  T range_add(int i, int j, T v) {
    return recursive_range_add(0, 0, _size - 1, i, j, v);
  }

  // range minimum query in range [i, j]
  T range_query(int i, int j) {
    return recursive_range_query(0, 0, _size - 1, i, j);
  }

 private:
  int _size;  // Size of the original array
  std::vector<T> _segment_tree;  // real segment tree
  std::vector<T> lazy;  // tree for lazy propagation

  // Function for moving between nodes
  int left(int i) {
    return 2*i + 1;
  }

  int right(int i) {
    return 2*i + 2;
  }

  int parent(int i) {
    return (i - 1)/2;
  }

  // propagate the laziness of the node
  void propagate_lazy(int p, int L, int R) {
    if (lazy[p] == 0) return;
    // Update this node
    _segment_tree[p] += lazy[p];

    // Propagate if it isnt a leaf
    if (L != R) {
      lazy[left(p)] += lazy[p];
      lazy[right(p)] += lazy[p];
    }

    // Reset the actual node
    lazy[p] = 0;
  }

  // Build the tree given initial vector
  void build(int p, int L, int R, const std::vector<T>& initial) {
    if (L == R) {  // It is a leaf
      _segment_tree[p] = initial[L];
    } else {
      // Building children
      build(left(p), L, (L + R) / 2,  initial);
      build(right(p), (L + R) / 2 + 1, R,  initial);
      _segment_tree[p] = std::min(_segment_tree[left(p)], _segment_tree[right(p)]);
    }
  }


  // Update the range [i, j] with the associative operation
  T recursive_range_add(int p, int L, int R, int i, int j, T v) {
    propagate_lazy(p, L, R);

    if (i > R || j < L) return _segment_tree[p];  // No intersection
    if (L >= i && R <= j) {  // Contained
      _segment_tree[p] +=  v;
      if (L != R) {  // If it isnt a leaf
        lazy[left(p)] += v;
        lazy[right(p)] += v;
      }
      return _segment_tree[p];
    }

    // Updating this node
    _segment_tree[p] = std::min(recursive_range_add(left(p), L, (L + R)/2, i, j, v),
                 recursive_range_add(right(p), (L + R)/2 + 1, R, i, j, v));

    return _segment_tree[p];
  }

  // Internal query, it has L and R as parametres
  T recursive_range_query(int p, int L, int R, int i, int j) {
    propagate_lazy(p, L, R);

    if (i > R || j < L)  // No intersection
      return LLONG_MAX;
    if (i <= L && R <= j)  // Contained
      return _segment_tree[p];

    return std::min(recursive_range_query(left(p), L, (L + R)/2, i, j),
                recursive_range_query(right(p), (L + R)/2 + 1, R, i, j));
  }

};


#endif  // __LAZY_SEGMENT_TREE_H__
