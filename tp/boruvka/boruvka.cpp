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
	// #ifdef DEBUG
	// 	G->print_edges();
	// #endif

	int numNodes = n;
	int numEdges = m;

	std::vector<Edge*> allEdges{std::begin(G->E), std::end(G->E)};

	//Every component
	Component *components[numNodes];

	// //Best edge for each node
	// Edge *edges[numNodes];

	//Stores the index for the best edges
	int *bestEdgesIndexes;
	bestEdgesIndexes = new int[numNodes];

	//Make set of 1 node per component initially
	//Get the best edge for each node
	for (unsigned u = 0; u < numNodes; u++)
	{
		bestEdgesIndexes[u] = -1;
		components[u] = makeSet(u+1);
	}
		
	int e = 0;
	int MAX_MST_EDGES = numNodes - 1;
	int MST_WEIGHT = 0;

	std::cout << "Max number of edges: " << MAX_MST_EDGES << std::endl;

	//While 
	while (e < MAX_MST_EDGES)
	{
		//Update the best edges for each component again!
		for (unsigned i = 0; i < allEdges.size(); i++)
		{
			Edge ed = *allEdges[i];
			int u = ed.u->id;
			int v = ed.v->id;
			Component * cp1 = find(components[u-1]);
			Component * cp2 = find(components[v-1]);
			if (cp1 == cp2)
			{
				continue;
			}			
			if ((bestEdgesIndexes[u-1] == - 1) || (ed < *allEdges[bestEdgesIndexes[u-1]]))
			{
				bestEdgesIndexes[u-1] = i;
			}
			if((bestEdgesIndexes[v-1] == -1) || (ed < *allEdges[bestEdgesIndexes[v-1]]))
			{
				bestEdgesIndexes[v-1] = i;
			}
		}

		for (unsigned u = 0; u < numNodes; u++)
		{
			Edge ed = *allEdges[bestEdgesIndexes[u]];
			Component * cp1 = find(components[ed.u->id-1]);
			Component * cp2 = find(components[ed.v->id-1]);
			if (cp1 != cp2)
			{
				#ifdef DEBUG
					std::cout << "picking edge: ";
					ed.print();
				#endif
				e++;
				MST.push_back(&ed);
				MST_WEIGHT += ed.weight;
				Union(cp1, cp2);
				allEdges.erase(allEdges.begin() + (bestEdgesIndexes[u]));
				bestEdgesIndexes[u] = - 1;
			}
		}

		

	}

	std::cout<<"\n\nWeight of MST: " << MST_WEIGHT << std::endl;

	return MST;
}