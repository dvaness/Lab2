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

BinTree::~BinTree()
{
	reclaim(root);
}

void BinTree::reclaim(Node* current)
{
	if(current != NULL && current->data != NULL)
	{
		reclaim(current->left);
		reclaim(current->right);
		delete current;
		delete current->data;
		current->data = NULL;
		current = NULL;
	}
}

ostream& operator<<(ostream& out, const BinTree& toOut)
{

}

bool BinTree::isEmpty()const
{
	return root == NULL;
}

void BinTree::displaySideways()const
{
	sideways(root, 0);
}

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

bool BinTree::retrieve(const NodeData& toFind, NodeData*& retNode)const
{
	retNode = retrieveHelper(toFind,root);
	return retNode == NULL;
}

NodeData* BinTree::retrieveHelper(const NodeData& toFind, Node* current)const
{
	if(toFind < *current->data)
		retrieveHelper(toFind, current->left);
	else if(toFind > *current->data)
		retrieveHelper(toFind, current->right);
	else
		return current->data;
}

void BinTree::bstreeToArray(NodeData* anArray[])
{
	// Node* parent = NULL;
	// Node* current = root;
	// int currentIndex = 0;
	// while(current->left != NULL)
	// {
	// 	parent = current;
	// 	current = current->left;
	// }
	// cout << *current->data << endl;
	// cout << *parent->data << endl;
	// cout << *parent->right->data << endl;
	// //anArray[currentIndex] = parent->data;
	// //currentIndex++;
	// //parent = current->right;
	// parent = NULL;
	// current = root;

	// while(current->right != NULL)
	// {
	// 	//anArray[currentIndex] = current->data;
	// 	parent = current;
	// 	current = current->right;
	// }
	// cout << *parent->left->data << endl;
	// cout << *parent->data << endl;
	// cout << *current->data << endl;
	arrayBuilder(0,root,anArray);
}

void BinTree::arrayBuilder(int index, Node* current, NodeData* theArray[])
{
	cout <<"current in array builder: " << *current->data << endl;
	if(current->left != NULL)
		arrayBuilder(index,current->left,theArray);
	theArray[index++] = current->data;
	if(current->right != NULL)
		arrayBuilder(index, current->right, theArray);
}

void BinTree::printInOrder()const
{
	inOrderHelper(root);
}

void BinTree::inOrderHelper(Node* current)const
{
	if(current->left != NULL)
		inOrderHelper(current->left);
	cout << *current->data << endl;
	if(current->right != NULL)
		inOrderHelper(current->right);
}