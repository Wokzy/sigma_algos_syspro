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

void lsd_radix_sort(vector<string> &arr) {
	if (arr.size() <= 1)
		return;
	int k = arr[0].size();

	for (int i = 0; i < k; i++) {
		for (int j = 1; j < arr.size(); j++) {
			if (arr[j].size() > k)
				k = arr[j].size();
			for (int l = j; l > 0; l--) {
				if (arr[l].size() < arr[l - 1].size())
					swap(arr[l], arr[l - 1]);
				else if ((arr[l].size() > i) && (arr[l][i] < arr[l - 1][i]))
					swap(arr[l], arr[l - 1]);
				else
					break;
			}
		}
	}
}


signed main(void) {
	vector<string> test1 = {"0000", "123", "001", "012", "9", "8", "7"};
	vector<string> test2 = {"0000", "123", "001", "012", "9", "8", "7"};
	lsd_radix_sort(test1);
	shell_sort(test2);
	cout << "Shell sort:\n";
	for (auto& c: test2)
		cout << c << '\n';

	cout << "\n LSD-radix sort\n";
	for (auto& c: test1)
		cout << c << '\n';

	return 0;
}
