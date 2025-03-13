#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BinHeapNode {
	int val;
	int degree;
	BinHeapNode *parent;
	BinHeapNode *sibling; // right node
	BinHeapNode *child; // left-most child

	void print() {
		BinHeapNode *cur = this;
		BinHeapNode *cur_save = cur;
		while (cur != nullptr) {
			cout << cur->val;
			cur = cur->sibling;
			while (cur != nullptr) {
				cout << ' ' << cur->val;
				cur = cur->sibling;
			}
			cout << '\n';
			cur = cur_save->child;
			cur_save = cur;
		}
	}
};

BinHeapNode *new_node() {
	BinHeapNode *node = new BinHeapNode;
	node->val = 0;
	node->degree = 0;
	node->parent = nullptr;
	node->sibling = nullptr;
	node->child = nullptr;
	return node;
}

BinHeapNode *new_node(int x) {
	BinHeapNode *node = new_node();
	node->val = x;

	return node;
}

struct BinomialHeap {
	BinHeapNode *head;

	BinomialHeap() : head(nullptr) {}
	BinomialHeap(int x) {
		head = new_node(x);
	}
	BinomialHeap(BinHeapNode* ptr) : head(ptr) {}

	bool empty() {
		return (head == nullptr);
	}

	void push(int x);
	int top();
	int pop();

	void print() {
		BinHeapNode *cur = head;
		while (cur != nullptr) {
			cout << "degree: " << cur->degree << "\n" << cur->val << '\n';
			(*cur->child).print();
			cout << '\n';
			cur = cur->sibling;
		}
	}
};

// merges tree1 into tree2
BinHeapNode *merge_equal_trees(BinHeapNode *tree1, BinHeapNode *tree2) {

	tree1->sibling = nullptr;
	tree2->sibling = nullptr;

	tree1->parent = tree2;
	BinHeapNode *cur1 = tree1;
	BinHeapNode *cur1_save = cur1;
	BinHeapNode *cur2 = tree2->child;

	while (cur2 != nullptr) {
		while (cur1->sibling != nullptr)
			cur1 = cur1->sibling;
		cur1->sibling = cur2;
		cur2 = cur2->child;
		cur1 = cur1_save->child;
		cur1_save = cur1;
	}

	tree2->degree++;
	tree2->child = tree1;

	cur2 = tree2;
	while ((cur2->child != nullptr) && (cur2->child->val < cur2->val)) {
		swap(cur2->val, cur2->child->val);
		cur2 = cur2->child;
	}

	return tree2;
}

BinomialHeap merge(BinomialHeap h1, BinomialHeap h2) {
	if (h1.head == nullptr)
		return h2;
	else if (h2.head == nullptr)
		return h1;

	BinomialHeap h;
	BinHeapNode *cur1 = h1.head;
	BinHeapNode *cur2 = h2.head;

	vector<BinHeapNode*> t1;
	vector<BinHeapNode*> t2;

	while (cur1 != nullptr) {
		while (t1.size() <= cur1->degree) {
			t1.push_back(nullptr);
		}
		t1[cur1->degree] = cur1;
		cur1 = cur1->sibling;
	}

	while (cur2 != nullptr) {
		while (t2.size() <= cur2->degree)
			t2.push_back(nullptr);
		t2[cur2->degree] = cur2;
		cur2 = cur2->sibling;
	}

	while (t2.size() < t1.size())
		t2.push_back(nullptr);

	while (t1.size() < t2.size())
		t1.push_back(nullptr);

	BinHeapNode *carry = nullptr;
	vector<BinHeapNode*> res(t1.size(), nullptr);
	for (int i = 0; i < t1.size(); i++) {
		if (t1[i] && t2[i] && carry) {
			res[i] = carry;
			carry = merge_equal_trees(t1[i], t2[i]);
		} else if (t1[i] && t2[i]) {
			carry = merge_equal_trees(t1[i], t2[i]);
		} else if (t1[i] && carry) {
			carry = merge_equal_trees(t1[i], carry);
		} else if (t2[i] && carry) {
			carry = merge_equal_trees(t2[i], carry);
		} else if (t1[i]) {
			res[i] = t1[i];
		} else if (t2[i]) {
			res[i] = t2[i];
		} else {
			res[i] = carry;
			carry = nullptr;
		}
	}

	if (carry) {
		res.push_back(carry);
	}

	BinHeapNode *out = nullptr;

	for (auto node : res) {
		if (node != nullptr) {
			if (!out) {
				h.head = node;
				out = node;
				continue;
			}
			out->sibling = node;
			out = out->sibling;
		}
	}

	return h;
}

void BinomialHeap::push(int x) {
	BinomialHeap new_heap(x);
	BinomialHeap merged = merge(*this, new_heap);
	head = merged.head;
}

int BinomialHeap::top() {
	int mn = head->val;
	auto cur = head;
	while (cur != nullptr) {
		if (cur->val < mn)
			mn = cur->val;
		cur = cur->sibling;
	}

	return mn;
}

int BinomialHeap::pop() {
	int value = top();

	BinHeapNode *prev = nullptr;
	auto cur = head;
	while (cur->val != value) {
		prev = cur;
		cur = cur->sibling;
	}

	if (prev) {
		prev->sibling = cur->sibling;
	} else {
		head = head->sibling;
	}

	BinomialHeap boogie(cur->child);
	BinomialHeap new_heap = merge(*this, boogie);
	head = new_heap.head;

	return value;
}
