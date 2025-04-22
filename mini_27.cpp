
#include <iostream>
#include <vector>

using namespace std;

class Solution { // https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/submissions/1614221326
public:

	vector<int> topsort(int n, vector<vector<int>> &graph, vector<int> &indegree) {
		vector<int> res;
		vector<int> stack;

		for (int i = 0; i < n; i++)
			if (indegree[i] == 0)
				stack.push_back(i);

		while (stack.size()) {
			int item = stack[stack.size() - 1];
			res.push_back(item);
			stack.pop_back();

			for (int c : graph[item]) {
				indegree[c]--;
				if (indegree[c] == 0)
					stack.push_back(c);
			}
		}

		if (res.size() != n)
			return {};

		return res;
	}

	vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {

		for (int i = 0; i < n; i++) {
			if (group[i] == -1) {
				group[i] = m;
				m++;
			}
		}

		vector<vector<int>> item_graph(n);
		vector<vector<int>> group_graph(m);

		vector<int> item_indegree(n, 0);
		vector<int> group_indegree(m, 0);


		for (int i = 0; i < n; i++) {
			for (int j : beforeItems[i]) {
				item_graph[j].push_back(i);
				item_indegree[i]++;

				if (group[i] != group[j]) {
					group_graph[group[j]].push_back(group[i]);
					group_indegree[group[i]]++;
				}
			}
		}

		vector<int> item_topsort = topsort(n, item_graph, item_indegree);
		if (item_topsort.size() == 0)
			return {};

		vector<int> group_topsort = topsort(m, group_graph, group_indegree);
		if (group_topsort.size() == 0)
			return {};

		vector<vector<int>> sort_by_group(m);

		for (int c : item_topsort)
			sort_by_group[group[c]].push_back(c);

		vector<int> res;
		for (auto gr : group_topsort)
			for (auto c : sort_by_group[gr])
				res.push_back(c);

		return res;
	}
};

int main(void) {

	Solution sol;
	vector<int> input_group = {2,0,-1,3,0};
	vector<vector<int>> input_beforeitems = {{2,1,3},{2,4},{},{},{}};
	vector<int> res = sol.sortItems(5, 5, input_group, input_beforeitems);

	if (res.size() == 0)
		return 0;

	cout << res[0];
	for (int i = 1; i < res.size(); i++)
		cout << ' ' << res[i];
	cout << '\n';

	return 0;
}
