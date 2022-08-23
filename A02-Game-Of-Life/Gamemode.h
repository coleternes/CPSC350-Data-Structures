#ifndef GAMEMODE_H
#define GAMEMODE_H
#include <iostream>
using namespace std;

//GAMEMODE BASE CLASS
class Gamemode {
  public:
    //Constructor with Parameters given in Command Line
    Gamemode(int row, int column, float cellProb);
    //Constructor with Parameters give in File
    Gamemode(string fileName);
    //Destructor
    virtual ~Gamemode();
    //Functions that will remain the same for all Gamemode subclasses
    void printGrid();
    void writeGrid(string fileName);
    int lineCounter();
    void initiateGrid();
    void flipGrids();
    bool isEmpty(string fileName);
    bool isSame(string fileName);


    virtual void checkGrid();
  protected:
    //Member Variables
    int gColumn;
    int gRow;
    int genCounter;
    float gCellProb;
    string gFileName;
    char** curGrid;
    char** newGrid;
};

#endif
