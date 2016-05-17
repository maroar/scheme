#include <iostream>
#include <stdlib.h>
#include <vector>

#include "../graph/graph.h"
#include "../set/set.h"

#define MYINF 10000

using namespace std;
//Graph
int n, m;
//Kruskal
pSet *set;
pEdge *best_edge;

void init()
{
  set = (pSet*) malloc((n+1)*sizeof(pSet));
  best_edge = (pEdge*) malloc((n+1)*sizeof(pEdge));
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
  free(best_edge);
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
  int tree_weight = 0, num_sub_trees;
  Graph G(undirected);
  pEdge e;
  G.read_edges();
  G.sort_edges();
  vector< list<void*> > adj(n+1);
  num_sub_trees = n;

  for (auto& e : G.E) {
    adj[e->u->id].push_back((void*) e);
  }

  for (int i = 1; i <= n; i++) {
    best_edge[i] = (pEdge) adj[i].front();
  }

  init();

  int u, v, w;
  while (num_sub_trees > 1) {
    //cout << "------------0" << endl;
    for (int i = 1; i <= n; i++) {
      //cout << "------------" << i << endl;
      e = (pEdge) adj[i].front();
      //cout << "e:" << e->weight << "  be:" << best_edge[find_set(set[i])->setId]->weight << endl;
      if (e->weight < best_edge[find_set(set[i])->setId]->weight)
        best_edge[find_set(set[i])->setId] = e;
      adj[i].pop_front();
    }
    //cout << "------------inf" << endl;
    for (int i = 1; i <= n; i++) {
      pSet root = find_set(set[i]);
      u = best_edge[root->setId]->u->id;
      v = best_edge[root->setId]->v->id;
      w = best_edge[root->setId]->weight;
      
      pSet rootU = find_set(set[u]);
      pSet rootV = find_set(set[v]);
      if (rootU != rootV) {
        //add edge
        cout << u << " - " << v << "("<< w  << ")" << endl;
        tree_weight += w;
        //make union
      }
    }
  }
  
  cout << "w: " << w << endl;

  erase_data();
  
  return 0;
}