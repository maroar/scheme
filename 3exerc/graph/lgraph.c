// implementation of a graph by lists
#include <stdio.h>
#include <stdlib.h>

#include "lgraph.h"
// node definition
pl_node create_lgraph_node(int i)
{
  pl_node node = (pl_node) malloc(sizeof(struct l_node));
  node->id = i;
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
  int i, count = 0;
  
  lgraph_ graph = (lgraph_) malloc(sizeof(struct struct_lgraph));
  graph->n = n;
  graph->node = (pl_node*) malloc(n*sizeof(pl_node));
  for (i = 0; i < n; i++) {
    graph->node[i] = create_lgraph_node(count++);
  }

  return graph;
}

lgraph_ create_lgraph_by_magraph(magraph_ magraph)
{
  int i, j;
  lgraph_ graph = create_lgraph(magraph->n);
  
  for (i = 0; i < magraph->n; i++) {
    for (j = 0; j < magraph->n; j++) {
      if (magraph->node[i][j]) add_lgraph_edge(graph, i, j);
    }
  }
  
  return graph;
}

void add_lgraph_edge(lgraph_ graph, int i, int j)
{
  pl_node next = graph->node[i]->next_node;
  graph->node[i]->next_node = create_lgraph_node(j);
  graph->node[i]->next_node->next_node = next;
}

void destroy_lgraph(lgraph_ graph)
{
  int i;
  pl_node node, old_node;

  for (i = 0; i < graph->n; i++) {
    node = graph->node[i]->next_node;
    while (node && (node != graph->node[i])) {
      old_node = node;
      node = node->next_node;
      free(old_node);
    }
    free(graph->node[i]);
  }
  free(graph);
}

void print_lgraph(lgraph_ graph)
{
  int i;
  pl_node node;

  for (i = 0; i < graph->n; i++) {
    printf("%d", graph->node[i]->id);
    node = graph->node[i]->next_node;
    while (node && (node != graph->node[i])) {
      printf(" %d", node->id);
      node = node->next_node;
    }
    printf("\n");
  }
}

