/*
 * File: table_parser.h
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#ifndef TABLE_PARSER
#define TABLE_PARSER

#include "stack.h"

char *T_INPUT;

/*
Driver functions
*/
void T_setINPUT(char *input);
char T_lookahead();
Tree* T_matchTerminal(char *terminal);

/*
Parsing functions
*/
Tree* T_raw_parser(Stack *stack, Tree *tree);
Tree* T_parse(char *input);

#endif