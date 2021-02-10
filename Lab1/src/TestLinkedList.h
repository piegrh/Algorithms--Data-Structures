#include <stdbool.h>
#include "LinkedList.h"

// run all linkedlist test functions, returns true if all tests passed
bool test_linked_list();
static bool eval_test_restult_bool(char *name, bool result, bool expected);
static bool eval_test_restult_int(char *name,int result,int expected);
static bool test_list_is_empty(void);
static bool test_list_insert(void);
static bool test_list_delete(void);
static bool test_list_minimum(void);
static bool test_list_maximum(void);
static bool test_list_successor(void);
static bool test_list_successor_maximum(void);
static bool test_list_predecessor(void);
static bool test_list_predecessor_minimum(void);
static LinkedList *create_list(int *arr, int count);
static ListElement *list_insert_key(LinkedList *list, int key);