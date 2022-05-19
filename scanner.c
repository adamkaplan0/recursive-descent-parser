/*
 * File: scanner.c
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#include "scanner.h"

/*
Help from: http://stackoverflow.com/questions/19323113/how-do-i-scan-a-file-in-c-using-fscanf
And from: http://stackoverflow.com/questions/13443793/fgets-includes-the-newline-at-the-end
*/
void Scanner_execLines(char *path, BOOL print, BOOL eval, BOOL table) {
	char line[200];

	f = fopen(path, "r");

	while(fgets(line, 200, f) != NULL) {
		//Strip the dongling new line character from the 
		strtok(line, "\n");
		evaluate(line, print, table, eval);
	}

	fclose(f);
}