// Author: Julia Swietochowska
// Last modified: 29th April 2021
// The application prints out the symbol table of the input file
// specified on the command line when running the app

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include "identifier.h"

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
	
// Prints the symbol table to an output file
// param: string representing the filename to write to
// param: vector containing the identifier structs to print 
void print_table(string &filename, vector<identifier> &identifier_list)
{
	// Open the file 
	ofstream file(filename);
	
	// Print the info for each identifier in the vector 
	for(auto item : identifier_list)
	{
		file << item.name << ", line " << item.line_number << ", " << item.category << ", " << item.type << ", referenced " << item.ref_number << endl;
	}
	
	// Close the file 
	file.close();
}

// Prints the number of variables, functions, if statements, for and while loops to the console
// params: variable counter, function counter, if statements counter, for loops counter, while loops counter to print 
void print_counters(int &variable_counter, int &function_counter, int &if_counter, int &for_counter, int &while_counter)
{
	cout << "Variables: " << variable_counter << endl;
	cout << "Functions: " << function_counter << endl;
	cout << "If statements: " << if_counter << endl;
	cout << "For loops: " << for_counter << endl;
	cout << "While loops: " << while_counter << endl;
}

// Tokenises the strings and processes the file, looking for if statements, loops and identifiers 
// param: vector of strings containing lines read in from the input file to process 
// param: vector of identifier structs to store the identifiers found in the input file
// params: variable counter, function counter, if statements counter, for loops counter, while loops counter
void process_lines(vector<string> &input, vector<identifier> &identifier_list, int &variable_counter, int &function_counter, int &if_counter, int &for_counter, int &while_counter)
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
						id.line_number = i + 1;
						id.category = "variable";
						variable_counter++;
						identifier_list.push_back(id);
						break;
					}
					// Else the type's just "long"
					else	
					{
						id.name = token;
						id.line_number = i + 1;
						id.category = "variable";
						variable_counter++;
						identifier_list.push_back(id);
						break;
					}
				}
				
				// If the identifier type is not long or long long 
				else
				{
					token = strtok(NULL, delimeters);
					id.name = token;
					id.line_number = i + 1; // index starts at 0, lines at 1
					token = strtok(NULL, delimeters);
				
					// If there's a bracket after identifier type, then it's a function 
					if(strcmp(token, "(") == 0)
					{
						id.category = "function";
						function_counter++;
						identifier_list.push_back(id);
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
							variable_counter++;
							identifier_list.push_back(param);
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
								variable_counter++;
								identifier_list.push_back(param);
							}
						}
					}
					// Check if the identifier type is not an array
					else if(strcmp(token, "[]") == 0)
					{	
						id.type += " ";
						id.type += "[]";
						id.category = "variable";
						variable_counter++;
						identifier_list.push_back(id);
					}
					// Else it's not a function, nor an array
					else
					{
						id.category = "variable";
						variable_counter++;
						identifier_list.push_back(id);
					}
					break;
				}
			}
			
			// Look for if statements, for and while loops and count them 
			if(strcmp(token, "if") == 0)
			{
				if_counter++;
			}
			else if(strcmp(token, "for") == 0)
			{
				for_counter++;
			}
			else if(strcmp(token, "while") == 0)
			{
				while_counter++;
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
	
	vector<identifier> identifier_list;

	int variable_counter = 0;
	int function_counter = 0;
	int if_counter = 0;
	int for_counter = 0;
	int while_counter = 0;
	
	// Look for identifiers, if statements and for and while loops 
	process_lines(input, identifier_list, variable_counter, function_counter, if_counter, for_counter, while_counter);
	
	// Print the if statements, for and while loops counters to the console 
	print_counters(variable_counter, function_counter, if_counter, for_counter, while_counter);
	
	string token;
	
	// for each identifier, count how many times it is referenced in the file 
	for(int i = 0; i < identifier_list.size(); i++)
	{
		// Get the identifier name
		string current_id = identifier_list.at(i).name;	
		int ref_counter = 0;
		for(int j = 0; j < input.size(); j++)
		{
			// Convert each line of the input file into stringstream and tokenise it
			stringstream stream(input.at(j));
			while(stream >> token)
			{
				// If identifer name is found throughout the file, count it 
				if(token.compare(current_id) == 0)
				{
					ref_counter++;
				}
			}
		}
		// Update the identifier struct in the vector with the reference number 
		identifier_list.at(i).ref_number = ref_counter - 1; // subtract the declaration
	}

	// Print the sumbol table to the output file  
	print_table(string("identifiers.txt"), identifier_list);
	
	return 0;
}