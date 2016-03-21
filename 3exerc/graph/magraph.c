// implementation of a graph by an adjacency matrix
#include <stdlib.h>
#include <stdio.h>

#include "magraph.h"

magraph_ create_magraph(int n)
{
  int i;
  magraph_ graph = (magraph_) malloc(sizeof(struct struct_magraph));
  graph->n = n;
  graph->node = (pma_node*) malloc(n*sizeof(pma_node));
  for (i = 0; i < n; i++)
    graph->node[i] = (pma_node) malloc(n*sizeof(ma_node));
  return graph;
}

void destroy_magraph(magraph_ graph)
{
  int i;
  for (i = 0; i < graph->n; i++)
    free(graph->node[i]);
  free (graph->node);
  free(graph);
}

void print_magraph(magraph_ graph)
{
  int i, j;
  for (i = 0; i < graph->n; i++) {
    for (j = 0; j < graph->n; j++) {
      printf(" %d", graph->node[i][j]);
    }
    printf("\n");
  }
}
