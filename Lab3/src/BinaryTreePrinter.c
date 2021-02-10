#include <stdio.h>
#include <math.h>
#include "BinaryTreePrinter.h"


static void _print_tree(BinaryTree *root,int space,int count)
{
	if (root == NULL)
		return;

	space += count;

	_print_tree(root->right,space,count);

	printf("\n");
	for (int i = count; i < space; i++)
		printf(" ");	
	printf("%d\n", root->value);

	_print_tree(root->left, space, count);
}

void binary_tree_print(BinaryTree *root)
{
	_print_tree(root, 0, binary_tree_depth(root));
}