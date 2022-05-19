/*
 * File: main.c
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#include "scanner.h"

int main(int argc, char *argv[]) {
	BOOL table = FALSE;
	BOOL eval = FALSE;
	BOOL print = FALSE;
	char *file = (char*)(malloc(sizeof(char)*100));
	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-t") == 0)
			table = TRUE;
		else if(strcmp(argv[i], "-e") == 0)
			eval = TRUE;
		else if(strcmp(argv[i], "-p") == 0)
			print = TRUE;
		else if(strcmp(argv[i], "-f") == 0) {
			file = argv[i+1];
		}
	}

	Scanner_execLines(file, print, eval, table);
}