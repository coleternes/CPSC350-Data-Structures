#ifndef GENSTACK_H
#define GENSTACK_H
#include <iostream>
#include <string.h>
using namespace std;

template <class T>
class GenStack {
  public:
    //Member Varaibles
    int size;
    int top;
    T *arr;

    //Default Constructor
    GenStack();
    //Overloaded Constructor
    GenStack(int maxSize);
    //Destructor
    ~GenStack();

    //Stack Functions
    void push(T data);
    T pop();
    T peek();
    void resize();
    bool isFull();
    bool isEmpty();
};

//Default Constructor
template <class T>
GenStack<T>::GenStack() {
  size = 128;
  top = -1;
  arr = new T[size];
}

//Overloaded Constructor
template <class T>
GenStack<T>::GenStack(int maxSize) {
  size = maxSize;
  top = -1;
  arr = new T[size];
}

//Destructor
template <class T>
GenStack<T>::~GenStack() {
  delete arr;
}

//push Function
template <class T>
void GenStack<T>::push(T data) {
  if (!isFull()) {
    //Pushes data to the top of the stack
    arr[++top] = data;
  } else {
    //Resizes the array
    resize();
    //Pushes data to the top of the stack
    arr[++top] = data;
  }
}

//pop Function
template <class T>
T GenStack<T>::pop() {
  if (!isEmpty()) {
    //Returns and removes top of the stack
    return arr[top--];
  }
}

//peek Function
template <class T>
T GenStack<T>::peek() {
  if (!isEmpty()) {
    //Returns and removes top of the stack
    return arr[top--];
  }
}

//resize Function
template <class T>
void GenStack<T>::resize() {
  int newSize = size*2;
  T *newArr = new T[newSize];
  memcpy(newArr, arr, size);

  size = newSize;
  delete [] arr;
  arr = newArr;
}

//isFull Function
template <class T>
bool GenStack<T>::isFull() {
  return (top == size-1);
}

//isEmpty Function
template <class T>
bool GenStack<T>::isEmpty() {
  return (top == -1);
}

#endif
