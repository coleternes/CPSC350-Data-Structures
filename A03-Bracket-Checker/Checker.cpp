#include <iostream>
#include <fstream>
#include "GenStack.h"
#include "Checker.h"
using namespace std;

//Constructor
Checker::Checker(string fn) {
  opener = '\0';
  closer = '\0';
  expOpener = '\0';
  expCloser = '\0';
  fileName = fn;
  lineNum = 1;
  maxLineNum = 0;
  outcome = '\0';
}

//Destructor
Checker::~Checker() {}

//checkFile Function
bool Checker::checkFile() {
  //Opens a file with the given name
  ifstream currentFile(fileName);
  string currentLine = "";

  //Checks to see if the file is currently open
  if (currentFile.is_open()) {
    //Iterates through each line in the file
    while (getline(currentFile, currentLine)) {
      for (int i = 0; i < currentLine.size(); ++i) {
        /* Checks for openers and pushes them to the stack */
        if (currentLine[i] == '{') {
          opener = '{';
          st.push(opener);
        } else if (currentLine[i] == '(') {
          opener = '(';
          st.push(opener);
        } else if (currentLine[i] == '[') {
          opener = '[';
          st.push(opener);
        }

        /* Checks for errors if closer is } */
        if (currentLine[i] == '}') {
          //Set closer to }
          closer = '}';
          //If there are no openers left in stack,
          //then return false and determine correct error outcome
          if (st.isEmpty()) {
            expOpener = '{';
            //Determines type of error outcome
            outcome = 'a';
            return false;
          }
          //If the popped opener on the stack does not equal appropriate opener,
          //then return false and determine correct error outcome
          else if (st.pop() != '{') {
            expOpener = '{';
            //Determines type of error outcome
            outcome = 'b';
            return false;
          }
        }
        /* Checks for errors if closer is ) */
        else if (currentLine[i] == ')') {
          //Set closer to }
          closer = ')';
          //If there are no openers left in stack,
          //then return false and determine correct error outcome
          if (st.isEmpty()) {
            expOpener = '(';
            //Determines type of error outcome
            outcome = 'a';
            return false;
          }
          //If the popped opener on the stack does not equal appropriate opener,
          //then return false and determine correct error outcome
          else if (st.pop() != '(') {
            expOpener = '(';
            //Determines type of error outcome
            outcome = 'b';
            return false;
          }
        }
        /* Checks for errors if closer is ] */
        else if (currentLine[i] == ']') {
          //Set closer to }
          closer = ']';
          //If there are no openers left in stack,
          //then return false and determine correct error outcome
          if (st.isEmpty()) {
            expOpener = '[';
            //Determines type of error outcome
            outcome = 'a';
            return false;
          }
          //If the popped opener on the stack does not equal appropriate opener,
          //then return false and determine correct error outcome
          else if (st.pop() != '[') {
            expOpener = '[';
            //Determines type of error outcome
            outcome = 'b';
            return false;
          }
        }
      }
      lineNum++;
    }
    //If the stack has remaining values in it after the file is fully read,
    //then return false and determine correct error outcome
    if (st.pop() == '{') {
      expCloser = '}';
      //Determines type of error outcome
      outcome = 'c';
      return false;
    } else if (st.pop() == '(') {
      expCloser = ')';
      //Determines type of error outcome
      outcome = 'c';
      return false;
    } else if (st.pop() == '[') {
      expCloser = ']';
      //Determines type of error outcome
      outcome = 'c';
      return false;
    }

    //If it is the last line and the stack is empty,
    //then the file has no syntax errors in it
    if (lineNum == maxLineNum && st.isEmpty())
      return true;
  } else {
    cout << "\nFILE ERROR: File cannot be opened\n" << endl;
    //Determines type of error outcome
    outcome = 'd';
    return false;
  }
}

//getOutcome Function
char Checker::getOutcome() {
  return outcome;
}

//calcMaxLineNum Function
void Checker::calcMaxLineNum() {
  //Opens a file with the given name
  ifstream currentFile(fileName);
  string currentLine = "";

  //Checks to see if the file is currently open
  if (currentFile.is_open()) {
    //Counts the lines
    while (getline(currentFile, currentLine)) {
      maxLineNum++;
    }
  }
  currentFile.close();
}

//errorMessage Function
void Checker::errorMessage() {
  //Error message determined by the outcome type
  if (outcome == 'a') {
    cout << "\nSYNTAX ERROR:\nLine " << lineNum << ": " << closer << " does not have a matching opening brace\nSyntax requires: " << expOpener << "\n" << endl;
  } else if (outcome == 'b') {
    cout << "\nSYNTAX ERROR:\nLine " << lineNum << ": " << closer << " does not match with " << opener << "\nSyntax requires: " << expOpener << "\n" << endl;
  } else if (outcome == 'c') {
    cout << "\nSYNTAX ERROR:\nLine " << lineNum-1 << ": " << opener << " does not have a matching closing brace\nSyntax requires: " << expCloser << "\n" << endl;
  }
}
