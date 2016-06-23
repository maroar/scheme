#include <iostream>
#include <iterator>
#include <list>
#include <chrono>
#include <omp.h>
#include "graph.h"
#include "Component.h"

#define NUM_THREADS 32

using namespace std;

using ns = std::chrono::milliseconds;
using s = std::chrono::seconds;
using get_time = std::chrono::steady_clock;

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
  for (int i = 1; i <= n; i++) {
    node = G[i];
    c = new Component(node);
    node->c = c;
    C[i-1] = c;
    c->pos = i-1;
  }
  
  //MST
  int tree_weight = 0;

  //Private variables
  int i, id, nthreads;

  //Measuring time
  get_time::time_point start = get_time::now();
  get_time::duration gbe_(0);
  get_time::duration union_(0);

  while (size > 1)
  {
    omp_set_nested(true);
    get_time::time_point start_aux = get_time::now();

    #pragma omp parallel private(i, id, nthreads) shared(C) num_threads(NUM_THREADS)
    {
      nthreads = omp_get_num_threads();
      id = omp_get_thread_num();

      // #pragma atomic
      // std::cout<< id << " " << std::endl;  

      for (i=id; i < size; i += nthreads)
      {
        C[i]->get_best_edge();
      }
    }
    get_time::time_point end_aux = get_time::now();
    gbe_ = gbe_ + (end_aux - start_aux);


    // std::cout << "1 " << std::endl;
    // #ifdef DEBUG
    //   for (int i = 0; i < size; i++) {
    //     C[i]->print();
    //   }
    //   cout << endl << "----------------" << endl;
    // #endif
    start_aux = get_time::now();

    for (int i = 0; i < size; )
    {
      if (Component::union_components(i, C, &size, &tree_weight))
        i++;
    }

    end_aux = get_time::now();
    union_ = union_ + (end_aux - start_aux);
    // std::cout << "2 " << std::endl;
    // #ifdef DEBUG
    //   for (int i = 0; i < size; i++) {
    //     C[i]->print();
    //   }
    //   cout << endl << "__________________________________" << endl;
    // #endif
  }

  //Time measuring
  get_time::time_point end = get_time::now();
  get_time::duration tot_diff = end - start;
  cout << "MST Weight: "  << tree_weight << endl;
  cout  << "GetBestEdge Elapsed Time:  " 
        << chrono::duration_cast<ns>(gbe_).count()
        <<" ns " << endl;
  cout  << "Union Elapsed Time:  " 
        << chrono::duration_cast<ns>(union_).count()
        <<" ns " << endl;
  cout  << "Total Elapsed Time:  " 
        << chrono::duration_cast<ns>(tot_diff).count()
        <<" ns " << endl;

  while(!C.empty()) {
    if (C.back())
      delete C.back(); 
    C.pop_back();
  }
  return 0;
}