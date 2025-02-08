#include <bits/stdc++.h>

using namespace std;


void shell_sort(vector<int>& data) {
	vector<int> seq = {1, 4, 10, 23, 57, 132, 301, 701};
	reverse(seq.begin(), seq.end());

	for (int& s : seq) {
		for (int i = s; i < data.size(); i++) {
			for (int j = i - s; j >= 0 && data[j] < data[j + s]; j -= s) {
				int temp = data[j];
				data[j] = data[j + s];
				data[j + s] = temp;
			}
		}
	}
}

class Solution {
public:
	int hIndex(vector<int>& citations) {
		shell_sort(citations);
		int res = 0;
		for (int i = 0; i < citations.size(); i++) {
			if (citations[i] < i + 1)
				break;
			res = i + 1;
		}
		return res;
	}
};

int main() {

	vector<int> a = {3,0,6,1,5};
	Solution sol;

	cout << sol.hIndex(a) << '\n';

	return 0;
}
