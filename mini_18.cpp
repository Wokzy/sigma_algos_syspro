#include <vector>
#include <iostream>

using namespace std;

class MinStack { // https://leetcode.com/problems/min-stack/submissions/1561166588
private:
	vector<int> content;
	vector<int> min_stack;
public:
	MinStack() {
		content = {};
		min_stack = {};
	}
	
	void push(int val) {
		content.push_back(val);
		if ((min_stack.size() == 0) || (min_stack[min_stack.size() - 1] >= val))
			min_stack.push_back(val);
	}
	
	void pop() {
		int val = content[content.size() - 1];
		content.pop_back();
		if (val == min_stack[min_stack.size() - 1])
			min_stack.pop_back();
	}
	
	int top() {
		return content[content.size() - 1];
	}
	
	int getMin() {
		return min_stack[min_stack.size() - 1];
	}
};

signed main(void) {
	return 0;
}
