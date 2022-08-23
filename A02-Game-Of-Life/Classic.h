#ifndef CLASSIC_H
#define CLASSIC_H
#include "Gamemode.h"
#include <iostream>
using namespace std;

//CLASSIC SUBCLASS
class Classic : public Gamemode {
  public:
    //Command Line Constructor
    Classic(int row, int column, float cellProb);
    //File Constructor
    Classic(string fileName);
};

#endif
