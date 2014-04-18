# include "bintree.h"

using namespace std;
//-------------------------- Constructor ----------------------------------
// Default constructor for class BinTree
// Preconditions:   None
// Postconditions:
// 	  -- a new BinTree object is created. root initialized to NULL
BinTree::BinTree()
{
	root = NULL;
}

BinTree::BinTree(const BinTree& toCopy)
{
	root = copier(toCopy.root);
}

BinTree& BinTree::operator=(const BinTree& toCopy)
{
	root = copier(toCopy.root);
	return *this;
}

BinTree::Node* BinTree::copier(Node* treePtr)
{
	if(treePtr != NULL)
	{
		//create and initialize the new Node
		Node* newTreePtr = new Node;
		newTreePtr->data = treePtr->data;
		//set the left and right pointers
		newTreePtr->left = copier(treePtr->left);
		newTreePtr->right = copier(treePtr->right);
		treePtr = newTreePtr;
		return treePtr;

	}
	else	//else tree is empty
		return NULL;
}
//-------------------------- Destructor -----------------------------------
// Destructor for class BinTree
// Preconditions:   None
// Postconditions:
// 	  -- all memory allocated by the calling object is returned to the OS
BinTree::~BinTree()
{
	makeEmpty();
}
//------------------------------  makeEmpty  ------------------------------
// Return all allocated memory to the OS
// Preconditions:   none
// Postconditions:  all memory is returned to the OS
void BinTree::makeEmpty()
{
	reclaim(root);			
}
//------------------------------  reclaim  --------------------------------
// Helper method for the makeEmpty method
// Preconditions:   none
// Postconditions:  none
void BinTree::reclaim(Node* current)
{
	if(current != NULL)
	{
		reclaim(current->left);
		reclaim(current->right);
		delete current;
		current = NULL;
	}
}

//------------------------------  isEmpty  --------------------------------
// Print the calling BinTree object "on its side"
// Preconditions:   none
// Postconditions:  returns true if the tree is empty, false if not.
bool BinTree::isEmpty()const
{
	return root == NULL;
}
//------------------------------  displaySideways  ------------------------
// Print the calling BinTree object "on its side"
// Preconditions:   none
// Postconditions:  none
void BinTree::displaySideways()const
{
	sideways(root, 0);
}
//------------------------------  sideways  -------------------------------
// Helper method for the displaySideways method
// Preconditions:   none
// Postconditions:  none
void BinTree::sideways(Node* current, int level)const
{
	if(current != NULL)
	{
		level++;
		sideways(current->right, level);
		//indent for readability, 4 spaces per depth level
		for(int i = level; i >= 0; i--)
			cout << "    ";
		cout << *current->data << endl;
		sideways(current->left, level);
	}
}
//------------------------------  insert  -------------------------------
// Insert a specific NodeData item into the BinTree
// Preconditions:   the NodeData parameter that is being pointed to has
//					been created and initalized
// Postconditions:  returns true if sucessfully inserted, false if not
bool BinTree::insert(NodeData* dataptr)
{
	Node* ptr = new Node;     // exception is thrown if memory is not allocated
   	ptr->data = dataptr;
   	dataptr = NULL;
  	 ptr->left = ptr->right = NULL;
   	if (isEmpty())
   	 {
		root = ptr;
   	 }		
   	else 
   	{
    	Node* current = root;
      	bool inserted = false;

      	// if item is less than current item, insert in left subtree,
      	// otherwise insert in right subtree
      	while (!inserted) 
      	{
      		if(*ptr->data == *current->data)
      		{
      			return false;
      		}
        if (*ptr->data < *current->data) 
        {
           	if (current->left == NULL)               // at leaf, insert left
           	{
            	current->left = ptr;
             	inserted = true;
            }
			else
   				current = current->left;               // one step left
        }
		else 
		{
        	if (current->right == NULL) 			  // at leaf, insert right
        	{             
               current->right = ptr;
               inserted = true;
            }
            else
               current = current->right;              // one step right
         }
      }
   }
   return true;
}
//------------------------------  retrieve  -------------------------------
// Retrieve a specific NodeData item from the BinTree
// Preconditions:   the NodeData*& parameter has been created and
//					initialized
// Postconditions:  returns the NodeData* as the NodeData*& provided as a
//					parameter, returns NULL otherwise
bool BinTree::retrieve(const NodeData& toFind, NodeData*& retNode)const
{
	retNode = retrieveHelper(toFind, root);
	return retNode != NULL;
}
//------------------------------  retrieveHelper  -------------------------
// Helper method for the retrieve method
// Preconditions:   none
// Postconditions:  none
NodeData* BinTree::retrieveHelper(const NodeData& toFind, Node* current)const
{
	if(current != NULL)
	{
		if(*current->data == toFind)
			return current->data;
		if(toFind < *current->data)
			return retrieveHelper(toFind, current->left);
		else
			return retrieveHelper(toFind, current->right);
	}
	else
		return NULL;
	
}
//------------------------------  arrayToBSTree  --------------------------
// Convert the calling BinTree object to be filled with the contents of the
// array passed in.
// Preconditions:
// Postconditions:  The calling BinTree object is filled with the contents
//					of the parameterized array
//					NOTE: The parameterized array currently is
//					uneffected by this method. Needs to be changed to
//					be empty after conversion to a BinTree.
void BinTree::arrayToBSTree(NodeData* theArray[])
{
	int numActive = 0;
	for(int i = 0; i < 100; i++)
	{
		if(theArray[i] == NULL)
			break;
		numActive++;
	}
	root = treeBuilder(theArray, 0,numActive);
}
//------------------------------  treeBuilder  --------------------------
// Helper method for the arrayToBSTree method
// Preconditions:   none
// Postconditions:  none
BinTree::Node* BinTree::treeBuilder(NodeData* theArray[], int start, int end)
{
	if(start >= end)
		return NULL;
	int mid = start + (end - start) / 2;
	if(!((start + end) % 2) && mid != 2)
		mid = (mid + (mid - 1))/2;
	Node* current = new Node();
	if(theArray[mid] != NULL)
	{
		current->data = new NodeData(*theArray[mid]);
		theArray[mid] = NULL;	
		current->left = treeBuilder(theArray, start, mid-1);
		current->right = treeBuilder(theArray, mid+1, end);		
		return current;
	}
	else
		return NULL;

	
	
	
	
}
//------------------------------  bstreeToArray  --------------------------
// Convert the calling BinTree object to a sorted array of NodeData*'s
// Preconditions:   the array is expected to be of size 100 and be full of
//					NULLs
// Postconditions:  The array passed is filled with the contents of the
//					calling BinTree object.
//					NOTE: The calling BinTree object currently is
//					uneffected by this method. Needs to be changed to
//					be empty after conversion to an array.
void BinTree::bstreeToArray(NodeData* anArray[])
{
	arrayBuilder(0,root,anArray);
	for(int i = 0; i < 100; i++)
	{
		if(anArray[i] == NULL)
			break;
		else
			cout << *anArray[i] << endl;
	}
}
//------------------------------  arrayBuilder  --------------------------
// Helper method for the bstreeToArray method
// Preconditions:   none
// Postconditions:  none
int BinTree::arrayBuilder(int index, Node* current, NodeData* theArray[])
{
	if(current->left != NULL)
		index = arrayBuilder(index,current->left,theArray);
	//cout <<"inserting " << *current->data << " into index " << index << endl;
	//ptrSwap(current->data, theArray[index++]);
	theArray[index++] = new NodeData(*current->data);
	delete current->data;
	current->data = NULL;
	//current->data = NULL;
	if(current->right != NULL)
		index = arrayBuilder(index, current->right, theArray);	
	return index;
}
//------------------------------  printInOrder  ---------------------------
// Print the result of a in-order depth first traversal
// Preconditions:   none
// Postconditions:  none
void BinTree::printInOrder()const
{
	inOrderHelper(root);
}
//------------------------------  inOrderHelper  --------------------------
// Helper method for the printInOrder method
// Preconditions:   none
// Postconditions:  none
void BinTree::inOrderHelper(Node* current)const
{
	if(current->left != NULL)
		inOrderHelper(current->left);
	cout << *current->data << endl;
	if(current->right != NULL)
		inOrderHelper(current->right);
}
//------------------------------  ==  -------------------------------------
// Determine if two binary search trees are equal.
// Preconditions:   ptr and right.ptr point to BinTrees with
//                    at least one non-null member each
// Postconditions:  true is returned if the BinTrees have the exact
//                    same members and structure,
//					  false is return otherwise
bool BinTree::operator==(const BinTree& rhs)const
{
	return(root == NULL && rhs.root == NULL)
		   ||(root != NULL && rhs.root != NULL && 
		   	  *root->data == *rhs.root->data);
}
//------------------------------  !=  -------------------------------------
// Determine if two binary search trees are unequal.
// Preconditions:   ptr and right.ptr point to BinTrees with
//                    at least one non-null member each
// Postconditions:  true is returned if the BinTrees have any of the
//                    same members, false is return otherwise
bool BinTree::operator!=(const BinTree& rhs)const
{
	return !(*this == rhs);
}
//------------------------------  getDepth  -------------------------------
// Find the depth of a specific NodeData item from the BinTree
// Preconditions:   the NodeData& parameter has been created and
//					initialized
// Postconditions:  returns the depth of the given NodeData item, with
//					the root being at level 1.
int BinTree::getDepth(const NodeData& toMeasure)const
{
	depthHelper(toMeasure, root, 1);
}
//------------------------------  depthHelper  ----------------------------
// Helper method for the getDepth method
// Preconditions:   none
// Postconditions:  none
int BinTree::depthHelper(const NodeData& toFind, Node* current, int level)const
{
	if(current == NULL)
		return 0;
	if(*current->data == toFind)
		return level;

	int level_down = depthHelper(toFind, current->left, level+1);

	if(level_down != 0)
		return level_down;

	level_down = depthHelper(toFind, current->right, level+1);
	return level_down;
}
//------------------------------  NON-FUNCTIONAL/USEFUL METHODS  --------------
void BinTree::ptrSwap(NodeData* lhs, NodeData* rhs)
{
	//lhs: theArray[index++]
	//rhs: current->data
	//tmp: NULL
	NodeData* tmp = NULL;
	// if(lhs == NULL)
	// 	cout << "left hand side in swap: NULL" << endl;
	// else
	// 	cout << "left hand side in swap: " << *lhs << endl;

	// if(rhs == NULL)
	// 	cout << "right hand side in swap: NULL" << endl;
	// else
	// 	cout << "right hand side in swap: " << *rhs << endl;
	// if(tmp == NULL)
	// 	cout << "tmp in swap: NULL" << endl;
	// else
	// 	cout << "tmp in swap: " << *tmp << endl;
	// cout << "------------------------------" << endl;
	tmp = lhs;
	//tmp = theArray[index++](NULL)
	lhs = rhs;
	//lhs = current->data
	rhs = tmp;
	//current->data = theArray[index++](NULL)

}

ostream& operator<<(ostream& out, const BinTree& toOut)
{
	toOut.printHelper(out);
	return out;
}

void BinTree::printHelper(ostream& out)const
{
	printTree(out, root);
}

void BinTree::printTree(ostream& out, Node* current)const
{
	if(current)
	{
		printTree(out, current->left);
		out << *current->data << endl;
		printTree(out, current->right);
	}
}

void BinTree::fillWithNulls()
{
	nullHelper(root);
}

void BinTree::nullHelper(Node* current)
{
	cout << *current->data << endl;
	if(current != NULL)
	{
		cout << "current isn't null"  << endl;
		nullHelper(current->left);
		nullHelper(current->right);
	}
	delete current->data;
	current->data = NULL;
			
}

NodeData* BinTree::getRootData()const
{
	return root->data;
}