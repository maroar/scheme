#include <iostream>
#include <iterator>
#include <vector>
#include "graph.h"
#include "Component.h"

using namespace std;

int main(int argc, char **argv) 
{
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
  int size = n;
  pComponent c;
  pNode node;
  vector<pComponent> C(n);
  for (int i = 1; i <= n; i++) {
    node = G[i];
    c = new Component(node);
    node->c = c;
    C[i-1] = c;
    c->pos = i-1;
  }
  // BORUVKA
  int tree_weight = 0;
  //list<pComponent>::iterator it, nxt, itc;
  while (size > 1)
  {
    for (int i = 0; i < size; i++)
    {
      C[i]->get_best_edge();
    }
    // #ifdef DEBUG
    //   for (int i = 0; i < size; i++) {
    //     C[i]->print();
    //   }
    //   cout << endl << "----------------" << endl;
    // #endif
    for (int i = 0; i < size; )
    {
      if (Component::union_components(i, C, &size, &tree_weight))
        i++;
    }
    // #ifdef DEBUG
    //   for (int i = 0; i < size; i++) {
    //     C[i]->print();
    //   }
    //   cout << endl << "__________________________________" << endl;
    // #endif
  }
  cout << tree_weight << endl;
  while(!C.empty()) {
    if (C.back())
      delete C.back(); 
    C.pop_back();
  }
  return 0;
}