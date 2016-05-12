#include <iostream>
#include <stdlib.h>

#include "../graph/graph.h"
//#include "../heap/heap.h"

#define MYINF 10000

using namespace std;
//Graph
int n, m;
//Kruskal
int *group;

void init()
{
  group= (int*) malloc((n+1)*sizeof(int));
}

void erase_data() 
{
  free(group);
}

void print_group()
{
  for (int i = 1; i <= n; i++) {
    cout << i << "(" << group[i] << ") ";
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
  } while (group[u] == group[v]);
  
  if (group[u] < group[v])
    group[v] = group[u];
  else
    group[u] = group[v];

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
  for (i = 0; i <= n; i++) {
    group[i] = i;
  }
  
  it = G.E.begin();
  for (i = 1; i < n; i++) {
    print_group();
    e = next_edge(it);
    e->print();
    print_group();
    cout << "-----------" << endl;
    tree_weight += e->weight;
  }
  
  cout << tree_weight << endl;
  
  erase_data();
  
  return 0;
}