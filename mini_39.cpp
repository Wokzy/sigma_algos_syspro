// #include <bits/stdc++.h>
#include <assert.h>
#include <utility>
#include <iostream>


using namespace std;

struct Treap {
	int priority;
	int sum;
	int size;
	int value;
	Treap *right;
	Treap *left;

	Treap(int p, int val) : sum(val), value(val), priority(p), size(1), right(nullptr), left(nullptr) {}
	~Treap() {
		if (right) delete right;
		if (left) delete left;
	}
};

void update(Treap *x) {
	x->size = 1;
	x->sum = x->value;
	if (x->left) {
		x->size += x->left->size;
		x->sum += x->left->sum;
	}
	if (x->right) {
		x->size += x->right->size;
		x->sum += x->right->sum;
	}
}


Treap *merge(Treap *x, Treap *y) {
	if (x == nullptr) return y;
	if (y == nullptr) return x;

	if (x->priority < y->priority) {
		x->right = merge(x->right, y);
		update(x->right);
		update(x);
		return x;
	}

	y->left = merge(x, y->left);
	update(y->left);
	update(y);
	return y;
}


pair<Treap *, Treap *> splitBySize(Treap *x, int k) {
	if (x == nullptr) return {nullptr, nullptr};

	int l_size = 0;
	if (x->left) l_size = x->left->size;

	if (k <= l_size) {
		auto ll_lr = splitBySize(x->left, k);
		x->left = ll_lr.second;
		update(x);
		return {ll_lr.first, x};
	}

	auto rl_rr = splitBySize(x->right, k - l_size - 1);
	x->right = rl_rr.first;
	update(x);
	return {x, rl_rr.second};
}


Treap *insert(Treap *x, int pos, int value) {
	auto l_r = splitBySize(x, pos - 1);
	auto y = new Treap(rand(), value);
	return merge(merge(l_r.first, y), l_r.second);
}

Treap *erase(Treap *x, int pos, int count) {
	auto l_r = splitBySize(x, pos - 1);
	auto rl_rr = splitBySize(l_r.second, count);

	return merge(l_r.first, rl_rr.second);
}

int sum(Treap *x, int lq, int rq) {
	auto l_r = splitBySize(x, lq - 1);
	auto rl_rr = splitBySize(l_r.second, rq - lq + 1);

	int res = 0;
	if (rl_rr.first != nullptr) {
		res = rl_rr.first->sum;
	}

	merge(l_r.first, merge(rl_rr.first, rl_rr.second));
	return res;
}


int main(void) {

	srand((unsigned)time(0));

	auto test = insert(nullptr, 1, 1);
	test = insert(test, 2, 14);
	test = insert(test, 3, 25);
	test = insert(test, 4, 25);
	test = insert(test, 3, 10);

	// {1, 14, 10, 25, 25}

	cout << sum(test, 1, 1) << '\n'; // 1
	cout << sum(test, 1, 10) << '\n'; // 75
	cout << sum(test, 3, 4) << '\n'; // 35
	cout << sum(test, 100, 230) << '\n'; // 0
	cout << sum(test, 4, 4) << '\n'; // 25


	test = erase(test, 3, 2);
	// {1, 14, 25};
	cout << sum(test, 1, 10) << '\n'; // 40
	cout << sum(test, 2, 2) << '\n'; // 14

	delete test;
	return 0;
}
