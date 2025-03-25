#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution { // https://leetcode.com/problems/binary-tree-right-side-view/submissions/1585965428
private:
	void dfs(TreeNode *root, vector<int> &res, int depth) {
		if (res.size() <= depth)
			res.resize(depth + 1, 0);

		res[depth] = root->val;

		if (root->left)
			dfs(root->left, res, depth + 1);
		if (root->right)
			dfs(root->right, res, depth + 1);
	}

public:
	vector<int> rightSideView(TreeNode* root) {
		if (!root)
			return {};

		vector<int> res;
		dfs(root, res, 0);
		return res;
	}
};

int main(void) {
	return 0;
}
