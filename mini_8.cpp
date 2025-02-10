#include <iostream>
#include <vector>

using namespace std;


vector<vector<int>> simple_mul(vector<vector<int>>& x, vector<vector<int>>& y) {
	int n = x.size();
	int half = (n >> 1);
	if (n == 1)
		return {{x[0][0] * y[0][0]}};

	vector<vector<int>> a(half, vector<int>(half, 0)), b(half, vector<int>(half, 0)), c(half, vector<int>(half, 0)), d(half, vector<int>(half, 0)), e(half, vector<int>(half, 0)), f(half, vector<int>(half, 0)), g(half, vector<int>(half, 0)), h(half, vector<int>(half, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i < half) {
				if (j < half) {
					a[i][j] = x[i][j];
					e[i][j] = y[i][j];
				} else {
					b[i][j - half] = x[i][j];
					f[i][j - half] = y[i][j];
				}
			} else {
				if (j < half) {
					c[i - half][j] = x[i][j];
					g[i - half][j] = y[i][j];
				} else {
					d[i - half][j - half] = x[i][j];
					h[i - half][j - half] = y[i][j];
				}
			}
		}
	}


	vector<vector<int>> ae = simple_mul(a, e);
	vector<vector<int>> bg = simple_mul(b, g);
	vector<vector<int>> af = simple_mul(a, f);
	vector<vector<int>> bh = simple_mul(b, h);
	vector<vector<int>> ce = simple_mul(c, e);
	vector<vector<int>> dg = simple_mul(d, g);
	vector<vector<int>> cf = simple_mul(c, f);
	vector<vector<int>> dh = simple_mul(d, h);

	vector<vector<int>> res(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i < half) {
				if (j < half) {
					res[i][j] = ae[i][j] + bg[i][j];
				} else {
					res[i][j] = af[i][j - half] + bh[i][j - half];
				}
			} else {
				if (j < half) {
					res[i][j] = ce[i - half][j] + dg[i - half][j];
				} else {
					res[i][j] = cf[i - half][j - half] + dh[i - half][j - half];
				}
			}
		}
	}

	return res;
}


signed main(void) {

	int n = 2;

	vector<vector<int>> a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {1, 2, 3, 4}, {5, 6, 7, 8}};
	vector<vector<int>> res = simple_mul(a, a);

	for (int i = 0; i < res.size(); i++) {
		cout << res[i][0];
		for (int j = 1; j < res.size(); j++)
			cout << ' ' << res[i][j];
		cout << '\n';
	}
	cout << '\n';

	return 0;
}
