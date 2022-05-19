/*
 * File: recursive_parser.c
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#include "recursive_parser.h"

/*
Setter functions
*/
void R_setINPUT(char *input) {
	R_INPUT = input;
}

/*
Driver functions
*/
char R_lookahead() {
	return R_INPUT[0];
}

Tree* R_matchTerminal(char *terminal) {
	//Case: Single character terminal
	if(terminal[1] == '\0') {
		if(R_INPUT[0] == terminal[0]) {
			R_INPUT++;
			Tree *tree = Tree_new(TRUE, terminal, terminal);

			return tree;
		}
		return NULL;
	}
	//Case: Multiple character terminal
	else {
		int c = 0;

		while(R_INPUT[c] == terminal[c] && (R_INPUT[c] != '\0' || terminal[c] != '\0'))
			c++;
		if(terminal[c] == '\0') {
			for(int i = 0; i < c; i++)
				R_INPUT++;

			Tree *tree = Tree_new(TRUE, terminal, terminal);

			return tree;
		}

		return NULL;
	}
}

/*
Production functions
*/
Tree* R_E() {
	Tree *E = Tree_new(FALSE, "<Expression>", "");

	Tree *t = R_T();

	if(t == NULL)
		return NULL;

	Tree *et = R_ET();

	if(et == NULL)
		return NULL;

	Tree_addSubTree(E->root, t);
	Tree_addSubTree(E->root, et);

	return E;
}

Tree* R_ET() {
	Tree *ET = Tree_new(FALSE, "<Expression Tail>", "");
	if(R_lookahead() == '+') {
		Tree *t1 = R_matchTerminal("+");

		if(t1 == NULL)
			return NULL;

		Tree *t = R_T();

		if(t == NULL)
			return NULL;

		Tree *et = R_ET();

		if(et == NULL)
			return NULL;

		Tree_addSubTree(ET->root, t1);
		Tree_addSubTree(ET->root, t);
		Tree_addSubTree(ET->root, et);
	}
	else if(R_lookahead() == '-') {
		Tree *t1 = R_matchTerminal("-");

		if(t1 == NULL)
			return NULL;

		Tree *t = R_T();

		if(t == NULL)
			return NULL;

		Tree *et = R_ET();

		if(et == NULL)
			return NULL;

		Tree_addSubTree(ET->root, t1);
		Tree_addSubTree(ET->root, t);
		Tree_addSubTree(ET->root, et);
	} 
	else
		Tree_addChild(ET->root, FALSE, "<Epsilon>", "");
	return ET;
}

Tree* R_T() {
	Tree *T = Tree_new(FALSE, "<Term>", "");

	Tree *f = R_F();

	if(f == NULL)
		return NULL;

	Tree *tt = R_TT();

	if(tt == NULL)
		return NULL;

	Tree_addSubTree(T->root, f);
	Tree_addSubTree(T->root, tt);

	return T;
}

Tree* R_TT() {
	Tree *TT = Tree_new(FALSE, "<Term Tail>", "");
	if(R_lookahead() == '*') {
		Tree *t1 = R_matchTerminal("*");

		if(t1 == NULL)
			return NULL;

		Tree *f = R_F();

		if(f == NULL)
			return NULL;

		Tree *tt = R_TT();

		if(tt == NULL)
			return NULL;

		Tree_addSubTree(TT->root, t1);
		Tree_addSubTree(TT->root, f);
		Tree_addSubTree(TT->root, tt);
	}
	else if(R_lookahead() == '/') {
		Tree *t1 = R_matchTerminal("/");

		if(t1 == NULL)
			return NULL;

		Tree *f = R_F();

		if(f == NULL)
			return NULL;

		Tree *tt = R_TT();

		if(tt == NULL)
			return NULL;

		Tree_addSubTree(TT->root, t1);
		Tree_addSubTree(TT->root, f);
		Tree_addSubTree(TT->root, tt);
	} 
	else
		Tree_addChild(TT->root, FALSE, "<Epsilon>", "");
	return TT;
}

Tree* R_F() {
	Tree *F = Tree_new(FALSE, "<Factor>", "");

	Tree *os = R_OS();

	if(os == NULL)
		return NULL;

	Tree *pf = R_PF();

	if(pf == NULL)
		return NULL;

	Tree *ft = R_FT();

	if(ft == NULL)
		return NULL;

	Tree_addSubTree(F->root, os);
	Tree_addSubTree(F->root, pf);
	Tree_addSubTree(F->root, ft);
	return F;
}

Tree* R_FT() {
	Tree *FT = Tree_new(FALSE, "<Factor Tail>", "");
	if(R_lookahead() == '!') {
		Tree *t1 = R_matchTerminal("!");

		if(t1 == NULL)
			return NULL;

		Tree *ft = R_FT();

		if(ft == NULL)
			return NULL;

		Tree_addSubTree(FT->root, t1);
		Tree_addSubTree(FT->root, ft);

	}
	else if(R_lookahead() == '^') {
		Tree *t1 = R_matchTerminal("^");

		if(t1 == NULL)
			return NULL;

		Tree *s = R_S();

		if(s == NULL)
			return NULL;

		Tree *ft = R_FT();

		if(ft == NULL)
			return NULL;

		Tree_addSubTree(FT->root, t1);
		Tree_addSubTree(FT->root, s);
		Tree_addSubTree(FT->root, ft);
	} 
	else
		Tree_addChild(FT->root, FALSE, "<Epsilon>", "");
	return FT;
}

Tree* R_OS() {
	Tree *OS = Tree_new(FALSE, "<Optional Sign>", "");
	if(R_lookahead() == '-') {
		Tree *t1 = R_matchTerminal("-");

		if(t1 == NULL)
			return NULL;

		Tree_addSubTree(OS->root, t1);
	}
	else
		Tree_addChild(OS->root, FALSE, "<Epsilon>", "");
	return OS;
}

Tree* R_PF() {
	if(R_lookahead() == 's') {
		Tree *PF = Tree_new(FALSE, "<Prefix Function>", "");

		Tree *t1 = R_matchTerminal("sin(");

		if(t1 == NULL)
			return NULL;

		Tree *E = R_E();

		if(E == NULL)
			return NULL;

		Tree *t2 = R_matchTerminal(")");

		if(t2 == NULL)
			return NULL;

		Tree_addSubTree(PF->root, t1);
		Tree_addSubTree(PF->root, E);
		Tree_addSubTree(PF->root, t2);

		return PF;
	}
	else if(R_lookahead() == 'c') {
		Tree *PF = Tree_new(FALSE, "<Prefix Function>", "");

		Tree *t1 = R_matchTerminal("cos(");

		if(t1 == NULL)
			return NULL;

		Tree *E = R_E();

		if(E == NULL)
			return NULL;

		Tree *t2 = R_matchTerminal(")");

		if(t2 == NULL)
			return NULL;

		Tree_addSubTree(PF->root, t1);
		Tree_addSubTree(PF->root, E);
		Tree_addSubTree(PF->root, t2);

		return PF;
	}
	else if(R_lookahead() == 't') {
		Tree *PF = Tree_new(FALSE, "<Prefix Function>", "");

		Tree *t1 = R_matchTerminal("tan(");

		if(t1 == NULL)
			return NULL;

		Tree *E = R_E();

		if(E == NULL)
			return NULL;

		Tree *t2 = R_matchTerminal(")");

		if(t2 == NULL)
			return NULL;

		Tree_addSubTree(PF->root, t1);
		Tree_addSubTree(PF->root, E);
		Tree_addSubTree(PF->root, t2);

		return PF;
	}
	else if(R_lookahead() == 'l') {
		Tree *PF = Tree_new(FALSE, "<Prefix Function>", "");

		Tree *t1 = R_matchTerminal("log(");

		if(t1 == NULL)
			return NULL;

		Tree *E = R_E();

		if(E == NULL)
			return NULL;

		Tree *t2 = R_matchTerminal(")");

		if(t2 == NULL)
			return NULL;

		Tree_addSubTree(PF->root, t1);
		Tree_addSubTree(PF->root, E);
		Tree_addSubTree(PF->root, t2);

		return PF;
	}
	else {
		Tree *PF = Tree_new(FALSE, "<Prefix Function>", "");

		Tree *S = R_S();

		if(S == NULL)
			return NULL;

		Tree_addSubTree(PF->root, S);
		return PF;
	}
}

Tree* R_S() {
	if(R_lookahead() == '(') {
		Tree *S = Tree_new(FALSE, "<Standard Expression>", "");
		Tree *t1 = R_matchTerminal("(");

		if(t1 == NULL)
			return NULL;

		Tree *E = R_E();

		if(E == NULL)
			return NULL;

		Tree *t2 = R_matchTerminal(")");

		if(t2 == NULL)
			return NULL;

		Tree_addSubTree(S->root, t1);
		Tree_addSubTree(S->root, E);
		Tree_addSubTree(S->root, t2);

		return S;
	}
	else if(R_lookahead() == '[') {
		Tree *S = Tree_new(FALSE, "<Standard Expression>", "");
		Tree *t1 = R_matchTerminal("[");

		if(t1 == NULL)
			return NULL;

		Tree *E = R_E();

		if(E == NULL)
			return NULL;

		Tree *t2 = R_matchTerminal("]");

		if(t2 == NULL)
			return NULL;

		Tree_addSubTree(S->root, t1);
		Tree_addSubTree(S->root, E);
		Tree_addSubTree(S->root, t2);

		return S;
	}
	else if(R_lookahead() == '{') {
		Tree *S = Tree_new(FALSE, "<Standard Expression>", "");
		Tree *t1 = R_matchTerminal("{");

		if(t1 == NULL)
			return NULL;

		Tree *E = R_E();

		if(E == NULL)
			return NULL;

		Tree *t2 = R_matchTerminal("}");

		if(t2 == NULL)
			return NULL;

		Tree_addSubTree(S->root, t1);
		Tree_addSubTree(S->root, E);
		Tree_addSubTree(S->root, t2);

		return S;
	}
	else if(R_lookahead() != '\0') {
		Tree *S = Tree_new(FALSE, "<Standard Expression>", "");
		Tree *N = R_N();

		if(N == NULL)
			return NULL;
		Tree_addSubTree(S->root, N);
		return S;
	}

	return NULL;
}

Tree* R_N() {
	//printf("Number\n");
	if(R_lookahead() != '\0') {
		//printf("Good number\n");
		Tree *D = R_D();
		

		if(D == NULL)
			return NULL;
		Tree *NT = R_NT();
		Tree *N = Tree_new(FALSE, "<Number>", "");
		Tree_addSubTree(N->root, D);
		Tree_addSubTree(N->root, NT);
		return N;
	}
	return NULL;
}

Tree* R_NT() {
	Tree *NT = Tree_new(FALSE, "<Number Tail>", "");

	if(R_lookahead() == '.') {
		Tree *t1 = R_matchTerminal(".");
		if(t1 == NULL)
			return NULL;

		Tree *ntt = R_NTT();

		if(ntt == NULL)
			return NULL;

		Tree_addSubTree(NT->root, t1);
		Tree_addSubTree(NT->root, ntt);
	}
	else {
		Tree *n = R_N();

		if(n == NULL)
			Tree_addChild(NT->root, FALSE, "<Epsilon>", "");
		else
			Tree_addSubTree(NT->root, n);
	}

	return NT;
}

Tree *R_NTT() {
	Tree *NTT = Tree_new(FALSE, "<Number Tail Tail>", "");

	Tree *d = R_D();

	if(d == NULL)
		return NULL;

	Tree *nttt = R_NTTT();

	if(nttt == NULL)
		return NULL;

	Tree_addSubTree(NTT->root, d);
	Tree_addSubTree(NTT->root, nttt);

	return NTT;
}

Tree *R_NTTT() {
	Tree *NTTT = Tree_new(FALSE, "<Number Tail Tail Tail>", "");

	Tree *ntt = R_NTT();

	if(ntt == NULL)
		Tree_addChild(NTTT->root, FALSE, "<Epsilon>", "");
	else
		Tree_addSubTree(NTTT->root, ntt);

	return NTTT;
}

Tree* R_D() {
	//printf("Digit\n");
	if(R_lookahead() == '0') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("0"));

		return D;
	}
	else if(R_lookahead() == '1') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("1"));

		return D;
	}
	else if(R_lookahead() == '2') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("2"));

		return D;
	}
	else if(R_lookahead() == '3') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("3"));

		return D;
	}
	else if(R_lookahead() == '4') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("4"));

		return D;
	}
	else if(R_lookahead() == '5') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("5"));

		return D;
	}
	else if(R_lookahead() == '6') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("6"));

		return D;
	}
	else if(R_lookahead() == '7') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("7"));

		return D;
	}
	else if(R_lookahead() == '8') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("8"));

		return D;
	}
	else if(R_lookahead() == '9') {
		Tree *D = Tree_new(FALSE, "<Digit>", "");
		Tree_addSubTree(D->root, R_matchTerminal("9"));

		return D;
	}

	return NULL;
}

/*
Parsing function
*/
Tree* R_parse(char *input, Tree* (*R_parser_function)(void)) {
	R_setINPUT(input);

	if(!B_parse(input, B_E))
		return NULL;
	else {
		if(B_INPUT[0] == '\0')
			return (*R_parser_function)();
		return NULL;
	}
}