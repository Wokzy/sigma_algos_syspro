#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution { // https://leetcode.com/problems/merge-k-sorted-lists/submissions/1561163074
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		priority_queue<int, vector<int>, greater<int>> pq;
		for (int i = 0; i < lists.size(); i++) {
			ListNode *cur = lists[i];
			while (cur != nullptr) {
				pq.push(cur->val);
				cur = cur->next;
			}
		}

		ListNode *cur = new ListNode;

		if (pq.empty())
			return nullptr;

		cur->val = pq.top();
		ListNode *out = cur;
		pq.pop();
		for (; !pq.empty(); pq.pop()) {
			cur->next = new ListNode;
			cur->next->val = pq.top();
			cur = cur->next;
		}

		return out;
	}
};

int main(void) {
	return 0;
}
