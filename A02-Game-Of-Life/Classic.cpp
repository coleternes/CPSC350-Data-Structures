#include "Classic.h"
#include <iostream>
using namespace std;

//Command Line Constructor
Classic::Classic(int row, int column, float cellProb) : Gamemode(row, column, cellProb) { }
//File Constructor
Classic::Classic(string fileName) : Gamemode(fileName) { }

/* Since checkCell() in the base class is based on the classic gamemode,
 * there is no need to use polymorphism and change the base class function
 */
