

#ifndef __LAZY_SEGMENT_TREE_H__
#define __LAZY_SEGMENT_TREE_H__
#include <vector>
#include <utility>
#include <type_traits>

#include "SegmentTree.h"

// Forward decl
template<typename T, class TT>
class LazySegmentTree;

template<typename T> class LazySegmentType : public SegmentType<T> {
 public:
  static T elaborate_lazy_children(T val);
  static T value_to_add(int start, const T& value,
                        const LazySegmentTree<T, LazySegmentType<T>>* seg);
  static T combine_lazy(const T& prec, const T& update);
};

template<typename T> class LazySegmentTypeAdd : public LazySegmentType<T>,
                                                public SegmentTypeAdd<T> {
 public:
  static T base() { return SegmentTypeAdd<T>::base(); }
  static T combine(const T& left, const T& right) {
    return SegmentTypeAdd<T>::combine(left, right);
  }
  static T elaborate_lazy_children(T val) { return val/2; }
  static T value_to_add(int start, const T& value,
                        const LazySegmentTree<T, LazySegmentTypeAdd<T>>* seg) {
    const auto msb = MSB(start);
    const auto size = seg->get_tree_size()/msb/2;
    return (size == 0) ? value : value*size;
  }
  static T combine_lazy(const T& prec, const T& update) {
    return prec + update;
  }
};

template<typename T> class LazySegmentTypeMin : public LazySegmentType<T>,
                                                public SegmentTypeMin<T> {
 public:
  static T base() { return SegmentTypeMin<T>::base(); }
  static T combine(const T& left, const T& right) {
    return SegmentTypeMin<T>::combine(left, right);
  }
  static T elaborate_lazy_children(T val) { return val; }
  static T value_to_add(int start, const T& value,
                        const LazySegmentTree<T, LazySegmentTypeMin<T>>* seg) {
    return value;
  }
  static T combine_lazy(const T& prec, const T& update) {
    const auto new_value = prec + update;
    return combine(new_value, prec);
  }
};

template<typename T> class LazySegmentTypeMax : public LazySegmentType<T>,
                                                public SegmentTypeMax<T> {
 public:
  static T base() { return SegmentTypeMax<T>::base(); }
  static T combine(const T& left, const T& right) {
    return SegmentTypeMax<T>::combine(left, right);
  }
  static T elaborate_lazy_children(T val) { return val; }
  static T value_to_add(int start, const T& value,
                        const LazySegmentTree<T, LazySegmentTypeMax<T>>* seg) {
    return value;
  }
  static T combine_lazy(const T& prec, const T& update) {
    const auto new_value = prec + update;
    return combine(new_value, prec);
  }
};




template<typename T, class TT>
class LazySegmentTree : public SegmentTree<T, TT> {
 public:
  explicit LazySegmentTree(int size);

  typename std::enable_if<std::is_base_of<LazySegmentType<T>, TT>::value, void>::type
  range_add(int pos1, int pos2, const T& value);

  typename std::enable_if<std::is_base_of<LazySegmentType<T>, TT>::value, T>::type
  range_query(int pos1, int pos2) override;

  template<typename U, typename V> friend
  std::ostream& print_all(std::ostream& os, const LazySegmentTree<U, V>& st);

 private:
  T recursive_range_query(int start, int pos1, int pos2) override;
  void recursive_range_add(int start, int pos1, int pos2, const T& value);
  void apply_to_children(int start);

  std::vector<T> lazy_tree_;
};


template<typename T, class TT>
LazySegmentTree<T, TT>::LazySegmentTree(int size) :
  SegmentTree<T, TT>(size) {
  lazy_tree_ = std::vector<T>(this->tree_.size());
}

template<typename T, class TT>
typename std::enable_if<std::is_base_of<LazySegmentType<T>, TT>::value, void>::type
LazySegmentTree<T, TT>::range_add(int pos1, int pos2, const T& value) {
  recursive_range_add(1, pos1, pos2, value);
}

template<typename T, class TT>
void LazySegmentTree<T, TT>::apply_to_children(int start) {
  std::cout << "start: " << start << std::endl;
  if (start > this->tree_size_) {
    return;
  }
  if (lazy_tree_[start]) {
    const auto appo = lazy_tree_[start];
    if ((start*2 + 1) < this->tree_size_) {
      lazy_tree_[start*2] = TT::elaborate_lazy_children(appo);
      lazy_tree_[start*2 + 1] = TT::elaborate_lazy_children(appo);
    }
    this->tree_[start] = this->tree_[start] + appo;
    lazy_tree_[start] = 0;

    auto parent = start/2;
    while (parent) {
      const auto other = (start % 2) ? start - 1 : start + 1;
      this->tree_[parent] = TT::combine(this->tree_[start], this->tree_[other]);
      parent /= 2;
    }
  }
}

template<typename T, class TT>
void LazySegmentTree<T, TT>::recursive_range_add(int start, int pos1, int pos2, const T& value) {
  if (start > this->tree_size_) {
    return;
  }
  apply_to_children(start);
  const auto attuale = this->range(start);
  if (attuale.first >= pos1 && attuale.second <= pos2) {
    const auto value_to_add = TT::value_to_add(start, value, this);
    lazy_tree_[start] = value_to_add;
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
typename std::enable_if<std::is_base_of<LazySegmentType<T>, TT>::value, T>::type
LazySegmentTree<T, TT>::range_query(int pos1, int pos2) {
  return recursive_range_query(1, pos1, pos2);
}

template<typename T, class TT>
T LazySegmentTree<T, TT>::recursive_range_query(int start, int pos1, int pos2) {
  if (start > this->tree_size_) {
    return TT::base();
  }
  apply_to_children(start);
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
