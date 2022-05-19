#
# File: Makefile
# Creator: Adam Kaplan
# Time-stamp: October 19, 2016
#

PROGRAMS = main
CFLAGS = -g -lm

programs: $(PROGRAMS)


main: parse_tree.o stack.o bool_parser.o table_parser.o recursive_parser.o evaluator.o scanner.o

clean:
	-rm $(PROGRAMS) *.o
	-rm -r *.dSYM