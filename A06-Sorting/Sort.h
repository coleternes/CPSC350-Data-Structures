#ifndef SORT_H
#define SORT_H
#include <iostream>
using namespace std;

class Sort {
  public:
    //Member Variables
    double *arr;
    double *bubbleArr;
    double *selectionArr;
    double *insertionArr;
    double *mergeArr;
    string fileName;
    int size;
    Sort(); //Constructor
    ~Sort(); //Destructor
    //File Functions
    void makeFile();
    void readFile();
    void writeFile();
    //Sorting Algorithms
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void mergeSub(double *subArr, int left, int middle, int right);
    void mergeRec(double *subArr, int left, int right);
    void mergeSort();
};

#endif
