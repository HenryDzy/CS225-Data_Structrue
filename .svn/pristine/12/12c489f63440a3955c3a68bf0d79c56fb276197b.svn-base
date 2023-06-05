/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
  length_ = 0;
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  
  ListNode* curr = head_;
  ListNode* next;
  while (curr != NULL){
    next = curr->next;
    delete curr;
    curr = next;
  }
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1

  ListNode* new_node = new ListNode(ndata);
  if(head_ == NULL && tail_ == NULL){
    head_ = new_node;
    tail_ = new_node;
  }
  else{
    new_node->prev = NULL;
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }
  length_ += 1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1

  ListNode* new_node = new ListNode(ndata);
  if(head_ == NULL && tail_ == NULL){
    head_ = new_node;
    tail_ = new_node;
  }
  else{
    new_node->prev = tail_;
    new_node->next = NULL;
    tail_->next = new_node;
    tail_ = new_node;
  }
  length_ += 1;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1
    ListNode* curr, *next, *prev;
    ListNode* end_next = endPoint->next;
    ListNode* start_prev = startPoint->prev;
    ListNode* new_start = endPoint;
    ListNode* new_end = startPoint;

    for (curr=startPoint; curr!=end_next ;){
      next = curr->next;
      prev = curr->prev;
      curr->next = prev;
      curr->prev = next;
      curr = next;
    }

    if(start_prev != NULL){
      endPoint->prev = start_prev;
      start_prev->next = endPoint;
    }
    else {endPoint->prev = NULL;}

    if(end_next != NULL){
      startPoint->next = end_next;
      end_next->prev = startPoint;
    }
    else {startPoint->next = NULL;}

    if(start_prev == NULL) head_ = new_start;
    if(end_next == NULL) tail_ = new_end;
    startPoint = new_start;
    endPoint = new_end;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if(n>length_){
    reverse(head_,tail_);
    return;
  }
  int counter;
  ListNode *startPoint, *endPoint;
  startPoint = head_;
  endPoint = head_;
  for(counter=n; counter<length_;){
    for(int i=1; i<n; i++){
      endPoint = endPoint->next;
    }
    reverse(startPoint, endPoint);
    startPoint = endPoint->next;
    endPoint = endPoint->next;

    counter += n;
    if(counter>=length_){
      int remain;
      counter -= n;
      remain = length_ - counter;
      for(int j=1; j<remain; j++){
        endPoint = endPoint->next;
      }
      reverse(startPoint, endPoint);  
      counter += n; 
    }

  }
  return;

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  ListNode* next;
  bool change = false;
  for(int i=1; curr!=tail_; i++){
    if(i%2 == 0) {change = true;}
    else {change = false;}
    next = curr->next;
    if(change){
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      curr->prev = tail_;
      curr->next = NULL;
      tail_->next = curr;
      tail_ = curr;
    }
    curr = next;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    for (int i=1; i<splitPoint; i++){
      start = start->next;
    }
    ListNode* split_next = start->next;
    start->next = NULL;
    return split_next;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == nullptr){
    return second;
  }
  if (second == nullptr){
    return first;
  }

  ListNode* new_head;
  ListNode* node1 = first;
  ListNode* node2 = second;
  if(first->data < second->data) {
    new_head = first;
    node1 = node1->next;
  }
  else {
    new_head = second;
    node2 = node2->next;
  }

  ListNode* curr = new_head;

  while (node1!=nullptr && node2!=nullptr){
    if(node1->data < node2->data){
      curr->next = node1;
      node1->prev = curr;
      node1 = node1->next;
    }
    else{
      curr->next = node2;
      node2->prev = curr;
      node2 = node2->next;
    }
    curr = curr->next;
  }


  if(node1==nullptr){
      curr->next = node2;
      node2->prev = curr;
  }
  else{
      curr->next = node1;
      node1->prev = node2;
  }

  return new_head;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if(chainLength == 1) {return start;}

    ListNode* another = split(start, chainLength/2);

    start = mergesort(start, chainLength/2);
    another = mergesort(another, chainLength/2 + chainLength%2);
    ListNode* after_merge = merge(start, another);
    return after_merge;
}
