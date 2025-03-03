#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

/* Я понял задачу следующим образом:
	Дан массив из `n` целых чисел, нужно выбрать произвольное число `a`, такое что
	sum(|xi - a|), где 0 <= i <= n, xi - эл массива.

Решение: нашим ответом будет медиана исходного массива, если n нечётное,
		иначе среднее арифметическое 2х медиан (нижней и верхней), найдём их с помощью
		детерменированного алгоритма поиска k-й порядковой статистики

		В целом, среднее арифметическое 2х медиан во втором случае искать вовсе не обязательно,
  		поскольку медиандой мы "поделим" координаты так, что снизу и сверху окажется поровну 
    		скважин. Изходя из этих рассуждений можно просто вывести любую медиану.
*/


int select(vector<int> &arr) {

	int n = arr.size();

	if (n < 5) {
		sort(arr.begin(), arr.end());
		return arr[n >> 1];
	}

	vector<int> medians;

	for (int l = 0; l + 5 <= n; l += 5) {
		sort(arr.begin() + l, arr.begin() + l + 5);
		medians.push_back(arr[l + 2]);
	}

	int q = (n / 5) * 5;
	if (q != n) {
		vector<int> vec;
		for (; q < n; q++)
			vec.push_back(arr[q]);
		medians.push_back(select(vec));
	}

	return select(medians);
}

int solution(vector<int> &arr, int k) {

	if (arr.size() == 1)
		return arr[0];

	int pivot = select(arr);

	vector<int> less;
	vector<int> equal;
	vector<int> greater;

	for (auto &c : arr) {
		if (c < pivot)
			less.push_back(c);
		else if (c == pivot)
			equal.push_back(c);
		else
			greater.push_back(c);
	}

	if (k < less.size())
		return solution(less, k);
	else if (k > (less.size() + equal.size()))
		return solution(greater, k - less.size() - equal.size());
	return pivot;
}


signed main(void) {

	// vector<int> arr = {1, 2, 3, 4, 4, 6, 7, 8, 9, 10};
	vector<int> arr = {7, 9, 2, 10, 4, 4, 3, 8, 6, 1};
	int n = arr.size();

	// int n;
	// cin >> n;
	// vector<int> arr(n, 0);
	// for (auto &c : arr)
	// 	cin >> c;

	cout << solution(arr, arr.size() >> 1) << '\n';
	// if (n & 1)
	// 	cout << solution(arr, arr.size() >> 1) << '\n';
	// else
	// 	cout << ((solution(arr, (arr.size() >> 1) - 1) + solution(arr, arr.size() >> 1)) >> 1) << '\n';

	return 0;
}
