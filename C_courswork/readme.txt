Application name: jdoc
Author: Julia Swietochowska

The purpose of jdoc is to process Javadoc comments into a new output text file 
and print details of the class in the input file to the console 
(class name, author, methods + their parameters and what they return). 
The application also counts the number of lines, non-blank lines and Javadoc comments
in the input file and outputs it to the console. 

jdoc application takes Java source code file (.java) as input and processes it. 
The file to be processed is specified by the user using the -i console command 
when running the application. It creates a new file, whose name is also specified by the user 
using the -o console command, with Javadoc comments and their following method and class declarations. 

Example command to run the application:
jdoc -i Input.java -o output.txt

"nmake jdoc" command builds the application using the makefile.
Tool chain used for building the application: Microsoft Compiler. 

 
