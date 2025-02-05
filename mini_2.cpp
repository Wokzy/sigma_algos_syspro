// #include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
// #include <list>
#include <inttypes.h>

using namespace std;


/*
Длинное умножение реализовано с помощью Алгоритма Карацубы

Вместо std::vector можно было бы использовать std::list (двусвязный список),
что непосредственно предоставило бы возможность за константу удалять (добавлять)
элементы с начала.
*/


void print_vector_rev(vector<auto> &a) {
	for (ssize_t i = a.size() - 1; i >= 0; i--)
		cout << a[i];
	cout << '\n';
}


class uintbig_t {
private:
	ssize_t msd = 0; // most significant digit
	int32_t BASE = 10;

	void recalc_msd() {
		msd = 0;
		for (ssize_t i = digits.size() - 1; i > 0; i--) {
			if (digits[i] != 0) {
				msd = i;
				return;
			}
			// digits.pop_back();
		}
	}

public:
	vector<int32_t> digits;
	// template<typename Type>
	// uintbig_t(Type n);
	uintbig_t() {
		digits = vector<int32_t>(1, 0);
	}
	uintbig_t(string n) {
		digits = vector<int32_t>(n.size(), 0);
		for (int i = 0; i < n.size(); i++)
			digits[n.size() - i - 1] = n[i] - '0';
		recalc_msd();
	}
	uintbig_t(int a) {
		digits = vector<int32_t>(1, a % 10);
		a /= 10;
		while (a) {
			msd++;
			digits.push_back(a % 10);
			a /= 10;
		}
	}
	uintbig_t(vector<int32_t> d) {
		digits = d;
		recalc_msd();
	}
	bool operator==(const uintbig_t &n) const {
		if (msd != n.msd)
			return false;

		for (ssize_t i = 0; i <= msd; i++)
			if (digits[i] != n.digits[i])
				return false;

		return true;
	}
	bool operator!=(const uintbig_t &n) const {
		return !(*this == n);
	}
	bool operator>=(const uintbig_t &n) const {
		if (msd > n.msd)
			return true;
		else if (msd < n.msd)
			return false;

		for (ssize_t i = msd; i >= 0; i--) {
			if (digits[i] > n.digits[i])
				return true;
			if (digits[i] < n.digits[i])
				return false;
		}
		return true;
	}
	bool operator>(const uintbig_t &n) const {
		if (msd > n.msd)
			return true;
		else if (msd < n.msd)
			return false;

		for (ssize_t i = msd; i >= 0; i--) {
			if (digits[i] > n.digits[i])
				return true;
			if (digits[i] < n.digits[i])
				return false;
		}
		return false;
	}
	bool operator<(const uintbig_t &n) const {
		return n > *this;
	}
	bool operator<=(const uintbig_t &n) const {
		return n >= *this;
	}
	uintbig_t &base_shr() {
		if (msd == 0) {
			digits[0] = 0;
			return *this;
		}
		digits.erase(digits.begin());
		msd--;
		return *this;
	}
	uintbig_t &base_shl() {
		if (msd == 0 && digits[0] == 0) {
			return *this;
		}
		digits.insert(digits.begin(), 0);
		msd++;
		return *this;
	}
	uintbig_t &operator+=(const uintbig_t& other) {
		while (digits.size() < other.digits.size())
			digits.push_back(0);

		for (ssize_t i = 0; i < other.digits.size(); i++) {
			digits[i] += other.digits[i];
		}

		for (ssize_t i = 0; i < digits.size(); i++) {
			if (digits[i] >= BASE) {
				if (i == digits.size() - 1)
					digits.push_back(0);
				digits[i] -= BASE;
				digits[i + 1]++;
			}
		}
		recalc_msd();
		return *this;
	}
	uintbig_t &operator-=(const uintbig_t& other) {
		if (other >= *this) {
			*this = 0;
			return *this;
		}
		for (ssize_t i = 0; i <= other.msd; i++) {
			digits[i] -= other.digits[i];
		}

		for (ssize_t i = 0; i <= msd; i++) {
			if (digits[i] < 0) {
				digits[i] += BASE;
				digits[i + 1]--;
			}
		}
		recalc_msd();
		return *this;
	}
	uintbig_t operator+(const uintbig_t& other) const {
		uintbig_t n = *this;
		n += other;
		return n;
	}
	uintbig_t operator-(const uintbig_t& other) const {
		uintbig_t n = *this;
		n -= other;
		return n;
	}
	uintbig_t &operator/=(const uintbig_t &other) {
		if (other == 0 || *this == 0) {
			*this = 0;
			return *this;
		}
		if (other > *this) {
			*this = 0;
			return *this;
		} else if (other == *this) {
			*this = 1;
			return *this;
		}
		vector<int32_t> new_digits;
		ssize_t old_msd = other.msd;

		uintbig_t n(other);

		while (n.msd < msd)
			n.base_shl();

		while (n.msd >= old_msd) {
			int32_t l_res = 0;
			while (*this >= n) {
				*this -= n;
				l_res++;
			}
			n.base_shr();
			new_digits.push_back(l_res);
		}

		reverse(new_digits.begin(), new_digits.end());
		digits = new_digits;

		recalc_msd();
		return *this;
	}
	uintbig_t &operator*=(const uintbig_t &other) {
		if (*this == 0 || other == 0) {
			*this = 0;
			return *this;
		}

		uintbig_t first, second;
		if (digits.size() >= other.digits.size()) {
			first = *this;
			second = other;
		} else {
			first = other;
			second = *this;
		}

		while (first.digits.size() > second.digits.size())
			second.digits.push_back(0);

		if (first.digits.size() & 1) {
			first.digits.push_back(0);
			second.digits.push_back(0);
		}

		if (second.msd == 0) {
			*this = 0;
			for (int32_t i = 0; i < second.digits[0]; i++)
				*this += first;
			recalc_msd();
			return *this;
		}

		if (first.msd == 0) {
			*this = 0;
			for (int32_t i = 0; i < first.digits[0]; i++)
				*this += second;
			recalc_msd();
			return *this;
		}

		/*
		a      b
		 12 34
		 56 78 станислав валерьевич
		c     d
		*/

		vector<int32_t> a_digits, b_digits, c_digits, d_digits;
		for (ssize_t i = 0; i < first.digits.size(); i++) {
			if (i < (first.digits.size() >> 1)) {
				b_digits.push_back(first.digits[i]);
				d_digits.push_back(second.digits[i]);
			} else {
				a_digits.push_back(first.digits[i]);
				c_digits.push_back(second.digits[i]);
			}
		}

		uintbig_t a(a_digits), b(b_digits), c(c_digits), d(d_digits);
		uintbig_t ac = a;
		ac *= c;
		uintbig_t bd = b;
		bd *= d;

		uintbig_t eq = a + b;
		eq *= (c + d);
		eq -= bd;
		eq -= ac;

		for (size_t i = 0; i < first.digits.size(); i++) {
			ac.base_shl();
			if (i < (first.digits.size() >> 1))
				eq.base_shl();
		}

		*this = ((ac + bd) + eq);
		return *this;
	}
	uintbig_t operator*(const uintbig_t& other) const {
		uintbig_t n = *this;
		n *= other;
		return n;
	}
};

ostream &operator<<(ostream &out, const uintbig_t &num) {
	bool flag = false;
	for (size_t i = num.digits.size(); i > 0; i--) {
		if (num.digits[i - 1] != 0)
			flag = true;

		if (flag)
			out << num.digits[i - 1];
	}

	if (!flag)
		out << '0';

	return out;
}

istream &operator>>(istream &in, uintbig_t &num) {
	string a;
	in >> a;
	num = a;

	return in;
};

int main(void)
{
	// list<int> q = {1, 8, 13};
	// cout << *(q.begin()) << '\n';
	uintbig_t test1_a = 13424;
	uintbig_t test1_b = 77777;
	cout << test1_a << " * " << test1_b << " = " << (test1_a * test1_b) << endl;

	uintbig_t test2_a = 1234;
	uintbig_t test2_b = 5678;
	cout << test2_a << " * " << test2_b << " = " << (test2_a * test2_b) << endl;

	cout << "Now enter 2 numbers manually:\n";
	uintbig_t a, b;
	cin >> a >> b;
	cout << (a *= b) << '\n';

	return 0;
}
