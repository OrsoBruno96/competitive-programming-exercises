

#ifndef __SEGMENT_TREE_H__
#define __SEGMENT_TREE_H__
#include <vector>
#include <utility>
#include <type_traits>


template<typename T> class SegmentType {
 public:
  static T base();
  static T combine(const T& left, const T& right);
};


template<typename T> class SegmentTypeAdd : public SegmentType<T> {
 public:
  static T base() { return 0; }
  static T combine(const T& left, const T& right) { return left + right; }
};

template<typename T> class SegmentTypeMax : public SegmentType<T> {
 public:
  static T base() { return INT_MIN; }
  static T combine(const T& left, const T& right) {
    return std::max(left, right);
  }
};

template<typename T> class SegmentTypeMin : public SegmentType<T> {
 public:
  static T base() { return INT_MAX; }
  static T combine(const T& left, const T& right) {
    return std::min(left, right);
  }
};


template<typename T, class TT>
class SegmentTree {
 public:
  explicit SegmentTree(int size);

  typename std::enable_if<std::is_base_of<SegmentType<T>, TT>::value, void>::type
  add(int pos, const T& value);

  virtual typename std::enable_if<std::is_base_of<SegmentType<T>, TT>::value, T>::type
  range_query(int pos1, int pos2);

  template<typename U, typename V> friend
  std::ostream& print_all(std::ostream& os, const SegmentTree<U, V>& st);

  int get_tree_size() const { return tree_size_; }

 protected:
  std::pair<int, int> range(int tree_pos_) const;
  virtual T recursive_range_query(int start, int pos1, int pos2);

  int size_;
  int tree_size_;
  std::vector<T> tree_;
};


template<typename T, class TT>
std::ostream& print_all(std::ostream& os, const SegmentTree<T, TT>& st) {
  for (const auto it: st.tree_) {
    os << it << "\t";
  }
  return os;
}

inline int MSB(int a) {
  int counter = -1;
  while (a) {
    a >>= 1;
    counter++;
  }
  return 1 << counter;
}

template<typename T, class TT>
std::pair<int, int> SegmentTree<T, TT>::range(int tree_pos_) const {
  const auto msb = MSB(tree_pos_);
  const auto size = tree_size_/msb/2;
  // std::cout << "tree pos: " << tree_pos_ << " msb " << msb <<
  //   " size: " << size << std::endl;
  const auto start = (size == 0) ? tree_pos_ - msb + 1 :
    (tree_pos_ - msb)*size + 1;
  const auto end = (size == 0) ? start : (tree_pos_ - msb + 1)*size;
  return std::pair<int, int>(start, end);
}


template<typename T, class TT>
SegmentTree<T, TT>::SegmentTree(int size) :
  size_(size), tree_size_(2*MSB(size)), tree_(tree_size_) {}


template<typename T, class TT>
typename std::enable_if<std::is_base_of<SegmentType<T>, TT>::value, void>::type
SegmentTree<T, TT>::add(int pos, const T& value) {
  pos += (tree_size_ / 2) - 1;
  tree_[pos] += value;
  pos /= 2;
  do {
    int p1, p2;
    p1 = pos*2;
    p2 = p1 + 1;
    // std::cout << "update pos: " << p1 << " with: " << p2 << std::endl;
    tree_[pos] = TT::combine(tree_[p1], tree_[p2]);
    pos /= 2;
  } while (pos > 0);
}


template<typename T, class TT>
T SegmentTree<T, TT>::recursive_range_query(int start, int pos1, int pos2) {
  if (start > tree_size_) {
    return TT::base();
  }

  const auto attuale = range(start);
  // std::cout << "debug range: (" << attuale.first << ", " <<
  //   attuale.second << ")" << std::endl;
  if (attuale.first >= pos1 && attuale.second <= pos2) {
    return tree_[start];
  }
  if (attuale.first > pos1 && attuale.second < pos2) {
    return TT::base();
  }
  return TT::combine(recursive_range_query(start*2, pos1, pos2),
                    recursive_range_query(start*2 + 1, pos1, pos2));
}

template<typename T, class TT>
typename std::enable_if<std::is_base_of<SegmentType<T>, TT>::value, T>::type
SegmentTree<T, TT>::range_query(int pos1, int pos2) {
  return recursive_range_query(1, pos1, pos2);
}


#endif  // __SEGMENT_TREE_H__
