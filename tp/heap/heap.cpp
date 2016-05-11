#include <iostream>
#include "heap.h"

#define INT_MIN 0

using namespace std;

void build(pHeap A, int n) 
{
  int left;
  
  left = (n>>1) + 1;
  while (left > 1) {
    left--;
    reconstruct(left, n, A);
  }
}

HItem extract_min(pHeap A, int *n)
{
  HItem min;
  if (*n < 1) cout << "Error: the heap is empty!" << endl;
  else {
    min = A[1];
    A[1] = A[*n];
    pos[A[*n].v] = 1;
    (*n)--;
    reconstruct(1, *n, A);
  }
  
  return min;
}

void decrease_key(int i, int w, pHeap A)
{
  int half = i>>1;
  HItem x;
  A[i].w = w;
  while (i > 1 && A[half].w > A[i].w) {
    x = A[half];
    A[half] = A[i];
    pos[A[i].v] = half;
    A[i] = x;
    pos[x.v] = i; 
    i = half;
    half = half>>1;
  }
}

void insert(pHeap x, pHeap A, int *n)
{
  (*n)++;
  A[*n] = *x;
  pos[A[*n].v] = *n;
  //A[*n].w = INT_MIN;
  decrease_key(*n, x->w, A);
}

void print_heap(pHeap A, int n)
{
  for (int i = 1; i <= n; i++) {
    cout << A[i].v << "(" << A[i].w << ") ";
  }
  cout << endl;
}

void reconstruct(int left, int right, pHeap A)
{
  int i = left, j;
  HItem x;
  
  j = i<<1;
  x = A[i];
  while (j <= right) {
    if (j < right) {
      if (A[j].w > A[j+1].w) {
        j++;
      }
    }
    if (x.w <= A[j].w) break;
    A[i] = A[j];
    pos[A[j].v] = i;
    i = j;
    j = i<<1;
  }
  A[i] = x;
  pos[x.v] = i;
}
