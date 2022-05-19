/*
 * File: parse_tree.c
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#include "parse_tree.h"

/*
Memory allocation functions
*/
TreeNode* tnalloc() {
	return (TreeNode*)(malloc(sizeof(TreeNode)));
}

Tree* talloc() {
	return (Tree*)(malloc(sizeof(Tree)));
}

/*
Init and free functions
*/
TreeNode* TreeNode_new(BOOL isTerminal, char *label, char *terminal) {
	//Allocate the memory for the node
	TreeNode *node = tnalloc();

	//Set all of the parameters
	node->isTerminal = isTerminal;
	node->label = label;
	node->terminal = terminal;

	//Set all of the children to NULL
	node->left = NULL;
	node->center = NULL;
	node->right = NULL;

	//Return the node
	return node;
}

TreeNode* TreeNode_new_empty() {
	TreeNode *node = tnalloc();

	//Set all of the children to NULL
	node->left = NULL;
	node->center = NULL;
	node->right = NULL;

	return node;
}

Tree* Tree_new(BOOL isTerminal, char *label, char *terminal) {
	//Allocate the memory for a tree
	Tree *tree = talloc();

	//Create the root node
	tree->root = TreeNode_new(isTerminal, label, terminal);

	//Return the tree
	return tree;
}

Tree* Tree_new_empty() {
	//Allocate the memory for a tree
	Tree *tree = talloc();

	//Create the root node
	tree->root = NULL;

	//Return the tree
	return tree;
}

void TreeNode_free(TreeNode *node) {
	//Free all of the children
	free(node->left);
	free(node->center);
	free(node->right);

	//Free the node itself
	free(node);
}

void Tree_free(Tree *tree) {
	//Recursively free all of the nodes in the tree
	TreeNode_free(tree->root);

	//Free the tree itself
	free(tree);
}

/*
Pre-functions for adding children
*/
void Tree_addLeftChild(TreeNode *parent, BOOL isTerminal, char *label, char *terminal) {
	//Check whether the left node is free, if so put the TreeNode as a child there
	if(parent->left == NULL)
		parent->left = TreeNode_new(isTerminal, label, terminal);
}

void Tree_addCenterChild(TreeNode *parent, BOOL isTerminal, char *label, char *terminal) {
	//Check whether the center node is free, if so put the TreeNode as a child there
	if(parent->center == NULL)
		parent->center = TreeNode_new(isTerminal, label, terminal);
}

void Tree_addRightChild(TreeNode *parent, BOOL isTerminal, char *label, char *terminal) {
	//Check whether the right node is free, if so put the TreeNode as a child there
	if(parent->right == NULL)
		parent->right = TreeNode_new(isTerminal, label, terminal);
}

void Tree_addLeftSubTree(TreeNode *parent, Tree *tree) {
	//Check whether the left node is free, if so put the tree as a child there
	if(parent->left == NULL) {
		parent->left = tree->root;
	}
}

void Tree_addCenterSubTree(TreeNode *parent, Tree *tree) {
	//Check whether the center node is free, if so put the tree as a child there
	if(parent->center == NULL) {
		parent->center = tree->root;
	}
}

void Tree_addRightSubTree(TreeNode *parent, Tree *tree) {
	//Check whether the right node is free, if so put the tree as a child there
	if(parent->right == NULL)
		parent->right = tree->root;
}

/*
Actual functions for adding children
*/
void Tree_addChild(TreeNode *parent, BOOL isTerminal, char *label, char *terminal) {
	//Check which one of the children are free and add the new node there
	if(parent->left == NULL)
		Tree_addLeftChild(parent, isTerminal, label, terminal);
	else if(parent->center == NULL)
		Tree_addCenterChild(parent, isTerminal, label, terminal);
	else if(parent->right == NULL)
		Tree_addRightChild(parent, isTerminal, label, terminal);
}

void Tree_addChildNode(TreeNode *parent, TreeNode *node) {
	//Check which one of the children are free and add the new node there
	if(parent->left == NULL)
		Tree_addLeftChild(parent, node->isTerminal, node->label, node->terminal);
	else if(parent->center == NULL)
		Tree_addCenterChild(parent, node->isTerminal, node->label, node->terminal);
	else if(parent->right == NULL)
		Tree_addRightChild(parent, node->isTerminal, node->label, node->terminal);
}

void Tree_addSubTree(TreeNode *parent, Tree *tree) {
	//Check which one of the children are free and add the new tree there
	if(parent->left == NULL)
		Tree_addLeftSubTree(parent, tree);
	else if(parent->center == NULL)
		Tree_addCenterSubTree(parent, tree);
	else if(parent->right == NULL)
		Tree_addRightSubTree(parent, tree);
}

/*
Pre-functions for printing the tree in postorder
*/
void Tree_printFromNode(TreeNode *node, int level) {
	for(int i = 0; i < level; i++)
		printf("%3c", ' ');
	printf("(%s", node->label);

	if(node->left != NULL) {
		printf("\n");
		Tree_printFromNode(node->left, ++level);
	}
	level--;
	if(node->center != NULL) {
		printf("\n");
		Tree_printFromNode(node->center, ++level);
	}
	level--;
	if(node->right != NULL) {
		printf("\n");
		Tree_printFromNode(node->right, ++level);
	}
	level--;
	printf(")");
	
}

/*
Printing the tree in postorder
*/
void Tree_print(Tree *tree) {
	if(tree != NULL) {
		Tree_printFromNode(tree->root, 0);
		printf("\n\n");
	}
}