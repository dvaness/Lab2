//---------------------------------------------------------------------------
// BIN_TREE_H
// Class to handle a BinarySearchTree
// Author: Dallas Van Ess
//---------------------------------------------------------------------------
// BinTree class:  includes a wide range of functionality relating to a Binary
//				   SearchTree
//   including:
//   -- retriving a specific NodeData object
//   -- comparing two BinTree objects(== and !=)
//   -- getting the depth of a specific NodeData  object
//   -- conversion to an array of NodeData pointers
//   -- conversion from an array of NodeData pointers to a BinTree object
//
// Assumptions:
//   -- only expects strings 
//   -- 
//   --
//   --
//---------------------------------------------------------------------------

#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <iostream>
#include "nodedata.h"

class BinTree
{
public:
	friend ostream& operator<<(ostream&, const BinTree&);
	//-------------------------- Constructor ----------------------------------
    // Default constructor for class BinTree
    // Preconditions:   None
    // Postconditions:
    // 	  -- a new BinTree object is created. root initialized to NULL
	BinTree();
	//-------------------------- Copy -----------------------------------------
    // Copy constructor for class BinTree
    // Preconditions:   None
    // Postconditions:
    // 	  -- a new BinTree object is created as an exact copy of the parameter.
	BinTree(const BinTree&);
	//-------------------------- Destructor -----------------------------------
    // Destructor for class BinTree
    // Preconditions:   None
    // Postconditions:
    // 	  -- all memory allocated by the calling object is returned to the OS
	~BinTree();
	//-----------------------------  =  ---------------------------------------
    // Overloaded assignment operator
    // Preconditions:   right.ptr points to a BinTree object with at least one
    //                    non-null member
    // Postconditions:  *this is assigned the same BinTree as right
	BinTree& operator=(const BinTree&);
	//------------------------------  ==  -------------------------------------
    // Determine if two binary search trees are equal.
    // Preconditions:   ptr and right.ptr point to BinTrees with
    //                    at least one non-null member each
    // Postconditions:  true is returned if the BinTrees have the exact
    //                    same members(regardless of structure),
    //					  false is return otherwise
	bool operator==(const BinTree&)const;
	//------------------------------  !=  -------------------------------------
    // Determine if two binary search trees are unequal.
    // Preconditions:   ptr and right.ptr point to BinTrees with
    //                    at least one non-null member each
    // Postconditions:  true is returned if the BinTrees have any of the
    //                    same members, false is return otherwise
	bool operator!=(const BinTree&)const;
	//------------------------------  retrieve  -------------------------------
    // Retrieve a specific NodeData item from the BinTree
    // Preconditions:   the NodeData*& parameter has been created and 
    //					initialized
    // Postconditions:  returns the NodeData* as the NodeData*& provided as a
    //					parameter, returns NULL otherwise
	bool retrieve(const NodeData&, NodeData*&)const;
	//------------------------------  insert  -------------------------------
    // Insert a specific NodeData item into the BinTree
    // Preconditions:   the NodeData parameter that is being pointed to has 
    //					been created and initalized
    // Postconditions:  returns true if sucessfully inserted, false if not
	bool insert(NodeData*);
	int getDepth(const NodeData&)const;
	void bstreeToArray(NodeData*[]);
	void arrayToBSTree(NodeData*[]);
	void displaySideways()const;
	bool isEmpty()const;
	void makeEmpty();
	void printInOrder()const;

private:
	struct Node
	{
		NodeData* data;
		Node* left;
		Node* right;
	};
	Node* root;
	void inOrderHelper(Node*)const;
	void sideways(Node*, int)const;
	void reclaim(Node*);
	int arrayBuilder(int, Node*, NodeData* []);
	NodeData* retrieveHelper(const NodeData&, Node*)const;

};
#endif
