#include <stdio.h>
#include "heap.h"

void build(int n, int* Q, int* weight) 
{
  int left, right;
  
  left = (n>>1) + 1;
  while (left > 1) {
    left = left - 1;
    reconstruct(left, n, Q, weight);
  }
}

int extract_min(int *Q, int *weight, int *n)
{
  int ret = Q[1];
  Q[1] = Q[*n];
  *n = *n - 1;
  reconstruct(1, *n, Q, weight);
  return ret;
}

void decrease_key(int i, int value, int *Q, int *weight)
{
  int x, half = i>>1;
  while (i > 1 && weight[Q[half]] > weight[Q[i]]) {
    x = Q[half];
    Q[half] = Q[i];
    Q[i] = x;
    i = half;
    half = i>>1;
  }
}

void reconstruct(int left, int right, int* Q, int* weight)
{
  int i, j, item, aux;
  
  i = left;
  j = i<<1;
  item = Q[i];
  while (j <= right) {
    if (j < right) {
      if (weight[Q[j]] > weight[Q[j + 1]])
        j = j + 1;
    }
    if (weight[item] < weight[Q[j]]) break;
    aux = Q[i];
    Q[i] = Q[j];
    Q[j] = aux;
    i = j;
    j = i<<1;
  }
}
