#ifndef BORUVKA_H
#define BORUVKA_H

#include "../graph/graph.h"
#include <list>

struct Component
{
	int parentID;
	int rank;
}typedef Component;

class Boruvka
{
private:
	int find(Component* components, int i);
	void Union(Component* components, int x, int y);
	void printComponents(Component *components, int size);

public:
	Boruvka() {};
	~Boruvka() {};
	std::list<Edge*> getMST(Graph* G);
	
};


#endif