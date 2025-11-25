#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.first <= b.first;
}

struct SegTree {
	SegTree *l, *r;
	int lb, rb, s;

	SegTree(SegTree *left, SegTree *right, int value, int lb, int rb) : lb(lb), rb(rb), l(left), r(right), s(value) {}
	SegTree(int value, int lb, int rb) : lb(lb), rb(rb), l(nullptr), r(nullptr), s(value) {}
	SegTree(int l_b, int r_b) {
		lb = l_b;
		rb = r_b;
		l = nullptr;
		r = nullptr;

		if (lb + 1 < rb) {
			int mid = (lb + rb) >> 1;
			l = new SegTree(lb, mid);
			r = new SegTree(mid, rb);
		}
	}

	int sum(int lq, int rq) {
		if (lb >= lq && rb <= rq)
			return s;
		if (max(lb, lq) >= min(rb, rq))
			return 0;

		return l->sum(lq, rq) + r->sum(lq, rq);
	}

	~SegTree() {
		if (l) delete l, r;
	}
};


SegTree *add(SegTree *v, int pos, int val) {
	if (v->lb + 1 == v->rb) {
		return new SegTree(v->s + val, v->lb, v->rb);
	}

	int mid = (v->lb + v->rb) >> 1;
	if (pos < mid) {
		return new SegTree(add(v->l, pos, val), v->r, v->s + val, v->lb, v->rb);
	} else {
		return new SegTree(v->l, add(v->r, pos, val), v->s + val, v->lb, v->rb);
	}
}


int query_stat(vector<SegTree *> &trees, vector<int> &arr, int lq, int rq, int k) {
	int left = 0;
	int right = arr.size() - 1;

	int mid = 0;
	while (left <= right) {
		mid = left + ((right - left) >> 2);
		// cout << left << ' ' << right << ' ' << mid << '\n';

		if (arr[mid] == k) {
			return trees[arr.size() - mid - 1]->sum(lq, rq);
		} else if (arr[mid] < k) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	// cout << trees[mid]->sum(0, 70) << endl;
	return trees[arr.size() - mid - 1]->sum(lq, rq);
}


int main() {

	vector<int> input = {46, 11, 40, 8, 2, 42, 65, 10};
	vector<pair<int, int>> arr;

	for (int i = 0; i < input.size(); i++) {
		arr.push_back({input[i], i});
	}

	sort(arr.begin(), arr.end(), cmp);

	for (int i = 0; i < input.size(); i++) {
		input[i] = arr[i].first;
	}

	reverse(arr.begin(), arr.end());

	auto prev = new SegTree(0, 128);
	vector<SegTree *> trees;

	for (auto &p : arr) {
		prev = add(prev, p.second, 1);
		trees.push_back(prev);
	}

	cout << query_stat(trees, input, 1, 4, 9) << '\n'; // [lq, rq)
	cout << query_stat(trees, input, 1, 4, 8) << '\n';
	cout << query_stat(trees, input, 0, 1, 46) << '\n';

	return 0;
}


