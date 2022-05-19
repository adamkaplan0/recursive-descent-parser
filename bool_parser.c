/*
 * File: bool_parser.c
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#include "bool_parser.h"

/*
Setter functions
*/
void B_setINPUT(char *input) {
	B_INPUT = input;
}

/*
Driver functions
*/
char B_lookahead() {
	return B_INPUT[0];
}

BOOL B_matchTerminal(char *terminal) {
	//Case: Single character terminal
	if(terminal[1] == '\0') {
		if(B_INPUT[0] == terminal[0]) {
			B_INPUT++;
			return TRUE;
		}
		return FALSE;
	}
	//Case: Multiple character terminal
	else {
		int c = 0;

		while(B_INPUT[c] == terminal[c] && (B_INPUT[c] != '\0' || terminal[c] != '\0'))
			c++;
		if(terminal[c] == '\0') {
			for(int i = 0; i < c; i++)
				B_INPUT++;

			return TRUE;
		}

		return FALSE;
	}
}

/*
Production functions
*/
BOOL B_E() {
	if(!B_T())
		return FALSE;
	if(!B_ET())
		return FALSE;

	return TRUE;
}

BOOL B_ET() {
	if(B_lookahead() == '+') {
		if(!B_matchTerminal("+"))
			return FALSE;

		if(!B_T())
			return FALSE;
		if(!B_ET())
			return FALSE;

		return TRUE;
	}
	else if(B_lookahead() == '-') {
		if(!B_matchTerminal("-"))
			return FALSE;

		if(!B_T())
			return FALSE;
		if(!B_ET())
			return FALSE;

		return TRUE;
	}

	return TRUE;
}

BOOL B_T() {
	if(!B_F())
		return FALSE;
	if(!B_TT())
		return FALSE;

	return TRUE;
}

BOOL B_TT() {
	if(B_lookahead() == '*') {
		if(!B_matchTerminal("*"))
			return FALSE;

		if(!B_F())
			return FALSE;
		if(!B_TT())
			return FALSE;

		return TRUE;
	}
	else if(B_lookahead() == '/') {
		if(!B_matchTerminal("/"))
			return FALSE;

		if(!B_F())
			return FALSE;
		if(!B_TT())
			return FALSE;

		return TRUE;
	}

	return TRUE;
}

BOOL B_F() {
	if(!B_OS())
		return FALSE;
	if(!B_PF())
		return FALSE;
	if(!B_FT())
		return FALSE;

	return TRUE;
}

BOOL B_OS() {
	if(B_lookahead() == '-') {
		if(!B_matchTerminal("-"))
			return FALSE;
		return TRUE;
	}

	return TRUE;
}

BOOL B_PF() {
	if(B_lookahead() == 's') {
		if(!B_matchTerminal("sin("))
			return FALSE;
		if(!B_E())
			return FALSE;
		if(!B_matchTerminal(")"))
			return FALSE;

		return TRUE;
	}
	else if(B_lookahead() == 'c') {
		if(!B_matchTerminal("cos("))
			return FALSE;
		if(!B_E())
			return FALSE;
		if(!B_matchTerminal(")"))
			return FALSE;

		return TRUE;
	}
	else if(B_lookahead() == 't') {
		if(!B_matchTerminal("tan("))
			return FALSE;
		if(!B_E())
			return FALSE;
		if(!B_matchTerminal(")"))
			return FALSE;

		return TRUE;
	}
	else if(B_lookahead() == 'l') {
		if(!B_matchTerminal("log("))
			return FALSE;
		if(!B_E())
			return FALSE;
		if(!B_matchTerminal(")"))
			return FALSE;

		return TRUE;
	}
	else {
		if(!B_S())
			return FALSE;

		return TRUE;
	}
}

BOOL B_S() {
	if(B_lookahead() == '(') {
		if(!B_matchTerminal("("))
			return FALSE;
		if(!B_E())
			return FALSE;
		if(!B_matchTerminal(")"))
			return FALSE;

		return TRUE;
	}
	else if(B_lookahead() == '[') {
		if(!B_matchTerminal("["))
			return FALSE;
		if(!B_E())
			return FALSE;
		if(!B_matchTerminal("]"))
			return FALSE;

		return TRUE;
	}
	else if(B_lookahead() == '[') {
		if(!B_matchTerminal("["))
			return FALSE;
		if(!B_E())
			return FALSE;
		if(!B_matchTerminal("]"))
			return FALSE;

		return TRUE;
	}
	else {
		if(!B_N())
			return FALSE;
		return TRUE;
	}
}

BOOL B_FT() {
	if(B_lookahead() == '!') {
		if(!B_matchTerminal("!"))
			return FALSE;

		if(!B_FT())
			return FALSE;

		return TRUE;
	}
	else if(B_lookahead() == '^') {
		if(!B_matchTerminal("^"))
			return FALSE;

		if(!B_S())
			return FALSE;
		if(!B_FT())
			return FALSE;

		return TRUE;
	}

	return TRUE;
}

BOOL B_N() {
	if(!B_D())
		return FALSE;
	if(!B_NT())
		return FALSE;

	return TRUE;
}

BOOL B_NT() {
	if(B_lookahead() == '.') {
		if(!B_matchTerminal("."))
			return FALSE;

		if(!B_NTT())
			return FALSE;
		
		return TRUE;
	}
	else {
		if(!B_N())
			return TRUE;

		return TRUE;
	}
}

BOOL B_NTT(){
	if(!B_D())
		return FALSE;
	if(!B_NTTT())
		return FALSE;

	return TRUE;
}

BOOL B_NTTT() {
	if(!B_NTT())
		return TRUE;

	return TRUE;
}

BOOL B_D() {
	if(B_matchTerminal("0") || B_matchTerminal("1") || B_matchTerminal("2") || B_matchTerminal("3") || B_matchTerminal("4")
			|| B_matchTerminal("5") || B_matchTerminal("6") || B_matchTerminal("7") || B_matchTerminal("8")
			|| B_matchTerminal("9")) {
		return TRUE;
	}

	return FALSE;
}

/*
Parsing function
*/
BOOL B_parse(char *input, BOOL (*parser_function)(void)) {
	B_setINPUT(input);

	if(!(*parser_function)())
		return FALSE;
	else {
		if(B_INPUT[0] == '\0')
			return TRUE;
		return FALSE;
	}
}