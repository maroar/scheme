#ifndef COMPONENT_H
#define COMPONENT_H

#include "graph.h"
#include <vector>
#include <list>
#define DEBUG

using namespace std;

typedef struct Component* pComponent;

struct Component {
  int id, order, pos;
  list<pComponent> to_update;
  pComponent parent;
  pEdge best_edge;
  vector<pNode> V;
  vector<pEdge> E;
  // CONSTRUCTOR
  Component(pNode n);
  ~Component();
  // OBJ
  pComponent  find_set();
  pComponent  next();
  void        add_to_update(pComponent p);
  void        get_best_edge();
  void        print();
  void        set_parent(pComponent p);
  void        update(pComponent c);
  // CLASS
  static bool link_set(pComponent A, pComponent B, vector<pComponent>& C, int *s);
  static bool union_components(int i, vector<pComponent>& C, int *s, int *w);
  static bool union_set(pComponent A, pComponent B, vector<pComponent> &C, int *s);
};

#endif