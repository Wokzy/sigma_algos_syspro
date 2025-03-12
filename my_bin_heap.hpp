#pragma once
#include <vector>

using namespace std;

template<typename T>
void siftdown(vector<T> &heap, int start_pos, int pos, bool (*cmp)(T, T)) {
	T cur = heap[pos];

	while (pos > start_pos) {
		int parent_pos = (pos - 1) >> 1;
		T parent = heap[parent_pos];
		if (cmp(cur, parent)) {
			heap[pos] = parent;
			pos = parent_pos;
			continue;
		}
		break;
	}
	heap[pos] = cur;
}

template<typename T>
void siftup(vector<T> &heap, int pos, bool (*cmp)(T, T)) {
	int end_pos = heap.size();
	int start_pos = pos;
	T item = heap[pos];

	int child_pos = 2*pos + 1;
	while (child_pos < end_pos) {
		int right_pos = child_pos + 1;
		if (right_pos < end_pos && !(cmp(heap[child_pos], heap[right_pos])))
			child_pos = right_pos;
		heap[pos] = heap[child_pos];
		pos = child_pos;
		child_pos = 2*pos + 1;
	}

	heap[pos] = item;
	siftdown(heap, start_pos, pos, cmp);
}

template<typename T>
void heapify(vector<T> &arr, bool (*cmp)(T, T)) {
	if (arr.size() <= 1)
		return;

	int n = (arr.size() >> 1) - 1;
	for (int i = n; i >= 0; i--)
		siftup(arr, i, cmp);
}

template<typename T>
T heappop(vector<T> &heap, bool (*cmp)(T, T)) {
	T last = heap[heap.size() - 1];
	heap.pop_back();

	if (heap.size()) {
		T ret = heap[0];
		heap[0] = last;
		siftup(heap, 0, cmp);
		return ret;
	}
	return last;
}

template<typename T>
void heappush(vector<T> &heap, T item, bool (*cmp)(T, T)) {
	heap.push_back(item);
	siftdown(heap, 0, heap.size() - 1, cmp);
}
