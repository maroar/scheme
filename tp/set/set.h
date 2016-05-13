#ifndef MYSET
#define MYSET

struct Element;
typedef Element* pElement;
typedef Element* pSet;
//Set
pSet find_set(pSet A);
void link_set(pSet A, pSet B);
pSet make_set(int id);
pSet make_set(int id, pSet parent);
void union_set(pSet A, pSet B);
//Element
struct Element {
  int  setId, order;
  pSet parent;
  
  Element(int id) : setId(id), order(0) {set_parent(this);};
  Element(int id, pSet p) : setId(id), parent(p), order(0) {};
  pSet next();
  void set_parent(pSet p);
};

#endif