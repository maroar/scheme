#include "set.h"
//Set
pSet find_set(pSet A)
{
  if (A != A->parent)
    A->parent = find_set(A->parent);
  return A->parent;
}

void link_set(pSet A, pSet B)
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

pSet make_set(int id)
{
  return new Element(id);
}

pSet make_set(int id, pSet parent)
{
  return new Element(id, parent);
}

void union_set(pSet A, pSet B)
{
  link_set(find_set(A), find_set(B));
}
//Element
void Element::set_parent(pSet p)
{
  parent = p;
}

pSet Element::next()
{
  return parent;
}
