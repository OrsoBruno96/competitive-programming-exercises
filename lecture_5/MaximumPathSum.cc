
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int data;
	struct Node *left;
	struct Node *right;

	Node(int x){
	    data = x;
	    left = NULL;
	    right = NULL;
	}
};
int maxPathSum(struct Node *root);
void insert(Node *root, int a1,int a2, char lr){
	if(root==NULL)
		return ;
	if(root->data==a1){
		switch(lr){
			case 'L':root->left=new Node(a2);
					break;
			case 'R':root->right=new Node(a2);
					break;
		}
	}
	insert(root->left,a1,a2,lr);
	insert(root->right,a1,a2,lr);
}
void inorder(Node *root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right)
;}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		Node *root=NULL;
		while(n--){
			int a1,a2;
			char lr;
			cin>>a1>>a2>>lr;
			if(root==NULL){
				root=new Node(a1);
				switch(lr){
					case 'L':root->left=new Node(a2);
							break;
					case 'R':root->right=new Node(a2);
							break;
				}
			}
			else
				insert(root,a1,a2,lr);
		}
		//inorder(root);
		//cout<<endl;
		cout<<maxPathSum(root)<<endl;
	}
}

/*This is a function problem.You only need to complete the function given below*/
/*Complete the function below
Node is as follows
struct Node{
	int data;
	Node *left, *right;
};
*/

constexpr int INF = INT_MIN;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int max_path_sum = INF;

// I keep 3 values for each node: the data itself and the maximum
// path sum I can get from the left subtree and right subtree respectively.
// Then I have a global variable that stores the maximum path sum from leaf
// to leaf, obtained by summing for each node of triples the maximum left,
// maximum right and the value itself.

// Global complexity is linear because I visit each node once and every
// operation done is in constant time.

ppii recursiveMaxSum(Node* node) {
  if (!node) {
    return ppii(INF, pii(INF, INF));
  }
  if (!node->left && !node->right) {
    // cout << "terna: (" << node->data << ", " << INF << ", " << INF << ")\n";
    return ppii(node->data, pii(INF, INF));
  }
  int left = INF, right = INF;
  if (node->left) {
    const auto appo = recursiveMaxSum(node->left);
    left = std::max(appo.second.first, appo.second.second);
    left = (left == INF) ? appo.first : appo.first + left;
  }
  if (node->right) {
    const auto appo = recursiveMaxSum(node->right);
    right = std::max(appo.second.first, appo.second.second);
    right = (right == INF) ? appo.first : appo.first + right;
  }
  // cout << "terna: (" << node->data << ", " << left << ", " << right << ")\n";
  if (left != INF && right != INF) {
    max_path_sum = std::max(max_path_sum, node->data + left + right);
  }
  return ppii(node->data, pii(left, right));
}

int maxPathSum(struct Node *root) {
  max_path_sum = INF;
  recursiveMaxSum(root);
  return max_path_sum;
}
