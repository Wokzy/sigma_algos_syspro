#include <iostream>
#include <vector>

using namespace std;

void quick_sort(vector<int> &arr, int l, int r) {
	if (r - l <= 1)
		return;

	int n = r - l;
	int p = abs(arr[0]) % n; // как мне кажется - достаточно случайный элемент
	swap(arr[l], arr[l + p]);

	int i = 1, j = 1;
	while (j < n) {
		if (arr[j + l] <= arr[l]) {
			if (i != j)
				swap(arr[i + l], arr[j + l]);
			i++;
		}
		j++;
	}
	if (i != 1)
		swap(arr[l], arr[i + l - 1]);

	quick_sort(arr, l, i + l - 1);
	quick_sort(arr, i + l, r);
}


signed main(void) {
	// vector<int> test = {0, 0, 1, 2, 0, 2, 1, 1, 0, 0, 0, 1};
	vector<int> test = {4, 1, 7, 8, 3, 33, -10, 2, 12};

	quick_sort(test, 0, test.size());
	cout << test[0];
	for (int i = 1; i < test.size(); i++)
		cout << ' ' << test[i];
	cout << '\n';
	return 0;
}
