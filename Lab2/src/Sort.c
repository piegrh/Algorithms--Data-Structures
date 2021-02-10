#include <stdlib.h>
#include <stdbool.h>
#include "Sort.h"
#include "Common.h"

// ======================================================= Insertion

/* Exercise 1 — Sorting I
 * Implement a sorting algorithm with quadratic complexity. */
void insertion_sort(int * arr, size_t size)
{
	int i, key;
	for (size_t j = 1; j < size; j++) {
		key = arr[j];
		i = j - 1;
		while (i >= 0 && arr[i] > key) 
			arr[i + 1] = arr[i--];
		arr[i + 1] = key;
	}
}

// ======================================================= Quick Sort

static void swap(int *arr,int a,int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

static int partition(int *arr, int l, int h)
{
	int j,i = l - 1, pivot = arr[h];
	for ( j = l; j < h; j++)
		if (arr[j] <= pivot)
			swap(arr, ++i, j);
	swap(arr, i + 1, h);
	return i + 1;
}

static void _quick_sort(int *arr, int l, int h)
{
	int j;
	if (l < h)
	{
		j = partition(arr, l, h);
		_quick_sort(arr, l, j-1);
		_quick_sort(arr, j+1, h);
	}
}

/* Exercise 2 — Sorting II
 * Implement a sorting algorithm with better than quadratic complexity */
void quick_sort(int * arr, size_t size)
{
	_quick_sort(arr, 0, size-1);
}

// ======================================================= Merge Sort

static void merge(int *arr, int l, int m, int h)
{
	int i, j, k, offset;
	int size_a = 1 + m - l;
	int size_b = h - m;

	int *a = malloc(sizeof(int)*size_a);
	malloc_assert(a == NULL, __func__);

	int *b = malloc(sizeof(int)*size_b);
	malloc_assert(b == NULL, __func__);

	// Copy data
	offset = l;
	for (i = 0; i < size_a; i++)
		a[i] = arr[offset + i];

	offset = m + 1;
	for (j = 0; j < size_b; j++)
		b[j] = arr[offset + j];

	i = 0, j = 0, k = l;

	// always pick the lowest value from a and b
	while (i < size_a && j < size_b)
		arr[k++] = (a[i] <= b[j]) ? a[i++] : b[j++];

	// Add rest from a
	while (i < size_a)
		arr[k++] = a[i++];
	// Add rest from b
	while (j < size_b)
		arr[k++] = b[j++];

	// free temp arrays
	free(a);
	free(b);
}

static void _merge_sort(int * arr, int l, int h)
{
	int m;
	if (l < h)
	{
		m = ((h + l) / 2);
		_merge_sort(arr, l, m);
		_merge_sort(arr, m + 1, h);
		merge(arr, l, m, h);
	}
}

void merge_sort(int * arr, size_t size)
{
	_merge_sort(arr, 0, size - 1); 

// ======================================================= Misc
char *get_sort_name(SortMethod sort)
{
	if (sort == &quick_sort)
		return "Quick sort";
	if (sort == &merge_sort)
		return "Merge sort";
	if (sort == &insertion_sort)
		return "Insertion sort";
	return "NONE";
}