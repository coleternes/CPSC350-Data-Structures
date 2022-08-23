#ifndef GENBST_H
#define GENBST_H
#include "TreeNode.h"
using namespace std;

template <class T>
class GenBST {
  private:
    //Member Variables
    TreeNode<T> *root;
  public:
    GenBST(); //Constrcutor
    ~GenBST(); //Destructor
    //Main Functions
    TreeNode<T>* search(int id);
    void insert(T *value);
    bool deleteNode(T *value);
    TreeNode<T>* getSuccessor(TreeNode<T> *d);
    //Helper functions
    void recPrint(TreeNode<T> *node);
    bool printTree();
    TreeNode<T>* getMin();
    TreeNode<T>* getMax();
    bool isEmpty();
};

//Constructor
template <class T>
GenBST<T>::GenBST() {
  root = new TreeNode<T>(); //Empty Tree
}

//Destructor
template <class T>
GenBST<T>::~GenBST() {
  //More Character Building
}

/* SEARCH FUNCTION */
template <class T>
TreeNode<T>* GenBST<T>::search(int id) {
  if (root->key == NULL) //Tree is empty
    return NULL;
  //Current TreeNode in the BST
  TreeNode<T> *current = root;
  //While-Loop to iterate through the tree
  while (current->key->getID() != id) {
    if (id < current->key->getID()) //Moves current to the left child
      current = current->left;
    else //Moves current to the right child
      current = current->right;
    if (current == NULL)
      return NULL;
  }
  return current;
}

/* INSERT FUNCTION */
template <class T>
void GenBST<T>::insert(T *value) {
  if (search(value->getID()) == NULL) { //Checks if value exists in tree before proceeding
    TreeNode<T> *node = new TreeNode<T>(value);
    if (root->key == NULL) //Tree is empty
      root = node;
    else { //Tree is not empty
      TreeNode<T> *current = root;
      TreeNode<T> *parent = NULL;
      //While-Loop to iterate through the tree
      while (true) {
        parent = current;
        //Go Left
        if (value->getID() < current->key->getID()) {
          current = current->left;
          //Found the insertion point
          if (current == NULL) {
            parent->left = node;
            break;
          }
        }
        //Go Right
        else {
          current = current->right;
          //Found the insertion point
          if (current == NULL) {
            parent->right = node;
            break;
          }
        }
      }
    }
  }
}

/* DELETE FUNCTION */
template <class T>
bool GenBST<T>::deleteNode(T *value) {
  if (root->key == NULL) //Tree is empty
    return false;
  TreeNode<T> *current = root;
  TreeNode<T> *parent = root;
  bool isLeft = true;
  //While-Loop to find the node to be deleted
  while (current->key->getID() != value->getID()) {
    parent = current;
    if (value->getID() < current->key->getID()) { //Go Left
      isLeft = true;
      current = current->left;
    } else { //Go Right
      isLeft = false;
      current = current->right;
    }
    if (current == NULL) { //Value doesn't exist
      return false;
    }
  }
  //If we make it here, then we found the node to be deleted
  if (current->left == NULL && current->right == NULL) {
    //Targeted node has no children
    if (current == root) //Root is the only TreeNode
      root = new TreeNode<T>();
    else if (isLeft) //Current is a left child
      parent->left = new TreeNode<T>();
    else //Current is a right child
      parent->right = new TreeNode<T>();
  } else if (current->right == NULL) {
    //Targeted node has one left child
    if (current == root) //Root is the only TreeNode
      root->key = current->left->key;
    else if (isLeft) //Current is a left child
      parent->left->key = current->left->key;
    else //Current is a right child
      parent->right->key = current->left->key;
    current->left = new TreeNode<T>();
  } else if (current->left == NULL) {
    //Targeted node has one right child
    if (current == root) //Root is the only TreeNode
      root->key = current->right->key;
    else if (isLeft) //Current is a left child
      parent->left->key = current->right->key;
    else //Current is a right child
      parent->right->key = current->right->key;
    current->right = new TreeNode<T>();
  } else {
    //Targeted node has two children
    //At this state, cortisol levels increase exponentially
    TreeNode<T> *successor = getSuccessor(current);
    if (current == root)
      root->key = successor->key;
    else if (isLeft)
      parent->left->key = successor->key;
    else
      parent->right->key = successor->key;
    delete successor;
    successor->left->key = current->left->key;
  }
  return true;
}

/* GETSUCCESSOR FUNCTION */
template <class T>
TreeNode<T>* GenBST<T>::getSuccessor(TreeNode<T> *d) { //d is the node to be deleted
  TreeNode<T> *current = d->right;
  TreeNode<T> *sp = d; //Successors parent
  TreeNode<T> *successor = d;

  while (current->key != NULL) {
    sp = successor;
    successor = current;
    current = current->left;
  }

  //We made it here, so we found the successor
  if (successor->key != d->right->key) {
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}

template <class T>
void GenBST<T>::recPrint(TreeNode<T> *node) {
  if (node != NULL) {
    recPrint(node->left);
    if (node->key != NULL) {
      node->key->toString();
    }
    recPrint(node->right);
  }
}

template <class T>
bool GenBST<T>::printTree() {
  if (root->key != NULL) {
    recPrint(root);
    return true;
  }
  return false;
}

template <class T>
TreeNode<T>* GenBST<T>::getMax() {
  TreeNode<T> *current = root;
  if (root == NULL)
    return NULL;
  while (current->right != NULL) {
    current = current->right; //Max value is stored on the farthest to the right;
  }
  return current; // return &(current->key)
}

template <class T>
TreeNode<T>* GenBST<T>::getMin() {
  TreeNode<T> *current = root;
  if (root == NULL)
    return NULL;
  while (current->left != NULL) {
    current = current->left; //Min value is stored on the farthest to the right;
  }
  return current; // return &(current->key)
}

template <class T>
bool GenBST<T>::isEmpty() {
  return (root->key == NULL);
}

#endif
