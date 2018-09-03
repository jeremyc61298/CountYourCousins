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

void buildTree(ifstream& fin, vector<Node> &familyTree, int numNodes)
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
			node.grandparent = familyTree[childlessNodes.front()].grandparent;
		}

		familyTree.push_back(node);
		childlessNodes.pop();
		// i + 1 is the node that was just placed in the tree
		childlessNodes.push(i + 1);
	}
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
	vector<Node> familyTree;
	int numNodes, nodeToFind;
	fin >> numNodes >> nodeToFind;

	while (numNodes != 0 && nodeToFind != 0)
	{
		buildTree(fin, familyTree, numNodes);
		fin >> numNodes >> nodeToFind;
	}
	
}