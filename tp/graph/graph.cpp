#include <iostream>
#include <stdlib.h>
#include "graph.h"

using namespace std;
// Others
template <typename T> bool PComp(T * const & a, T * const & b)
{
   return *a < *b;
}
// Node
void Node::add_edge(pNode v)
{
  adj.push_back(new Edge(this, v, 0));
}

void Node::add_edge(pNode v, int w)
{
  adj.push_back(new Edge(this, v, w));
}

void Node::print()
{
  print_id();
  cout << ":";
  list<pEdge>::const_iterator it;
  for (it = adj.begin(); it != adj.end(); ++it) {
    cout << " ";
    (*it)->v->print_id();
  }
}

void Node::print_id()
{
  cout << "v" << id;
}

pNode create_node(int id)
{
  pNode v = new Node(id);

  return v;
}

pNode* create_nodes(int n)
{
  int i;
  pNode* V = (pNode*) malloc(n * sizeof(pNode));
  for (i = 0; i < n; i++) {
    V[i] = create_node(i);
  }

  return V;
}

void free_node(pNode v)
{
  delete v;
}

void free_nodes(pNode* V, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    while(!V[i]->adj.empty()) delete V[i]->adj.front(), V[i]->adj.pop_front();
    free_node(V[i]);
  }
  free(V);
}

void print_nodes(pNode* V, int n)
{
  int i;

  cout << "Nodes:" << endl; 
  for (i = 1; i < n; i++) {
    cout << "<";
    V[i]->print();
    cout << ">" << endl;
  }
  cout << "______________________" << endl;
}
// Edge
bool Edge::operator<(const Edge& r)
{
  if ((weight != r.weight))
    return weight < r.weight;
  else
    if (u->id != r.u->id)
      return u->id < r.u->id;
    else
      return v->id < r.v->id;
}

void Edge::print()
{
  cout << u->id << " - " << v->id << "(" << weight << ")" << endl;
}
// Graph
Graph::Graph(int n_) : n(n_)
{
  V = create_nodes(n);
}

Graph::Graph(int n_, int m_) : n(n_), m(m_) 
{
  V = create_nodes(n);
}

Graph::~Graph(void)
{
  free_nodes(V, n);
  while(!E.empty()) delete E.front(), E.pop_front();
}

pNode Graph::operator[](int i) 
{
  return V[i];
}

void Graph::add_edge(int u, int v)
{
  V[u]->add_edge(V[v]);
  V[v]->add_edge(V[u]);
  E.push_back(new Edge(V[u], V[v], 0));
  E.push_back(new Edge(V[v], V[u], 0));
}

void Graph::add_edge(int u, int v, int w)
{
  V[u]->add_edge(V[v], w);
  V[v]->add_edge(V[u], w);
  E.push_back(new Edge(V[u], V[v], w));
  E.push_back(new Edge(V[v], V[u], w));
}

void Graph::add_edge_(int u, int v)
{
  V[u]->add_edge(V[v]);
  E.push_back(new Edge(V[u], V[v], 0));
}

void Graph::add_edge_(int u, int v, int w)
{
  V[u]->add_edge(V[v], w);
  E.push_back(new Edge(V[u], V[v], w));
}

void Graph::print()
{
  print_nodes(V, n);
}

void Graph::sort_edges() 
{
  E.sort(PComp<Edge>);
}

