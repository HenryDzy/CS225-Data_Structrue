/**
 * CS 225 e08
 * @file avltree.cpp
 * @author NEW
 * Definitions of the binary tree functions you'll be writing for this exam.
 * You'll need to modify this file.
 */


// TODO
/* attach a given subtree (t) to the existing tree (this)
 * assumption 1: both trees are AVL
 * assumption 2: all nodes in tree (t) have values strictly larger that the nodes in the existing tree (this)
 */
template <class K, class V>
void AVLTree<K, V>::join(const AVLTree<K, V> &t)
{
    // write your AVLTree::join code here
    Node* right_most = root;
    Node* pre_right_most;
    Node* pop_vector;
    // inorder_push(inorder_vec, t.root);
    // for(unsigned i = 0;i<inorder_vec.size(); i++){
    //     pop_vector = inorder_vec[i];
    //     for(right_most = root; right_most->right!=NULL; right_most = right_most->right){}
    //     insert(pop_vector->key, pop_vector->value);
    //     rebalance(right_most);
    // }
    // insert(pop_vector);
    // rebalance(right_most);
    while(right_most != NULL){
        pre_right_most = right_most;
        right_most = right_most->right;
    }
    pre_right_most->right = t.root;
    right_most = t.root;
    height(root);
    inorder_push(inorder_vec, pre_right_most);
    for(unsigned i=0; i<inorder_vec.size(); i++){
        pop_vector = inorder_vec[i];
        rebalance(pop_vector);
    }
    // printf("%d\n%d\n%d", pre_right_most->height, right_most->height,root->height);
    // rebalance(pre_right_most);
    // rebalance(root);

}

template <class K, class V>
void AVLTree<K, V>::inorder_push(vector<Node*> & inorder_vector, Node* node){
    if(node == NULL){
        return;
    }
    inorder_push(inorder_vector, node->left);
    inorder_push(inorder_vector, node->right);
    inorder_vector.push_back(node);
}


template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	if (root == NULL) {
		root = new Node(key, value);
		return;
	}

	vector<Node*> path;
	Node* walk = root;

	while (walk != NULL) {
		path.push_back(walk);
		if (walk->key == key)
			return;
		if (key < walk->key) {
			walk = walk->left;
		}
		else {
			walk = walk->right;
		}
	}

	if (key < path.back()->key) {
		path.back()->left = new Node(key, value);
	}
	else {
		path.back()->right = new Node(key, value);
	}

	while (!path.empty()) {
		rebalance(path.back()->left);
		rebalance(path.back()->right);
		path.pop_back();
	}

	rebalance(root);
}


template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    /*  a                            b
       / \                         /   \
      al  b                       a     c
         / \         -->         / \   / \
        bl  c                   al bl cl cr
           / \
          cl cr
        */
    Node* newroot = t->right;
    t->right = newroot->left;
    newroot->left = t;
    t = newroot;
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    /*          a                          b
               / \                       /   \
              b  ar                     c     a
             / \         -->           / \   / \
            c   br                    cl cr br ar
           / \
          cl cr
    */
    Node* newroot = t->left;
    t->left = newroot->right;
    newroot->right = t;
    t = newroot;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    Node* y = t->left;
    Node* z = y->right;
    y->right = z->left;
    z->left = y;
    t->left = z->right;
    z->right = t;
    t = z; 
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    Node* y = t->right;
    Node* z = y->left;
    y->left = z->right;
    z->right = y;
    t->right = z->left;
    z->left = t;
    t = z; 
}


template <class K, class V>
int AVLTree<K, V>::height(Node* subtree)
{
   if (subtree == NULL)
        return -1;
    subtree->height = 1 + max(height(subtree->left), height(subtree->right));
    return subtree->height;
}


template <class K, class V>
int AVLTree<K, V>::balance(Node* subtree)
{
    if (subtree == NULL)
        return 0;
    return height(subtree->right) - height(subtree->left);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    int curBF = balance(subtree);
    
    if(curBF > 1)
    {
        if(balance(subtree->right) == 1)
        	rotateLeft(subtree);
        else
            rotateRightLeft(subtree);
    }
    else if(curBF < -1)
    {
        if(balance(subtree->left) == -1)
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);
    }
    height(root);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* tmp = subtree->left;
            while(tmp->right != NULL)
                tmp = tmp->right;
            swap(subtree, tmp);
            remove(subtree->left, tmp->key);
        } else { 
            /* one-child remove */
            // your code here
            Node* tmp = subtree;
            subtree = (subtree->left)?(subtree->left):(subtree->right);
            delete tmp;
            tmp = NULL;
        }
        // your code here
        rebalance(subtree);
    }
}
