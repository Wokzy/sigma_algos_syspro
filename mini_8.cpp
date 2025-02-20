#include <fstream>
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


vector<vector<int>> shtrassen(vector<vector<int>>& x, vector<vector<int>>& y) {
	int n = x.size();
	int half = (n >> 1);
	if (n == 1)
		return {{x[0][0] * y[0][0]}};
	else if (n <= 8) {
		return simple_mul(x, y);
	}

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

	vector<vector<int>> f_h(half, vector<int>(half, 0));
	vector<vector<int>> a_b(half, vector<int>(half, 0));
	vector<vector<int>> c_d(half, vector<int>(half, 0));
	vector<vector<int>> g_e(half, vector<int>(half, 0));
	vector<vector<int>> a_d(half, vector<int>(half, 0));
	vector<vector<int>> e_h(half, vector<int>(half, 0));
	vector<vector<int>> b_d(half, vector<int>(half, 0));
	vector<vector<int>> g_h(half, vector<int>(half, 0));
	vector<vector<int>> a_c(half, vector<int>(half, 0));
	vector<vector<int>> e_f(half, vector<int>(half, 0));

	for (int i = 0; i < half; i++) {
		for (int j = 0; j < half; j++) {
			f_h[i][j] = f[i][j] - h[i][j];
			a_b[i][j] = a[i][j] + b[i][j];
			c_d[i][j] = c[i][j] + d[i][j];
			g_e[i][j] = g[i][j] - e[i][j];
			a_d[i][j] = a[i][j] + d[i][j];
			e_h[i][j] = e[i][j] + h[i][j];
			b_d[i][j] = b[i][j] - d[i][j];
			g_h[i][j] = g[i][j] + h[i][j];
			a_c[i][j] = a[i][j] - c[i][j];
			e_f[i][j] = e[i][j] + f[i][j];
		}
	}

	vector<vector<int>> p1 = shtrassen(a, f_h);
	vector<vector<int>> p2 = shtrassen(a_b, h);
	vector<vector<int>> p3 = shtrassen(c_d, e);
	vector<vector<int>> p4 = shtrassen(d, g_e);
	vector<vector<int>> p5 = shtrassen(a_d, e_h);
	vector<vector<int>> p6 = shtrassen(b_d, g_h);
	vector<vector<int>> p7 = shtrassen(a_c, e_f);

	vector<vector<int>> res(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i < half) {
				if (j < half) {
					res[i][j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j];
				} else {
					res[i][j] = p1[i][j - half] + p2[i][j - half];
				}
			} else {
				if (j < half) {
					res[i][j] = p3[i - half][j] + p4[i - half][j];
				} else {
					res[i][j] = p1[i - half][j - half] + p5[i - half][j - half] - p3[i - half][j - half] - p7[i - half][j - half];
				}
			}
		}
	}

	return res;
}


signed main(void) {

	ifstream input;
	ofstream out;

	input.open("input.txt");
	out.open("output.txt", ios::trunc);

	int n;
	input >> n;

	vector<vector<int>> a(n, vector<int>(n, 0)), b(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			input >> a[i][j];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			input >> b[i][j];

	#ifdef SHTRASSEN
	vector<vector<int>> res = shtrassen(a, b);
	#else
	vector<vector<int>> res = simple_mul(a, b);
	#endif

	for (int i = 0; i < res.size(); i++) {
		out << res[i][0];
		for (int j = 1; j < res.size(); j++)
			out << ' ' << res[i][j];
		out << '\n';
	}

	input.close();
	out.close();

	return 0;
}
