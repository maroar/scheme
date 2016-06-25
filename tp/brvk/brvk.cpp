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
  vector<int> cheapest(n+1);
  for (int i = 1; i <= n; i++) {
    node = G[i];
    c = new Component(node);
    node->c = c;
    C[i-1] = c;
    cheapest[i] = -1;
  }
  // BORUVKA
  int tree_weight = 0;
  while (size > 1)
  {
    // traverse through all edges and update cheapest of every component
    for (int i = 0; i < (m<<1); i++) {
      pComponent set1 = G.E[i]->u->c->find_set();
      pComponent set2 = G.E[i]->v->c->find_set();
      if (set1 == set2) {
        continue;
      } else {
        if (cheapest[set1->id] == -1 || G.E[cheapest[set1->id]]->weight > G.E[i]->weight)
          cheapest[set1->id] = i;
        if (cheapest[set2->id] == -1 || G.E[cheapest[set2->id]]->weight > G.E[i]->weight)
          cheapest[set2->id] = i;
      }
    }
    // Consider the above picked cheapest edges and add them to MST
    for (int i = 1; i <= n; i++) {
      if (cheapest[i] != -1) {
        pComponent set1 = G.E[cheapest[i]]->u->c->find_set();
        pComponent set2 = G.E[cheapest[i]]->v->c->find_set();

        if (set1 == set2) {
          continue;
        }

        tree_weight += G.E[cheapest[i]]->weight;
        Component::union_set(set1, set2);
        cheapest[set1->id] = cheapest[set2->id] = -1;
        size--;
      }
    }
  }
  cout << tree_weight << endl;
  while(!C.empty()) {
    if (C.back())
      delete C.back(); 
    C.pop_back();
  }
  return 0;
}