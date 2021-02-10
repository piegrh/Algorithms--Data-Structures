#include "TestLinkedList.h"
#include <stdlib.h>
#include "Common.h"
#include "DebugLogger.h"

#define TEST_NUM 9

bool test_linked_list(void)
{
	int i;
	bool test[TEST_NUM] =
	{
		test_list_is_empty(),
		test_list_insert(),
		test_list_delete(),
		test_list_minimum(),
		test_list_maximum(),
		test_list_successor(),
		test_list_successor_maximum(),
		test_list_predecessor(),
		test_list_predecessor_minimum()
	};

	for (i = 0; i < TEST_NUM; i++)
		if (!test[i])
			return false;

	return true;
}

// creates a new list and adds the ints from arr as nodes
static LinkedList *create_list(int *arr, int count) {
	int i;
	LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));
	malloc_assert(list == NULL, __func__);

	list->head = NULL;

	for (i = 0; i < count; i++) {
		ListElement *n = (ListElement*)malloc(sizeof(ListElement));
		malloc_assert(n == NULL, __func__);
		n->key = arr[i];
		list_insert(list, n);
	}

	return list;
}

// create a new node,set key to value,insert it into list and returns the new node.
static ListElement *list_insert_key(LinkedList *list, int value) {
	ListElement *node = (ListElement*)malloc(sizeof(ListElement));
	malloc_assert(node == NULL, __func__);
	node->key = value;
	return list_insert(list, node) ? node : NULL;
}

static char *bool_to_string(bool b) {
	return (b) ? "TRUE" : "FALSE";
}

static bool eval_test_restult_bool(char *name, bool result, bool expected) {
	if (result == expected) {
		debug_message("%s() PASS\n", name, bool_to_string(result), bool_to_string(expected));
		return true;
	}

	debug_error("%s() FAIL (Result %s, Expected %s)\n", name, bool_to_string(result), bool_to_string(expected));
	return false;
}

static bool eval_test_restult_int(char * name, int result, int expected) {
	if (result == expected) {
		debug_message("%s() PASS\n", name, result, expected);
		return true;
	}

	debug_error("%s() FAIL (Result %d, Expected %d)\n", name, result, expected);
	return false;
}

static bool test_list_is_empty(void) {
	bool result, expected = true;

	LinkedList *list = (LinkedList*)malloc(sizeof(ListElement));
	malloc_assert(list == NULL, __func__);
	list->head = NULL;

	result = list_is_empty(list);

	free_linked_list(list);
	return eval_test_restult_bool(__func__, result, expected);
}

static bool test_list_insert(void)
{
	int result,expected = 5;

	int data[] = { 2,4,1,6,7 };
	LinkedList *list = create_list(data, sizeof(data) / sizeof(int));

	result = list_count(list);

	free_linked_list(list);
	return eval_test_restult_int(__func__, result, expected);
}

static bool test_list_delete(void)
{
	int result, expected = 0;

	LinkedList *list = create_list(NULL, 0);
	ListElement *node = list_insert_key(list, 123);

	list_delete(list, node);

	result = list_count(list);

	free(node);
	free_linked_list(list);
	return eval_test_restult_int(__func__, result, expected);
}

static bool test_list_minimum(void)
{
	int result, expected = -13;

	int data[] = { 2,4,5,1,7, 12, -13, 3,1,0,-10 };
	LinkedList *list = create_list(data, sizeof(data) / sizeof(int));

	result = list_minimum(list)->key;
	free_linked_list(list);
	return eval_test_restult_int(__func__, result, expected);
}

static bool test_list_maximum(void)
{
	int result,expected = 9;

	int data[] = { 2,4,9,6,7, 1,0,-1,-3,-10 };
	LinkedList *list = create_list(data, sizeof(data) / sizeof(int));

	result = list_maximum(list)->key;

	free_linked_list(list);
	return eval_test_restult_int(__func__, result, expected);
}

static bool test_list_successor(void)
{
	int result, expected = 30;

	int data[] = { 5,8,6,12,3,9,30 };
	LinkedList *list = create_list(data, sizeof(data) / sizeof(int));

	ListElement *node = list_insert_key(list, 19);

	result = list_successor(list, node)->key;

	free_linked_list(list);
	return eval_test_restult_int(__func__, result, expected);
}

static bool test_list_successor_maximum(void)
{
	bool result, expected = true;

	int data[] = { 5,8,6,12,3,9,30 };
	LinkedList *list = create_list(data, sizeof(data) / sizeof(int));

	ListElement *node = list_insert_key(list, 200);

	result = list_successor(list, node) == NULL;

	free_linked_list(list);

	return eval_test_restult_bool(__func__, result, expected);
}

static bool test_list_predecessor(void)
{
	int result, expected = 12;

	int data[] = { 5,8,6,12,3,9,30 };
	LinkedList *list = create_list(data, sizeof(data) / sizeof(int));

	ListElement *node = list_insert_key(list, 29);

	result = list_predecessor(list, node)->key;

	free_linked_list(list);
	return eval_test_restult_int(__func__, result, expected);
}

static bool test_list_predecessor_minimum(void)
{
	bool result, expected = true;

	int data[] = { 5,8,6,12,3,9,30 };
	LinkedList *list = create_list(data, sizeof(data) / sizeof(int));

	ListElement *node = list_insert_key(list, 1);

	result = list_predecessor(list, node) == NULL;

	free_linked_list(list);
	return eval_test_restult_bool(__func__, result, expected);
}