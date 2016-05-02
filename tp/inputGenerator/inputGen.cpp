#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<list>
#include<iostream>
#define N 21
#define M 10
#define R 10
#define E 10
#define A 10

using namespace std;

list< pair<int, int> > f;
list< pair<int, int> > f_;

bool compare (int& l, int& r)
{
  return l < r;
}

bool same (int l, int r)
{ 
  return l==r; 
}

void combinations (int v[], int start, int n, int k, int maxk) {
        int     i;
        if (k > maxk) {
                /* insert code here to use combinations as you please */
                //for (i=1; i<=maxk; i++) printf ("%i ", v[i]);
                //printf ("\n");
                f.push_back(make_pair(v[1], v[2]));
                return;
        }
        for (i=start; i<=n; i++) {
                v[k] = i;
                combinations (v, i+1, n, k+1, maxk);
        }
}

int main ()
{
  bool *vf;
  int i, n, m, r, m_aux, m_max, m_min, *v, j, k, c_max, aux;
  list< pair< int, int> >::iterator it;
  list<int> fc;
  list<int>::iterator iti;
  
  srand (time(NULL));
 
  n = (rand() % N)+N;
  m_max = n*(n-1)/2;
  v = (int*) malloc(n*sizeof(int));
  m_min = n;
  do {
    m = (rand() % m_max) + m_min;
  } while((m > m_max));
  
  combinations (v, 1, n, 1, 2);
  
  c_max = (n*(n-1))/2;
  for (i = 0; i < m; i++) {
    j = (rand()%(c_max-i));
    k = 0;
    it = f.begin();
    while (k < j){
      it++;
      k++;
    }
    f_.push_back( make_pair((*it).first, (*it).second) );
    f.erase(it);
  }
  
  cout << n << " " << f_.size() << endl;
  for(it = f_.begin(); it != f_.end(); ++it) {
    cout << it->first << " " << it->second << " " << (rand() % N) + 1 << endl;
  }
  
  free(v);
  f.clear();
  
  return 0;
}
















