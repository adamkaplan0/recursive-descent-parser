/*
 * File: recursive_parser.h
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#ifndef RECURSIVE_PARSER
#define RECURSIVE_PARSER

#include "declarations.h"
#include "bool_parser.h"
#include "parse_tree.h"

/*
Important variables
*/
char *R_INPUT;
Tree *R_parse_tree;
char *res;

/*
Setter functions
*/
void R_setINPUT(char *input);

/*
Driver functions
*/
char R_lookahead();
Tree* R_matchTerminal(char *terminal);

/*
Production functions
*/
Tree* R_E();	//Expression
Tree* R_ET();	//Expression Tail
Tree* R_T();	//Term
Tree* R_TT();	//Term Tail
Tree* R_F();	//Factor
Tree* R_FT();	//Factor Tail
Tree* R_OS();	//Optional Sign
Tree* R_PF();	//Prefix Function
Tree* R_S();	//Standard expression
Tree* R_N();	//Number
Tree* R_NT();	//Number Tail
Tree* R_NTT();	//Number Tail Tail
Tree* R_NTTT();	//Number Tail Tail Tail
Tree* R_D();	//Digit

/*
Parsing function
*/
Tree* R_parse(char *input, Tree* (*R_parser_function)(void));

#endif