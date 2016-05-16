#include "boruvka.h"
#include <list>
#include <vector>
#include <iostream>
#define DEBUG

//Union-find algorithm. Each component is represented by a 
//ROOT node. If two components have the same ROOT, they are obviously
//connected. This FIND algorithm finds the root for one component.
Component * Boruvka::find(Component *cp)
{
	Component * root = cp;
	Component * temp;

	while (root->parent != NULL)
		root = root->parent;

	while (cp->parent != NULL)
	{
		temp = cp->parent;
		cp->parent = root;
		cp = temp;
	}

	return root;
}

//This function makes the union between components in
//which the nodes X and Y are.
void Boruvka::Union(Component * cp1, Component * cp2)
{
	Component * xRoot = Boruvka::find(cp1);
	Component * yRoot = Boruvka::find(cp2);

	if (xRoot->rank > yRoot->rank)
	{
		yRoot->parent = xRoot;
	}
	else if (yRoot->rank > xRoot->rank)
	{
		xRoot->parent = yRoot;
	}
	else
	{
		yRoot->parent = xRoot;
		xRoot->rank++;
	}
}

Component * Boruvka::makeSet(int ID)
{
	Component * cp = new Component;
	cp->ID = ID;
	cp->parent = NULL;
	cp->rank = 0;

	return cp;
}

void Boruvka::printComponents(Component * components, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "Component: "
							<< components[i].ID 
							<< " Rank: "
							<< components[i].rank
							<< " Root: "
							<< ((components[i].parent != NULL) ? components[i].parent->ID : components[i].ID)
							<< std::endl;
	}
}

int n, m;
std::list<Edge*> Boruvka::getMST(Graph* G)
{
	std::list<Edge*> MST;
	if (G == NULL)
	{
		std::cout<<"Graph not initialized. " << std::endl;
		return MST;
	}
	#ifdef DEBUG
		G->print();
	#endif

	int numNodes = n;
	int numEdges = m;

	//Every component
	Component *components[numNodes];

	//Best edge for each node
	Edge *edges[numNodes];

	//Make set of 1 node per component initially
	//Get the best edge for each node
	for (unsigned u = 0; u < numNodes; u++)
		(*G)[u+1]->adj.sort();
		edges[u] = (*G)[u+1]->adj.front();
		components[u] = makeSet(u+1);

	int e = 0;
	int MAX_MST_EDGES = numNodes - 1;

	//While 
	while (e <= MAX_MST_EDGES)
	{
		for (unsigned u = 0; u < numNodes; u++)
		{
			Component * cp1 = find(components[u]);
		}
	}


	return MST;
}