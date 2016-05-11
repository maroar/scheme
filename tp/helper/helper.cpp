#include <iostream>
#include "helper.h"

using namespace std;
static int n, m, u, v, w;
Graph *g;

void build_graph()
{
  cin >> n;
  cin >> m;
  g = new Graph(n, m);
}

void read_undirected_edges()
{
  for (int i = 1; i <= m; i++) {
    cin >> u;
    cin >> v;
    cin >> w;
    g->add_edge(u, v, w);
  }
}

Graph* read_undirected_graph() {
  build_graph();
  read_undirected_edges();
  
  return g;
}

void read_directed_edges()
{
  for (int i = 1; i <= m; i++) {
    cin >> u;
    cin >> v;
    cin >> w;
    g->add_edge_(u, v, w);
  }
}

Graph* read_directed_graph() {
  build_graph();
  read_directed_edges();
  
  return g;
}