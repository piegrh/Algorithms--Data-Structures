#define TEST_NUM 14
#define FAILED INT_MIN
#include <stdbool.h>
#include "BinaryTree.h"
// Test binary tree implementation
bool test_binary_tree(void);
static bool print_test_results_int(int result,int expected,char *func_name);
static bool test_binary_tree_is_empty(void);
static bool test_binary_tree_insert(void);
static bool test_binary_tree_search(void);
static bool test_binary_tree_delete_1_child(void);
static bool test_binary_tree_delete_2_child(void);
static bool test_binary_tree_delete_leaf(void);
static bool test_binary_tree_minimum(void);
static bool test_binary_tree_maximum(void);
static bool test_binary_tree_successor(void);
static bool test_binary_tree_successor_max(void);
static bool test_binary_tree_predecessor(void);
static bool test_binary_tree_predecessor_min(void);
static bool test_binary_tree_depth(void);
static bool test_binary_tree_size(void);
static BinaryTree *create_and_add_node(BinaryTree *root, int key);