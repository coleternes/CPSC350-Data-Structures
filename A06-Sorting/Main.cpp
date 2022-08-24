#include "Sort.h"
using namespace std;

int main(int argc, char **argv) {
  Sort mySort; //Create sort object
  string userInput = "";

  do {
    cout << "\n========MENU========" << endl;
    cout << "Make a New File\t\t(m)" << endl;
    cout << "Read and sort a File\t(r)" << endl;
    cout << "Exit\t\t\t(e)" << endl;
    cin >> userInput; //User inputs what they want the program to do

    if (userInput == "m" || userInput == "M")
      mySort.makeFile(); //Creates a new file that generates double values
    else if (userInput == "r" || userInput == "R") {
      mySort.readFile(); //Reads in the values of the file to arr
      mySort.bubbleSort(); //Copies arr to bubbleArr and sorts bubbleArr
      mySort.selectionSort(); //Copies arr to selectionArr and sorts selectionArr
      mySort.insertionSort(); //Copies arr to insertionArr and sorts insertionArr
      mySort.mergeSort(); //Copies arr to mergeArr and sorts mergeArr
      cout << "\nLook at the Results.txt file for results" << endl;
    }
    else if (userInput != "e" && userInput != "E")
      cout << "\nPlease enter \"m\", \"r\", or \"e\"" << endl; //Error check
  } while (userInput != "e" || userInput == "E");
}
