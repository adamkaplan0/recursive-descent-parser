/*
 * File: stack.h
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#ifndef STACK
#define STACK

#include "declarations.h"
#include "parse_tree.h"

//Define the Element type
typedef struct Element{
	Tree *data;
	struct Element *next;
} Element;

//Define the Stack type
typedef struct {
	Element *top;
} Stack;

/*
Memory allocation functions
*/
Stack* salloc();
Element* ealloc();

/*
Initialization functions
*/
Stack* Stack_new(Tree *data);
Element* Element_new(Tree *data);

/*
Data manipulation functions
*/
void Stack_push(Stack *stack, Tree *data);
Tree* Stack_pop(Stack *stack);
Tree* Stack_peek(Stack *stack);

BOOL Stack_isEmpty(Stack *stack);

#endif