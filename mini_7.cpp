#include <bits/stdc++.h>

using namespace std;

#define int long long
int sum(vector<int>& t, int r) {
	int res = 0;
	for (; r > 0; r -= r & -r)
		res += t[r];
	return res;
}

void add(vector<int>& t, int k, int x) {
	for (; k <= t.size() - 1; k += k & -k)
		t[k] += x;
}

#undef int

class Solution {
public:
	bool isIdealPermutation(vector<int>& nums) {
		int n = nums.size();
		int locals = 0;
		int globals = 0;

		vector<long long> t(n + 1, 0);
		for (int i = 0; i < n - 1; i++) {
			if (nums[i] > nums[i + 1])
				locals += 1;
			globals += sum(t, n - nums[i]);
			add(t, n - nums[i], 1);
		}
		globals += sum(t, n - nums[n - 1]);
		return globals == locals;
	}
};


signed main(void) {
	vector<int> data = {1,2,0};
	Solution sol;

	cout << sol.isIdealPermutation(data) << '\n';
	return 0;
}
