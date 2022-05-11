// Author: Julia Swietochowska
// Last modified: 30th April 2021
// Header file for the tree class

#pragma once

#include "identifier.h"

// The node of a tree
struct node
{
	identifier id; 	
	node *left; 
	node *right; 
};

// Tree class for managing binary search trees
class tree
{
private:
	// Root node of the tree  
	node *root;
	
	// Inserts new identifers into the BST, or updates the reference count 
	// if the identifier name is already in the tree
	// param: root node of the tree
	// param: identifier struct to be inserted into the tree 
	void update_helper(node **root, identifier &id);
	
	// Prints all identifiers in the tree in alphabetical order
	// param: the root node of the tree 
	void print_table_helper(node *root);
	
	// Deletes all nodes in the tree and sets them to nullptrs 
	// param: root node of the tree 
	void delete_tree_helper(node *root);

public:
	// Constructor for the tree class
	tree();
	
	// Updates the BST, by calling a private helper method 
	// param: identifier to be inserted into the tree
	void update(identifier &id);
	
	// Prints the BST alphabetically, by calling a private helper method	
	void print_table();
	
	// Destructor for the tree class 
	~tree();
};
