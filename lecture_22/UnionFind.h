


#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__


#include <vector>



class UnionFind {
 public:
  UnionFind(unsigned int N) {
    _connected_components = N;
    _parent.assign(N, 0);
    _rank.assign(N, 0);
    for (unsigned int i = 0; i < N; i++) {
      _parent[i] = i;
    }
  }
  bool is_same_set(unsigned int i, unsigned int j) const {
    return repr(i) == repr(j);
  }
  unsigned int repr(unsigned int i) const {
    return (_parent[i] == i) ? i : repr(_parent[i]);
  }

  void insert_link(unsigned int i, unsigned int j) {
    if (!is_same_set(i, j)) {
      _connected_components--;
      unsigned int x = repr(i), y = repr(j);
      if (_rank[x] > _rank[y]) {
        _parent[y] = x;
      } else {
        _parent[x] = y;
        if (_rank[x] == _rank[y]) {
          _rank[y]++;
        }
      }
    }
  }

  int connected_components() const { return _connected_components; }


 private:
  std::vector<unsigned int> _parent;
  std::vector<unsigned int> _rank;
  int _connected_components;
};




#endif  // __UNION_FIND_H__
