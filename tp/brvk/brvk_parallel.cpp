#include <iostream>
#include <iterator>
#include <list>
#include <omp.h>
#include "graph.h"
#include "Component.h"

#define NUM_THREADS 8

using namespace std;


int main(int argc, char **argv) 
{
  omp_set_nested(1);
  omp_set_num_threads(NUM_THREADS);

  // READ THE GRAPH
  int m, n, u, v, w;
  // read graph size
  cin >> n;
  cin >> m;
  // create graph
  Graph G(n, m, undirected);
  // read edges
  for (int i = 0; i < m; i++) {
    cin >> u;
    cin >> v;
    cin >> w;
    G.add_edge(u, v, w);
  }

  // CREATE THE COMPONENTS
  pComponent c;
  pNode node;
  list<pComponent> C, all;

  // #pragma omp parallel for num_threads(NUM_THREADS)
  for (int i = 1; i <= n; i++)
  {
    node = G[i];
    c = new Component(node);
    node->c = c;
    C.push_back(c);
    c->pos = prev(C.end());
  }
  
  all = C;

  // BORUVKA
  int tree_weight = 0;
  list<pComponent>::iterator it, nxt;
  int size = C.size();
  while (size > 1) 
  {
    #pragma omp parallel
    #pragma omp single
    {
      for (list<pComponent>::iterator cc = C.begin(); cc != C.end(); ++cc)
      {
        #pragma omp task
        (*cc)->get_best_edge();
      }      
    }

    it = C.begin();
    nxt = next(it);
    while (it != C.end())
    {
      it = Component::union_components(it, nxt, C, &tree_weight);
      nxt = next(it);
    }
    size = C.size();
  }
  cout << tree_weight << endl;
  while(!all.empty()) delete all.back(), all.pop_back();
  return 0;
}