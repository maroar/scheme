#ifndef MYGRAPH
#define MYGRAPH
#include <cstddef>
#include <list>
#include <vector>
struct Component;
typedef Component* pComponent;
struct  Node; 
typedef Node* pNode;
struct Edge;
typedef Edge* pEdge;
struct  Graph; 
typedef Graph* pGraph;
// Node
struct Node {
  int id;
  std::list<pEdge> adj;
  pComponent c;

  Node(int id_) : id(id_) {};
  ~Node(void);
  void add_edge(pNode v);
  void add_edge(pNode v, int w);
  void add_edge(pNode v, int w, int i);
  void print();
  void print_id();
  pEdge get_best_edge();
};
// Edge
typedef enum kindOfEdge { directed, undirected } kEdge;
struct Edge {
  int weight, i;
  pNode u, v;
  static int edge_cnt;

  Edge(pNode u_, pNode v_) : u(u_), v(v_), weight(0) {i = edge_cnt++;};
  Edge(pNode u_, pNode v_, int w) : u(u_), v(v_), weight(w) {i = edge_cnt++;};
  Edge(pNode u_, pNode v_, int w, int i_) : u(u_), v(v_), weight(w), i(i_) {};
  bool operator<(const Edge& r);
  void print();
};
// Graph
struct Graph {
  int m, n;
  kEdge kedge;
  std::vector<pNode> V;
  std::vector<pEdge> E;

  Graph(void);
  Graph(kEdge kedge_);
  Graph(int n_);
  Graph(int n_, int m_);
  Graph(int n_, int m_, kEdge kedge_);
  ~Graph(void);
  pNode operator[](size_t i);
  void  add_edge(int u, int v);
  void  add_edge(int u, int v, int w);
  void  add_edge_(int u, int v);
  void  add_edge_(int u, int v, int w);
  void  print();
  void  print_edges();
  void  read_directed_edges();
  void  read_edges();
  void  read_graph_size();
  void  read_undirected_edges();
  void  sort_edges();
};
#endif
