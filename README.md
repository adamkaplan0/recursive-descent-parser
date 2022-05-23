# Recursive Descent Parser in `C`

## General Information

This project is a recursive descent parser for arithmetic expressions. It implements a straight-forward arithmetic descent parser as well as a table-driven one. It also contains an evaluator for the created parse trees.

## How To Get Going

Before anything you have to run ```make```. This will create all of the executables for you. Now you get to customize how you want to run it.

```shell
./main -t -p -e -f test.txt

```

* Here `-t` is the flag for activating the table-driven parser. By default the recursive descent parser will be used.
* If you want to see the trees to be printed as well, make sure you include the `-p` flag.
* The next flag is the `-e`. It activates the evaluator, which means you will also see the result to each of the expressions in the file.
* The last flag, `-f`, lets you specify which file to read in and evaluate the expressions from. (Make sure to keep the file in the same folder)

### Warning

Since I am using the ``math.h`` library, I need to include the `-lm` flag in my makefile. On Macs `gcc` will say it is useless, but if you want to compile it on the linux machines, it is actually necessary to do that, as otherwise it would just not include the library by default.

### File Layout

The layout of a file such as ``test.txt`` should be as follows:

```plaintext
1+1
2*2-(5+22)
...
```

The important thing here is that the **expressions do not include spaces**.

## Supported Functions

My grammar supports the following arithmetic expressions:

* Addition
* Subtraction
* Multiplication
* Division
* Parentheses: (), [], {}
* Trigonometric functions: sin(), cos(), tan()
* Logarithm function: log()
* Factorial: 5! or 5.2! (yup it also calculates factorials for decimal numbers)
* Power: 5^2 or 5.2^2.5

My calculator works for all decimals up to 6 decimal places (because I decided more are not usually necessary). If you were wondering, it uses the gamma function to calculate the factorials, that way I can also do factorials of decimal numbers.

## File Information

* `declarations.h` -- Does all of the necessary library inclusions as well as type declarations.
* `parse_tree.h` -- Header file for my parse tree.
* `parse_tree.c` -- Actual parse tree.
* `stack.h` -- Header file for my stack.
* `stack.c` -- Actual stack file.
* `bool_parser.h` -- Header file for a very simple implementation of a recursive descent parser which only tells you if an input is "parseable" or not.
* `bool_parser.c` -- Actual bool parser.
* `recursive_parser.h` -- Header file for my straightforward recursive descent parser.
* `recursive_parser.c` -- Actual straightforward recursive descent parser.
* `table_parser.h` -- Header file for my table-driven parser.
* `table_parser.c` -- Actual table-driven parser.
* `evaluator.h` -- Header file for my evaluator.
* `evaluator.c` -- Actual evaluator.
* `scanner.h` -- Header file for my file scanner.
* `scanner.c` -- Actual scanner file.
* `main.c` -- Main executable where everything comes together.
* `test.txt` -- Testing file for my grammar with some random expressions, feel free to modify/use your own.
