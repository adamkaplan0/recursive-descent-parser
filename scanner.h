/*
 * File: scanner.h
 * Creator: Adam Kaplan
 * Time-stamp: October 19, 2016
 * Project 2
 */

#ifndef SCANNER
#define SCANNER

#include "declarations.h"
#include "evaluator.h"

FILE *f;

void Scanner_execLines(char *path, BOOL print, BOOL eval, BOOL table);

#endif