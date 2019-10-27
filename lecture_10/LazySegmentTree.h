

#ifndef __LAZY_SEGMENT_TREE_H__
#define __LAZY_SEGMENT_TREE_H__
#include <vector>
#include <utility>
#include <type_traits>

#include "SegmentTree.h"


template<typename T, class TT>
class LazySegmentTree : public SegmentTree<T, TT> {
 public:
  explicit LazySegmentTree(int size);

  typename std::enable_if<std::is_base_of<SegmentType<T>, TT>::value, void>::type
  range_add(int pos1, int pos2, const T& value);

  typename std::enable_if<std::is_base_of<SegmentType<T>, TT>::value, T>::type
  range_query(int pos1, int pos2) override;

  template<typename U, typename V> friend
  std::ostream& print_all(std::ostream& os, const LazySegmentTree<U, V>& st);

 private:
  T recursive_range_query(int start, int pos1, int pos2) override;
  void recursive_range_add(int start, int pos1, int pos2, const T& value);

  std::vector<T> lazy_tree_;
};


template<typename T, class TT>
LazySegmentTree<T, TT>::LazySegmentTree(int size) :
  SegmentTree<T, TT>(size) {
  lazy_tree_ = std::vector<T>(this->tree_.size());
}

template<typename T, class TT>
typename std::enable_if<std::is_base_of<SegmentType<T>, TT>::value, void>::type
LazySegmentTree<T, TT>::range_add(int pos1, int pos2, const T& value) {
  recursive_range_add(1, pos1, pos2, value);
}

template<typename T, class TT>
void LazySegmentTree<T, TT>::recursive_range_add(int start, int pos1, int pos2, const T& value) {
  if (start > this->tree_size_) {
    return;
  }
  if (lazy_tree_[start]) {
    const auto appo = lazy_tree_[start];
    if ((start*2 + 1) < this->tree_size_) {
      lazy_tree_[start*2] = appo/2;
      lazy_tree_[start*2 + 1] = appo/2;
    }
    this->tree_[start] += appo;
    lazy_tree_[start] = 0;
  }
  const auto attuale = this->range(start);
  if (attuale.first >= pos1 && attuale.second <= pos2) {
    const auto msb = MSB(start);
    const auto size = this->tree_size_/msb/2;
    lazy_tree_[start] = (size == 0) ? value : value*size;
    return;
  }
  if (attuale.first > pos1 && attuale.second < pos2) {
    return;
  }
  recursive_range_add(start*2, pos1, pos2, value);
  recursive_range_add(start*2 + 1, pos1, pos2, value);
  return;
}

template<typename T, class TT>
typename std::enable_if<std::is_base_of<SegmentType<T>, TT>::value, T>::type
LazySegmentTree<T, TT>::range_query(int pos1, int pos2) {
  return recursive_range_query(1, pos1, pos2);
}

template<typename T, class TT>
T LazySegmentTree<T, TT>::recursive_range_query(int start, int pos1, int pos2) {
  if (start > this->tree_size_) {
    return TT::base();
  }
  if (lazy_tree_[start]) {
    const auto appo = lazy_tree_[start];
    if ((start*2 + 1) < this->tree_size_) {
      lazy_tree_[start*2] = appo/2;
      lazy_tree_[start*2 + 1] = appo/2;
    }
    this->tree_[start] += appo;
    lazy_tree_[start] = 0;
  }
  const auto attuale = this->range(start);
  // std::cout << "debug range: (" << attuale.first << ", " <<
  //   attuale.second << ")" << std::endl;
  if (attuale.first >= pos1 && attuale.second <= pos2) {
    return this->tree_[start];
  }
  if (attuale.first > pos1 && attuale.second < pos2) {
    return TT::base();
  }
  return TT::combine(recursive_range_query(start*2, pos1, pos2),
                    recursive_range_query(start*2 + 1, pos1, pos2));
}


template<typename T, class TT>
std::ostream& print_all(std::ostream& os, const LazySegmentTree<T, TT>& st) {
  os << "normal tree: " << std::endl;
  for (const auto it: st.tree_) {
    os << it << "\t";
  }
  os << std::endl << "lazy tree: " << std::endl;
  for (const auto it: st.lazy_tree_) {
    os << it << "\t";
  }
  return os;
}


#endif  // __LAZY_SEGMENT_TREE_H__
