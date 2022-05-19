/*
 * File: stack.c
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#include "stack.h"

/*
Memory allocation functions
*/
Stack* salloc() {
	return (Stack*)(malloc(sizeof(Stack)));
}

Element* ealloc() {
	return (Element*)(malloc(sizeof(Element)));
}

/*
Initialization functions
*/
Stack* Stack_new(Tree *data) {
	Stack *stack = salloc();

	stack->top = Element_new(data);

	return stack;
}

Element* Element_new(Tree *data) {
	Element *element = ealloc();

	element->data = data;
	element->next = NULL;

	return element;
}

/*
Data manipulation functions
*/
void Stack_push(Stack *stack, Tree *data) {
	Element *current = stack->top;

	Element *element = Element_new(data);
	element->next = current;
	stack->top = element;
}

Tree* Stack_pop(Stack *stack) {
	Element *element = stack->top;

	if(stack->top->next == NULL)
		stack->top = NULL;
	else
		stack->top = stack->top->next;
	return element->data;
}

Tree* Stack_peek(Stack *stack) {
	return stack->top->data;
}

BOOL Stack_isEmpty(Stack *stack) {
	return stack->top == NULL;
}