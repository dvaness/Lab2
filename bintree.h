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
//
//---------------------------------------------------------------------------

#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <iostream>
#include "nodedata.h"

class BinTree
{
public:
	//-------------------------- << -------------------------------------------
    // Overloaded output operator for BinTree class
    // Preconditions:   None
    // Postconditions:	None
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
	//------------------------------  makeEmpty  ------------------------------
	// Return all allocated memory to the OS
	// Preconditions:   none
	// Postconditions:  all memory is returned to the OS
	void makeEmpty();
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
	//------------------------------  getDepth  -------------------------------
	// Find the depth of a specific NodeData item from the BinTree
	// Preconditions:   the NodeData& parameter has been created and
	//					initialized
	// Postconditions:  returns the depth of the given NodeData item, with
	//					the root being at level 1.
	int getDepth(const NodeData&)const;
	//------------------------------  bstreeToArray  --------------------------
	// Convert the calling BinTree object to a sorted array of NodeData*'s
	// Preconditions:   the array is expected to be of size 100 and be full of
	//					NULLs
	// Postconditions:  The array passed is filled with the contents of the
	//					calling BinTree object.
	//					NOTE: The calling BinTree object currently is
	//					uneffected by this method. Needs to be changed to
	//					be empty after conversion to an array.
	void bstreeToArray(NodeData*[]);
	//------------------------------  arrayToBSTree  --------------------------
	// Convert the calling BinTree object to be filled with the contents of the
	// array passed in.
	// Preconditions:
	// Postconditions:  The calling BinTree object is filled with the contents
	//					of the parameterized array
	//					NOTE: The parameterized array currently is
	//					uneffected by this method. Needs to be changed to
	//					be empty after conversion to a BinTree.
	void arrayToBSTree(NodeData*[]);
	//------------------------------  displaySideways  ------------------------
	// Print the calling BinTree object "on its side"
	// Preconditions:   none
	// Postconditions:  none
	void displaySideways()const;
	//------------------------------  isEmpty  --------------------------------
	// Print the calling BinTree object "on its side"
	// Preconditions:   none
	// Postconditions:  returns true if the tree is empty, false if not.
	bool isEmpty()const;

	//------------------------------  printInOrder  ---------------------------
	// Print the result of a in-order depth first traversal
	// Preconditions:   none
	// Postconditions:  none
	void printInOrder()const;
	
private:
	struct Node
	{
		NodeData* data;
		Node* left;
		Node* right;
		Node()
		{
			data = NULL;
			left = NULL;
			right = NULL;
		}
		Node(NodeData* someData)
		{
			data = someData;
			left = NULL;
			right = NULL;
		}
		~Node()
		{
			if(data != NULL)
			{
				data = NULL;	
				delete data;
				
			}
			
			left = NULL;
			right = NULL;


		}
		//------------------------------  ==  ---------------------------------
    	// Determine if Nodes are equal.
    	// Preconditions:   none
    	// Postconditions:  true is returned if the Nodes are exactly
    	//                    the same, false is return otherwise
		friend bool operator==(Node const& lhs, Node const& rhs)
		{
			return *lhs.data == *rhs.data
			//both left nodes are null
			&& ((lhs.left == NULL && rhs.left == NULL)	
			//both left nodes are not null, check for same members
			|| (lhs.left != NULL && rhs.left != NULL && *lhs.left == *rhs.left)) 
			//both right nodes are null
			&& ((lhs.right == NULL && rhs.right == NULL)
			//both right nodes are not null, check for same members
			|| (lhs.right != NULL && rhs.right != NULL && *lhs.right == *rhs.right));
		}
	};
	Node* root;
	//------------------------------  inOrderHelper  --------------------------
	// Helper method for the printInOrder method
	// Preconditions:   none
	// Postconditions:  none
	void inOrderHelper(Node*)const;
	//------------------------------  sideways  -------------------------------
	// Helper method for the displaySideways method
	// Preconditions:   none
	// Postconditions:  none
	void sideways(Node*, int)const;
	//------------------------------  reclaim  --------------------------------
	// Helper method for the makeEmpty method
	// Preconditions:   none
	// Postconditions:  none
	void reclaim(Node*);
	//------------------------------  arrayBuilder  --------------------------
	// Helper method for the bstreeToArray method
	// Preconditions:   none
	// Postconditions:  none
	int arrayBuilder(int, Node*, NodeData* []);
	//------------------------------  treeBuilder  --------------------------
	// Helper method for the arrayToBSTree method
	// Preconditions:   none
	// Postconditions:  none
	BinTree::Node* treeBuilder(NodeData*[],int,int);
	//------------------------------  retrieveHelper  -------------------------
	// Helper method for the retrieve method
	// Preconditions:   none
	// Postconditions:  none
	NodeData* retrieveHelper(const NodeData&, Node*)const;
	//------------------------------  depthHelper  ----------------------------
	// Helper method for the getDepth method
	// Preconditions:   none
	// Postconditions:  none
	int depthHelper(const NodeData&, Node*, int)const;
	//------------------------------  copier  ----------------------------
	// Handles the logic required by operator= and copy c'tor
	// Preconditions:   none
	// Postconditions:  none
	BinTree::Node* copier(Node*);
	
	


};
#endif
