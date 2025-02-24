#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	ListNode(int x, ListNode *ptr) : val(x), next(ptr) {}
};

class Solution { // https://leetcode.com/problems/linked-list-cycle-ii/submissions/1553477945
public:
	ListNode *detectCycle(ListNode *head) {
		ListNode *p1 = head, *p2 = head;

		while ((p2 != NULL) && (p2->next != NULL)) {
			p1 = p1->next;
			p2 = p2->next->next;

			if (p1 == p2)
				break;
		}

		if ((p2 == NULL) || (p2->next == NULL))
			return NULL;

		p2 = head;
		while (p2 != p1) {
			p1 = p1->next;
			p2 = p2->next;
		}

		return p1;
	}
};

signed main(void) {
	ListNode a(-4, NULL);
	ListNode c = {0, &a};
	ListNode b = {2, &c};
	ListNode d = {3, &b};
	a.next = &b;
	Solution sol;
	ListNode *res = sol.detectCycle(&c);
	cout << res->val << '\n';
	return 0;
}
