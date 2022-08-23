#ifndef CHECKER_H
#define CHECKER_H
#include <iostream>
#include "GenStack.h"
using namespace std;

class Checker {
  private:
    //Member Variables
    char opener;
    char closer;
    char expOpener;
    char expCloser;
    string fileName;
    int lineNum;
    int maxLineNum;
    char outcome;
    GenStack<char> st;
  public:
    //Constructor & Destructor
    Checker(string fn);
    ~Checker();
    //Function Signatures
    bool checkFile();
    char getOutcome();
    void calcMaxLineNum();
    void errorMessage();
};

#endif
