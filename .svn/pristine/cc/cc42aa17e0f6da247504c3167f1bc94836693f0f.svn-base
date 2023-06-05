/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

/** * This fuction take in two points and return a boolean value
 * representing whether or not the first Point has smaller value than
 * the second in the dimension specified **/
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim >= Dim || curDim <0 ) {return false;} //check if the curDim is valid

    if(first[curDim] < second[curDim]){
      return true;
    }
    else if (first[curDim] == second[curDim]){
      return first < second;
    }
    else{
      return false;
    }
}

/** * This function should take three templated Points: target, currentBest, 
 * and potential. This should return true if potential is closer to target
 * than currentBest. **/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double sqdist_pt= 0.0 , sqdist_ct=0.0; //two Euclidean square-distance
    for(int i=0; i<Dim; i++){ //calculate two square-distance
      sqdist_pt += (target[i]-potential[i])*(target[i]-potential[i]);
      sqdist_ct += (target[i]-currentBest[i])*(target[i]-currentBest[i]);
    }
    if(sqdist_pt != sqdist_ct){   //if no tie
      if(sqdist_pt < sqdist_ct){return true;}
      else {return false;}
    } 
    else{                         //if there is a tie
      if(potential < currentBest){return true;}
      else{return false;}
    }
}

/** * This function is consturctor of kdTree**/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     if(newPoints.empty()){   //if there is no points
       root = NULL;
       size = 0;
     }
     else{       //copying points into a vector
       vector<Point<Dim>> points = newPoints;
       size = 0;
       KDTreeBuilder(root, 0, points, 0, points.size() - 1);
     }

}

/** * This function help build the KDTree recursively**/
template <int Dim>
void KDTree<Dim>::KDTreeBuilder(KDTreeNode*& node, int dim, vector<Point<Dim>>& Points, int v_left, int v_right)
{
  if(v_left > v_right){ //Base case
    return;
  }
  size_t mid = (v_left + v_right) / 2; //the mid index

  Point<Dim> mid_point = quickSelect(Points, v_left, v_right, dim, mid); //find the mid point in spcefic dimension
  node = new KDTreeNode(mid_point); 
  size++;
  // if(root == NULL){cout << "subroot is null\n"<< endl;}
  KDTreeBuilder(node->left, (dim+1)%Dim, Points, v_left, mid-1);
  KDTreeBuilder(node->right, (dim+1)%Dim, Points, mid+1, v_right);
}


/** * This function group a list (ranging from indices left to right) into two parts: 
 * those less than a certain element, and those greater than or equal to the element.**/
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& to_find, int left, int right, size_t pivotIndex, int dim)
{
  Point<Dim> pivotPoint = to_find[pivotIndex]; // set pivot Point
  swap(to_find[pivotIndex], to_find[right]);  // Move pivot to end
  size_t storeIndex = left;
  for(int i = left; i < right; i++){
    if(smallerDimVal(to_find[i], pivotPoint, dim)){
      swap(to_find[storeIndex], to_find[i]);
      storeIndex++;
    }
  }
  swap(to_find[right], to_find[storeIndex]);  // Move pivot to final place
  return storeIndex;
}


/** * Returns the k-th smallest element of points vector **/ 
template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& to_sort, int left, int right, int dim, size_t k)
{
  if(left == right){     // If the list contains only one element,
    return to_sort[left];
  }
  size_t pivotIndex = (left + right) / 2;    // set pivot index
  pivotIndex = partition(to_sort, left, right, pivotIndex, dim);
  
  if (k == pivotIndex){
    return to_sort[k];
  }
  else if(k < pivotIndex){
    return quickSelect(to_sort, left, pivotIndex - 1, dim, k);
  }
  else{
    return quickSelect(to_sort, pivotIndex + 1, right, dim, k);
  }
}

/** * This function is a copy consturctor**/
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  root = nullptr;
  KDTreeNode* new_root = other.root;
  copy_helper(root, new_root);
  size = other.size;
}

/** This is a copy constructor helper function**/
template <int Dim>
void KDTree<Dim>::copy_helper(KDTreeNode*& node, KDTreeNode*& other_node){
  if(other_node == NULL){return;}
  node = new KDTreeNode(other_node->point);
  copy_helper(node->left, other_node->left);
  copy_helper(node->right, other_node->right);
}

/** *This function overload operator= **/
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  root = nullptr;
  size = rhs.size;
  KDTreeNode* new_root = rhs.root;
  destruct_helper(root);
  copy_helper(root, new_root);
  return *this;
}

/** This is destructor function**/
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  destruct_helper(root);
}

/** This is desturctor helper function**/
template <int Dim>
void KDTree<Dim>::destruct_helper(KDTreeNode* node){
  if(node == NULL){return;}
  destruct_helper(node->left);
  destruct_helper(node->right);
  delete node;
}

/**This function takes a point query as target and find the nearest Point
 * to it in KDTree **/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> query1 = query;     //These two points are used for const
    Point<Dim> point1 = root->point;
    FindNNhelper(query1, point1, root, 0);
    return point1;
}

/**This is a helper function for findNearestNeighbour function**/
template <int Dim>
void KDTree<Dim>::FindNNhelper(Point<Dim>& query, Point<Dim>& currBest, KDTreeNode* node, int dim) const{
  if(node == NULL){return;}
  KDTreeNode* next, *other;
  if(smallerDimVal(query, node->point, dim)){ //Deside which region the target is in
    next = node->left;
    other = node->right;
  }
  else{
    next = node->right;
    other = node->left;
  }
  FindNNhelper(query, currBest, next, (dim+1)%Dim);

  if(shouldReplace(query, currBest, node->point)){  //change the currentBest node
    currBest = node->point;
  }

  double radius=0.0, dist;
  for(int i=0; i<Dim; i++){
    radius += (currBest[i] - query[i])*(currBest[i] - query[i]);
  }
  dist = (node->point[dim] - query[dim])*(node->point[dim] - query[dim]);
  
  if(dist <= radius){     //compare if the node is in the current best radius
    FindNNhelper(query, currBest, other, (dim+1)%Dim);
  }
}
