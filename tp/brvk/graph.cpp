#include <iostream>
#include <algorithm>
#include <list>
#include <stdlib.h>

#include "graph.h"

using namespace std;
// Others
template <typename T> bool PComp(T * const & a, T * const & b)
{
   return *a < *b;
}
// Node
Node::~Node(void)
{
  while(!adj.empty()) delete adj.front(), adj.pop_front();
}

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

pEdge Node::get_best_edge()
{
  return adj.front();
}

pNode create_node(int id)
{
  pNode v = new Node(id);

  return v;
}

void create_nodes(vector<pNode>& V, int n_)
{
  int i;
  for (i = 0; i < n_; i++) {
    V.push_back(create_node(i));
  }
}

void free_node(pNode v)
{
  delete v;
}

void free_nodes(pNode* V, int n_)
{
  int i;
  for (i = 0; i <= n_; i++) {
    delete V[i];
  }
  free(V);
}

void print_nodes(vector<pNode>& V, int n_)
{
  int i;

  cout << "Nodes:" << endl; 
  for (i = 1; i <= n_; i++) {
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
Graph::Graph(int n_) : kedge(undirected)
{
  n = n_;
  kedge = undirected;
  create_nodes(V, n+1);
}

Graph::Graph(int n_, int m_) : kedge(undirected)
{
  n = n_;
  m = m_;
  create_nodes(V, n+1);
}

Graph::Graph(int n_, int m_, kEdge kedge_) : kedge(kedge_)
{
  n = n_;
  m = m_;
  create_nodes(V, n+1);
}

Graph::Graph(void) : kedge(undirected)
{
  read_graph_size();
  create_nodes(V, n+1);
}

Graph::Graph(kEdge kedge_) : kedge(kedge_)
{
  read_graph_size();
  create_nodes(V, n+1);
}

Graph::~Graph(void)
{
  while(!E.empty()) delete E.back(), E.pop_back();
  while(!V.empty()) delete V.back(), V.pop_back();
}

pNode Graph::operator[](size_t i) 
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

void Graph::print_edges()
{
  for (auto& e : E) {
    e->print();
  }
}

void Graph::read_edges()
{
  if(kedge == directed)
    read_directed_edges();
  else
    read_undirected_edges();
}

void Graph::sort_edges() 
{
  //E.sort(PComp<Edge>);
}

void Graph::read_graph_size()
{
  cin >> n;
  cin >> m;
}

void Graph::read_undirected_edges()
{
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    cin >> u;
    cin >> v;
    cin >> w;
    add_edge(u, v, w);
  }
}

void Graph::read_directed_edges()
{
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    cin >> u;
    cin >> v;
    cin >> w;
    add_edge_(u, v, w);
  }
}
