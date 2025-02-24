
import os
import math
import time
import random

from format_table import format_table


MAX_LOGN = 8

SINGLE_TEST_ATTEMPTS = 6
BASIC_EXEC_NAME = './mini_8_basic'
SHTRASSEN_EXEC_NAME = './mini_8_shtrassen'

def run_test(n, x, y, exec_name) -> tuple[float, float, float]:
	with open('input.txt', 'w', encoding='utf-8') as f:
		f.write(str(n) + '\n')
		for line in x:
			f.write(' '.join(list(map(str, line))) + '\n')
		for line in y:
			f.write(' '.join(list(map(str, line))) + '\n')

	results = []

	for i in range(SINGLE_TEST_ATTEMPTS):
		start_time = time.time()
		os.system(exec_name)
		results.append(time.time() - start_time)

	smean = sum(results) / SINGLE_TEST_ATTEMPTS
	dev = math.sqrt(sum([(r - smean)**2 for r in results]) / SINGLE_TEST_ATTEMPTS) # standart diviation
	gmean = 1
	for r in results:
		gmean *= r
	gmean = gmean**(1 / SINGLE_TEST_ATTEMPTS)

	return (smean.real, gmean.real, dev)

def gen_random_matrix(n: int):
	return [[random.randint(1, 10) for j in range(n)] for i in range(n)]


def main():
	results = []

	for i in range(1, MAX_LOGN + 1):
		n = 1 << i
		print(f"testing {n}")
		res_basic = run_test(n, gen_random_matrix(n), gen_random_matrix(n), BASIC_EXEC_NAME)
		res_shtrassen = run_test(n, gen_random_matrix(n), gen_random_matrix(n), SHTRASSEN_EXEC_NAME)
		results.append([f'{res_basic[0]:.3f}/{res_basic[1]:.3f}/{res_basic[2]:.3f}',
						f'{res_shtrassen[0]:.3f}/{res_shtrassen[1]:.3f}/{res_shtrassen[2]:.3f}'])

	print(format_table(
				 [str(1 << i) for i in range(1, MAX_LOGN + 1)],
				 ["basic (smean/gmean/dev)", "shtrassen (smean/gmean/dev)"],
				 results, name='N'))


if __name__ == '__main__':
	main()
