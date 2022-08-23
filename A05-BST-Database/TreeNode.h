#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
using namespace std;

template <class T>
class TreeNode {
  public:
    //Member Variables
    T *key;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode(); //Default Constructor
    TreeNode(T *k); //Overloaded Constructor
    TreeNode(TreeNode<T> *tn); //Copy Constructor
    ~TreeNode(); //Destructor
};

//Default Constructor
template <class T>
TreeNode<T>::TreeNode() {
  key = NULL;
  left = NULL; //new TreeNode<T>();
  right = NULL; //new TreeNode<T>();
}

//Overloaded Constructor
template <class T>
TreeNode<T>::TreeNode(T *k) {
  key = k;
  left = NULL; //new TreeNode<T>();
  right = NULL; //new TreeNode<T>();
}

//Copy Constructor
template<class T>
TreeNode<T>::TreeNode(TreeNode<T> *tn) {
  key = tn->key;
  left = tn->left;
  right = tn->right;
}

//Destructor
template <class T>
TreeNode<T>::~TreeNode() {
  delete key;
  left = NULL;
  right = NULL;
}

#endif
