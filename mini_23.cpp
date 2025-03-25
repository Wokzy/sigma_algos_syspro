
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class SolutionSimple { // https://leetcode.com/problems/balance-a-binary-search-tree/submissions/1586031805
public:

	void bfs(TreeNode* root, vector<TreeNode*> &res) {
		if (!root)
			return;

		bfs(root->left, res);
		res.push_back(root);
		bfs(root->right, res);
	}

	TreeNode *build(vector<TreeNode*> arr, int l, int r) {
		if (l == r)
			return nullptr;

		int mid = (l + r) >> 1;

		TreeNode *node = arr[mid];
		node->left = build(arr, l, mid);
		node->right = build(arr, mid + 1, r);

		return node;
	}

	TreeNode* balanceBST(TreeNode* root) {
		if (!root)
			return nullptr;

		vector<TreeNode*> values;
		bfs(root, values);

		return build(values, 0, values.size());
	}
};

// DSW
class Solution { // https://leetcode.com/problems/balance-a-binary-search-tree/submissions/1586068202
public:

	int flatten(TreeNode *root) {
		TreeNode *cur = root->right;
		int counter = 0;

		while (cur != nullptr) {
			if (cur->left != nullptr) {
				auto prev = cur;
				cur = cur->left;
				prev->left = cur->right;
				cur->right = prev;
				root->right = cur;
			}
			else {
				counter++;
				root = cur;
				cur = cur->right;
			}
		}

		return counter;
	}

	void compress(TreeNode *root, int m) {
		auto cur = root->right;
		while (m-- > 0) {
			auto prev = cur;
			cur = cur->right;
			root->right = cur;
			prev->right = cur->left;
			cur->left = prev;
			root = cur;
			cur = cur->right;
		}
	}

	TreeNode* balanceBST(TreeNode *root) {
		TreeNode *root2 = new TreeNode(0, nullptr, root);

		int counter = flatten(root2);
		int m = (1 << (int)log2(counter + 1)) - 1;

		compress(root2, counter - m);
		for (m >>= 1; m > 0; m >>= 1)
			compress(root2, m);

		return root2->right;
	}
};

int main(void) {
	return 0;
}
