#ifndef MYGRAPH
#define MYGRAPH

#include <list>
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

  Node(int id_) : id(id_) {};
  ~Node(void);
  void add_edge(pNode v);
  void add_edge(pNode v, int w);
  void print();
  void print_id();
};
// Edge
typedef enum kindOfEdge { directed, undirected } kEdge;
struct Edge {
  int weight;
  pNode u, v;

  Edge(pNode u_, pNode v_) : u(u_), v(v_), weight(0) {};
  Edge(pNode u_, pNode v_, int w) : u(u_), v(v_), weight(w) {};
  bool operator<(const Edge& r);
  void print();
};
// Graph
extern int n, m;
struct Graph {
  kEdge kedge;
  pNode *V;
  std::list<pEdge> E;

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
  void  read_directed_edges();
  void  read_edges();
  void  read_graph_size();
  void  read_undirected_edges();
  void  sort_edges();
};
#endif
