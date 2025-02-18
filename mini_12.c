#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
	int *lomuto;
	int *hoare;
} test_ctx;


void print_arr(int *arr, size_t n) {
	if (n == 0)
		return;

	printf("%d", arr[0]);
	for (size_t i = 1; i < n; i++)
		printf(" %d", arr[i]);
	putchar('\n');
}

void quick_sort_hoare(int *arr, int l, int r) {
	if (r <= l)
		return;

	int v = arr[(l + r) / 2];
	int i = l;
	int j = r;

	while (i <= j) {
		while (arr[i] < v)
			i++;
		while (arr[j] > v)
			j--;
		if (i >= j)
			break;

		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		i++;
		j--;
	}

	quick_sort_hoare(arr, l, j);
	quick_sort_hoare(arr, j + 1, r);
}

int *lomuto_partition_branchfree(int *first, int *last) {
	--last;
	if (*first > *last) {
		int temp = *first;
		*first = *last;
		*last = *first;
	}
	int *pivot_pos = first;
	int pivot = *first;
	do {
		++first;
	} while (*first < pivot);
	for (int *read = first + 1; read < last; ++read) {
		int x = *read;
		int smaller = -(int)(x < pivot);
		int delta = smaller & (read - first);
		first[delta] = *first;
		read[-delta] = x;
		first -= smaller;
	}
	--first;
	*pivot_pos = *first;
	*first = pivot;
	return first;
}

void quick_sort_lomuto_advanced(int *first, int *last) {
	if (last - first < 2)
		return;

	int *pivot = lomuto_partition_branchfree(first, last);
	quick_sort_lomuto_advanced(first, pivot + 1);
	quick_sort_lomuto_advanced(pivot + 1, last);
}

test_ctx gen_random_ctx(size_t size) {
	test_ctx res;
	res.lomuto = malloc(sizeof(int) * size);
	res.hoare = malloc(sizeof(int) * size);
	for (size_t i = 0; i < size; i++) {
		res.lomuto[i] = rand() % 20;
		res.hoare[i] = res.lomuto[i];
	}

	return res;
}

void clear_ctx(test_ctx ctx) {
	free(ctx.lomuto);
	free(ctx.hoare);
}

signed main(void) {
	srand(time(NULL));

	for (size_t n = 10; n <= 100000; n *= 10) {
		printf("N = %zu\n", n);
		test_ctx ctx = gen_random_ctx(n);

		clock_t startclock = clock();
		quick_sort_hoare(ctx.hoare, 0, n - 1);
		clock_t endclock = clock();
		printf("\tHoare : %9.4f\n", (float)(endclock-startclock)/(float)CLOCKS_PER_SEC);
		startclock = clock();
		quick_sort_lomuto_advanced(ctx.lomuto, ctx.lomuto + n);
		endclock = clock();
		printf("\tLomuto : %9.4f\n", (float)(endclock-startclock)/(float)CLOCKS_PER_SEC);
		clear_ctx(ctx);
	}

	return 0;
}

