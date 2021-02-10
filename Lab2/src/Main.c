#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TestSort.h"
#include "sort.h"
#include "Common.h"

#define per_n 12
#define l1_n 6
#define l2_n 6
#define DEBUG_ON 1

void print_arr(int arr[], size_t size) {
	size_t i;
	printf("[");
	for (i = 0; i < size; i++)
		printf("%d%s", arr[i], i ==size-1 ? "" : ", ");
	printf("]");
}

bool sort(int arr[], size_t size, SortMethod sort_func)
{
	size_t i;
	bool success;

	int *temp = malloc(sizeof(int)*size);
	malloc_assert(temp == NULL, __func__);

	// Copy data
	for (i = 0; i < size; i++)
		temp[i] = arr[i];

	// Sort
	sort_func(temp, size);

	success = is_sorted(temp, size);

	// Print 
	if (!success) {
		printf("Test failed! (%s)\n", get_sort_name(sort_func));
		print_arr(arr, size);
		printf(" --> ");
		print_arr(temp, size);
		printf("\n");
		abort();
	} else if (DEBUG_ON) {
		print_arr(arr, size);
		printf(" --> ");
		print_arr(temp, size);
		printf("\n");
	}

	free(temp);

	return success;
}

int main(void)
{
	// Exercise 4 — Testing I
	int personnummer[per_n] = { 1,9,3,7,0,4,2,0,2,3,1,9 }; // not my  ssn
	int L1[l1_n] = { 3,1,5,10,8,7};
	int L2[l2_n] = { 5,2,9,6,1,2 };

	SortMethod insertion = &insertion_sort;
	SortMethod quick = &quick_sort;

	sort(personnummer, per_n, insertion);
	sort(personnummer, per_n, quick);

	sort(L1, l1_n, insertion);
	sort(L1, l1_n, quick);

	sort(L2, l2_n, insertion);
	sort(L2, l2_n, quick);

	printf("Testing done... SUCCSESS!\n"); 
	getchar();
}
