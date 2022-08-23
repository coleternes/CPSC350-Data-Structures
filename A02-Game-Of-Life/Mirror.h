#ifndef MIRROR_H
#define MIRROR_H
#include "Gamemode.h"
#include <iostream>
using namespace std;

//MIRROR SUBCLASS
class Mirror : public Gamemode {
public:
  //Command Line Constructor
  Mirror(int row, int column, float cellProb);
  //File Constructor
  Mirror(string fileName);
protected:
  //Adjusts the checkCell functiuon to fit this gamemode subclass
  virtual void checkGrid();
};

#endif
