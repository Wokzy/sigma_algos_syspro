// #include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
// #include <list>
#include <inttypes.h>

using namespace std;


/*
Анализ сложности алгоритма деления (N, M - количество цифр в делимом и делителе соотв.):
Текущая реализация с использованием контейнера std::vector в процессе деления
делает операции удаления первого элемента с начала, что имеет линейную сложность,
однако, если принебречь этим, и положить, что удаление самой "правой" цифры числа
происходит за константу, то алгоритм делает N сдвигов, на каждом из
которых происходит вычитание, работающее за M, поэтому в среднем и худшем
случаях алгоритм работает за O(N*M), а в лучшем случае
(числа равны или делитель больше делимого) за O(1)

Вместо std::vector можно было бы использовать std::list (двусвязный список),
что непосредственно предоставило бы возможность за константу удалять (добавлять)
элементы с начала.
*/


class uintbig_t {
private:
	ssize_t msd = 0; // most significant digit
	int32_t BASE = 10;

	void recalc_msd() {
		for (ssize_t i = digits.size() - 1; i >= 0; i--) {
			if (digits[i] != 0) {
				msd = i;
				return;
			}
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
		bool flag = true;
		for (int i = 0; i < n.size(); i++) {
			if (flag && n[i] != '0') {
				msd = n.size() - i - 1;
				flag = false;
			}
			digits[n.size() - i - 1] = n[i] - '0';
		}
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
	bool operator==(const uintbig_t &n) const {
		if (msd != n.msd)
			return false;

		for (ssize_t i = 0; i <= msd; i++)
			if (digits[i] != n.digits[i])
				return false;

		return true;
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

	uintbig_t &operator/=(const uintbig_t &other) {
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

	uintbig_t a, b;
	cin >> a >> b;
	cout << (a /= b) << '\n';

	return 0;
}
