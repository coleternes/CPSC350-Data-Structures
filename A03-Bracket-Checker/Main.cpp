#include <iostream>
#include "Checker.h"
using namespace std;

int main(int argc, char **argv) {
  //Checks to make sure there is a second command line argument
  if (argc > 1) {
    string fileName = argv[1];
    string cont = "";
    //Do-While Loop to prompt user if they wish to run the program again
    do {
      Checker ch(fileName);
      //Asks user for if they wish to input another file if there are no errors found in the current file
      if (ch.checkFile()) {
        cout << "\n\nYour file has correct delimiter syntax\nWould you like to check another file? (Y/N)" << endl;
        cin >> cont;
        if (cont == "y" || cont == "Y") {
          cout << "\n\nPlease input the file name:" << endl;
          cin >> fileName;
        }
      //Program outputs the error message for the current file
      } else {
        if (ch.getOutcome() == 'a' || ch.getOutcome() == 'b' || ch.getOutcome() == 'c') {
          ch.errorMessage();
        }
        cont = "";
      }
    } while (cont == "y" || cont == "Y");
  }
  //Prints the error
  else {
    cout << "\nCOMMAND ERROR: Please provide a file name.\nUSAGE: ./Checker.out [file_name.cpp]\n\n" << endl;
  }

  return 0;
}
