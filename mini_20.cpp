#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Codec { // https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/1585958284
private:
	void serialize(TreeNode* root, string& res, bool initial) {
		if (!initial)
			res += "|";
		if (root) {
			res += to_string(root->val);
			serialize(root->left, res, false);
			serialize(root->right, res, false);
		} else {
			res += "-";
		}
	}

	TreeNode *deserialize(string boo, int &index) {
		string cur = "";
		while (index < boo.size() && boo[index] != '|') {
			cur += boo[index];
			index++;
		}

		index++;
		if (cur == "-")
			return nullptr;

		TreeNode *res = new TreeNode(stoi(cur));
		res->left = deserialize(boo, index);
		res->right = deserialize(boo, index);
		return res;
	}

public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (root == nullptr)
			return "";

		string res;
		serialize(root, res, true);
		return res;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.size() == 0)
			return nullptr;

		int index = 0;
		return deserialize(data, index);
	}
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main(void) {
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->right->left = new TreeNode(4);
	root->right->right = new TreeNode(5);

	Codec sol;

	cout << sol.serialize(root) << endl;
	return 0;
}
