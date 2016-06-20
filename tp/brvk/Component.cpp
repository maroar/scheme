#include <iostream>
#include "Component.h"
// CONSTRUCTOR
Component::Component(pNode n) : id(n->id), order(0), to_update(nullptr) 
{
  set_parent(this);

  for (auto& e : n->adj) {
    E.push_back(e);
  }
}

Component::~Component() {}
// OBJ
pComponent Component::find_set()
{
  if (this != parent)
    parent = parent->find_set();
  return parent;
}

pComponent Component::next()
{
  return parent;
}

void Component::get_best_edge() 
{
  if (to_update)
    update(to_update);

  best_edge = *E.begin();
  for (auto& e : E) {
    if (*e < *best_edge) {
      best_edge = e;
    }
  }
}

void Component::print()
{
  cout << id << " ";
}

void Component::set_parent(pComponent p)
{
  parent = p;
}

void Component::update(pComponent c)
{
  for (auto& e : c->E) {
    if (e->v->c->find_set() != this->find_set())
      E.push_back(e);
  }
  vector<pEdge>::iterator it;
  for (it = E.begin(); it != E.end(); ) {
    if ((*it)->u->c->find_set() == (*it)->v->c->find_set()) {
      it = E.erase(it);
    }
    else {
      it++;
    }
  }
}
// CLASS
list<pComponent>::iterator Component::link_set(pComponent A, pComponent B, list<pComponent>& C)
{
  if (A->order > B->order) {
    B->parent = A;
    A->to_update = B;
    return C.erase(B->pos);
  } else {
    A->parent = B;
    B->to_update = A;
    if (A->order == B->order) {
      B->order = B->order + 1;
    }
    return C.erase(A->pos);
  }
}

list<pComponent>::iterator Component::union_components(
  list<pComponent>::iterator it, 
  list<pComponent>::iterator nxt,
  list<pComponent>& C,
  int *w)
{
  pComponent A = *it, 
             B = (*it)->best_edge->v->c;
  if (A->find_set() == B->find_set()) return nxt;
  // (*it)->best_edge->print();
  *w += (*it)->best_edge->weight;
  return union_set(A, B, C);
}

list<pComponent>::iterator Component::union_set(pComponent A, pComponent B, list<pComponent>& C)
{
  return link_set(A->find_set(), B->find_set(), C);
}
