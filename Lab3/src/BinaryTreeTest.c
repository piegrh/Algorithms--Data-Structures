#include <stdlib.h>
#include "BinaryTreeTest.h"
#include "DebugLogger.h"
#include "Common.h"
#include "BinaryTreePrinter.h"

bool test_binary_tree(void)
{
	int i;
	bool test[TEST_NUM] =
	{
		test_binary_tree_is_empty(),
		test_binary_tree_insert(),
		test_binary_tree_search(),
		test_binary_tree_maximum(),
		test_binary_tree_minimum(),
		test_binary_tree_predecessor(),
		test_binary_tree_predecessor_min(),
		test_binary_tree_successor(),
		test_binary_tree_successor_max(),
		test_binary_tree_depth(),
		test_binary_tree_size(),
		test_binary_tree_delete_leaf(),
		test_binary_tree_delete_1_child(),
		test_binary_tree_delete_2_child()
	};

	for (i = 0; i < TEST_NUM; i++)
		if (!test[i])
			return false;

	return true;
}

bool print_test_results_int(int result, int expected, char * func_name)
{
	if (expected == result) {
		debug_message("%s PASSED! (result = %d, expected = %d)\n", func_name, result, expected);
		return true;
	}

	debug_error("%s FAILED! (result = %d, expected = %d)\n", func_name,result,expected);
	return false;
}

static BinaryTree *create_and_add_node(BinaryTree *root, int key) {
	BinaryTree *node = createNode(key);
	binary_tree_insert(root, node);
	return node;
}

static bool test_binary_tree_is_empty(void)
{
	int result, expected = 1;
	BinaryTree *root = NULL;
	result = (binary_tree_is_empty(root) ? 1 : 0);
	free_binary_tree(root);
	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_insert(void)
{
	int result, expected = 0;

	BinaryTree *root = createNode(100);
	BinaryTree *node = createNode(50);

	result = binary_tree_insert(root, node) == NULL ? 1 : 0;

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_search(void)
{
	BinaryTree *result_node;
	int result, expected = 27;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));
	BinaryTree *node = create_and_add_node(root, 27);

	if (result_node = binary_tree_search(root, node))
		result = result_node->value;
	else
		result = FAILED;

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_delete_leaf(void)
{
	BinaryTree *result_node;
	int result, expected = 27;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));

	BinaryTree *node = create_and_add_node(root, 27);

	if (result_node = binary_tree_delete(node)) {
		result = result_node->value;
		free_binary_tree(result_node);
	}
	else {
		result = FAILED;
	}

	free_binary_tree(root);
	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_delete_1_child(void)
{
	BinaryTree *result_node;
	int result, expected = 56;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));
	BinaryTree *node = binary_tree_find_value(root, 56);

	if (result_node = binary_tree_delete(node)) {
		result = result_node->value;
		free_binary_tree(result_node);
	}
	else {
		result = FAILED;
	}

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_delete_2_child(void)
{
	BinaryTree *result_node;
	int result, expected = 58;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));
	BinaryTree *node = binary_tree_find_value(root, 58);

	if (result_node = binary_tree_delete(node)) {
		result = result_node->value;
		free_binary_tree(result_node);
	}
	else {
		result = FAILED;
	}

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_minimum(void)
{
	BinaryTree *result_node;
	int result, expected = 30;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));

	if (result_node = binary_tree_minimum(root))
		result = result_node->value;
	else
		result = FAILED;

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_maximum(void)
{
	BinaryTree *result_node;
	int result, expected = 85;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));

	if (result_node = binary_tree_maximum(root))
		result = result_node->value;
	else
		result = FAILED;

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_successor(void)
{
	BinaryTree *result_node;
	int result, expected = 47;
	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));

	if (result_node = binary_tree_successor(binary_tree_find_value(root, 45)))
		result = result_node->value;
	else
		result = FAILED;

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_successor_max(void)
{
	BinaryTree *result_node;
	int result, expected = FAILED;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));
	BinaryTree *node = create_and_add_node(root, 85);

	if (result_node = binary_tree_successor(node))
		result = result_node->value;
	else
		result = FAILED;

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_predecessor(void)
{
	BinaryTree *result_node;
	int result, expected = 30;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data)/sizeof(int));

	if (result_node = binary_tree_predecessor(binary_tree_find_value(root, 45)))
		result = result_node->value;
	else
		result = FAILED;

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_predecessor_min(void)
{
	BinaryTree *result_node;
	int result, expected = FAILED;

	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));
	BinaryTree *node = create_and_add_node(root, 0);

	if (result_node = binary_tree_predecessor(node))
		result = result_node->value;
	else
		result = FAILED;

	free_binary_tree(root);

	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_depth(void)
{
	int result , expected = 5;
	int data[] = { 50,45,55,30,47,58,56,85,57 };
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));
	result = binary_tree_depth(root);
	free_binary_tree(root);
	return print_test_results_int(result, expected, __func__);
}

static bool test_binary_tree_size(void)
{
	int result, expected = 14;
	int data[] = { 10, 7,8,5,2,1,3,20,13,30,11,15,27,35};
	BinaryTree *root = create_binary_tree(data, sizeof(data) / sizeof(int));
	result = binary_tree_size(root);
	free_binary_tree(root);
	return print_test_results_int(result, expected, __func__);
}