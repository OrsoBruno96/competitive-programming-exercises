
#include <bits/stdc++.h>
using namespace std;



// The idea is to modify the merge sort algorithm
// including some subroutine that counts the number of inversions.
// It is well known that the complexity of merge sort is \theta(n log n).
// Adding a constant time calculation for each update will lead to
// the same time complexity for the solution of this problem.


// The number of inversion can be calculated in the merge phase of the
// algorithm. When I have to put an element of the right part of the merge
// in the left part, I will have to do a number of swaps that is equal
// to the number of elements that follow the left item in the left vector.

// Time complexity: O(n log n)
// Space complexity: O(n)

using ll = long long;

ll merge(vector<int>& arr, int left,
          int mid, int right) {
  int i = left, j = mid + 1, k = 0;
  ll inv_count = 0;
  vector<int> temp((right - left) + 1, 0);


  while ((i <= mid) && (j <= right)) {
    if (arr[i] < arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
      inv_count += (mid - i + 1);
    }
  }
  while (i <= mid) {
    temp[k++] = arr[i++];
  }
  while (j <= right) {
    temp[k++] = arr[j++];
  }

  std::copy(temp.begin(), temp.end(), arr.begin() + left);
  return inv_count;
}



ll _mergeSort(vector<int>& arr, int left, int right)  {
  ll mid, inv_count = 0;
  if (right > left) {
    mid = (right + left) / 2;
    inv_count += _mergeSort(arr, left, mid);
    inv_count += _mergeSort(arr, mid + 1, right);
    inv_count += merge(arr, left, mid, right);
  }
  return inv_count;
}



int main(int argc, char* argv[]) {
  int TC = 0;
  cin >> TC;
  while (TC--) {
    int N = 0;
    cin >> N;
    vector<int> arr;
    arr.reserve(N);
    for (int i = 0; i < N; i++) {
      int appo;
      cin >> appo;
      arr.push_back(appo);
    }
    auto res = _mergeSort(arr, 0, N - 1);
    cout << res << "\n";
  }
  return 0;
}
