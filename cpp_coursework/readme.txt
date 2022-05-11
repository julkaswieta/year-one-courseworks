Applications names: symbol_table and part_b
Author: Julia Swietochowska

The purpose of symbol_table is to process C source code file and look for identifiers in it.
A symbol table with details of these identifiers is created and output to identifiers.txt document. 
The application also counts the number of if statements, for and while loops in the input file
and outputs them to the console. 

The file to be processed by symbol_table is specified by the user on the command line when 
running the application in the following manner:
	symbol_table filename.c

To build the symbol_table using makefile, the command "nmake symbol_table" should be used.

The purpose of part_b is as well to process C source code file and look for identifiers in it, 
however, it uses the binary search tree to enhance performance and outputs the symbol table to the console.

The file to be processed by part_b is specified by the user on the command line when 
running the application in the following manner:
	part_b filename.c

To build the part_b application using makefile, the command "nmake part_b" should be used.

Both applications were built using the Microsoft Compiler. 

