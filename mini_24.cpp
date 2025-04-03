#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class FreqStack { // https://leetcode.com/problems/maximum-frequency-stack/submissions/1595315215
private:
	int counter = 0;
	vector<int> heap;
	unordered_map<int, int> index_mapping;
	unordered_map<int, vector<int>> stack;

	bool cmp(int first, int second) {
		if (!stack[first].size())
			return false;
		if (!stack[second].size())
			return true;

		if (stack[first].size() > stack[second].size())
			return true;
		else if ((stack[first].size() == stack[second].size()) && (stack[first][stack[first].size() - 1] > stack[second][stack[second].size() - 1]))
			return true;
		return false;
	}

	void siftdown(int start_pos, int pos) {
		int cur = heap[pos];

		while (pos > start_pos) {
			int parent_pos = (pos - 1) >> 1;
			int parent = heap[parent_pos];
			if (cmp(cur, parent)) {
				heap[pos] = parent;
				index_mapping[parent] = pos;
				pos = parent_pos;
				continue;
			}
			break;
		}
		heap[pos] = cur;
		index_mapping[cur] = pos;
	}

	void siftup(int pos) {
		int end_pos = heap.size();
		int start_pos = pos;
		int item = heap[pos];

		int child_pos = 2*pos + 1;
		while (child_pos < end_pos) {
			int right_pos = child_pos + 1;
			if (right_pos < end_pos && !(cmp(heap[child_pos], heap[right_pos])))
				child_pos = right_pos;
			heap[pos] = heap[child_pos];
			index_mapping[heap[child_pos]] = pos;
			pos = child_pos;
			child_pos = 2*pos + 1;
		}

		heap[pos] = item;
		index_mapping[item] = pos;
		siftdown(start_pos, pos);
	}

public:
	FreqStack() {
	}

	int pop() {
		int first = heap[0];

		stack[first].pop_back();
		siftup(0);
		return first;
	}

	void push(int item) {
		if (!stack.contains(item))
			stack[item] = {counter};
		else
			stack[item].push_back(counter);
		counter++;
		if (index_mapping.contains(item)) {
			siftdown(0, index_mapping[item]);
		} else {
			heap.push_back(item);
			siftdown(0, heap.size() - 1);
		}
	}
};

int main(void) {
	FreqStack* obj = new FreqStack();
	obj->push(5);
	obj->push(7);
	obj->push(5);
	obj->push(7);
	obj->push(4);
	obj->push(5);
	cout << obj->pop() << endl;
	cout << obj->pop() << endl;
	cout << obj->pop() << endl;
	cout << obj->pop() << endl;
	return 0;
}
