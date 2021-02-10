#include <stdio.h>
#include "DebugLogger.h"
#include "BinaryTreePrinter.h"
#include "BinaryTreeTest.h"

void print_node(BinaryTree *root) {
	if (root == NULL)
		return;
	printf("%d ", root->value);
	print_node(binary_tree_predecessor(root));
}

void print_tree_sorted(int *data,int n) {
	BinaryTree *root = create_binary_tree(data, n);
//	binary_tree_print(root);
	printf("[ ");
	print_node(binary_tree_maximum(root));
	printf("]\n");

	free_binary_tree(root);
}

void exercise_two()
{
	printf("Exercise two\n");

	int personnummer[] = { 1,9,3,7,0,4,2,0,2,3,1,9 };
	int L1[] = { 3,1,5,10,8,7 };
	int L2[] = { 5,2,9,6,1,2 };

	printf("SSN: "); print_tree_sorted(personnummer, sizeof(personnummer) / sizeof(int));
	printf("L1: "); print_tree_sorted(L1, sizeof(L1) / sizeof(int));
	printf("L2: "); print_tree_sorted(L2, sizeof(L2) / sizeof(int));
}

int main(void) {
	if (test_binary_tree()) 
		debug_message("================== Binary Tree test PASSED ==================\n");
	exercise_two();
	getchar();
	return 0;
}