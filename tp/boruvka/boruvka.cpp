#include "boruvka.h"
#include <list>
#include <vector>
#include <iostream>
// #define DEBUG

//Union-find algorithm. Each component is represented by a 
//ROOT node. If two components have the same ROOT, they are obviously
//connected. This FIND algorithm finds the root for one component.
int Boruvka::find(Component *components, int i)
{
	if (components[i-1].parentID != i)
		components[i-1].parentID = 
			Boruvka::find(components, components[i-1].parentID);

	return components[i-1].parentID;
}

//This function makes the union between components in
//which the nodes X and Y are.
void Boruvka::Union(Component * components, int x, int y)
{
	int x_root = Boruvka::find(components, x);
	int y_root = Boruvka::find(components, y);

	if (components[x_root-1].rank < components[y_root-1].rank)
		components[x_root-1].parentID = y_root;
	else if (components[x_root-1].rank > components[y_root-1].rank)
		components[y_root-1].parentID = x_root;

	//If the ranks are the same, just unite them and make one of them as root
	else
	{
		components[y_root-1].parentID = x_root;
		components[x_root-1].rank++;
	}

}

void Boruvka::printComponents(Component * components, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << components[i].parentID 
							<< " Rank: "
							<< components[i].rank
							<< std::endl;
	}
}

std::list<Edge*> Boruvka::getMST(Graph* G)
{
	std::list<Edge*> MST;
	if (G == NULL)
	{
		std::cout<<"Graph not initialized. " << std::endl;
		return MST;
	}
	int numNodes = G->n;
	int numEdges = G->m;
	std::vector<Edge*> edges{std::begin(G->E), std::end(G->E)};
	// #ifdef DEBUG
	// 	std::cout << "\nEDGES: " << std::endl;
	// 	for (std::vector<Edge*>::iterator it = edges.begin(); it != edges.end(); ++it)
	// 	{
	// 		(*it)->print();
	// 		std::cout<<std::endl;
	// 	}
	// #endif

	//In the beginning, each node is a component. There are V components.
	Component * components = new Component[numNodes];

	//An array that stores the best/cheapest edge for each subset.
	int * bestEdge = new int[numNodes];

	//Create V components with one Node each
	for (unsigned u = 0; u < numNodes; u++)
	{
		components[u].parentID = u+1;
		components[u].rank = 0;
		bestEdge[u] = -1;
	}

	// #ifdef DEBUG
	// 	Boruvka::printComponents(components, numNodes);
	// #endif

	//Starting with an empty MST and number of components = V
	int numComponents = numNodes;
	int MSTWeight = 0;

	while (numComponents > 1)
	{
		//Traverse through every EDGE and update the best edge for every component
		for (unsigned u = 0; u < numEdges; u++)
		{
			//Get the ID's of the nodes of the current edge
			int source_ID = edges[u]->u->id;
			int dest_ID = edges[u]->v->id;

			// #ifdef DEBUG
			// 	std::cout << "\nanalising edge: ";
			// 	edges[u]->print();
			// #endif

			//Find components of each node of the current edge
			int component_1 = Boruvka::find(components, source_ID);
			int component_2 = Boruvka::find(components, dest_ID);

			// #ifdef DEBUG
			// 	std::cout << "Component U: "
			// 						<< component_1
			// 						<< " Component V: "
			// 						<< component_2
			// 						<< std::endl;
			// #endif

			if (component_1 == component_2)
				continue;
			else
			{
				if ((bestEdge[component_1 - 1] == -1) || 
							(edges[bestEdge[component_1 - 1]]->weight > edges[u]->weight))
				{
					bestEdge[component_1 - 1] = u;
				}
				if ((bestEdge[component_2 - 1] == -1) || 
							(edges[bestEdge[component_2 - 1]]->weight > edges[u]->weight))
				{
					bestEdge[component_2 - 1] = u;
				}
			}
		}

		//add the cheapest edges to the MST
		for (unsigned u = 0; u < numNodes; u++)
		{
			if (bestEdge[u] != -1)
			{
				//Get the ID's of the nodes of the current edge
				int source_ID = edges[bestEdge[u]]->u->id;
				int dest_ID = edges[bestEdge[u]]->v->id;

				//Find components of each node of the current edge
				int component_1 = Boruvka::find(components, source_ID);
				int component_2 = Boruvka::find(components, dest_ID);

				if (component_1 == component_2)
					continue;
				MSTWeight += edges[bestEdge[u]]->weight;
				MST.push_back(edges[bestEdge[u]]);
				// #ifdef DEBUG
					std::cout << "Edge Included: " 
										<< edges[bestEdge[u]]->u->id 
										<< " To "
										<< edges[bestEdge[u]]->v->id 
										<< " Weight: " 
										<< edges[bestEdge[u]]->weight
										<< std::endl;
				// #endif
				//Union of the components that were connected
				Boruvka::Union(components, component_1, component_2);
				numComponents--;
			}
		}
	}
	std::cout << "Weight of the MST is " << MSTWeight << std::endl;

	return MST;
}