// Author: Julia Swietochowska
// Last modified: 29th April 2021
// Tree class for creating and managing the binary search tree to store identifier structs

#include <iostream>
#include "tree.h"

using namespace std;
	
// Constructor for the tree class
tree::tree()
{
	root = nullptr;
}
	
// Inserts new identifers into the BST, or updates the reference count 
// if the identifier name is already in the tree
// param: root node of the tree
// param: identifier struct to be inserted into the tree 
void tree::update_helper(node **root, identifier &id)
{
	// Create new node if the current root node is empty 
	if(*root == nullptr)
	{
		*root = new node;
		(*root)->id = id;
		(*root)->left = nullptr;
		(*root)->right = nullptr;
	}
	// Else check where to add the new node according to the alphabetical order
	else
	{
		// If the name comes before the root's name alphabetically, insert in the left branch
		if(id.name < (*root)->id.name)
		{
			update_helper(&((*root)->left), id);
		}
		// If the name comes after the root's name alphabetically, insert in the right branch
		else if(id.name > (*root)->id.name)
		{
			update_helper(&((*root)->right), id);
		}
		// if the name is the same, update the reference count of the id already in the tree
		else if(id.name == (*root)->id.name)
		{
			((*root)->id.ref_number)++;
		}
		else
			return;
	}
}

// Prints all identifiers in the tree in alphabetical order
// param: the root node of the tree 
void tree::print_table_helper(node *root)
{
	if(root != nullptr)
	{
		// first, print the left branch 
		print_table_helper(root->left);
		// then, print the root
		cout << root->id.name << ", line " << root->id.line_number << ", " << root->id.category << ", " << root->id.type << ", referenced " << root->id.ref_number << endl;
		// finally, print the right branch 
		print_table_helper(root->right);
	}
}

// Deletes all nodes in the tree and sets them to nullptrs 
// param: root node of the tree 
void tree::delete_tree_helper(node *root)
{
	if(root == nullptr)
	{
		return;
	}
	else
	{
		// first, delete all nodes in the left branch
		delete_tree_helper(root->left);
		delete root->left;
		root->left = nullptr;
		
		// then, delete all nodes in the right branch 
		delete_tree_helper(root->right);
		delete root->right;
		root->right = nullptr;
	}
}

// Prints the BST alphabetically, by calling a private helper method	
void tree::print_table()
{
	print_table_helper(root);
}
	
// Updates the BST, by calling a private helper method 
// param: identifier to be inserted into the tree
void tree::update(identifier &id)
{
	update_helper(&root, id);
}

// Destructor for the tree class 
tree::~tree()
{
	delete_tree_helper(root);
}		
	