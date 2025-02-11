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

class SolutionFenwick {
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


class SolutionSimple { // TLE
public:
	bool isIdealPermutation(vector<int>& nums) {
		int n = nums.size();
		int locals = 0;
		int globals = 0;

		for (int i = 1; i < n; i++) {
			if (nums[i - 1] > nums[i])
				locals++;
			for (int j = i - 1; j >= 0; j--)
				if (nums[j] > nums[i])
					globals++;
		}
		return globals == locals;
	}
};


class SolutionMerge {
	public:
	int merge_count(vector<int>& nums) {
		if (nums.size() == 1)
			return 0;
		if (nums.size() == 2) {
			if (nums[0] > nums[1]) {
				swap(nums[0], nums[1]);
				return 1;
			}
			return 0;
		}

		vector<int> left, right;

		for (int i = 0; i < nums.size(); i++) {
			if (i < (nums.size() >> 1))
				left.push_back(nums[i]);
			else
				right.push_back(nums[i]);
		}

		int p1 = 0;
		int p2 = 0;
		int res = merge_count(left) + merge_count(right);

		while ((p1 < left.size()) && (p2 < right.size())) {
			if (left[p1] < right[p2]) {
				nums[p1 + p2] = left[p1];
				p1++;
			} else {
				res += left.size() - p1;
				nums[p1 + p2] = right[p2];
				p2++;
			}
		}

		while (p1 < left.size()) {
			nums[p1 + p2] = left[p1];
			p1++;
		}

		while (p2 < right.size()) {
			nums[p1 + p2] = right[p2];
			p2++;
		}

		return res;
	}
	bool isIdealPermutation(vector<int>& nums) {
		int n = nums.size();
		int locals = 0;
		int globals = 0;

		for (int i = 1; i < n; i++) {
			if (nums[i - 1] > nums[i])
				locals++;
		}
		return merge_count(nums) == locals;
	}
};


signed main(void) {
	vector<int> data = {1,0,2};
	SolutionMerge sol;

	cout << sol.isIdealPermutation(data) << '\n';
	return 0;
}
