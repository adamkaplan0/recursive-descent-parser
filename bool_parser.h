/*
 * File: bool_parser.h
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#ifndef BOOL_PARSER
#define BOOL_PARSER

#include "declarations.h"

/*
Important variables
*/
char *B_INPUT;

/*
Setter functions
*/
void B_setINPUT(char *input);

/*
Driver functions
*/
char B_lookahead();
BOOL B_matchTerminal(char *terminal);

/*
Production functions
*/
BOOL B_E();		//Expression
BOOL B_ET();	//Expression Tail
BOOL B_T();		//Term
BOOL B_TT();	//Term Tail
BOOL B_F();		//Factor
BOOL B_FT();	//Factor Tail
BOOL B_OS();	//Optional Sign
BOOL B_PF();	//Prefix Function
BOOL B_S();		//Standard expression
BOOL B_N();		//Number
BOOL B_NT();	//Number Tail
BOOL B_NTT();	//Number Tail Tail
BOOL B_NTTT();	//Number Tail Tail Tail
BOOL B_D();		//Digit

/*
Parsing function
*/
BOOL B_parse(char *input, BOOL (*parser_function)(void));

#endif