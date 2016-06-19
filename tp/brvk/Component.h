#ifndef COMPONENT_H
#define COMPONENT_H

#include "graph.h"
#include <vector>
#include <list>

using namespace std;

typedef struct Component* pComponent;

struct Component {
  int id, order;
  list<pComponent>::iterator pos;
  pComponent parent;
  pComponent parent, to_update;
  pEdge best_edge;
  vector<pNode> V;
  vector<pEdge> E;
  // CONSTRUCTOR
  Component(pNode n);
  ~Component();
  // OBJ
  pComponent  find_set();
  pComponent  next();
  void        get_best_edge();
  void        print();
  void        set_parent(pComponent p);
  void        update(pComponent c);
  // CLASS
  static list<pComponent>::iterator link_set(pComponent A, pComponent B, list<pComponent>& C);
  static list<pComponent>::iterator union_components(list<pComponent>::iterator it, list<pComponent>::iterator nxt, list<pComponent>& C, int* w);
  static list<pComponent>::iterator union_set(pComponent A, pComponent B, list<pComponent>& C);
};

#endif