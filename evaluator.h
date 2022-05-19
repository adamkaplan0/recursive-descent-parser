/*
 * File: evaluator.h
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#ifndef EVALUATOR
#define EVALUATOR

#include "recursive_parser.h"
#include "table_parser.h"

/*
Important side functions
*/
char* cat(char *dest, char *src);
double factorial(double x);
void print_char(char *input);

/*
Evaluation function
*/
char* R_eval(TreeNode *node, char *n);
Tree* get_Tree(char *input, BOOL print, BOOL table);
void raw_eval(Tree *tree);
void evaluate(char *input, BOOL print, BOOL table, BOOL eval);

#endif