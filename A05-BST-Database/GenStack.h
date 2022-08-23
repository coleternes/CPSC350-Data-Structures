#ifndef GENSTACK_H
#define GENSTACK_H
#include <iostream>
using namespace std;

template <class T>
class GenStack {
  public:
    //Member Varaibles
    int size;
    int top;
    T **arr;
    GenStack(); //Default Constructor
    ~GenStack(); //Destructor
    //Stack Functions
    void push(T *data);
    T* pop();
    T* peek();
    //Helper Functions
    bool isFull();
    bool isEmpty();
};

//Default Constructor
template <class T>
GenStack<T>::GenStack() {
  size = 3;
  top = 0;
  arr = new T*[size];
  for (int i = 0; i < size; ++i) {
    arr[i] = new T;
  }
}

//Destructor
template <class T>
GenStack<T>::~GenStack() {
  for (int i = 0; i < size; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

//Push Function
template <class T>
void GenStack<T>::push(T *data) {
  arr[top] = data;
  top = (top + 1) % size;
}

//Pop Function
template <class T>
T* GenStack<T>::pop() {
  top = (top - 1 + size) % size;
  return arr[top];
}

//Peek Function
template <class T>
T* GenStack<T>::peek() {
  //Returns top of the stack
  return arr[top];
}

//isFull Function
template <class T>
bool GenStack<T>::isFull() {
  for (int i = 0; i < size; ++i) {
    if (arr[i] == NULL)
      return false;
  }
  return true;
}

//isEmpty Function
template <class T>
bool GenStack<T>::isEmpty() {
  for (int i = 0; i < size; ++i) {
    if (arr[i] != NULL)
      return false;
  }
  return true;
}

#endif
