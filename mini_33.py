import math
import heapq


def naive_for_test(deadlines: list[int], weights: list[int]) -> int:
    """
    Наивная реализация за O(n^2) для тестов корректности реализации с union-find
    """
    placement = [-1] * len(deadlines)
    penalty = 0

    # Можно было бы ипользовать zip(weights, deadlines, range(len(deadlines))), но мне кажется, он медленнее =)
    heap = [(weights[i], deadlines[i], i) for i in range(len(deadlines))]
    heapq._heapify_max(heap)

    while len(heap) > 0:
        cur = heapq._heappop_max(heap)

        contender = cur[1] - 1
        while placement[contender] > -1:
            contender -= 1

        if contender < 0:
            penalty += cur[0]

            contender = len(placement) - 1
            while placement[contender] > -1:
                contender -= 1

        placement[contender] = cur[2]

    return penalty


class DisjontSet:
    def __init__(self, size: int):
        self.parent = list(range(size))
        self.rank = [0] * size
        self.real = list(range(size))

    def find(self, a: int, get_real: bool = True) -> int:
        buffer = []
        res = self.parent[a]

        while self.parent[res] != res:
            buffer.append(res)
            res = self.parent[res]

        for node in buffer:
            self.parent[node] = res

        if get_real:
            return self.real[res]
        return res

    def union(self, x: int, y: int) -> None:
        a = self.find(x, get_real=False)
        b = self.find(y, get_real=False)
        # self.parent[b] = a
        if self.rank[a] > self.rank[b]:
            self.parent[b] = a
        else:
            self.parent[a] = b
            if self.rank[a] == self.rank[b]:
                self.rank[b] += 1
            self.real[b] = self.real[a]


def union_find_solution(deadlines: list[int], weights: list[int]) -> int:
    """
    Основной трюк решения - поддерживать ближайший свободный слева день для каждого дня в календаре
    Он реализован через union-find со сжатием путей и объединением по рангам.

    Забавный факт - даже на очень большом случайном массиве выигрыша по скорости от объединения по рангам **НЕТ!**

    В остальном, так же как в наивной реализации, берём самую дорогую задачу и пытаемся поставить её в день
            дедлайна, если не вышло - ставим левее, если и это не вышло, то как можно правее
    """
    disjoint_set = DisjontSet(len(deadlines) + 1)

    def bucket_sort(arr, min_el, max_el):
        nonlocal weights
        if len(arr) < 2 or min_el == max_el:
            return arr

        num_buckets = len(arr)
        buckets = [[] for i in range(num_buckets)]
        min_buckets = [weights[arr[0]] for i in range(num_buckets)]
        max_buckets = [weights[arr[0]] for i in range(num_buckets)]

        rng = max_el - min_el + 1
        for i in range(len(arr)):
            index = math.floor(num_buckets * (weights[arr[i]] - min_el) // rng)

            buckets[index].append(arr[i])

            if weights[arr[i]] < min_buckets[index]:
                min_buckets[index] = weights[arr[i]]

            if weights[arr[i]] > max_buckets[index]:
                max_buckets[index] = weights[arr[i]]

        for i in range(num_buckets):
            buckets[i] = bucket_sort(buckets[i], min_buckets[i], max_buckets[i])

        res = []
        for i in range(num_buckets):
            for k in range(len(buckets[i])):
                res.append(buckets[i][k])

        return res

    min_w = weights[0]
    max_w = weights[0]

    for i in range(1, len(weights)):
        if weights[i] < min_w:
            min_w = weights[i]
        if weights[i] > max_w:
            max_w = weights[i]

    data = [
        (weights[i], deadlines[i])
        for i in reversed(bucket_sort(list(range(len(deadlines))), min_w, max_w))
    ]
    penalty = 0

    for w, d in data:
        available = disjoint_set.find(d)
        if available == 0:
            last = disjoint_set.find(len(deadlines))
            disjoint_set.union(last - 1, last)
            penalty += w
            continue

        disjoint_set.union(available - 1, available)

    return penalty


if __name__ == "__main__":
    import random

    # deadlines = [6, 6, 10, 6, 7, 10, 6, 1, 10, 3]
    # weights = [0, 2, 17, 8, 12, 11, 15, 1, 12, 1]

    size = 8

    # deadlines = [random.randint(1, size - 2) for i in range(size)]
    # weights = [random.randint(0, 25) for i in range(size)]
    deadlines = [3, 5, 1, 6, 4, 2, 5, 6]
    weights = [8, 6, 20, 25, 14, 21, 5, 7]

    print(f"{deadlines=}")
    print(f"{weights=}")

    print(naive_for_test(deadlines, weights))
    print(union_find_solution(deadlines, weights))
