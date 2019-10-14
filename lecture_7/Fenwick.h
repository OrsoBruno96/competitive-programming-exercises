

#ifndef __FENWICK_TREE_H
#define __FENWICK_TREE_H

#include <vector>
#include <stdexcept>


template<typename I> class Fenwick {
 public:
  explicit Fenwick(const int size);
  void add(int pos, const I& val);
  I sum(int pos) const;

  I operator[](const int pos);
  void check_bound(const int pos) const;

  I get(const int pos) const { return tree_[pos]; }

 private:
  I size_;
  std::vector<I> tree_;
};


template<typename I> Fenwick<I>::Fenwick(const int size) :
  size_(size), tree_(size, 0) {}


template<typename I> void Fenwick<I>::check_bound(const int pos) const {
  if (pos < 0 || pos >= size_) {
    throw std::out_of_range("Accessing position " + std::to_string(pos) +
                            " is out of bound in a "
                            "Fenwick of size " + std::to_string(size_));
  }
}

template<typename I> I Fenwick<I>::sum(int pos) const {
  I ret = 0;
  pos += 1;
  while (pos) {
    ret += tree_[pos - 1];
    pos -= pos & (-pos);
  }
  return ret;
}


template<typename I> void Fenwick<I>::add(int pos, const I& val) {
  check_bound(pos);
  pos += 1;
  while (pos <= size_) {
    tree_[pos - 1] += val;
    pos += pos & (-pos);
  }
}


template<typename I> I Fenwick<I>::operator[](int pos) {
  if (pos == 0) {
    return sum(pos);
  } else {
    return sum(pos) - sum(pos - 1);
  }
}


#endif  // __FENWICK_TREE_H
