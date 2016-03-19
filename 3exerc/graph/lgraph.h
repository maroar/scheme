// header of a graph implemented by lists
#ifndef LGRAPH
#define LGRAPH
#include "magraph.h"
// node definition
int lgraph_node_count = 0;

typedef struct l_node* pl_node;
struct l_node 
{
  int id;
  pl_node next_node;
};

pl_node create_lgraph_node();
void destroy_lgraph_node();

// graph definition
typedef struct struct_lgraph* lgraph_;
struct struct_lgraph
{
  int n;
  pl_node* node;
};

lgraph_ create_lgraph(int n);
lgraph_ create_lgraph_by_magraph();
void destroy_lgraph();
void print_lgraph();
#endif
