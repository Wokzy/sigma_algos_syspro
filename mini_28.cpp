
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using namespace std;


void _dfs(unordered_map<string, vector<string>> &graph, unordered_set<string> &visited, string current, unordered_map<string, int> &counter, int &depth) {

	visited.insert(current);

	for (string &c : graph[current]) {
		if (visited.contains(c))
			continue;

		_dfs(graph, visited, c, counter, depth);
	}

	counter[current] = depth;
	depth++;
}

void _dfs2(unordered_map<string, vector<string>> &graph, unordered_set<string> &visited, string current, vector<string> &res) {
	res.push_back(current);
	visited.insert(current);

	for (string &c: graph[current]) {
		if (visited.contains(c))
			continue;

		_dfs2(graph, visited, c, res);
	}
}

bool _dfs3(unordered_map<string, vector<string>> &graph, unordered_set<string> &visited, string current, unordered_map<string, bool> &have_loops) {

	bool propagate = false;
	visited.insert(current);

	for (string &c : graph[current]) {
		if (visited.contains(c)) {
			propagate = true;
			continue;
		}

		if (have_loops.contains(c)) {
			propagate |= have_loops[c];
			continue;
		}

		propagate |= _dfs3(graph, visited, c, have_loops);
	}

	have_loops[current] = propagate;
	return propagate;
}

pair<vector<string>, unordered_map<string, bool>> max_recursive_component(unordered_map<string, vector<string>> &graph) {
	int n = graph.size();

	if (n == 0)
		return {{}, {}};

	unordered_map<string, vector<string>> rev(n);

	for (auto& it: graph) {
		for (string &name : it.second) {
			rev[name].push_back(it.first);
		}
	}

	int depth = 0;
	unordered_map<string, int> counter;
	unordered_set<string> visited;
	for (auto& it: rev)
		if (!visited.contains(it.first))
			_dfs(rev, visited, it.first, counter, depth);

	visited.clear();
	vector<string> mx_component;

	// sorting by counter
	for (auto& it: graph)
		for (int i = 1; i < graph[it.first].size(); i++)
			for (int j = i; (j > 0) && counter[graph[it.first][j]] > counter[graph[it.first][j - 1]]; j--)
				swap(graph[it.first][j], graph[it.first][j - 1]);

	// calculating mx_component
	for (auto &it : graph) {
		if (!visited.contains(it.first)) {
			vector<string> temp_res;
			_dfs2(graph, visited, it.first, temp_res);

			if (temp_res.size() > mx_component.size())
				mx_component = temp_res;
		}
	}

	unordered_map<string, bool> have_loops;

	for (auto &it : graph) {
		visited.clear();
		if (!have_loops.contains(it.first)){
			_dfs3(graph, visited, it.first, have_loops);
		}
	}

	return {mx_component, have_loops};
}


int main(void) {

	unordered_map<string, vector<string>> graph;
	graph["foo"] = {"bar", "baz", "qux"};
	graph["bar"] = {"baz", "foo", "bar"};
	graph["baz"] = {};
	graph["qux"] = {"qux"};

	pair<vector<string>, unordered_map<string, bool>> res = max_recursive_component(graph);

	cout << "Max component:\n";
	for (string &c : res.first) {
		cout << c << '\n';
	}

	cout << "\nHave recursion:\n";
	for (auto &it : res.second) {
		if (it.second)
			cout << it.first << '\n';
	}

	return 0;
}
