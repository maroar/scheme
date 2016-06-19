#include <iostream>
#include <iterator>
#include <list>
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
  pComponent c;
  pNode node;
  list<pComponent> C, all;
  for (int i = 1; i <= n; i++) {
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
  list<pComponent>::iterator it, nxt, itc;
  while (C.size() > 1) {
    for (auto& c : C) {
      c->get_best_edge();
    itc = it = C.begin();
    for ( ; itc != C.end(); itc++) {
      (*itc)->get_best_edge();
    }
    it = C.begin();
    nxt = next(it);
    while (it != C.end()) {
      it = Component::union_components(it, nxt, C, &tree_weight);
      nxt = next(it);
    }
  }
  cout << tree_weight << endl;
  while(!all.empty()) delete all.back(), all.pop_back();
  return 0;
}