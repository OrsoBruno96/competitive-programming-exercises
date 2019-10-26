

#ifndef __SEGMENT_TREE_H__
#define __SEGMENT_TREE_H__
#include <vector>
#include <utility>


template<typename T> class SegmentTree {
 public:
  SegmentTree(int size);
  void add(int pos, const T& value);
  T range_query(int pos1, int pos2) const;

  template<typename U>
  friend std::ostream& print_all(std::ostream& os, const SegmentTree<U>& st);

 private:
  std::pair<int, int> range(int tree_pos_) const;
  T recursive_range_query(int start, int pos1, int pos2) const;

  int size_;
  int tree_size_;
  std::vector<T> tree_;

};


template<typename T>
std::ostream& print_all(std::ostream& os, const SegmentTree<T>& st) {
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

template<typename T>
std::pair<int, int> SegmentTree<T>::range(int tree_pos_) const {
  const auto msb = MSB(tree_pos_);
  const auto size = tree_size_/msb/2;
  // std::cout << "tree pos: " << tree_pos_ << " msb " << msb <<
  //   " size: " << size << std::endl;
  const auto start = (size == 0) ? tree_pos_ - msb + 1 :
    (tree_pos_ - msb)*size + 1;
  const auto end = (size == 0) ? start : (tree_pos_ - msb + 1)*size;
  return std::pair<int, int>(start, end);
}


template<typename T> SegmentTree<T>::SegmentTree(int size) :
   size_(size), tree_size_(2*MSB(size)), tree_(size + tree_size_) {}



template<typename T> void SegmentTree<T>::add(int pos, const T& value) {
  pos += (tree_size_ / 2) - 1;
  do {
    // std::cout << "update pos: " << pos << std::endl;
    tree_[pos] += value;
    pos /= 2;
  } while (pos > 0);
}


template<typename T>
T SegmentTree<T>::recursive_range_query(int start, int pos1, int pos2) const {
  if (start > tree_size_) {
    return 0;
  }

  const auto attuale = range(start);
  // std::cout << "debug range: (" << attuale.first << ", " <<
  //   attuale.second << ")" << std::endl;
  if (attuale.first >= pos1 && attuale.second <= pos2) {
    return tree_[start];
  }
  if (attuale.first > pos1 && attuale.second < pos2) {
    return 0;
  }
  return recursive_range_query(start*2, pos1, pos2) +
    recursive_range_query(start*2 + 1, pos1, pos2);
}

template<typename T> T SegmentTree<T>::range_query(int pos1, int pos2) const {
  return recursive_range_query(1, pos1, pos2);
}


#endif  // __SEGMENT_TREE_H__
