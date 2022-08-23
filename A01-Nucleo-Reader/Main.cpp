#include "NucleoReader.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    //Takes in the command line argument
    string fileName = argv[1];
    //Creates an instance of NucleoReader
    NucleoReader nr;
    //The variable used to see if the user wants to continue the program or not
    char cont;
    do {
      //Calculates the statistics
      nr.calcSum(fileName);
      nr.calcMean();
      nr.calcVar(fileName);
      nr.calcStdDev();
      nr.calcNucleoProb(fileName);
      nr.calcNucleoBigramProb(fileName);
      //Prints out 1000 lines of nucleotides
      nr.printSampleFile();
      //Prompts the user if the program should be continued or exited
      cout << "Would you like to analyze another file? (y/n)" << endl;
      cin >> cont;
      //Asks the user for the fileName if they choose to continue
      if (cont == 'y' || cont == 'Y') {
        cout << "Please enter the file name:" << endl;
        cin >> fileName;
      }
    } while (cont == 'y' || cont == 'Y');
  } else {
    cout << "ERROR: Please provide a file name.\nUSAGE: ./TextAnalyzer.out [file_name]" << endl;
  }
  return 0;
}
