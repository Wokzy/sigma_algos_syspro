#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution { // https://leetcode.com/problems/validate-binary-search-tree/submissions/1586004849
private:
	bool dfs(TreeNode* root, long long left, long long right) {
		if (!root)
			return true;

		if (root->val >= right)
			return false;
		if (root->val <= left)
			return false;

		return dfs(root->left, left, root->val) && dfs(root->right, root->val, right);
	}

public:
	bool isValidBST(TreeNode* root) {
		long long a = -1000000000;
		long long b = 1000000000;
		a *= 3;
		b *= 3;

		return dfs(root, a, b);
	}
};

signed main(void) {
	TreeNode *root = new TreeNode(5);
	root->left = new TreeNode(4);
	root->right = new TreeNode(6);
	root->right->left = new TreeNode(3);
	root->right->right = new TreeNode(7);

	// TreeNode *root = new TreeNode(2);
	// root->left = new TreeNode(1);
	// root->right = new TreeNode(3);
	Solution sol;
	cout << sol.isValidBST(root) << endl;
	return 0;
}
