
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution { // https://leetcode.com/problems/is-graph-bipartite/submissions/1613556738
public:

	bool dfs(vector<vector<int>> &graph, int parent, int current, unordered_map<int, bool>& mapping) {
		bool color = !mapping[parent];
		mapping[current] = color;

		for (int c : graph[current]) {
			if (c == parent)
				continue;

			if (mapping.contains(c)) {
				if (mapping[c] == color) {
					return false;
				}
				continue;
			}

			if (!dfs(graph, current, c, mapping))
				return false;
		}

		return true;
	}

	bool isBipartite(vector<vector<int>>& graph) {
		unordered_map<int, bool> mapping;
		mapping[-1] = true;

		for (int i = 0; i < graph.size(); i++) {
			if (mapping.contains(i))
				continue;

			if (!dfs(graph, -1, i, mapping))
				return false;
		}
		return true;
	}
};

int main(void) {

	Solution sol;
	vector<vector<int>> test = {{1},{0,3},{3},{1,2}};

	cout << sol.isBipartite(test) << endl;
	return 0;
}
