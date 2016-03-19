#include <stdio.h>

#include "lgraph.h"
#include "magraph.h"

int main()
{
  int i, j, n;
  lgraph_ lgraph;
  magraph_ magraph;

  scanf("%d", &n);
  magraph = create_magraph(n);

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &magraph->node[i][j]);
    }
  }

  //print_magraph(magraph);
  //lgraph = 

  destroy_magraph(magraph);

  return 0;
}
