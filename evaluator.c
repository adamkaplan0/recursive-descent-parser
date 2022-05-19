/*
 * File: evaluator.c
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#include "evaluator.h"

/*
Important side functions
*/

/*
I had some issues with connecting string together, so I tried to use strcat, but I had issues with that
So I looked it up and I figured out that my issue was that 
Source: http://stackoverflow.com/questions/18819131/c-function-using-strcat-with-strings
*/
char* cat(char *dest, char *src) {
	int size = strlen(dest) + strlen(src) + 1;
	char *temp = (char*)(malloc(size));
	strcpy(temp, dest);
	strcat(temp, src);
	
	return temp;
}

/*
I adjusted my factorial function so it actually can give you a result for any number > 0 in the reals
*/
double factorial(double x) {
	return x * tgamma(x);
}

/*
Just a function to print my char, because for whatever reason I get a weird character string otherwise
*/
void print_char(char *input) {
	while(input[0] != '\0') {
		printf("%c", input[0]);
		input++;
	}
}

/*
Evaluation functions
*/

/*
This is where all the magic happens, spiced up with a ton of if-else statements
*/
char* R_eval(TreeNode *node, char *n) {
	if(strcmp(node->label, "<Expression>") == 0) {
		char *t = R_eval(node->left, n);
		char *et = R_eval(node->center, t);
		double var = atof(et);

		char r[200]; char *result = (char*)r;
		sprintf(result, "%f", var);
		
		return result;
	}
	else if(strcmp(node->label, "<Expression Tail>") == 0) {
		if(strcmp(node->left->label, "+") == 0) {
			char *temp = "";
			double var1 = atof(n);
			double var2 = atof(R_eval(node->center, temp));

			double res = var1 + var2;

			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			result = R_eval(node->right, result);

			return result;
		}
		else if(strcmp(node->left->label, "-") == 0) {
			char *temp = "";
			double var1 = atof(n);
			double var2 = atof(R_eval(node->center, temp));

			double res = var1 - var2;

			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			result = R_eval(node->right, result);

			return result;
		}
		else
			return n;
	}
	else if(strcmp(node->label, "<Term>") == 0) {
		char *f = R_eval(node->left, n);
		char *tt = R_eval(node->center, f);
		double var = atof(tt);

		char r[200]; char *result = (char*)r;
		sprintf(result, "%f", var);
		
		return result;
	}
	else if(strcmp(node->label, "<Term Tail>") == 0) {
		if(strcmp(node->left->label, "*") == 0) {
			char *temp = "";
			double var1 = atof(n);
			double var2 = atof(R_eval(node->center, temp));

			double res = var1 * var2;

			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			result = R_eval(node->right, result);

			return result;
		}
		else if(strcmp(node->left->label, "/") == 0) {
			char *temp = "";
			double var1 = atof(n);
			double var2 = atof(R_eval(node->center, temp));

			double res = var1 / var2;

			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			result = R_eval(node->right, result);

			return result;
		}
		else
			return n;
	}
	else if(strcmp(node->label, "<Factor>") == 0) {
		BOOL neg = FALSE;

		if(strcmp(node->left->left->label, "<Epsilon>") != 0)
			neg = TRUE;

		if(neg) {
			char *temp = cat("-", n);
			char *pf = R_eval(node->center, temp);

			char *ft = R_eval(node->right, pf);

			double var = atof(ft);

			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", var);
		
			return result;
		}
		else {
			char *pf = R_eval(node->center, n);

			char *ft = R_eval(node->right, pf);

			double var = atof(ft);

			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", var);
		
			return result;
		}
	}
	else if(strcmp(node->label, "<Factor Tail>") == 0) {

		if(strcmp(node->left->label, "!") == 0) {

			double var = atof(n);
			double res = factorial(var);

			char r[200]; char *result = (char*)r;

			sprintf(result, "%f", res);

			result =  R_eval(node->center, result);

			return result;
		}
		else if(strcmp(node->left->label, "^") == 0) {

			char *temp = "";
			double var = atof(n);
			double power = atof(R_eval(node->center, temp));
			double res = pow(var, power);

			

			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			result = R_eval(node->right, result);

			return result;
		}
		else {
			return n;
		}
	}
	else if(strcmp(node->label, "<Prefix Function>") == 0) {
		
		if(strcmp(node->left->terminal, "sin(") == 0) {
			char *e = R_eval(node->center, n);
			double num = atof(e);
			num *= M_PI/180;
			double res = sin(num);
			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			return result;
		}
		else if(strcmp(node->left->terminal, "cos(") == 0) {
			char *e = R_eval(node->center, n);
			double num = atof(e);
			num *= M_PI/180;
			double res = cos(num);
			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			n = result;

			return n;
		}
		else if(strcmp(node->left->terminal, "tan(") == 0) {
			char *e = R_eval(node->center, n);
			double num = atof(e);
			num *= M_PI/180;
			double res = tan(num);
			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			return result;
		}
		else if(strcmp(node->left->terminal, "log(") == 0) {
			char *e = R_eval(node->center, n);
			double num = atof(e);
			double res = log(num);
			char r[200]; char *result = (char*)r;
			sprintf(result, "%f", res);

			return result;
		}
		else {
			char *result = R_eval(node->left, n);

			return result;
		}
	}
	else if(strcmp(node->label, "<Standard Expression>") == 0) {
		//Make the exceptions
		if(strcmp(node->left->label, "<Number>") == 0) {
			char *result = R_eval(node->left, n);

			return result;
		}
		else if(strcmp(node->left->terminal, "(") == 0) {
			char *result = R_eval(node->center, n);

			return result;
		}
		else if(strcmp(node->left->terminal, "[") == 0) {
			char *result = R_eval(node->center, n);

			return result;
		}
		else if(strcmp(node->left->terminal, "{") == 0) {
			char *result = R_eval(node->center, n);

			return result;
		}
	}
	else if(strcmp(node->label, "<Number>") == 0) {
		char *r = R_eval(node->left, n); //N is the left child
		char *result = R_eval(node->center, r); //N is the right child

		return result;
	}
	else if(strcmp(node->label, "<Number Tail>") == 0) {
		if(strcmp(node->left->terminal, ".") == 0) {
			char *res = cat(n, node->left->terminal); //append the period
			char *result = R_eval(node->center, res); //append the rest of the numbers

			return result;
		}
		else {
			char *result = R_eval(node->left, n);

			return result;
		}
	}
	else if(strcmp(node->label, "<Number Tail Tail>") == 0) {
		char *r = R_eval(node->left, n); //N is the left child
		char *result = R_eval(node->center, r); //N is the right child

		return result;
	}
	else if(strcmp(node->label, "<Number Tail Tail Tail>") == 0) {
		char *result = R_eval(node->left, n);

		return result;
	}
	else if(strcmp(node->label, "<Digit>") == 0) {
		n = cat(n, node->left->terminal); //Add the digit to the number

		return n;
	}
	else if(strcmp(node->label, "<Epsilon>") == 0) {
		return n;
	}

	return NULL;
}

/*
Quick function to print out the tree as well as actually compute it
*/
Tree* get_Tree(char *input, BOOL print, BOOL table) {

	if(table) {
		Tree *tree = T_parse(input);

		if(tree == NULL) {
			printf("The input is not valid.\n");
			return NULL;
		}

		if(print)
			Tree_print(tree);

		return tree;
	}
	else {
		Tree *tree = R_parse(input, R_E);
		
		if(tree == NULL) {
			printf("The input is not valid.\n");
			return NULL;
		}

		if(print)
			Tree_print(tree);

		return tree;
	}
	
}

/*
Driver function to evaluate the tree
*/
void raw_eval(Tree *tree) {
	if(tree != NULL) {
		char *n = (char*)(malloc(sizeof(char)*200 + 1));
		char *result = R_eval(tree->root, n);
		print_char(result);

		printf("\n");
	}
}

/*
The pretty function for evaluating a parse tree
*/
void evaluate(char *input, BOOL print, BOOL table, BOOL eval) {
	Tree* tree = get_Tree(input, print, table);
	if(tree != NULL && eval) {
		printf("%s = ", input);
		raw_eval(tree);
	}
}