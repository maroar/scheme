#include <iostream>
#include <stdlib.h>

#include "../graph/graph.h"
#include "../set/set.h"

#define MYINF 10000

using namespace std;
//Graph
int n, m;
//Kruskal
pSet *set;

void init()
{
  set = (pSet*) malloc((n+1)*sizeof(pSet));
  for (int i = 1; i <= n; i++) {
    set[i] = make_set(i);
  }
}

void erase_data() 
{
  for (int i = 1; i <= n; i++) {
    delete set[i];
  }
  free(set);
}

void print_set()
{
  for (int i = 1; i <= n; i++) {
    cout << set[i]->setId << "(" << set[i]->order << ", p={" << set[i]->parent->setId << "}) ";
  }
  cout << endl;
}

pEdge next_edge(list<pEdge>::iterator& it)
{
  int u, v;
  
  do {
    u = (*it)->u->id;
    v = (*it)->v->id;
    it++;
  } while (find_set(set[u]) == find_set(set[v]));
  
  union_set(set[u], set[v]);

  return (*it);
}

int main(int argc, char *argv[]) 
{
  int i, tree_weight = 0;
  pEdge e;
  list<pEdge>::iterator it;
  
  Graph G(undirected);
  G.read_edges();
  G.sort_edges();

  init();
  
  it = G.E.begin();
  for (i = 1; i < n; i++) {
    //print_set();
    e = next_edge(it);
    e->print();
    //print_set();
    cout << "-----------" << endl;
    tree_weight += e->weight;
  }
  
  cout << tree_weight << endl;
  
  erase_data();
  
  return 0;
}