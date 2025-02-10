#include <bits/stdc++.h>

using namespace std;

#define int long long

void merge_sort(vector<int>& nums, int l, int r) {
	if (l == r)
		return;
	if (r == l + 1) {
		if (nums[l] > nums[r])
			swap(nums[l], nums[r]);
		return;
	}

	int mid = (l + r) / 2;

	merge_sort(nums, l, mid);
	merge_sort(nums, mid + 1, r);

	int mx = nums[mid];
	if (nums[r] > mx)
		mx = nums[r];
	mx++;

	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r && k <= r) {

		int e1 = nums[i] % mx;
		int e2 = nums[j] % mx;
		if (e1 <= e2) {
			nums[k] += (e1 * mx);
			i++;
			k++;
		}
		else {
			nums[k] += (e2 * mx);
			j++;
			k++;
		}
	}

	while (i <= mid) {
		int el = nums[i] % mx;
		nums[k] += (el * mx);
		i++;
		k++;
	}

	while (j <= r) {
		int el = nums[j] % mx;
		nums[k] += (el * mx);
		j++;
		k++;
	}

	for (int i = l; i <= r; i++)
		nums[i] /= mx;
}

void merge_sort_with_negative(vector<int>& nums) {
	int mn = nums[0];
	for (int &c : nums)
		if (c < mn)
			mn = c;

	for (int &c : nums)
		c -= mn;

	merge_sort(nums, 0, nums.size() - 1);

	for (int &c : nums)
		c += mn;
}

#undef int

class Solution {
public:
	vector<int> sortArray(vector<int>& nums) {
		if (nums.size() == 1)
			return nums;
		vector<long long> temp(nums.size(), 0);
		for (int i = 0; i < nums.size(); i++)
			temp[i] = nums[i];
		merge_sort_with_negative(temp);
		for (int i = 0; i < nums.size(); i++)
			nums[i] = temp[i];
		return nums;
	}
};


signed main(void) {

	vector<long long> nums = {5,1,1,2,0,0};
	merge_sort_with_negative(nums);

	for (auto &c : nums)
		cout << c << ' ';
	cout << '\n';

	return 0;
}
