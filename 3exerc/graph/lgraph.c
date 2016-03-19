// implementation of a graph by lists
#include <stdlib.h>

#include "lgraph.h"
// node definition
pl_node create_lgraph_node()
{
  pl_node node = (pl_node) malloc(sizeof(struct l_node));
  node->id = lgraph_node_count++;
  node->next_node = 0;
  return node;
}

void destroy_lgraph_node(pl_node node)
{
  free(node);
}

// graph definition
lgraph_ create_lgraph(int n)
{
  int i;
  
  lgraph_ graph = (lgraph_) malloc(sizeof(struct struct_lgraph));
  graph->n = 0;
  graph->node = (pl_node*) malloc(n*sizeof(pl_node));
  for (i = 0; i < n; i++) {
    graph->node[i] = create_lgraph_node();
  }

  return graph;
}

lgraph_ create_lgraph_by_magraph()
{}

void destroy_lgraph()
{}

void print_lgraph()
{}
