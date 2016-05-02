#include <iostream>
#include <stdlib.h>
#include "graph.h"

using namespace std;

void Node::add_node(pNode v)
{
  adj.push_back(v);
}

void Node::print()
{
  print_id();
  cout << ":";
  list<pNode>::const_iterator it;
  for (it = adj.begin(); it != adj.end(); ++it) {
    cout << " ";
    (*it)->print_id();
  }
  cout << endl;
}

void Node::print_id()
{
  cout << "v" << id + 1;
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
    free_node(V[i]);
  }
  free(V);
}

void print_nodes(pNode* V, int n)
{
  int i;

  cout << "Nodes:" << endl; 
  for (i = 0; i < n; i++) {
    V[i]->print();
  }
  cout << "______________________" << endl;
}
