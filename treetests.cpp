#include "bintree.h"
#include <iostream>

using namespace std;

const int ARRAY_SIZE = 100;

void buildTree(BinTree&, ifstream&);
void initArray(NodeData* []);             // initialize array to NULL
void printArray(NodeData* []);

int main()
{
	ifstream infile("data2.txt");
   	if (!infile) {
      cout << "File could not be opened." << endl;
      return 1;
   	}


	BinTree tree1,tree2;
	NodeData notND("not");
   	NodeData andND("and");
   	NodeData sssND("sss");
   	NodeData eND("e");
   	NodeData mND("m");
   	NodeData tND("t");

	NodeData* ndArray[ARRAY_SIZE];
	initArray(ndArray);
	buildTree(tree1, infile);
  buildTree(tree2, infile);
	cout << endl;
	if(tree1.isEmpty())
		cout << "The tree is empty!" << endl;
	tree1.displaySideways();
  cout << endl << "-------------" << endl;
  tree2.displaySideways();

	cout << "tree1.In order: " << endl << "-----------" << endl;
	tree1.printInOrder();
	cout << "-----------" << endl;
  cout << "tree2.In order: " << endl << "-----------" << endl;
  tree2.printInOrder();
  cout << "-----------" << endl;
  if(tree1 != tree2)
    cout << "tree1 is not equal to tree2!" << endl;
  else
    cout << "tree1 is equal to tree2!" << endl;
	tree1.bstreeToArray(ndArray);
	printArray(ndArray);
  tree1.arrayToBSTree(ndArray);
  tree1.displaySideways();
  tree1.printInOrder();
  if(tree1.isEmpty())
    cout << "The tree is empty!" << endl;
  else
    cout << "the tree is still populated!" << endl;

	
	NodeData* p;                    // pointer of retrieved object
  bool found;                     // whether or not object was found in tree
  found = tree1.retrieve(andND, p); 
  cout << "Retrieve --> and:  " << (found ? "found":"not found") << endl;
  found = tree1.retrieve(notND, p);
  cout << "Retrieve --> not:  " << (found ? "found":"not found") << endl;
  found = tree1.retrieve(sssND, p);
  cout << "Retrieve --> sss:  " << (found ? "found":"not found") << endl;

  cout << "Depth    --> and:  " << tree1.getDepth(andND) << endl;
  cout << "Depth    --> not:  " << tree1.getDepth(notND) << endl;
  cout << "Depth    --> sss:  " << tree1.getDepth(sssND) << endl;

	return 0;
}

//------------------------------- buildTree ----------------------------------
// YOU COMMENT

// To build a tree, read strings from a line, terminating when "$$" is
// encountered. Since there is some work to do before the actual insert that is
// specific to the client problem, it's best that building a tree is not a 
// member function. It's a global function. 

void buildTree(BinTree& T, ifstream& infile) {
   string s;

   for (;;) {
      infile >> s;
      cout << s << ' ';
      if (s == "$$") break;                // at end of one line
      if (infile.eof()) break;             // no more lines of data
      NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
      // would do a setData if there were more than a string

      bool success = T.insert(ptr);   
      if (!success)
         delete ptr;                       // duplicate case, not inserted 
   }
}

void initArray(NodeData* theArray[])
{
	for(int i = 0; i < ARRAY_SIZE; i++)
		theArray[i] = NULL;
}

void printArray(NodeData* theArray[])
{
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		if(theArray[i] == NULL)
      break;
		  cout << *theArray[i] << endl;
	}
}
