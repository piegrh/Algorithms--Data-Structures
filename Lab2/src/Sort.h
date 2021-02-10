#include <stdlib.h>

typedef void(*SortMethod)(int *arr, size_t size);

// sorts an array of ints into ascending order
void merge_sort(int *arr,size_t size);
 
// sorts an array of ints into ascending order
void insertion_sort(int *arr, size_t size);

// sorts an array of ints into ascending order
void quick_sort(int *arr, size_t size);

char *get_sort_name(SortMethod sort);
