#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution { // https://leetcode.com/problems/reverse-linked-list-ii/submissions/1553584478
public:
	ListNode* reverseBetween(ListNode* head, int left, int right) {
		if (right == left)
			return head;

		left--;
		right--;

		ListNode *prev = nullptr;
		ListNode *cur = head;

		int i = 0;
		for (; i < left; i++) {
			prev = cur;
			cur = cur->next;
		}

		ListNode *p1 = prev;
		ListNode *p2 = cur;

		prev = cur;
		cur = cur->next;
		ListNode *nxt = nullptr;
		for (; i < right; i++) {
			nxt = cur->next;
			cur->next = prev;
			prev = cur;
			cur = nxt;
		}


		p2->next = cur;

		if (p1 != nullptr) {
			p1->next = prev;
		} else {
			return prev;
		}

		return head;
	}
};

signed main(void) {
	return 0;
}