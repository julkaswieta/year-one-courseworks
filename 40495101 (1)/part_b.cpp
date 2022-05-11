// Author: Julia Swietochowska
// Last modified: 29th April 2021
// The application prints out the symbol table of the input file
// specified on the command line using a binary search tree 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "identifier.h"
#include "tree.h"

using namespace std;

// Reads in the input file and creates a vector that stores 
// each line of the file as a separate string in the vector
// param: string representing the filename to be read in 
vector<string> readfile(string &filename)
{
	// Open the file 
	ifstream input(filename);
	string line;
	vector<string> lines;
	
	// Read in until the end of file
	while(getline(input, line))
	{
		lines.push_back(line);
	}
	
	// Close the file
	input.close();

	return lines;
}

// Tokenises the strings and processes the file, looking for if statements, loops and identifiers 
// param: vector of strings containing lines read in from the input file to process
// param: the binary search tree to store the identifiers found
void process_lines(vector<string> &input, tree **bst)
{
	char *delimeters = " \t\n";
	
	// Tokenise the strings and process the file
	for(int i = 0; i < input.size(); ++i)
	{
		// Get the raw C string from the string object 
		const char *raw_string = input[i].c_str();
		
		// As the raw string is constant, copy it into a new variable
		char line[200];
		strcpy(line, raw_string);
		
		// Get the first token 
		char *token = strtok(line, delimeters);
		
		while(token != NULL)
		{
			// Look for identifiers
			if(strcmp(token, "int") == 0 || strcmp(token, "char") == 0 || strcmp(token, "short") == 0 || strcmp(token, "long") == 0 || strcmp(token, "float") == 0 || strcmp(token, "double") == 0 || strcmp(token, "int*") == 0 || strcmp(token, "short*") == 0 || strcmp(token, "long*") == 0 || strcmp(token, "float*") == 0 || strcmp(token, "double*") == 0 || strcmp(token, "char*") == 0 || strcmp(token, "void") == 0)
			{
				identifier id;
				id.type = token;
				
				// If the token is "long", check if the next is not "long" (long long type) 
				if(strcmp(token, "long") == 0)
				{
					token = strtok(NULL, delimeters);
					// If the type is "long long"
					if(strcmp(token, "long") == 0)
					{
						id.type += " ";
						id.type += token;
						token = strtok(NULL, delimeters);
						id.name = token;
						id.line_number = i + 1; // index starts at 0, lines numbering at 1
						id.category = "variable";
						id.ref_number = 0;
						(*bst)->update(id);
						break;
					}
					// Else the type's just "long"
					else
					{
						id.name = token;
						id.line_number = i + 1;
						id.category = "variable";
						id.ref_number = 0;
						(*bst)->update(id);
						break;
					}
				}
				
				// If the identifier type is not long or long long 
				else
				{
					token = strtok(NULL, delimeters);
					id.name = token;
					id.line_number = i + 1;
					token = strtok(NULL, delimeters);
				
					// If there's a bracket after identifier type, then it's a function 
					if(strcmp(token, "(") == 0)
					{
						id.category = "function";
						id.ref_number = 0;
						(*bst)->update(id);
						token = strtok(NULL, delimeters);
						
						// Look for parameters of the function 
						if(strcmp(token, "int") == 0 || strcmp(token, "char") == 0 || strcmp(token, "short") == 0 || strcmp(token, "long") == 0 || strcmp(token, "float") == 0 || strcmp(token, "double") == 0 || strcmp(token, "int*") == 0 || strcmp(token, "short*") == 0 || strcmp(token, "long*") == 0 || strcmp(token, "float*") == 0 || strcmp(token, "double*") == 0 || strcmp(token, "char*") == 0)
						{
							identifier param;
							param.type = token;
							token = strtok(NULL, delimeters);
							param.name = token;
							param.name += " (";
							param.name += id.name;
							param.name += ")";
							param.line_number = i + 1;
							param.category = "variable";
							id.ref_number = 0;
							(*bst)->update(param);
							token = strtok(NULL, delimeters); 
							
							// If the next token is a comma, process the second parameter	
							if(strcmp(token, ",") == 0)
							{
								token = strtok(NULL, delimeters);
								identifier param;
								param.type = token;
								token = strtok(NULL, delimeters);
								param.name = token;
								param.name += " (";
								param.name += id.name;
								param.name += ")";
								param.line_number = i + 1;
								param.category = "variable";
								id.ref_number = 0;
								(*bst)->update(param);
							}
						}
					}
					// Check if the identifier type is not an array
					else if(strcmp(token, "[]") == 0)
					{	
						id.type += " ";
						id.type += "[]";
						id.category = "variable";
						id.ref_number = 0;
						(*bst)->update(id);
					}
					// Else it's not a function, nor an array
					else
					{
						id.category = "variable";
						id.ref_number = 0;
						(*bst)->update(id);
					}
					break;
				}
			}
			// Go to the next line 
			token = strtok(NULL, delimeters);
		}
	}
}

int main(int argc, char **argv)
{
	// Filename to read in specified on the command line
	string filename = argv[1];
	
	// Read in the file into the vector 
	vector<string> input = readfile(filename);
	
	// Create a new binary search tree to store the identifiers 
	tree *bst = new tree();
	
	// Process the lines of the input file, looking for identifiers
	process_lines(input, &bst);
	
	// Print the symbol table from the BST 
	bst->print_table();
	
	// Delete the BST from memory
	delete bst;
	bst = nullptr;

	return 0;
}	
	