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
	makeEmpty();
}

void BinTree::makeEmpty()
{
	reclaim(root);
}

void BinTree::reclaim(Node*& current)
{
	if(current)
	{
		reclaim(current->left);
		reclaim(current->right);
		delete current->data;
		delete current;
	}
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
	retNode = retrieveHelper(toFind, root);
	return retNode != NULL;
}

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

void BinTree::bstreeToArray(NodeData* anArray[])
{
	arrayBuilder(0,root,anArray);
}

int BinTree::arrayBuilder(int index, Node* current, NodeData* theArray[])
{
	
	if(current->left != NULL)
		index = arrayBuilder(index,current->left,theArray);
	//cout <<"inserting " << *current->data << " into index " << index << endl;
	theArray[index++] = current->data;
	if(current->right != NULL)
		index = arrayBuilder(index, current->right, theArray);	
	return index;
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
