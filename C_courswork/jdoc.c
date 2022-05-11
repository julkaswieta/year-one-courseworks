// An application that reads in Java source code and processes Javadoc comments 
// into a new output document and outputs class details to the console. 
// Author: Julia Swietochowska 

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	// Open the input file
	FILE *input = fopen(argv[2], "r");
	
	// Read in the .java file line by line
	char java_line[500];
	int line_counter = 0; 	// a counter for all lines
	int non_blank_counter = 0; 	// a counter for non-blank lines 
	int javadoc_counter = 0; 	// a counter for javadoc comments
	
	while(fgets(java_line, 500, input) != NULL)
	{
		line_counter++;
		
		// Check if the line is not blank 
		int check = 0;
		for(int i = 0; i < strlen(java_line); ++i)
		{
			if(java_line[i] != '\t' && java_line[i] != ' ' && java_line[i] != '\n')
			{
				check = 1;
			}
		}
		
		// Count the non-blank lines
		if(check)
		{
			non_blank_counter++;
		}
		check = 0;
	}
	
	rewind(input);
	
	// Open the output file
	FILE *output = fopen(argv[4], "w");
	char *delimeters = " \t\n";
	int flag = 0;

	// Handles printing to the output file and counting Javadoc comments 
	while(fgets(java_line, 500, input) != NULL)
	{	
		//If inside Javadoc comment, go to the next line in output
		if(flag == 1)
		{
			fprintf(output, "\n ");
		}
		
		// Print the class/method line if "*/" was found 
		if(flag == 2)
		{
			fprintf(output, "\n");
			// Remove the opening curly bracket
			int len = strlen(java_line);
			java_line[len - 2] = ' ';
			fprintf(output, "%s\n", java_line);
			flag = 0;
			continue;
		}
		
		// Split each line into tokens 
		char *token = strtok(java_line, delimeters);
	
		while(token != NULL)
		{	
			if(strcmp(token, "/**") == 0)
			{
				// count the Javadoc comments
				javadoc_counter++;
				flag = 1;	// mark the start of a comment
			}
			
			else if(strcmp(token, "*/") == 0)
			{
				// If the end of the comment is found, print the symbol 
				// and move on to the next line of the input file 
				fprintf(output, "%s", token);
				token = strtok(NULL, delimeters);
				flag = 2;	// For printing class/method name
				break;
			}
			
			// If inside a Javadoc comment, keep printing the tokens inside
			if(flag == 1)
			{
				if(strcmp(token, "/**") == 0)
				{
					fprintf(output, "%s", token);
				}
				
				else
				{
					fprintf(output, "%s ", token);
				}
			}
			token = strtok(NULL, delimeters);
		}	
	}
	
	fclose(input);
	fclose(output);

	// Open the output file to process it to console
	FILE *comments = fopen(argv[4], "r");
	char comments_line[500];
	
	flag = 0;
	int flag2 = 0;
	char author[100] = "\0";
	char method_returns[200] = "\0";
	char method_param1[200] = "\0";
	char method_param2[200] = "\0";
	
	// Handles printing class, author and methods to the console
	while(fgets(comments_line, 500, input) != NULL)
	{
		flag = 0;
		char *token = strtok(comments_line, delimeters);
		while(token != NULL)
		{
			if(strcmp(token, "@author") == 0)
			{
				strcat(author, "Author: ");
				token = strtok(NULL, delimeters);
				flag = 1;	// for storing author name 
			}
			
			else if(strcmp(token, "@return") == 0)
			{
				strcat(method_returns, "Returns: ");
				token = strtok(NULL, delimeters);
				flag = 2;	// for storing what a method returns
			}
			
			else if(strcmp(token, "@param") == 0)
			{
				if(method_param1[0] == '\0' || method_param1 == NULL)
				{
					strcat(method_param1, "Parameter: ");
					token = strtok(NULL, delimeters);
					flag = 3;	// for storing the first parameter 
				}
				else
				{
					strcat(method_param2, "Parameter: ");
					token = strtok(NULL, delimeters);
					flag = 4;	// for storing the secodn parameter
				}
			}
			
			else if(strcmp(token, "*/") == 0)
			{
				flag2 = 1;	// indicates that the next line will be a method/class declaration
				break;		// skip to the next line of the document
			}
			
			// handles storing author name
			if(flag == 1)
			{
				strcat(author, token);
				strcat(author, " ");
			}
			
			// handles storing method return
			else if(flag == 2)
			{
				strcat(method_returns, token);
				strcat(method_returns, " ");
			}
			
			// handles storing 1st parameter data
			else if(flag == 3)
			{
				strcat(method_param1, token);
				strcat(method_param1, " ");
			}
			
			// handles stroing 2nd parameter data
			else if(flag == 4)
			{
				strcat(method_param2, token);
				strcat(method_param2, " ");
			}
			
			// If the current line is a method or class declaration
			if(flag2 == 1)
			{
				// check the second token of the line
				token = strtok(NULL, delimeters);
				if(strcmp(token, "class") == 0)
				{
					// print the class name and author
					token = strtok(NULL, delimeters);
					printf("Class %s\n", token);
					printf("%s\n", author);
					printf("\n");
					flag2 = 0;
					break;
				}
				else
				{
					// print method name and return and/or parameters
					token = strtok(NULL, delimeters);
					printf("Method: %s\n", token);
					if(method_returns[0] != '\0')
					{
						printf("%s\n", method_returns);
						method_returns[0] = '\0';	// empty the string
					}
					if(method_param1[0] != '\0')
					{
						printf("%s\n", method_param1);
						method_param1[0] = '\0';	// empty the string
					}
					if(method_param2[0] != '\0')
					{
						printf("%s\n", method_param2);
						method_param2[0] = '\0';	// empty the string 
					}
					printf("\n");
					flag2 = 0;
					break;
				}
			}
			token = strtok(NULL, delimeters);
		}
	}
	
	fclose(comments);
	
	printf("Total numbers of lines: %d\n", line_counter);
	printf("Number of non-blank lines: %d\n", non_blank_counter);
	printf("Number of Javadoc comments: %d\n", javadoc_counter);

	return 0;
}
