#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "DebugLogger.h"
#include "BinaryTree.h"
#include "BinaryTreePrinter.h"

bool binary_tree_is_empty(BinaryTree * root)
{
	return root == NULL;
}

static BinaryTree *_binary_tree_insert(BinaryTree * grandParent ,BinaryTree * parent, BinaryTree * node, bool *inserted)
{
	if (parent == NULL) {
		node->parent = grandParent;
		parent = node;
		*inserted = true;
	} else 	if (node->value < parent->value) {
		parent->left = _binary_tree_insert(parent,parent->left, node, inserted);
	} else {
		parent->right = _binary_tree_insert(parent, parent->right, node, inserted);
	}
	return parent;
}

BinaryTree *binary_tree_insert(BinaryTree * root, BinaryTree * node)
{
	bool inserted = false;
	return _binary_tree_insert(NULL, root, node,&inserted) ? node : NULL;
}

BinaryTree *binary_tree_search(BinaryTree * root, BinaryTree * node)
{
	if (root == NULL)
		return NULL;
	if (node->value < root->value) 
		return binary_tree_search(root->left, node);
	else if (node->value > root->value) 
		return binary_tree_search(root->right, node);
	else 
		return root;
}

static int binary_tree_node_child_count(BinaryTree * node)
{
	if (node == NULL)
		debug_error("Null pointer exception (%s)", __func__);
	else if(node->left == NULL && node->right == NULL)
		return 0;
	else if (node->left != NULL && node->right != NULL)
		return 2;
	return 1;
}

static void _set_node_to_null(BinaryTree * node)
{
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
}

// Case: node has 0 children
static BinaryTree * _delete_leaf_node(BinaryTree * node) 
{
	if (node->value < node->parent->value) 
		node->parent->left = NULL;
	else 
		node->parent->right = NULL;
	node->parent = NULL;
	return node;
}

// Case: node has 1 child
static BinaryTree * _delete_1child_node(BinaryTree * node)
{
	// compare node value and node parent value
	if (node->value < node->parent->value) {
		// Smaller, put childnode in parent left
		node->parent->left = (node->left != NULL) ? node->left : node->right; // Set child of node parent 
		node->parent->left->parent = node->parent;
	} else {
		// not smaller, put childnode in parent right
		node->parent->right = (node->left != NULL) ? node->left : node->right; // set child of node parent
		node->parent->right->parent = node->parent;
	}

	_set_node_to_null(node);

	return node;
}

// Case: node has 2 children
static BinaryTree * _delete_2child_node(BinaryTree * node) {
	// swap places of min and node, and change all edges :<>

	BinaryTree *min = binary_tree_minimum(node->right);

	// Left Node
	min->left = node->left;
	min->left->parent = min;

	// Right Node
	min->right = (node->right == min) ? NULL : node->right;
	if (min->right != NULL)
		min->right->parent = min;

	// Parent Node
	min->parent = node->parent;
	if (node->value < node->parent->value)
		min->parent->left = min;
	else
		min->parent->right = min;

	_set_node_to_null(node);

	return node;
}

BinaryTree * binary_tree_delete(BinaryTree * node)
{
	if (node == NULL) 
	{
		debug_warning("NULL pointer exception! (%s)\n", __func__);
		return NULL;
	}

	switch (binary_tree_node_child_count(node))
	{
		case 2:
			return _delete_2child_node(node);
		case 1:
			return _delete_1child_node(node);
		default:
			return _delete_leaf_node(node);
	}
}

BinaryTree * binary_tree_minimum(BinaryTree * root)
{
	if (root == NULL)
		return NULL;
	return (root->left == NULL) ? root : binary_tree_minimum(root->left);
}

BinaryTree * binary_tree_maximum(BinaryTree * root)
{
	return (root->right == NULL) ? root : binary_tree_maximum(root->right);
}

BinaryTree * binary_tree_successor(BinaryTree * node)
{
	BinaryTree *x, *y;

	if (node == NULL)
		return NULL;
	else if (node->right != NULL)
		return binary_tree_minimum(node->right);

	x = node;
	y = node->parent;

	while (y != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}

	return y;
}

BinaryTree * binary_tree_predecessor(BinaryTree * node)
{
	BinaryTree *x, *y;

	if (node == NULL)
		return NULL;
	else if (node->left != NULL)
		return binary_tree_maximum(node->left);

	x = node;
	y = node->parent;

	while (y != NULL && x == y->left) {
		x = y;
		y = y->parent;
	}

	return y;
}

int binary_tree_size(BinaryTree * root)
{
	return (root == NULL) ? 0 : (1 + binary_tree_size(root->left) + binary_tree_size(root->right));
}

int binary_tree_depth(BinaryTree * root)
{
	int left, right;

	if (root == NULL)
		return 0;

	left = binary_tree_depth(root->left);
	right = binary_tree_depth(root->right);

	return (left > right) ? left + 1 : right + 1;
}

// ====================================================== Extra stuff

BinaryTree *createNode(int value) {
	BinaryTree *node = (BinaryTree*)malloc(sizeof(BinaryTree));
	malloc_assert(node == NULL, __func__);
	node->value = value;
	_set_node_to_null(node);
	return node;
}

BinaryTree *create_binary_tree(int *data, int node_count) {
	int i;
	BinaryTree *root = createNode(data[0]);
	for (i = 1; i < node_count; i++) 
		binary_tree_insert(root, createNode(data[i]));
	return root;
}

BinaryTree * binary_tree_find_value(BinaryTree * root, int value) {
	if (root == NULL)
		return NULL;
	if (value < root->value)
		return binary_tree_find_value(root->left, value);
	else if (value > root->value)
		return binary_tree_find_value(root->right, value);
	else
		return root;
}

void free_binary_tree(BinaryTree *root)
{
	if (root == NULL)
		return;
	free_binary_tree(root->left);
	free_binary_tree(root->right);
	free(root);
}
