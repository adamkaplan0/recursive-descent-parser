#Recursive Descent Parser in C

##General Information

This project is a recursive descent parser for arithmetic expressions. We had to implement a straight-forward arithmetic descent parser as well as a table-driven one. Furthermore, we also had to create an evaluator for the parse trees created.

##How to get it running

Before anything you have to run ```make```. This will create all of the executables for you. Now you get to customize how you want to run it.

```
./main -t -p -e -f test.txt

```
Here ```-t``` is the flag for activating the table-driven parser. By default the straightforward recursive descent parser will be used.

If you want to see the trees to be printed as well, make sure you include the ```-p``` flag.

The next flag is the ```-e``` one. This one activates the evaluator, which means you will also see the result to each of the expressions in the file.

The last flag is ```-f```, which lets you specify which file to read in and evaluate the expressions from. (Make sure to keep the file in the same folder)

###Warnings
So since I am using the ``math.h`` library, I need to include the ```-lm``` flag in my makefile. Now on macs GCC will say it is useless, but if you want to compile it on the linux machines, it is actually necessary to do that, as otherwise it would just not include the library by default. 

###Example runs
For some quick examples you can run any of these commands after you ran the ```make``` command.

```
./main -t -p -e -f test.txt
./main -p -e -f test.txt
./main -t -e -f test.txt
./main -e -f test.txt
./main -p -f test.txt
./main -t -p -f test.txt

```

##File Layout
The layout of a file such as ``test.txt`` should be as follows:

```
1+1
2*2-(5+22)
...

```
The important thing here is that the **expressions do not include spaces**.

##Supported Functions
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

My calculator works for all decimals up to 6 decimal places (because I decided more are not usually necessary).

If you were wondering, it uses the gamma function to calculate the factorials, that way I can also do factorials of decimal numbers.

###Extra credit
You can see that I implemented functions such as sin() and factorial. I also added support for decimal numbers in all aspects.

##Mentions
I had some issues with the scanner, so I looked through StackOverflow, sine we never covered how to make a file reader in C. I, of course, wrote down the two threads in Stack Overflow that I used in my code.

I also used an article from StackOverflow, because I noticed that I was wrongly concatenating strings, since an empty char pointer does not end with ```'\0'``` and therefore I cannot concatenate them together. I also commented the source to my code

##File Information

* ``declarations.h``: This file does all of the necessary library inclusions as well as type declarations.
* ``parse_tree.h``: This file is the header file for my parse tree.
* ``parse_tree.c``: This is the actual parse tree.
* ``stack.h``: Header file for my stack.
* ``stack.c``: Actual stack file.
* ``bool_parser.h``: Header file for a very simple implementation of a recursive descent parser which only tells you if an input is parseable or not.
* ``bool_parser.c``: The actual bool parser.
* ``recursive_parser.h``: Header file for my straightforward recursive descent parser.
* ``recursive_parser.c``: The actual straightforward recursive descent parser.
* ``table_parser.h``: Header file for my table-driven parser.
* ``table_parser.c``: Actual table-driven parser.
* ``evaluator.h``: Header file for my evaluator.
* ``evaluator.c``: My actual evaluator.
* ``scanner.h``: Header file for my file scanner.
* ``scanner.c``: My actual scanner file.
* ``main.c``: The main executable where everything comes together.
* ``test.txt``: A testing file for my grammar with some random expressions, feel free to modify/use your own.