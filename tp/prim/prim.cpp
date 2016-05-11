#include <iostream>
#include <stdlib.h>

#include "../graph/graph.h"
#include "../heap/heap.h"

#define MYINF 10000

using namespace std;
//heap
int *pos;
pHeap h;
//prim
bool *visited;
int *pi;
//Graph
int n, m;

void init()
{
  pos = (int*) malloc((n+2)*sizeof(int));
  pi = (int*) malloc((n+2)*sizeof(int));
  visited = (bool*) malloc((n+2)*sizeof(bool));
  h = (pHeap) malloc((n+2)*sizeof(HItem));
}

void erase_data() 
{
  free(pos);
  free(pi);
  free(visited);
  free(h);
}

void Prim() 
{
  Graph G(undirected);
  G.read_edges();
  
  init();
  int i, j, v, tree_weight = 0;
  HItem u;
  
  for (i = 0; i <= n+1; i++) {
    visited[i] = false;
    h[i].v = i;
    h[i].w = MYINF;
    pos[i] = i;
    pi[i] = 0;
  }

  visited[0] = visited[n+1] = true;

  h[1].w = 0;
  build(h, n);

  j = n;
  for (i = 1; i <= n; i++) {
    u = extract_min(h, &j);
    visited[u.v] = true;
    cout << pi[u.v] <<" - " << u.v << "(" << u.w << ")" << endl;
    tree_weight += u.w;
    for (auto& e : G[u.v]->adj) {
      v = e->v->id;
      if (!visited[v] && e->weight < h[pos[v]].w) {
        decrease_key(pos[v], e->weight, h);
        pi[v] = u.v;
      }
    }
  }
  cout << tree_weight << endl;
}

int main(int argc, char *argv[]) 
{
  Prim();
  erase_data();

  return 0;
}
