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

void quick_sort_simple(vector<int> &arr, int l, int r) {
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

	quick_sort_simple(arr, l, i + l + 1);
	quick_sort_simple(arr, k + l + 1, r);
}

void quick_sort_advanced(vector<int> &arr, int l, int r) {
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

	quick_sort_advanced(arr, l, j);
	quick_sort_advanced(arr, j + 1, r);
}


signed main(void) {
	// vector<int> test = {2, 5, 3, 1};
	// vector<int> test = {2, 5, 3, 1, -10, 7, 143, 32817, -123};
	vector<int> test1 = {4, 9, 7, 8, 8, 3, 33, -10, 8, 8, 8, 2, 12};
	vector<int> test2 = {4, 9, 7, 8, 8, 3, 33, -10, 8, 8, 8, 2, 12};

	cout << "Initial\n";
	print_arr(test1);

	cout << "Lomuto's\n";
	quick_sort_simple(test1, 0, test1.size());
	print_arr(test1);

	cout << "Hoare's\n";
	quick_sort_advanced(test2, 0, test2.size() - 1);
	print_arr(test2);
	return 0;
}
