#include <iostream>
#include "Component.h"
// CONSTRUCTOR
Component::Component(pNode n) : id(n->id), order(0), parent(this)
{}

Component::~Component() {}
// OBJ
pComponent Component::find_set()
{
  if (this != parent)
    parent = parent->find_set();
  return parent;
}

void Component::print()
{
  cout << id << " ";
}
// CLASS
void Component::union_set(pComponent A, pComponent B)
{
  if (A->order > B->order) {
    B->parent = A;
  } else {
    A->parent = B;
    if (A->order == B->order) {
      B->order = B->order + 1;
    }
  }
}