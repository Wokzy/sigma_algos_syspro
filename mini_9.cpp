#include <bits/stdc++.h>

using namespace std;

void shell_sort(vector<string>& data) {
	vector<int> seq = {1, 4, 10, 23, 57, 132, 301, 701};

	for (auto& s : views::reverse(seq)) {
		for (int i = s; i < data.size(); i++) {
			for (int j = i - s; j >= 0 && data[j] > data[j + s]; j -= s) {
				string temp = data[j];
				data[j] = data[j + s];
				data[j + s] = temp;
			}
		}
	}
}


void count_sort(vector<string> &arr, int index) {
	int n = arr.size();
	vector<string> res(n, "");
	vector<int> count(256, 0);

	for (int i = 0; i < n; i++) {
		if (index >= arr[i].size())
			count[0]++;
		else
			count[arr[i][index]]++;
	}

	for (int i = 1; i < 256; i++)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; i--) {
		int k = 0;
		if (arr[i].size() > index)
			k = arr[i][index];
		res[count[k] - 1] = arr[i];
		count[k]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = res[i];
}


void lsd_radix_sort(vector<string> &arr) {
	if (arr.size() <= 1)
		return;

	int k = 0;
	for (auto &c: arr)
		if (c.size() > k)
			k = c.size();

	for (int i = 0; i < k; i++)
		count_sort(arr, i);
}


signed main(void) {
	vector<string> test1 = {"0000", "123", "001", "012", "9", "8", "7"};
	vector<string> test2 = {"0000", "123", "001", "012", "9", "8", "7"};
	lsd_radix_sort(test1);
	shell_sort(test2);
	cout << "Shell sort:\n";
	for (auto& c: test2)
		cout << c << '\n';

	cout << "\nLSD-radix sort\n";
	for (auto& c: test1)
		cout << c << '\n';

	return 0;
}
