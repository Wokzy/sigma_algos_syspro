
#include <limits.h>
#include <bits/stdc++.h>
using namespace std;

#define VERYBIG 1000000007



vector<vector<int>> generate_graph(int n) {
	vector<vector<int>> res(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			res[i][j] = (rand() % 3072) + 1;
			res[j][i] = res[i][j];
		}
	}

	cout << "generated" << endl;

	return res;
}


int native_solution(vector<vector<int>> &graph, int cur, vector<bool> &visited, int total_visited) {

	if (total_visited == graph.size() - 1)
		return 0;


	int min_res = -1;


	visited[cur] = true;
	for (int i = 0; i < graph.size(); i++) {
		if (visited[i]) continue;

		int lres = native_solution(graph, i, visited, total_visited + 1) + graph[cur][i];
		if (lres < min_res || min_res == -1) min_res = lres;
	}

	visited[cur] = false;
	return min_res;
}


int dp_solution(vector<vector<int>> &graph) {

	int n = graph.size();
	if (n == 1) {
		return 0;
	}
	if (n == 2){
		return graph[0][1];
	}


	vector<vector<int>> dp(n, vector<int>((size_t)(1) << n, VERYBIG));

	dp[0][1] = 0;

	for (int m = 1; m < n; m++) {
		for (size_t i = 0; i < ((size_t)(1) << (n - 1)); i++) { // тк 1 всегда в s, то пробежимся по [2, 3, ..., n-1, n]
			if (__builtin_popcount(i) != m) continue;
			size_t s = (i << 1) | 1; // включаем 1 в s, тк она всегда должна там быть
			for (int v = 1; v < n; v++) { // итерируемся по элементам мн-ва S пропуская 1
				if ((s & (1 << v)) == 0) continue; // если v не в s, continue

				int min_val = VERYBIG;
				for (int w = 0; w < n; w++) {
					if ((w == v) || ((s & (1 << w)) == 0)) continue;
					if (dp[w][s & (~(1 << v))] + graph[v][w] < min_val) min_val = dp[w][s & (~(1 << v))] + graph[v][w];
				}
				dp[v][s] = min_val;
			}
		}
	}

	size_t s = ((size_t)(1) << n) - 1;
	// cout << s << endl;
	int min_val = VERYBIG;
	for (int v = 1; v < n; v++) {
		if (dp[v][s] + graph[v][0] < min_val) min_val = dp[v][s] + graph[v][0];
	}

	return min_val;
}


signed main(void) {

	int n = 7; // 7s for dp
	auto graph = generate_graph(n);
	// vector<vector<int>> graph = {{0, 1, 2, 3}, {1, 0, 6, 4}, {2, 6, 0, 5}, {3, 4, 5, 0}};

	// vector<bool> visited(n, false);
	// cout << native_solution(graph, 0, visited, 0) << '\n';
	cout << dp_solution(graph) << '\n';

	return 0;
}

