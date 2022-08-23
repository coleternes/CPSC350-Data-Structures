#ifndef LISTNODE_H
#define LISTNODE_H
using namespace std;

template <class T>
class ListNode {
  public:
    //Member Variables
    T *data;
    ListNode<T> *next;
    ListNode<T> *prev;
    ListNode(); //Default Constructor
    ListNode(T *d); //Overloaded Constructor
    ~ListNode(); //Destructor
};

template <class T>
ListNode<T>::ListNode() { //Default Constructor
  data = NULL;
  next = NULL;
  prev = NULL;
}

template <class T>
ListNode<T>::ListNode(T *d) { //Overloaded Constructor
  data = d;
  next = NULL;
  prev = NULL;
}

template <class T>
ListNode<T>::~ListNode() { //Destructor
  delete data;
  next = NULL;
  prev = NULL;
}

#endif
