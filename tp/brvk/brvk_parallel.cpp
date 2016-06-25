#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "graph.h"
#include "Component.h"

#define NUM_THREADS 2

using namespace std;
int num_threads, // total number of threads
      workspace, // amount of work to each thread
      rest,      // rest of the work
      max_edges; // maximum number of edges
vector<int> cheapest;

void work(int begin, int end, Graph *G) 
{
  for (int i = begin; i <= end; i++) {
    for (auto& e : G->V[i]->adj) {
      pComponent set1 = e->u->c->find_set();
      pComponent set2 = e->v->c->find_set();
      if (set1 == set2) {
        continue;
      } else {
        if (cheapest[set1->id] == -1 || G->E[cheapest[set1->id]]->weight > e->weight) {
          cheapest[set1->id] = e->i;
        } 
      }
    }
  }
}

struct task {
  int begin, end;
};

int main(int argc, char **argv) 
{
  // READ THE GRAPH
  int m, n, u, v, w;
  // read graph size
  cin >> n;
  cin >> m;
  // create graph
  Graph G(n, m, undirected);
  // read edges
  for (int i = 0; i < m; i++) {
    cin >> u;
    cin >> v;
    cin >> w;
    G.add_edge(u, v, w);
  }
  // CREATE THE COMPONENTS
  int size = n;
  pComponent c;
  pNode node;
  vector<pComponent> C(n);
  cheapest.resize(n+1);
  for (int i = 1; i <= n; i++) {
    node = G[i];
    c = new Component(node);
    node->c = c;
    C[i-1] = c;
    cheapest[i] = -1;
  }
  // BORUVKA PARALLEL
  int tree_weight = 0; 
  // preparing parellel data
  vector<thread> threads;
  max_edges = m << 1;
  num_threads = NUM_THREADS,
  workspace = n / NUM_THREADS,
  rest = n % NUM_THREADS;
  if (rest) {
    num_threads++;
  }
  vector<task> tsk(num_threads);
  for (int i = 0; i < num_threads; i++) {
    tsk[i].begin = workspace * i + 1;
    tsk[i].end = tsk[i].begin + workspace - 1;
  }
  if (rest)
    tsk[NUM_THREADS].end = tsk[NUM_THREADS].begin + rest -1;
  while (size > 1) {
    // each thread must traverse through all edges and update cheapest of every component
    for (int i = 0; i < num_threads; i++) {
      threads.push_back(thread(work, tsk[i].begin, tsk[i].end, &G));
    }
    for (int i = 0; i < num_threads; i++) {
      threads[i].join();
    }
    threads.clear();
    // Consider the above picked cheapest edges and add them to MST
    for (int i = 1; i <= n; i++) {
      if (cheapest[i] != -1) {
        pComponent set1 = G.E[cheapest[i]]->u->c->find_set();
        pComponent set2 = G.E[cheapest[i]]->v->c->find_set();

        if (set1 == set2) {
          continue;
        }

        tree_weight += G.E[cheapest[i]]->weight;
        Component::union_set(set1, set2);
        cheapest[set1->id] = cheapest[set2->id] = -1;
        size--;
      }
    }
  }
  cout << tree_weight << endl;
  while(!C.empty()) {
    if (C.back())
      delete C.back(); 
    C.pop_back();
  }
  return 0;
}