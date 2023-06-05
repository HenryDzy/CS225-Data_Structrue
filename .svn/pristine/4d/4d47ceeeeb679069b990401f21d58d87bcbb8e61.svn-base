/* Your code here! */
#include <iostream>
#include <map>
#include "dsets.h"
#include <vector>

using namespace cs225;
using namespace std;

/**
 * Creates n unconnected root nodes at the end of the vector
 *
 * @param num the number of unconnected root nodes
 */
void DisjointSets::addelements(int num){
    for(int i=0; i<num; i++){
        disjointset.push_back(-1); //push_back -1
    }
    return;
}

/**
 * find the root of given elem and compress the path
 *
 * @param num the number of unconnected root nodes
 * @return the index of the root of the up-trees
 **/
int DisjointSets::find(int elem){
    if(disjointset[elem] < 0){
        return elem; //if the value is negative, this elem is root
    }
    else{
        disjointset[elem] = find(disjointset[elem]); //compress the path
        return disjointset[elem]; //recursive
    }
}

/**
 * set union by size to two up-tree
 *
 * @param a the first elem index
 * @param b the second elem index
 *
 **/
void DisjointSets::setunion(int a, int b){
    int root_a = find(a);  //find two root
    int root_b = find(b);
    if(root_a == root_b){return;} // if the root is the same, return
    int size = disjointset[root_a] + disjointset[root_b];
    if(disjointset[root_a] <= disjointset[root_b]){ //if the size of a is bigger than b
        disjointset[root_b] = root_a;               //more negative
        disjointset[root_a] = size;
    }
    else{
        disjointset[root_a] = root_b;
        disjointset[root_b] = size;
    }
    return;
}