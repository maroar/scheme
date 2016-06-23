#include <iostream>
#include "Component.h"
// CONSTRUCTOR
Component::Component(pNode n) : id(n->id), order(0)
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

void Component::add_to_update(pComponent p)
{
  for (auto &itt : p->to_update) {
    to_update.push_back(itt);
  }
  to_update.push_back(p);
  p->to_update.clear();
}

void Component::get_best_edge() 
{
  for (auto &c : to_update)
    update(c);

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
/*list<pComponent>::iterator Component::union_components(
  list<pComponent>::iterator it, 
  list<pComponent>::iterator nxt,
  list<pComponent>& C,
  int *w)
{
  pComponent A = *it, 
             B = (*it)->best_edge->v->c;
  if (A->find_set() == B->find_set()) return nxt;
  #ifdef DEBUG
    (*it)->best_edge->print();
  #endif
  *w += (*it)->best_edge->weight;
  return union_set(A, B, C);
}*/

/*list<pComponent>::iterator Component::union_set(pComponent A, pComponent B, list<pComponent>& C)
{
  return link_set(A->find_set(), B->find_set(), C);
}

list<pComponent>::iterator Component::link_set(pComponent A, pComponent B, list<pComponent>& C)
{
  if (A->order > B->order) {
    B->parent = A;
    //A->update(B);
    A->add_to_update(B);
    return C.erase(B->pos);
  } else {
    A->parent = B;
    //B->update(A);
    B->add_to_update(A);
    if (A->order == B->order) {
      B->order = B->order + 1;
    }
    return C.erase(A->pos);
  }
}

*/
void swap_component(int i, int j, vector<pComponent>& C)
{
  pComponent aux = C[i];
  C[i] = C[j];
  C[j] = aux;
}

bool Component::link_set(pComponent A, pComponent B, vector<pComponent>& C, int *s)
{
  int last = (*s) - 1;
  if (A->order > B->order) { // A absorbs B
    B->parent = A;
    A->add_to_update(B);
    C[last]->pos = B->pos;
    swap_component(B->pos, last, C);
    *s = last;
    return A->pos < B->pos;
  } else { // B absorbs A
    A->parent = B;
    B->add_to_update(A);
    if (A->order == B->order) {
      B->order = B->order + 1;
    }
    C[last]->pos = A->pos;
    swap_component(A->pos, last, C);
    *s = last;
    return B->pos < A->pos;
  }
}

bool Component::union_set(pComponent A, pComponent B, vector<pComponent> &C, int *s) 
{
  return link_set(A->find_set(), B->find_set(), C, s);
}

bool Component::union_components(int i, vector<pComponent> &C, int *s, int* w) 
{
  pComponent A = C[i], 
             B = C[i]->best_edge->v->c;
  if (A->find_set() == B->find_set()) return true;
  #ifdef DEBUG
    A->best_edge->print();
  #endif
  *w += A->best_edge->weight;
  return union_set(A, B, C, s);
}

/*list<pComponent>::iterator Component::link_set(pComponent A, pComponent B, list<pComponent>& C)
{
  if (A->order > B->order) {
    B->parent = A;
    //A->update(B);
    A->add_to_update(B);
    return C.erase(B->pos);
  } else {
    A->parent = B;
    //B->update(A);
    B->add_to_update(A);
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
  #ifdef DEBUG
    (*it)->best_edge->print();
  #endif
  *w += (*it)->best_edge->weight;
  return union_set(A, B, C);
}


*/