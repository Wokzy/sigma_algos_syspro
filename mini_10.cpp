#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/sort-colors/submissions/1544098339

void netherlands_sort(vector<int> &arr) {
	int p1 = 0, p2 = 0;

	if (arr.size() <= 1)
		return;

	int k = 0;

	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] >= k) {
			k = arr[i];
			if (k == 0) {
				p1 = i + 1;
				p2 = i + 1;
			}
			else if (k == 1) {
				p2 = i + 1;
			}
			continue;
		}
		if (arr[i] == 0) {
			if (arr[p1] == 2) {
				swap(arr[p1], arr[i]);
			} else {
				arr[p1] = 0;
				arr[i] = arr[p2];
				arr[p2] = 1;
			}
			p1++;
		} else {
			arr[i] = arr[p2];
			arr[p2] = 1;
		}
		p2++;
	}
}


signed main(void) {
	ios::sync_with_stdio(false);
	cout.tie(0);

	vector<int> test = {0, 0, 1, 2, 0, 2, 1, 1, 0, 0, 0, 1};
	// vector<int> test = {1, 0, 0};
	netherlands_sort(test);

	cout << test[0];
	for (int i = 1; i < test.size(); i++)
		cout << ' ' << test[i];
	cout << '\n';
	return 0;
}
