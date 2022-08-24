#include "Sort.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

Sort::Sort() { //Constructor
  fileName = "";
  size = -1;
}

Sort::~Sort() { } //Destructor

void Sort::makeFile() {
  cout << "\nPlease enter the name of the file you wish to create:" << endl;
  cin >> fileName; //User inputs the file name

  string testInput = "";
  bool isNum = false;
  cout << "\nPlease enter the number of doubles you wish to generate:" << endl;
  cin >> testInput; //User inputs size of array

  do { //Do-While-Loop to check if the testInput is valid
    isNum = true;
    for (int i = 0; i < testInput.size(); ++i) { //For-Loop to check if each char is an int
      if (!isdigit(testInput[i]))
        isNum = false;
    }
    if (isNum)
      size = stoi(testInput);
    else { //Prompts user until an int is entered
      cout << "\nPlease enter an integer:" << endl;
      cin >> testInput;
    }
  } while (!isNum);

  ofstream currentFile;
  currentFile.open(fileName);

  srand(time(NULL)); //Random seed

  if (currentFile.is_open()) {
    double min = 0.0;
    double max = 100.0;
    currentFile << size << endl; //Adds the size to the file
    for (int i = 0; i < size; ++i) {
      double tmpRand = (double)rand() / RAND_MAX;
      double newDble = min + tmpRand * (max - min); //Generates a random double
      currentFile << newDble << endl; //Adds the tmpRand to the file
    }
  }

  currentFile.close();
}

void Sort::readFile() {
  cout << "\nPlease enter the name of the file you wish to organize:" << endl;
  cin >> fileName; //User inputs the file name

  ifstream currentFile(fileName);
  string currentLine = "";
  int lineNum = 0;

  if (currentFile.is_open()) {
    while (getline(currentFile, currentLine)) {
      if (lineNum == 0) { //Grabs the size
        size = stoi(currentLine);
        arr = new double[size];
      }
      else //Fills the array
        arr[lineNum-1] = stod(currentLine);
      lineNum++;
    }
    currentFile.close();
  } else
    cout << "\n" << fileName << " could not be opened" << endl;
}

void Sort::bubbleSort() {
  bubbleArr = new double[size];

  //Copies the array to the bubble array
  for (int i = 0; i < size; ++i)
    bubbleArr[i] = arr[i];


  auto start = high_resolution_clock::now(); //Starts the timer
  for (int i = 0; i < size; ++i) {
    double tmp = 0.0;
    for (int j = 0; j < size-1; ++j) {
      if (bubbleArr[j] > bubbleArr[j+1]) { //Swaps the values
        tmp = bubbleArr[j+1];
        bubbleArr[j+1] = bubbleArr[j];
        bubbleArr[j] = tmp;
      }
    }
  }
  auto stop = high_resolution_clock::now(); //Stops the timer

  std::time_t startTime = std::chrono::system_clock::to_time_t(start);
  std::time_t stopTime = std::chrono::system_clock::to_time_t(stop);
  std::chrono::duration<double> elapsedSeconds = stop-start; //Calculates the elapsed time
  cout << "\n====Bubble Sort====" << endl;
  cout << "Start Time: " << std::ctime(&startTime); //Writes the start time
  cout << "Stop Time: " << std::ctime(&stopTime); //Writes the stop time
  cout << "Elapsed Time: " << elapsedSeconds.count() << " seconds" << endl; // Writes the elapsed time
}

void Sort::selectionSort() {
  selectionArr = new double[size];

  //Copies the array to the selection array
  for (int i = 0; i < size; ++i)
    selectionArr[i] = arr[i];

  int minIndex = -1;
  double tmp = -1.0;
  auto start = high_resolution_clock::now(); //Starts the timer
  for (int i = 0; i < size-1; ++i) {
    minIndex = i;
    for (int j = i+1; j < size; ++j) {
      if (selectionArr[j] < selectionArr[minIndex])
        minIndex = j; //Sets the lower index
      if (minIndex != i) { //Swaps the values
        tmp = selectionArr[i];
        selectionArr[i] = selectionArr[minIndex];
        selectionArr[minIndex] = tmp;
      }
    }
  }
  auto stop = high_resolution_clock::now(); //Stops the timer

  std::time_t startTime = std::chrono::system_clock::to_time_t(start);
  std::time_t stopTime = std::chrono::system_clock::to_time_t(stop);
  std::chrono::duration<double> elapsedSeconds = stop-start; //Calculates the elapsed time
  cout << "\n====Selection Sort====" << endl;
  cout << "Start Time: " << std::ctime(&startTime); //Writes the start time
  cout << "Stop Time: " << std::ctime(&stopTime); //Writes the stop time
  cout << "Elapsed Time: " << elapsedSeconds.count() << " seconds" << endl; // Writes the elapsed time
}

void Sort::insertionSort() {
  insertionArr = new double[size];

  //Copies the array to the insertion array
  for (int i = 0; i < size; ++i)
    insertionArr[i] = arr[i];

  auto start = high_resolution_clock::now(); //Starts the timer
  for (int i = 1; i < size; ++i) { //Marker
    double tmp = insertionArr[i]; //Store marked item
    int j = i; //Where to start shifting
    while (j > 0 && insertionArr[j-1] >= tmp) { //While the thing to the left is larger, shift
      insertionArr[j] = insertionArr[j-1];
      --j;
    }
    insertionArr[j] = tmp; //Put marked item in right spot
  }
  auto stop = high_resolution_clock::now(); //Stops the timer

  std::time_t startTime = std::chrono::system_clock::to_time_t(start);
  std::time_t stopTime = std::chrono::system_clock::to_time_t(stop);
  std::chrono::duration<double> elapsedSeconds = stop-start; //Calculates the elapsed time
  cout << "\n====Insertion Sort====" << endl;
  cout << "Start Time: " << std::ctime(&startTime); //Writes the start time
  cout << "Stop Time: " << std::ctime(&stopTime); //Writes the stop time
  cout << "Elapsed Time: " << elapsedSeconds.count() << " seconds" << endl; // Writes the elapsed time
}

void Sort::mergeSub(double *subArr, int left, int middle, int right) {
  //Sets the subsizes
  int subSize1 = middle - left + 1;
  int subSize2 = right - middle;

  //Create tmp arrs
  double *leftSubArr = new double[subSize1];
  double *rightSubArr = new double[subSize2];

  //Copy data to tmp arrs
  for (int i = 0; i < subSize1; ++i)
    leftSubArr[i] = subArr[left + i];
  for (int i = 0; i < subSize2; ++i)
    rightSubArr[i] = subArr[middle + 1 + i];

  //Merge the tmp arrs back into subArr
  //Set the indexes
  int firstIndex = 0;
  int secondIndex = 0;
  int mergedIndex = left;
  //Copy the values into subArr
  while (firstIndex < subSize1 && secondIndex < subSize2) {
    if (leftSubArr[firstIndex] <= rightSubArr[secondIndex]) { //Add the leftSubArr value
      subArr[mergedIndex] = leftSubArr[firstIndex];
      firstIndex++;
    } else { //Add the rightSubArr value
      subArr[mergedIndex] = rightSubArr[secondIndex];
      secondIndex++;
    }
    mergedIndex++;
  }

  //Copy the remaining values of leftSubArr
  while (firstIndex < subSize1) {
    subArr[mergedIndex] = leftSubArr[firstIndex];
    firstIndex++;
    mergedIndex++;
  }

  //Copy the remaining values of rightSubArr
  while (secondIndex < subSize2) {
    subArr[mergedIndex] = rightSubArr[secondIndex];
    secondIndex++;
    mergedIndex++;
  }
}

void Sort::mergeRec(double *subArr, int left, int right) {
  if (left < right) {
    int middle = left + (right - left ) / 2;
    //Sort first and second halves
    mergeRec(subArr, left, middle);
    mergeRec(subArr, middle + 1, right);
    mergeSub(subArr, left, middle, right);
  }
}

void Sort::mergeSort() {
  mergeArr = new double[size];

  //Copies the array to the merge array
  for (int i = 0; i < size; ++i) {
    mergeArr[i] = arr[i];
  }

  auto start = high_resolution_clock::now(); //Starts the timer
  mergeRec(mergeArr, 0, size-1);
  auto stop = high_resolution_clock::now(); //Stops the timer


  std::time_t startTime = std::chrono::system_clock::to_time_t(start);
  std::time_t stopTime = std::chrono::system_clock::to_time_t(stop);
  std::chrono::duration<double> elapsedSeconds = stop-start; //Calculates the elapsed time
  cout << "\n====Merge Sort====" << endl;
  cout << "Start Time: " << std::ctime(&startTime); //Writes the start time
  cout << "Stop Time: " << std::ctime(&stopTime); //Writes the stop time
  cout << "Elapsed Time: " << elapsedSeconds.count() << " seconds" << endl; // Writes the elapsed time
}
