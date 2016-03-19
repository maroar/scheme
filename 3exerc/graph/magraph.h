// header of a graph implemented by an adjacency matrix
#ifndef MAGRAPH
#define MAGRAPH
typedef int ma_node;
typedef ma_node* pma_node;
typedef struct struct_magraph* magraph_;

struct struct_magraph
{
  int n;
  pma_node* node;
};

magraph_ create_magraph(int n);
void destroy_magraph(magraph_ graph);
void print_magraph(magraph_ graph);
#endif
