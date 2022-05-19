/*
 * File: parse_tree.h
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#ifndef PARSE_TREE
#define PARSE_TREE

#include "declarations.h"

/*
Create TreeNode and Tree objects
*/
typedef struct TreeNode {
	BOOL isTerminal;
	char *terminal;
	char *label;

	struct TreeNode *left;
	struct TreeNode *center;
	struct TreeNode *right;
} TreeNode;

typedef struct Tree {
	TreeNode *root;
} Tree;



/* 
Memory allocation functions
*/
TreeNode* tnalloc();
Tree* talloc();



/*
Init and Free functions
*/
TreeNode* TreeNode_new(BOOL isTerminal, char *label, char *terminal);
TreeNode* TreeNode_new_empty();
Tree* Tree_new(BOOL isTerminal, char *label, char *terminal);
Tree* Tree_new_empty();
void TreeNode_free(TreeNode *node);
void Tree_free(Tree *tree);



/*
Pre-functions for adding children
*/
void Tree_addLeftChild(TreeNode *parent, BOOL isTerminal, char *label, char *terminal);
void Tree_addCenterChild(TreeNode *parent, BOOL isTerminal, char *label, char *terminal);
void Tree_addRightChild(TreeNode *parent, BOOL isTerminal, char *label, char *terminal);
void Tree_addLeftSubTree(TreeNode *parent, Tree *tree);
void Tree_addCenterSubTree(TreeNode *parent, Tree *tree);
void Tree_addRightSubTree(TreeNode *parent, Tree *tree);


/*
Actual functions for adding children
*/
void Tree_addChild(TreeNode *parent, BOOL isTerminal, char *label, char *terminal);
void Tree_addChildNode(TreeNode *parent, TreeNode *node);
void Tree_addSubTree(TreeNode *parent, Tree *tree);



/*
Pre-functions for printing the tree in postorder
*/
void Tree_printFromNode(TreeNode *node, int level);



/*
Printing the tree in postorder
*/
void Tree_print(Tree *tree);

#endif