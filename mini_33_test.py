
import pytest
import random
import mini_33


def test_naive():
	deadlines = [3, 4, 1, 3, 3]
	weights = [25, 10, 30, 50, 20]

	assert mini_33.naive_for_test(deadlines, weights) == 20

def test_unionfind_1():
	deadlines = [3, 4, 1, 3, 3]
	weights = [25, 10, 30, 50, 20]

	assert mini_33.union_find_solution(deadlines, weights) == 20

def test_unionfind_2():
	deadlines = [4, 5, 1, 2, 3]
	weights = [500, 100, 10, 10, 10]

	"""
	наивный жадный алгоритм вернул бы 20
	"""

	assert mini_33.union_find_solution(deadlines, weights) == mini_33.naive_for_test(deadlines, weights) == 0

@pytest.mark.parametrize("size", [10, 100, 1000])
def test_unionfind_random(size: int):
	deadlines = [random.randint(1, size) for i in range(size)]
	weights = [random.randint(0, 1<<32) for i in range(size)]

	assert mini_33.naive_for_test(deadlines, weights) == mini_33.union_find_solution(deadlines, weights)
