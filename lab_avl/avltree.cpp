/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

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
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    t->height = 1 + max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    t = y;
    t->height = 1 + max(heightOrNeg1(t->right), heightOrNeg1(t->left)); 
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    t->height = 1 + max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    t = y;
    t->height = 1 + max(heightOrNeg1(t->right), heightOrNeg1(t->left));    
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{ 
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == NULL){
        return;
    }
    
    int b = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if(b == -2){
        int b_left=0;
        if(subtree->left != NULL){
            b_left = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        }
        if (b_left == -1) {
            rotateRight(subtree);
        }
        else {
            rotateLeftRight(subtree);
        }
    }
    else if(b == 2) {
        int b_right=0;
        if(subtree->right != NULL){
            b_right = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        }
        if(b_right == 1) {
            rotateLeft(subtree);
        }
        else {
            rotateRightLeft(subtree);
        }
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
        
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL){
        subtree = new Node(key, value);
    }
    else if(key < subtree->key){
        insert(subtree->left, key, value);
    }
    else if (key >= subtree->key){
        insert(subtree->right, key, value);
    }
    else if (key == subtree->key){
        subtree->value = value;
    }
    rebalance(subtree);
    subtree->height = 1+max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));    

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
        {return;}

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            // subtree->left = NULL;
            // subtree->right = NULL;
            delete subtree;
            subtree = NULL;
            // return;
        } 
        else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* IOP = subtree->left;
            while(IOP->right != NULL){
                IOP = IOP->right;
            }
            swap(subtree, IOP);
            remove(subtree->left, key);
        } 
        else {
            /* one-child remove */
            // your code here
            Node* t_left = subtree->left;
            Node* t_right = subtree->right;
            if(subtree->left != NULL){
                delete subtree;
                subtree = t_left;
            }
            else if (subtree->right!=NULL){
                delete subtree;
                subtree = t_right;
            }
            // else{
            //     delete subtree;
            //     subtree = NULL;
            // }
        }
    }
        // subtree->height = 1+max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
        rebalance(subtree);
        
        // your code here
}
