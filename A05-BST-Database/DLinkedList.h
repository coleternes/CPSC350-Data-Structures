#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include "ListNode.h"
using namespace std;

template <class T>
class DLinkedList {
  public:
    //Member Variables
    ListNode<T> *front;
    ListNode<T> *back;
    unsigned int size;
    DLinkedList(); //Constructor
    virtual ~DLinkedList(); //Destructor
    //Main Functions
    void insertFront(T *d);
    T* removeFront();
    void insertBack(T *d);
    T* removeBack();
    //Helper Functions
    void remove(T *d);
    bool isEmpty();
};

template <class T>
DLinkedList<T>::DLinkedList() { //Constructor
  front = NULL;
  back = NULL;
  size = 0;
}

template <class T>
DLinkedList<T>::~DLinkedList() { //Destructor
  ListNode<T> *curr = front;

  while (curr != NULL) { //Iterates through entire list
    ListNode<T> *next = curr->next;
    delete curr;
    curr = next;
  }
}

template <class T>
void DLinkedList<T>::insertFront(T *d) {
  ListNode<T> *node = new ListNode<T>(d);
  if (isEmpty()) { //Empty List
    back = node;
  } else { //Not an Empty List
    front->prev = node;
    node->next = front;
  }

  front = node; //Set front to newly added node
  size++;
}

template <class T>
T* DLinkedList<T>::removeFront() {
  if (front != NULL) { //Front is not empty
    ListNode<T> *ft = front; //Temp pointer to the front
    if (front->next == NULL) { //One node in the list
      back = NULL;
    } else { //List has more than one node
      front->next->prev = NULL;
    }

    front = front->next; //Set the front to the next ListNode
    ft->next = NULL; //Nullify the pointer of ft
    T *temp = ft->data; //temp to hold the data
    delete ft; //Delete ft (old front)
    size--;
    return temp;
  }
}

template <class T>
void DLinkedList<T>::insertBack(T *d) {
  ListNode<T> *node = new ListNode<T>(d);
  if (isEmpty()) { //Empty List
    front = node;
  } else { //Not an Empty List
    back->next = node;
    node->prev = back;
  }

  back = node; //Set front to newly added node
  size++;
}

template <class T>
T* DLinkedList<T>::removeBack() {
  if (back != NULL) { //Back is not empty
    ListNode<T> *bk = back; //Temp pointer to the back
    if (back->prev == NULL) { //One node in the list
      front = NULL;
    } else { //List has more than one node
      back->prev->next = NULL;
    }

    back = back->prev; //Set the back to the next ListNode
    bk->prev = NULL; //Nullify the pointer of bk
    T *temp = bk->data; //temp to hold the data
    delete bk; //Delete bk (old back)
    size--;
    return temp;
  }
}

template <class T>
void DLinkedList<T>::remove(T *d) {
  ListNode<T> *current = front;
  while (current != NULL) {
    if (current->data == d)
      break;
    current = current->next;
  }
  if (current->data != d)
    current = NULL;

  ListNode<T> *tmpPrev = current->prev;
  current->prev->next = current->next;
  current->next->prev = tmpPrev;
}

template <class T>
bool DLinkedList<T>::isEmpty() {
  return (size == 0); //Returns if the doubly-linked list is empty or not
}

#endif
