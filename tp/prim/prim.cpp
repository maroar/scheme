#include <iostream>
#include <vector>
#include <stdlib.h>

#include "../graph/graph.h"
#include "heap.h"

#define MYINF 10000

using namespace std;

int n, m, *key, *weight, *pi;
bool *visited;
Graph *G;

void read_data() {
  int u, v, w;

  cin >> n;
  cin >> m;
  
  key = (int*) malloc(n*sizeof(int)+2);
  weight = (int*) malloc(n*sizeof(int)+2);
  pi = (int*) malloc(n*sizeof(int)+2);
  visited = (bool*) malloc(n*sizeof(bool)+2);
  G = new Graph(n+1);
  
  for (int i = 1; i <= m; i++) {
    cin >> u;
    cin >> v;
    cin >> w;
    G->add_edge(u, v, w);
  }
}

void erase_data() 
{
  free(key);
  free(weight);
  free(pi);
  free(visited);
  delete G;
}

void Prim() 
{
  int i, j, u, v, tree_weight = 0;
  list<pEdge>::iterator e;
  
  for (i = 1; i <= n; i++) {
    key[i] = i;
    weight[i] = MYINF;
    pi[i] = 0;
    visited[i] = false;
  }
  
  weight[1] = 0;
  
  //build(n, key, weight);
  
  j = n;
  for (i = 1; i <= j; i++) {
    //print_heap(key, n, weight);
    u = extract_min(key, weight, &n);
    visited[u] = true;
    cout << pi[u] <<" - " << u << "(" << weight[u] << ")" << endl;
    for(e = G->V[u]->adj.begin(); e != G->V[u]->adj.end(); ++e) {
      v = (*e)->v->id;
      if(!visited[v] && (*e)->weight < weight[v]) {
        weight[v] = (*e)->weight;
        reconstruct(1, n, key, weight);
        pi[v] = u;
      }
    }
  }
}

int main(int argc, char *argv[]) {

  read_data();
  Prim();
  erase_data();

  return 0;
}
