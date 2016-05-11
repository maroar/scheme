#ifndef MYHEAP
#define MYHEAP

struct HItem;
typedef HItem* pHeap;

struct HItem {
  int w, v;
};

extern int *pos;

void  build(pHeap A, int n);//
void  decrease_key(int i, int w, pHeap);//
HItem extract_min(pHeap A, int *n);//
void  insert(pHeap x, pHeap A, int *n);//
void  print_heap(pHeap A, int n);//
void  reconstruct(int left, int right, pHeap A);

#endif