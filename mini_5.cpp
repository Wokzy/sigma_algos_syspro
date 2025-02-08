#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	void wiggleSort(vector<int>& nums) {
		sort(nums.begin(), nums.end());

		vector<int> res(nums.size(), 0);
		for (int i = 0; i < nums.size(); i++) {
			if (i & 1)
				res[i] = nums[nums.size() - (i >> 1) - 1];
			else
				res[i] = nums[(nums.size() >> 1) - (i >> 1) - ((nums.size() & 1) == 0)];
		}
		nums = res;
	}
};

int main() {
	vector<int> a = {1,5,1,1,6,4};
	Solution sol;
	sol.wiggleSort(a);

	for (auto &i : a)
		cout << i << ' ';
	cout << '\n';
}
