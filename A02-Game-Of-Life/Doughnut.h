#ifndef DOUGHNUT_H
#define DOUGHNUT_H
#include "Gamemode.h"
#include <iostream>
using namespace std;

//DOUGHNUT SUBCLASS
class Doughnut : public Gamemode {
  public:
    //Command Line Constructor
    Doughnut(int row, int column, float cellProb);
    //File Constructor
    Doughnut(string fileName);
  protected:
    //Adjusts the checkCell functiuon to fit this gamemode subclass
    virtual void checkGrid();
};

#endif
