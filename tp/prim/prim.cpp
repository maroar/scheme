#include <iostream>
#include <vector>
#include <stdlib.h>

#include "../helper/helper.h"
#include "../graph/graph.h"
#include "heap.h"

#define MYINF 10000

using namespace std;

int *pos;
int *heap, *weight, *pi;
pHeap h;
bool *visited;
Graph *G;

void init()
{
  G = read_undirected_graph();
  //heap = (int*) malloc((G->n+2)*sizeof(int));
  //weight = (int*) malloc((G->n+2)*sizeof(int));
  pos = (int*) malloc((G->n+2)*sizeof(int));
  pi = (int*) malloc((G->n+2)*sizeof(int));
  visited = (bool*) malloc((G->n+2)*sizeof(bool));
  h = (pHeap) malloc((G->n+2)*sizeof(HItem));
}

void erase_data() 
{
  //free(heap);
  //free(weight);
  free(pos);
  free(pi);
  free(visited);
  free(h);
  delete G;
}

void Prim() 
{
  int i, j, v, tree_weight = 0;
  list<pEdge>::iterator e;
  HItem u;
  
  for (i = 0; i <= G->n+1; i++) {
    visited[i] = false;
    h[i].v = i;
    pos[i] = i;
    h[i].w = MYINF;
    pi[i] = 0;
  }
  visited[0] = visited[G->n+1] = true;
  
  h[1].w = 0;
  build(h, G->n);
  
  j = G->n;
  for (i = 1; i <= G->n; i++) {
    //print_heap(h, j);
    u = extract_min(h, &j);
    visited[u.v] = true;
    cout << pi[u.v] <<" - " << u.v << "(" << u.w << ")" << endl;
    tree_weight += u.w;
    for (e = G->V[u.v]->adj.begin(); e != G->V[u.v]->adj.end(); ++e) {
      v = (*e)->v->id;
      //cout << " <" << v << ">: b:" << visited[v] << " w:" << h[pos[v]].w << " e.w:" <<  (*e)->weight << endl;
      if (!visited[v] && (*e)->weight < h[pos[v]].w) {
        //cout << "  ";
        //print_heap(h, j);
        decrease_key(pos[v], (*e)->weight, h);
        //cout << "  ";
        //print_heap(h, j);
        pi[v] = u.v;
      }
    }
    //print_heap(h, j);
    //cout << "---------------------------" << endl;
  }
  cout << tree_weight << endl;
}

int main(int argc, char *argv[]) 
{
  init();
  Prim();
  erase_data();

  return 0;
}
