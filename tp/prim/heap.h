#ifndef MYHEAP
#define MYHEAP

void build(int n, int* Q, int* weight);
void decrease_key(int i, int value, int *Q, int *weight);
int  extract_min(int *Q, int *weight, int *n);
void reconstruct(int left, int right, int* Q, int* weight);

#endif