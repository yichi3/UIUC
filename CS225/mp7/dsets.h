/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <vector>
using namespace std;

class DisjointSets{
  public:
    DisjointSets();
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
    void clear();

  private:
    vector<int> disjointset_;
};


#endif
