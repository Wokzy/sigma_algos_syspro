#include <bits/stdc++.h>

using namespace std;

void shell_sort(vector<int>& data) {
	vector<int> seq = {1, 4, 10, 23, 57, 132, 301, 701};

	for (auto& s : views::reverse(seq)) {
		for (int i = s; i < data.size(); i++) {
			for (int j = i - s; j >= 0 && data[j] > data[j + s]; j -= s) {
				int temp = data[j];
				data[j] = data[j + s];
				data[j + s] = temp;
			}
		}
	}
}

class Solution {
public:
	void wiggleSort(vector<int>& nums) {
		shell_sort(nums);

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
