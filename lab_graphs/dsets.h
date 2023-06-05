/* Your code here! */
#ifndef _DESTS_H_
#define _DESTS_H_

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class DisjointSets{
    public:

    void addelements(int num);

    int find(int elem);

    void setunion(int a, int b);

    int size(int elem);

    private:
    vector<int> disjointset;
};
#endif