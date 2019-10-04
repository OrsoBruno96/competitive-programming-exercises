
#include <bits/stdc++.h>
using namespace std;
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct Node {
    int data;
    Node* right;
    Node* left;

    Node(int x){
        data = x;
        right = NULL;
        left = NULL;
    }
};
/* Returns true if the given tree is a binary search tree
 (efficient version). */
bool isBST(struct Node* node);
int isBSTUtil(struct Node* node, int min, int max);
/* Driver program to test size function*/
int main()
{
  int t;
  struct Node *child;
  scanf("%d ", &t);
  while (t--)
  {
     map<int, Node*> m;
     int n;
     scanf("%d ",&n);
     struct Node *root = NULL;
     while (n--)
     {
        Node *parent;
        char lr;
        int n1, n2;
        scanf("%d %d %c", &n1, &n2, &lr);
      //  cout << n1 << " " << n2 << " " << (char)lr << endl;
        if (m.find(n1) == m.end())
        {
           parent = new Node(n1);
           m[n1] = parent;
           if (root == NULL)
             root = parent;
        }
        else
           parent = m[n1];
        child = new Node(n2);
        if (lr == 'L')
          parent->left = child;
        else
          parent->right = child;
        m[n2]  = child;
     }
     cout << isBST(root) << endl;
  }
  return 0;
}


/*This is a function problem.You only need to complete the function given below*/
/* A binary tree node has data, pointer to left child
   and a pointer to right child
struct Node {
    int data;
    Node* right;
    Node* left;

    Node(int x){
        data = x;
        right = NULL;
        left = NULL;
    }
}; */


// The main point of this problem is noting that it is not sufficient
// to test recursively if our tree is balanced, because it may happen that
// the left subtree of a node contains a bigger value, but nested a lot
// in the left.
// To solve this problem we have to keep track of the minimum and maximum
// value in each subtree and get this value back to the top.

using pii = pair<int, int>;
using pbi = pair<bool, pii>; // isBst, min, max

pbi check_recurse(Node* node) {
    pbi left, right;
    // left
    if (!node->left) {
        left = pbi(true, pii(node->data, node->data));
    } else {
        left = check_recurse(node->left);
    }
    // no matter what we have for minimum and maximum, the result
    // will be false no matter what.
    if (!left.first) return pbi(false, pii(0, 0));
    // right
    if (!node->right) {
        right = pbi(true, pii(node->data, node->data));
    } else {
        right = check_recurse(node->right);
    }
    if (!right.first) return pbi(false, pii(0, 0));
    // combine
    if (left.second.second > node->data) { return pbi(false, pii(0, 0)); }
    if (right.second.first < node->data) { return pbi(false, pii(0, 0)); }
    int min = std::min(left.second.first, right.second.first);
    int max = std::max(left.second.second, right.second.second);
    return pbi(true, pii(min, max));
}


bool isBST(Node* root) {
  if (!root) { return true; }
  auto appo = check_recurse(root);
  return appo.first;
}
