// ----------------------------------------------------------------------------------
// cousins.cpp
// Jeremy Campbell
// Given a tree hierarchy, the program can find out which of the nodes are "cousins",
// having different parents but the same grandparent.
// ----------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::queue;

struct Node
{
	int id;
	int parent;
	int grandparent;
};

Node buildTree(ifstream& fin, vector<Node> &familyTree, int numNodes, int nodeToFind)
{
	// Hold the indexes of the nodes without children
	queue<int> childlessNodes;

	// Read in root
	Node node;
	fin >> node.id;
	node.grandparent = 0;
	node.parent = 0;
	familyTree.push_back(node);
	childlessNodes.push(0);
	
	// Curious is initialized to the first node in case there is only one node
	Node curious = node;

	for (int i = 0; i < numNodes - 1; i++)
	{
		fin >> node.id;
		if (familyTree[i].id == node.id - 1)
		{
			// The nodes are siblings
			node.parent = familyTree[i].parent;
			node.grandparent = familyTree[i].grandparent;
		}
		else
		{
			// The input is no longer continuous, find the first node without children
			node.parent = familyTree[childlessNodes.front()].id;
			node.grandparent = familyTree[childlessNodes.front()].parent;
			childlessNodes.pop();
		}

		familyTree.push_back(node);
		// i + 1 is the node that was just placed in the tree
		childlessNodes.push(i + 1);

		if (node.id == nodeToFind)
		{
			curious = node;
		}
	}
	return curious;
}

// nodeToFind is the ID of the node, not the index in the vector
int countCousins(vector<Node> &familyTree, Node curious)
{
	int cousinCount = 0;
	if (curious.id != familyTree[0].id && curious.parent != familyTree[0].id)
	{
		for (auto leaf : familyTree)
		{
			if (leaf.grandparent == curious.grandparent &&
				leaf.parent != curious.parent &&
				leaf.id != curious.id)
			{
				cousinCount++;
			}
		}
	}
	return cousinCount;
}

int main()
{
	ifstream fin("cousins.in");
	if (!fin)
	{
		cout << "Input file could not be opened. " << endl;
		return -1;
	}

	ofstream fout("cousins.out");
	int numNodes, nodeToFind;
	fin >> numNodes >> nodeToFind;

	while (numNodes != 0 && nodeToFind != 0)
	{
		vector<Node> familyTree;
		Node curious = buildTree(fin, familyTree, numNodes, nodeToFind);
		int cousins = countCousins(familyTree, curious);
		fout << cousins;
		fin >> numNodes >> nodeToFind;

		if (numNodes != 0 && nodeToFind != 0)
		{
			fout << endl;
		}
	}
	
	return 0;
}