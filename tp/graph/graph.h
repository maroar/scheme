#ifndef MYGRAPH
#define MYGRAPH

#include <list>

struct  Node; 
typedef Node* pNode;

struct Node {
  int id;
  std::list<pNode> adj;

  Node(int id_) : id(id_) {}; 
  void add_node(pNode v);
  void print();
  void print_id();
};

#endif