#ifndef BINARY_TREE_HEADER
#define BINARY_TREE_HEADER
#include <stdbool.h>

typedef struct binary_tree_t {
	int value;
	struct binary_tree_t *parent;
	struct binary_tree_t *left;
	struct binary_tree_t *right;
} BinaryTree;

// returns true if list is empty and false otherwise;
bool binary_tree_is_empty(BinaryTree *root);

// returns a pointer to the inserted node, NULL if the insertion failed
BinaryTree *binary_tree_insert(BinaryTree *root, BinaryTree *node);

// returns a pointer to the node N if node is in the List L, and NULL if N is not on the list
BinaryTree *binary_tree_search(BinaryTree *root, BinaryTree *node);

// returns a pointer to the node N and N is deleted from the list, and NULL if deletion was not successful
BinaryTree *binary_tree_delete(BinaryTree *node);

// returns a pointer to the node with the smallest key
BinaryTree *binary_tree_minimum(BinaryTree *root);

// returns a pointer to the node with the largest key.
BinaryTree *binary_tree_maximum(BinaryTree *root);

// returns a pointer to the next larger node, or NULL if N is the maximum;
BinaryTree *binary_tree_successor(BinaryTree *node);

// returns a pointer to the next smaller node, or NULL if N is the minimum.
BinaryTree *binary_tree_predecessor(BinaryTree *node);

// BinaryTree depth
int binary_tree_depth(BinaryTree *root);

// returns number of tree nodes in the BinaryTree
int binary_tree_size(BinaryTree *root);

// ====================== Extra client code ======================

BinaryTree *createNode(int value);
BinaryTree *create_binary_tree(int *data, int node_count);
BinaryTree *binary_tree_find_value(BinaryTree * root, int value);
void free_binary_tree(BinaryTree *root);
#endif


