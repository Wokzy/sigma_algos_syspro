#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void print_arr(vector<T> arr) {
	if (arr.size() == 0)
		return;
	cout << arr[0];
	for (int i = 1; i < arr.size(); i++)
		cout << ' ' << arr[i];
	cout << '\n';
}

template<typename T>
void print_arr(vector<T> arr, int l, int r) {
	if (arr.size() == 0)
		return;
	cout << arr[l];
	for (int i = 1; i < r - l; i++)
		cout << ' ' << arr[l + i];
	cout << '\n';
}

void quick_sort_lomuto_simple(vector<int> &arr, int l, int r) {
	if (r - l <= 1)
		return;

	int n = r - l;
	int p = abs(arr[0]) % n; // как мне кажется - достаточно случайный элемент
	swap(arr[l], arr[l + p]);

	int i = -1, k = 0;

	for (int j = 1; j < n; j++) {
		if (arr[l + j] < arr[l + k]) {
			swap(arr[l + i + 1], arr[l + j]);
			swap(arr[l + k + 1], arr[l + j]);
			i++;
			k++;
		} else if (arr[l + j] == arr[l + k]) {
			swap(arr[l + k + 1], arr[l + j]);
			k++;
		}
	}

	quick_sort_lomuto_simple(arr, l, i + l + 1);
	quick_sort_lomuto_simple(arr, k + l + 1, r);
}

void quick_sort_mem(vector<int> &arr) {
	if (arr.size() <= 1)
		return;

	int value = arr[abs(arr[0]) % arr.size()];

	vector<int> less;
	vector<int> equal;
	vector<int> greater;

	for (int &c : arr) {
		if (c < value)
			less.push_back(c);
		else if (c == value)
			equal.push_back(c);
		else
			greater.push_back(c);
	}

	quick_sort_mem(less);
	quick_sort_mem(greater);

	int i = 0;
	for (int &c : less)
		arr[i++] = c;
	for (int &c : equal)
		arr[i++] = c;
	for (int &c : greater)
		arr[i++] = c;
}

int lomuto_partition_advanced(vector<int> &arr, int l, int r) {
	if (r - l < 2)
		return l;

	r--;
	if (arr[l] > arr[r])
		swap(arr[l], arr[r]);

	int pivot_pos = l;
	int pivot = arr[l];

	do {
		l++;
	} while (arr[l] < pivot);

	for (int i = l + 1; i < r; i++) {
		int x = arr[i];
		int smaller = - (int)(x < pivot);
		int delta = smaller & (i - l);
		arr[l + delta] = arr[l];
		arr[i - delta] = x;
		l -= smaller;
	}

	--l;
	arr[pivot_pos] = arr[l];
	arr[l] = pivot;
	return l;
}

void quick_sort_lomuto_advanced(vector<int> &arr, int l, int r) {
	if (r - l < 2)
		return;

	int pivot = lomuto_partition_advanced(arr, l, r);
	quick_sort_lomuto_advanced(arr, l, pivot);
	quick_sort_lomuto_advanced(arr, pivot + 1, r);
}

void quick_sort_hoare(vector<int> &arr, int l, int r) {
	if (r <= l)
		return;

	int v = arr[(l + r) / 2];
	int i = l;
	int j = r;

	while (i <= j) {
		while (arr[i] < v)
			i++;
		while (arr[j] > v)
			j--;
		if (i >= j)
			break;
		swap(arr[i++], arr[j--]);
	}

	quick_sort_hoare(arr, l, j);
	quick_sort_hoare(arr, j + 1, r);
}


signed main(void) {
	// vector<int> test = {-4,0,7,4,9,-5,-1,0,-7,-1};
	// vector<int> test = {2, 5, 3, 1, -10, 7, 143, 32817, -123};
	vector<int> test1 = {4, 9, 7, 8, 8, 3, 33, -10, 8, 8, 8, 2, 12};
	vector<int> test2 = {4, 9, 7, 8, 8, 3, 33, -10, 8, 8, 8, 2, 12};
	vector<int> test3 = {4, 9, 7, 8, 8, 3, 33, -10, 8, 8, 8, 2, 12};
	vector<int> test4 = {4, 9, 7, 8, 8, 3, 33, -10, 8, 8, 8, 2, 12};

	cout << "Initial\n";
	print_arr(test1);

	cout << "Lomuto's\n"; // TLE on {110, 100, 0} leetcode bug??
	quick_sort_lomuto_simple(test1, 0, test1.size());
	print_arr(test1);

	cout << "Lomuto's advanced\n";
	quick_sort_lomuto_advanced(test4, 0, test4.size());
	print_arr(test4);

	cout << "Hoare's\n"; // https://leetcode.com/problems/sort-an-array/submissions/1546457206
	quick_sort_hoare(test2, 0, test2.size() - 1);
	print_arr(test2);

	cout << "Memory\n"; // https://leetcode.com/problems/sort-an-array/submissions/1547181830
	quick_sort_mem(test3);
	print_arr(test3);
	return 0;
}
