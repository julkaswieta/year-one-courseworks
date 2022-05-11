// Author: Julia Swietochowska
// Last modified: 1st April 2021
// struct for storing info about each identifier 
#pragma once

#include <string>

struct identifier
{
	std::string name;
	int line_number;
	std::string category;	// whether it's a variable, an array, or a function
	std::string type;	// type or return type
	int ref_number;		// number of times the identifier is referenced in the file
};