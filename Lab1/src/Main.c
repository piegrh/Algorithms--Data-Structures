#include <stdio.h>
#include <stdlib.h>
#include "TestLinkedList.h"
#include "StackTest.h"
#include "QueueTest.h"
#include "Common.h"
#include "DebugLogger.h"

#define NUMBER_OF_LISTS 2
#define LIST_SIZE 6

static void print_line(void) {
	debug_message("=======================================================\n");
}

// Print highest and lowest keys in list
static void print_min_max(LinkedList *list, char* name) {
	int max = list_maximum(list)->key;
	int min = list_minimum(list)->key;
	printf("%s minimum = %d, maximum = %d\n", name, min, max);
}

// Find successor and predecessor of target_key in list and print keys.
static void print_successor_and_predecessor(LinkedList *list, char* name, int target_key) {
	ListElement *temp, *target = NULL, *suc = NULL, *pred = NULL;

	// find target_key in the list
	for (temp = list->head; temp; temp = temp->next) 
		if (temp->key == target_key) 
			target = temp;

	printf("%s successor and predecessor of %d\n", name, target_key);

	if (target != NULL) {
		suc = list_successor(list, target);
		pred = list_predecessor(list, target);

		if (suc == NULL) 
			printf("successor = NULL (%d is maximum)\n", target_key);
		else 
			printf("successor = %d\n", suc->key);

		if (pred == NULL) 
			printf("predecessor = NULL (%d is minimum)\n", target_key);
		else 
			printf("predecessor = %d\n", pred->key);

		return;
	}

	printf("Node with key %d not found in. (%s)", target_key, __func__);
	return;
}

static bool list_add_multiple(LinkedList * list, int data[], int length)
{
	int i;

	if (list == NULL)
		return false;

	for (i = 0; i < length; i++) {
		ListElement *n = (ListElement*)malloc(sizeof(ListElement));
		malloc_assert(n == NULL, __func__);
		n->key = data[i];
		list_insert(list, n);
	}

	return (i != -1);
}

// Exercise 2
void linked_list_exercise_two() {
	printf("(Exercise 2)\n");
	int data[NUMBER_OF_LISTS][LIST_SIZE] = { { 7,8,10,5,1,3},{2,1,6,9,2,5} };
	int i;

	LinkedList *lists[NUMBER_OF_LISTS];

	for (i = 0; i < NUMBER_OF_LISTS; i++) {
		lists[i] = (LinkedList*)malloc(sizeof(LinkedList));
		malloc_assert(lists[i] == NULL, __func__);
		lists[i]->head = NULL;
		list_add_multiple(lists[i], data[i], sizeof(data[i]) / sizeof(int));
	}

	printf("L1 = "); list_print(lists[0]);
	printf("L2 = "); list_print(lists[1]);

	print_min_max(lists[0], "L1");
	print_min_max(lists[1], "L2");

	print_successor_and_predecessor(lists[0], "L1", 5);
	print_successor_and_predecessor(lists[1], "L2", 9);

	printf("The key of the predecessor in L2 of the maximum of L1 is %d\n", list_predecessor(lists[1], list_maximum(lists[0]))->key);
	printf("The key of the predecessor in L1 of the maximum of L2 is %d\n", list_predecessor(lists[0], list_maximum(lists[1]))->key);

	for (i = 0; i < NUMBER_OF_LISTS; i++) 
		free_linked_list(lists[i]);
}

void print_test_results(bool result, char *test_name) {
	if (result)
		debug_message("%s SUCCEEDED\n", test_name);
	else
		debug_error("%s FAILED\n", test_name);
	print_line();
}

int main(void) {
	print_test_results(test_stack(), "(Exercise 5) Stack Test");
	print_test_results(test_queue(), "(Exercise 5) Queue Test");
	print_test_results(test_linked_list(), "Linked List Test");
	linked_list_exercise_two();
	getchar();
	return 0;
}
