#include <stdlib.h>
#include <stdbool.h>
#include "Sort.h"
#include "TestSort.h"

static bool test_sort(SortMethod sort)
{
	int arr[] = { 6,4,3,5,1,9,7,8,2,0 };
	size_t size = sizeof(arr) / sizeof(int);
	sort(arr, size);
	return is_sorted(arr, size);
}

bool test_merge_sort()
{
	SortMethod sort = &merge_sort;
	return test_sort(sort);
}

bool test_insertion_sort()
{
	SortMethod sort = &insertion_sort;
	return test_sort(sort);
}

bool test_quick_sort()
{
	SortMethod sort = &quick_sort;
	return test_sort(sort);
}

bool is_sorted(int * arr, size_t size)
{
	size_t i;
	for (i = 0; i < size - 1; i++)
		if (arr[i] > arr[i + 1])
			return false;
	return true;
}
