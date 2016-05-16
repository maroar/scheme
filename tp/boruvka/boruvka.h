#ifndef BORUVKA_H
#define BORUVKA_H

#include "../graph/graph.h"
#include <list>

struct Component
{
	Component * parent;
	int ID, rank;
}typedef Component;

class Boruvka
{
private:
	Component * find(Component* components);
	void Union(Component * cp1, Component * cp2);
	void printComponents(Component *components, int size);

public:
	Boruvka() {};
	~Boruvka() {};
	std::list<Edge*> getMST(Graph* G);
	
};


#endif