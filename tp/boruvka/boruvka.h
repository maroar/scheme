#ifndef BORUVKA_H
#define BORUVKA_H

#include "../graph/graph.h"
#include <list>

struct Component
{
	Component * parent;
	int ID, rank;
}typedef Component;

template <typename T> bool PComp(T * const & a, T * const & b)
{
   return *a < *b;
}

class Boruvka
{
private:
	Component * find(Component* components);
	void Union(Component * cp1, Component * cp2);
	void printComponents(Component *components, int size);
	Component * makeSet(int ID);


public:
	Boruvka() {};
	~Boruvka() {};
	std::list<Edge*> getMST(Graph* G);
	
};


#endif