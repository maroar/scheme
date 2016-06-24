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
  pComponent parent;
  // CONSTRUCTOR
  Component(pNode n);
  ~Component();
  // OBJ
  pComponent  find_set();
  void        print();
  // CLASS
  static void union_set(pComponent A, pComponent B);
};

#endif