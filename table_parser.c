/*
 * File: table_parser.c
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#include "table_parser.h"

/*
Driver functions
*/
void T_setINPUT(char *input) {
	T_INPUT = input;
}

char T_lookahead() {
	return T_INPUT[0];
}

BOOL T_lookaheadDigit() {
	return (T_lookahead() == '0' || T_lookahead() == '1' || T_lookahead() == '2' || T_lookahead() == '3' || T_lookahead() == '4'
		|| T_lookahead() == '5' || T_lookahead() == '6' || T_lookahead() == '7' || T_lookahead() == '8' || T_lookahead() == '9');
}

Tree* T_matchTerminal(char *terminal) {
	//Case: Single character terminal
	if(terminal[1] == '\0') {
		if(T_INPUT[0] == terminal[0]) {
			T_INPUT++;
			Tree *tree = Tree_new(TRUE, terminal, terminal);

			return tree;
		}
		return NULL;
	}
	//Case: Multiple character terminal
	else {
		int c = 0;

		while(T_INPUT[c] == terminal[c] && (T_INPUT[c] != '\0' || terminal[c] != '\0'))
			c++;
		if(terminal[c] == '\0') {
			for(int i = 0; i < c; i++)
				T_INPUT++;

			Tree *tree = Tree_new(TRUE, terminal, terminal);

			return tree;
		}

		return NULL;
	}
}

/*
Parsing functions
*/
Tree* T_raw_parser(Stack *stack, Tree *tree) {
	if(strcmp(Stack_peek(stack)->root->label, "<Expression>") == 0) {
		//Push the expression off the stack
		Stack_pop(stack);

		if(T_lookahead() == '-' || T_lookaheadDigit() || T_lookahead() == 's' || T_lookahead() == 'c'
			|| T_lookahead() == 't' || T_lookahead() == 'l' || T_lookahead() == '(' || T_lookahead() == '['
			|| T_lookahead() == '{') {
			Tree *T = Tree_new(FALSE, "<Term>", "");
			Tree *ET = Tree_new(FALSE, "<Expression Tail>", "");

			Stack_push(stack, ET);
			Stack_push(stack, T);

			Tree *Tparsed = T_raw_parser(stack, T);
			Tree *ETparsed = T_raw_parser(stack, ET);

			if(Tparsed == NULL || ETparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Tparsed);
				Tree_addSubTree(tree->root, ETparsed);

				return tree;
			}
		}
		else return NULL;
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Expression Tail>") == 0) {
		//Push the expression tail off the stack
		Stack_pop(stack);

		if(T_lookahead() == '+') {
			Tree_addSubTree(tree->root, T_matchTerminal("+"));

			Tree *T = Tree_new(FALSE, "<Term>", "");
			Tree *ET = Tree_new(FALSE, "<Expression Tail>", "");

			Stack_push(stack, ET);
			Stack_push(stack, T);

			Tree *Tparsed = T_raw_parser(stack, T);
			Tree *ETparsed = T_raw_parser(stack, ET);

			if(Tparsed == NULL || ETparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Tparsed);
				Tree_addSubTree(tree->root, ETparsed);

				return tree;
			}
		}
		else if(T_lookahead() == '-') {
			Tree_addSubTree(tree->root, T_matchTerminal("-"));

			Tree *T = Tree_new(FALSE, "<Term>", "");
			Tree *ET = Tree_new(FALSE, "<Expression Tail>", "");

			Stack_push(stack, ET);
			Stack_push(stack, T);

			Tree *Tparsed = T_raw_parser(stack, T);
			Tree *ETparsed = T_raw_parser(stack, ET);

			if(Tparsed == NULL || ETparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Tparsed);
				Tree_addSubTree(tree->root, ETparsed);

				return tree;
			}
		}
		else {
			Tree *Epsilon = Tree_new(FALSE, "<Epsilon>", "");

			Tree_addSubTree(tree->root, Epsilon);

			return tree;
		}
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Term>") == 0) {
		//Push the term off the stack
		Stack_pop(stack);

		if(T_lookahead() == '-' || T_lookaheadDigit() || T_lookahead() == 's' || T_lookahead() == 'c'
			|| T_lookahead() == 't' || T_lookahead() == 'l' || T_lookahead() == '(' || T_lookahead() == '['
			|| T_lookahead() == '{') {

			Tree *F = Tree_new(FALSE, "<Factor>", "");
			Tree *TT = Tree_new(FALSE, "<Term Tail>", "");

			Stack_push(stack, TT);
			Stack_push(stack, F);

			Tree *Fparsed = T_raw_parser(stack, F);
			Tree *TTparsed = T_raw_parser(stack, TT);

			if(Fparsed == NULL || TTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Fparsed);
				Tree_addSubTree(tree->root, TTparsed);

				return tree;
			}
		}
		else return NULL;
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Term Tail>") == 0) {
		//Push the term tail off the stack
		Stack_pop(stack);

		if(T_lookahead() == '*') {
			Tree_addSubTree(tree->root, T_matchTerminal("*"));

			Tree *F = Tree_new(FALSE, "<Factor>", "");
			Tree *TT = Tree_new(FALSE, "<Term Tail>", "");

			Stack_push(stack, TT);
			Stack_push(stack, F);

			Tree *Fparsed = T_raw_parser(stack, F);
			Tree *TTparsed = T_raw_parser(stack, TT);

			if(Fparsed == NULL || TTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Fparsed);
				Tree_addSubTree(tree->root, TTparsed);

				return tree;
			}
		}
		else if(T_lookahead() == '/') {
			Tree_addSubTree(tree->root, T_matchTerminal("/"));

			Tree *F = Tree_new(FALSE, "<Factor>", "");
			Tree *TT = Tree_new(FALSE, "<Term Tail>", "");

			Stack_push(stack, TT);
			Stack_push(stack, F);

			Tree *Fparsed = T_raw_parser(stack, F);
			Tree *TTparsed = T_raw_parser(stack, TT);

			if(Fparsed == NULL || TTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Fparsed);
				Tree_addSubTree(tree->root, TTparsed);

				return tree;
			}
		}
		else {
			Tree *Epsilon = Tree_new(FALSE, "<Epsilon>", "");

			Tree_addSubTree(tree->root, Epsilon);

			return tree;
		}
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Factor>") == 0) {
		//Push the factor off the stack
		Stack_pop(stack);

		if(T_lookahead() == '-' || T_lookaheadDigit() || T_lookahead() == 's' || T_lookahead() == 'c'
			|| T_lookahead() == 't' || T_lookahead() == 'l' || T_lookahead() == '(' || T_lookahead() == '['
			|| T_lookahead() == '{') {

			Tree *OS = Tree_new(FALSE, "<Optional Sign>", "");
			Tree *PF = Tree_new(FALSE, "<Prefix Function>", "");
			Tree *FT = Tree_new(FALSE, "<Factor Tail>", "");

			Stack_push(stack, FT);
			Stack_push(stack, PF);
			Stack_push(stack, OS);

			Tree *OSparsed = T_raw_parser(stack, OS);
			Tree *PFparsed = T_raw_parser(stack, PF);
			Tree *FTparsed = T_raw_parser(stack, FT);

			if(OSparsed == NULL || PFparsed == NULL || FTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, OSparsed);
				Tree_addSubTree(tree->root, PFparsed);
				Tree_addSubTree(tree->root, FTparsed);

				return tree;
			}
		}
		else return NULL;
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Prefix Function>") == 0) {
		//Push the prefix function off the stack
		Stack_pop(stack);

		if(T_lookahead() == 's') {
			Tree *terminal = T_matchTerminal("sin(");

			if(terminal == NULL)
				return NULL;

			Tree_addSubTree(tree->root, terminal);

			Tree *E = Tree_new(FALSE, "<Expression>", "");

			Stack_push(stack, E);

			Tree *Eparsed = T_raw_parser(stack, E);

			if(Eparsed == NULL) {
				return NULL;
			}
			else {
				Tree *terminal2 = T_matchTerminal(")");

				if(terminal2 == NULL)
					return NULL;

				Tree_addSubTree(tree->root, Eparsed);
				Tree_addSubTree(tree->root, terminal2);
				return tree;
			}
		}
		else if(T_lookahead() == 'c') {
			Tree *terminal = T_matchTerminal("cos(");

			if(terminal == NULL)
				return NULL;

			Tree_addSubTree(tree->root, terminal);

			Tree *E = Tree_new(FALSE, "<Expression>", "");

			Stack_push(stack, E);

			Tree *Eparsed = T_raw_parser(stack, E);

			if(Eparsed == NULL) {
				return NULL;
			}
			else {
				Tree *terminal2 = T_matchTerminal(")");

				if(terminal2 == NULL)
					return NULL;

				Tree_addSubTree(tree->root, Eparsed);
				Tree_addSubTree(tree->root, terminal2);

				return tree;
			}
		}
		else if(T_lookahead() == 't') {
			Tree *terminal = T_matchTerminal("tan(");

			if(terminal == NULL)
				return NULL;

			Tree_addSubTree(tree->root, terminal);

			Tree *E = Tree_new(FALSE, "<Expression>", "");

			Stack_push(stack, E);

			Tree *Eparsed = T_raw_parser(stack, E);

			if(Eparsed == NULL) {
				return NULL;
			}
			else {
				Tree *terminal2 = T_matchTerminal(")");

				if(terminal2 == NULL)
					return NULL;

				Tree_addSubTree(tree->root, Eparsed);
				Tree_addSubTree(tree->root, terminal2);

				return tree;
			}
		}
		else if(T_lookahead() == 'l') {
			Tree *terminal = T_matchTerminal("log(");

			if(terminal == NULL)
				return NULL;

			Tree_addSubTree(tree->root, terminal);

			Tree *E = Tree_new(FALSE, "<Expression>", "");

			Stack_push(stack, E);

			Tree *Eparsed = T_raw_parser(stack, E);

			if(Eparsed == NULL) {
				return NULL;
			}
			else {
				Tree *terminal2 = T_matchTerminal(")");

				if(terminal2 == NULL)
					return NULL;

				Tree_addSubTree(tree->root, Eparsed);
				Tree_addSubTree(tree->root, terminal2);

				return tree;
			}
		}
		else if(T_lookaheadDigit() || T_lookahead() == '(' || T_lookahead() == '['
			|| T_lookahead() == '{'){
			Tree *S = Tree_new(FALSE, "<Standard Expression>", "");

			Stack_push(stack, S);

			Tree *Sparsed = T_raw_parser(stack, S);

			if(Sparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Sparsed);

				return tree;
			}
		}
		else return NULL;
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Optional Sign>") == 0) {
		//Push the optional sign off the stack
		Stack_pop(stack);

		if(T_lookahead() == '-') {
			Tree_addSubTree(tree->root, T_matchTerminal("-"));

			return tree;
		}
		else {
			Tree *Epsilon = Tree_new(FALSE, "<Epsilon>", "");

			Tree_addSubTree(tree->root, Epsilon);

			return tree;
		}
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Factor Tail>") == 0) {
		//Push the factor tail off the stack
		Stack_pop(stack);

		if(T_lookahead() == '!') {
			Tree_addSubTree(tree->root, T_matchTerminal("!"));

			Tree *FT = Tree_new(FALSE, "<Factor Tail>", "");

			Stack_push(stack, FT);

			Tree *FTparsed = T_raw_parser(stack, FT);

			if(FTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, FTparsed);

				return tree;
			}
		}
		else if(T_lookahead() == '^') {
			Tree_addSubTree(tree->root, T_matchTerminal("^"));

			Tree *S = Tree_new(FALSE, "<Standard Expression>", "");
			Tree *FT = Tree_new(FALSE, "<Factor Tail>", "");

			Stack_push(stack, FT);
			Stack_push(stack, S);

			Tree *Sparsed = T_raw_parser(stack, S);
			Tree *FTparsed = T_raw_parser(stack, FT);

			if(FTparsed == NULL || Sparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Sparsed);
				Tree_addSubTree(tree->root, FTparsed);

				return tree;
			}
		}
		else {
			Tree *Epsilon = Tree_new(FALSE, "<Epsilon>", "");

			Tree_addSubTree(tree->root, Epsilon);

			return tree;
		}
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Standard Expression>") == 0) {
		//Push the standard expression off the stack
		Stack_pop(stack);

		if(T_lookahead() == '(') {
			Tree_addSubTree(tree->root, T_matchTerminal("("));

			Tree *E = Tree_new(FALSE, "<Expression>", "");

			Stack_push(stack, E);

			Tree *Eparsed = T_raw_parser(stack, E);

			if(Eparsed == NULL) {

				return NULL;
			}
			else {
				Tree *terminal = T_matchTerminal(")");

				if(terminal == NULL) {

					return NULL;
				}

				Tree_addSubTree(tree->root, Eparsed);
				Tree_addSubTree(tree->root, terminal);
				return tree;
			}
		}
		else if(T_lookahead() == '[') {
			Tree_addSubTree(tree->root, T_matchTerminal("["));

			Tree *E = Tree_new(FALSE, "<Expression>", "");

			Stack_push(stack, E);

			Tree *Eparsed = T_raw_parser(stack, E);

			if(Eparsed == NULL) {
				return NULL;
			}
			else {
				Tree *terminal = T_matchTerminal("]");

				if(terminal == NULL) {
					return NULL;
				}

				Tree_addSubTree(tree->root, Eparsed);
				Tree_addSubTree(tree->root, terminal);
				return tree;
			}
		}
		else if(T_lookahead() == '{') {
			Tree_addSubTree(tree->root, T_matchTerminal("{"));

			Tree *E = Tree_new(FALSE, "<Expression>", "");

			Stack_push(stack, E);

			Tree *Eparsed = T_raw_parser(stack, E);

			if(Eparsed == NULL) {
				return NULL;
			}
			else {
				Tree *terminal = T_matchTerminal("}");

				if(terminal == NULL) {
					return NULL;
				}

				Tree_addSubTree(tree->root, Eparsed);
				Tree_addSubTree(tree->root, terminal);
				return tree;
			}
		}
		else if(T_lookaheadDigit()){
			Tree *N = Tree_new(FALSE, "<Number>", "");

			Stack_push(stack, N);

			Tree *Nparsed = T_raw_parser(stack, N);

			if(Nparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Nparsed);
				return tree;
			}
		}
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Number>") == 0) {
		//Push the number off the stack
		Stack_pop(stack);

		if(T_lookaheadDigit()) {
			Tree *D = Tree_new(FALSE, "<Digit>", "");
			Tree *NT = Tree_new(FALSE, "<Number Tail>", "");

			Stack_push(stack, NT);
			Stack_push(stack, D);
			Tree *Dparsed = T_raw_parser(stack, D);
			Tree *NTparsed = T_raw_parser(stack, NT);

			if(Dparsed == NULL || NTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Dparsed);
				Tree_addSubTree(tree->root, NTparsed);

				return tree;
			}
			
		}
		else return NULL;
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Number Tail>") == 0) {
		//Push the number tail off the stack
		Stack_pop(stack);
		if(T_lookahead() == '.') {
			Tree_addSubTree(tree->root, T_matchTerminal("."));

			Tree *NTT = Tree_new(FALSE, "<Number Tail Tail>", "");

			Stack_push(stack, NTT);

			Tree *NTTparsed = T_raw_parser(stack, NTT);

			if(NTTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, NTTparsed);

				return tree;
			}
			
		}
		else if(T_lookaheadDigit()) {
			Tree *N = Tree_new(FALSE, "<Number>", "");

			//Push the number onto the stack;
			Stack_push(stack, N);

			Tree *Nparsed = T_raw_parser(stack, N);

			if(Nparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Nparsed);

				return tree;
			}
		}
		else {
			Tree *Epsilon = Tree_new(FALSE, "<Epsilon>", "");

			Tree_addSubTree(tree->root, Epsilon);

			return tree;
		}
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Number Tail Tail>") == 0) {
		//Push the number tail tail off the stack
		Stack_pop(stack);

		if(T_lookaheadDigit()) {
			Tree *D = Tree_new(FALSE, "<Digit>", "");
			Tree *NTTT = Tree_new(FALSE, "<Number Tail Tail Tail>", "");

			Stack_push(stack, NTTT);
			Stack_push(stack, D);

			Tree *Dparsed = T_raw_parser(stack, D);
			Tree *NTTTparsed = T_raw_parser(stack, NTTT);

			if(Dparsed == NULL || NTTTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, Dparsed);
				Tree_addSubTree(tree->root, NTTTparsed);

				return tree;
			}
			
		}
		else return NULL;
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Number Tail Tail Tail>") == 0) {
		//Push the number tail tail tail off the stack
		Stack_pop(stack);

		if(T_lookaheadDigit()) {
			Tree *NTT = Tree_new(FALSE, "<Number Tail Tail>", "");

			//Push the number onto the stack;
			Stack_push(stack, NTT);

			Tree *NTTparsed = T_raw_parser(stack, NTT);

			if(NTTparsed == NULL) {
				return NULL;
			}
			else {
				Tree_addSubTree(tree->root, NTTparsed);

				return tree;
			}
			
		}
		else {
			Tree *Epsilon = Tree_new(FALSE, "<Epsilon>", "");

			Tree_addSubTree(tree->root, Epsilon);

			return tree;
		}
	}
	else if(strcmp(Stack_peek(stack)->root->label, "<Digit>") == 0) {
		//Push the digit off the stack
		Stack_pop(stack);
		if(T_lookahead() == '0') {
			Tree_addSubTree(tree->root, T_matchTerminal("0"));

			return tree;
		}
		else if(T_lookahead() == '1') {
			Tree_addSubTree(tree->root, T_matchTerminal("1"));

			return tree;
		}
		else if(T_lookahead() == '2') {
			Tree_addSubTree(tree->root, T_matchTerminal("2"));

			return tree;
		}
		else if(T_lookahead() == '3') {
			Tree_addSubTree(tree->root, T_matchTerminal("3"));

			return tree;
		}
		else if(T_lookahead() == '4') {
			Tree_addSubTree(tree->root, T_matchTerminal("4"));

			return tree;
		}
		else if(T_lookahead() == '5') {
			Tree_addSubTree(tree->root, T_matchTerminal("5"));

			return tree;
		}
		else if(T_lookahead() == '6') {
			Tree_addSubTree(tree->root, T_matchTerminal("6"));

			return tree;
		}
		else if(T_lookahead() == '7') {
			Tree_addSubTree(tree->root, T_matchTerminal("7"));

			return tree;
		}
		else if(T_lookahead() == '8') {
			Tree_addSubTree(tree->root, T_matchTerminal("8"));

			return tree;
		}
		else if(T_lookahead() == '9') {
			Tree_addSubTree(tree->root, T_matchTerminal("9"));

			return tree;
		}
		else return NULL;
	}

	return NULL;
}

Tree* T_parse(char *input) {
	//Initialization
	T_setINPUT(input);
	Tree *E = Tree_new(FALSE, "<Expression>", "");
	Tree *result = E;
	Stack *stack = Stack_new(E);

	Tree *test = T_raw_parser(stack, result);

	if(test == NULL) {
		//printf("The parsing failed.\n");
		return NULL;
	}
	else
		return result;
}