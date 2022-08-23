#include "Gamemode.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//Command Line Constructor
Gamemode::Gamemode(int row, int column, float cellProb) {
  gRow = row;
  gColumn = column;
  gCellProb = cellProb;
  genCounter = 1;
  gFileName = "";
}
//File Constructor
Gamemode::Gamemode(string fileName) {
  gRow = 0;
  gColumn = 0;
  gCellProb = -1;
  genCounter = 1;
  gFileName = fileName;
}
//Destructor
Gamemode::~Gamemode() {
  delete curGrid;
  delete newGrid;
}

//Prints out the grid
void Gamemode::printGrid() {
  if (genCounter == 1)
    cout << "(Initial Grid) ";
  cout << "Generation " << genCounter << ":" << endl;
  for (int i = 0; i < gRow; ++i) {
    for (int j = 0; j < gColumn; ++j) {
      //Prints the curGrid generation that has no changes applied
      cout << curGrid[i][j] << ' ';
    }
    cout << endl;
  }
  cout << "\n\n";
  genCounter++;
}

//Writes out the grid to file
void Gamemode::writeGrid(string fileName) {
  ofstream outputFile;
  outputFile.open(fileName + ".out", ios::app);
  if (genCounter == 1)
    outputFile << "(Initial Grid) ";
  outputFile << "Generation " << genCounter-1 << ":" << endl;
  for (int i = 0; i < gRow; ++i) {
    for (int j = 0; j < gColumn; ++j) {
      //Prints the curGrid generation that has no changes applied
      outputFile << curGrid[i][j] << ' ';
    }
    outputFile << endl;
  }
  outputFile << "\n\n";
  genCounter++;
  outputFile.close();
}

//Counts the num of lines in the file
int Gamemode::lineCounter() {
  //Opens a file with the given name
  ifstream curFile (gFileName + ".txt");
  //Variable for the number of lines in the file
  int numLines = 0;
  //The current line in the file
  string curLine = "";
  //Makes sure that a file name is actually put in
  if (gCellProb == -1) {
    //Counts the lines
    while (getline(curFile, curLine)) {
      numLines++;
    }
  } else {
    cout << "!!!!ERROR!!!!\nFile cannot be opened" << endl;
  }
  curFile.close();
  return numLines;
}

//Initiates the Grid the same way for all Types of Gamemode
void Gamemode::initiateGrid() {
  //User uses a File to initiate grid values
  if (gCellProb == -1) {
    //Opens a file with the given name
    ifstream curFile (gFileName + ".txt");
    //The line index in the file
    int lineIndex = 0;
    //The current line from the file being added to the array
    string curLine = "";
    //A temporary line from the array thats being read into the grid
    string tempLine = "";
    //The array that stores the lines from the file
    string lineArray[lineCounter()];

    //Checks to see if the file is currently open
    if (curFile.is_open()) {
      //Fils lineArray with each line of the file
      while (getline(curFile, curLine)) {
        lineArray[lineIndex] = curLine;
        lineIndex++;
      }
      //The first two lines of the files is the dimension of the grid
      gRow = stoi(lineArray[0]);
      gColumn = stoi(lineArray[1]);

      //Declares the grid with the row and column from the file
      //This is the grid that is printed out
      curGrid = new char*[gRow];
      for(int i = 0; i < gRow; ++i)
        curGrid[i] = new char[gColumn];
      //This is the grid that changes are applied to
      newGrid = new char*[gRow];
      for(int i = 0; i < gRow; ++i)
        newGrid[i] = new char[gColumn];

      /* curGrid will be the grid that is always printed out
       * newGrid will be the grid that has changes applied to
       * So newGrid will need to be copied and pasted onto curGrid each generation
       */

      //Fills the grids with the given grid in the file
      for (int i = 2; i < lineCounter(); ++i) {
        //tempLine is the current file line from the array
        tempLine = lineArray[i];
        for (int j = 0; j < tempLine.size(); ++j) {
          //tempChar is the current char from the current file line
          char tempChar = toupper(tempLine[j]);
          //Since i starts at i = 2, the appropriate grid line is equal to i - 2
          //If the tempChar is X, then fill it appropriately
          if (tempChar == 'X') {
            curGrid[i-2][j] = tempChar;
          }
          //If the tempChar is anything other than X, then fill it blank
          else {
            curGrid[i-2][j] = '-';
          }
        }
      }
    } else {
      cout << "!!!!ERROR!!!!\nFile cannot be opened" << endl;
    }
    curFile.close();
  }
  //User uses the Command Line to initiate grid values
  else {
    //Creates the seed for rand()
    srand(time(NULL));
    //User defined the row and column from the command line
    //Grid that is printed out
    curGrid = new char*[gRow];
    for(int i = 0; i < gRow; ++i)
      curGrid[i] = new char[gColumn];
    //Grid that changes are applied to
    newGrid = new char*[gRow];
    for(int i = 0; i < gRow; ++i)
      newGrid[i] = new char[gColumn];
    /* curGrid will be the grid that is always printed out
     * newGrid will be the grid that has changes applied to
     * So newGrid will need to be copied and pasted onto curGrid each generation
     */

    //Calculates the total number of cells in the grid
    //and then used gCellProb to see how many need to be filled with x's
    int totalCells = gRow * gColumn;
    int filledCells = gCellProb * totalCells;

    //Fills an array of numbers with length
    int numArray[totalCells];
    for (int i = 0; i < totalCells; ++i) {
      numArray[i] = i;
    }

    //Double For-Loop to iterate through grids
    for (int i = 0; i < gRow; ++i) {
      for (int j = 0; j < gColumn; ++j) {
        //Randomly picks a num between 0 and totalCells
        int randIndex = rand() % totalCells;

        //If the numArray element at randIndex == -1, then it has already been chosen
        //and must pick a different index that has a value in it that't not -1
        while (numArray[randIndex] == -1) {
          randIndex = rand() % totalCells;
        }

        //If the randIndex < filledCells, then that cell will be filled with an X
        if (randIndex < filledCells) {
          curGrid[i][j] = 'X';
          numArray[randIndex] = -1;
        }
        //If the randIndex > filledCells, then that cell will be filled with a dash
        else {
          curGrid[i][j] = '-';
          numArray[randIndex] = -1;
        }

        /* This method of filling the grid will accurately and randomly fill
         * the grid with an appropriate num of cells that are alive and dead
         */
      }
    }
  }
}

//Copies and pastes all the changes that are applied to newGrid onto curGrid
void Gamemode::flipGrids() {
  for (int i = 0; i < gRow; ++i) {
    for (int j = 0; j < gColumn; ++j) {
      curGrid[i][j] = newGrid[i][j];
    }
  }
}

//Checks to see if the grid is empty of cell life
bool Gamemode::isEmpty(string fileName) {
  int totalCells = gRow * gColumn;
  int cellCounter = 0;
  //Counts the number of empty cells on the grid
  for (int i = 0; i < gRow; ++i) {
    for (int j = 0; j < gColumn; ++j) {
      if (curGrid[i][j] == '-')
        cellCounter++;
    }
  }
  //Checks to see if the number of empty cells is equal to the total number of cells on the grid
  if (cellCounter == totalCells) {
    if (gCellProb == -1) {
      ofstream outputFile;
      outputFile.open(fileName + ".out", ios::app);
      outputFile << "The Grid is devoid of life\n====GAME OVER====\n\n" << endl;
      outputFile.close();
      return true;
    }
    else {
      cout << "The Grid is devoid of life\n====GAME OVER====\n\n" << endl;
      return true;
    }
  }
  else
    return false;
}

//Checks to see if the grid is the same as the last generation
bool Gamemode::isSame(string fileName) {
  int totalCells = gRow * gColumn;
  int cellCounter = 0;
  //Counts the number of cells that are the same from both generations
  for (int i = 0; i < gRow; ++i) {
    for (int j = 0; j < gColumn; ++j) {
      if (curGrid[i][j] == newGrid[i][j])
        cellCounter++;
    }
  }
  //Checks to see if the number of cells that remained the same over the two generations
  //is equal to the total number of cells on the grid
  if (cellCounter == totalCells) {
    if (gCellProb == -1) {
      ofstream outputFile;
      outputFile.open(fileName + ".out", ios::app);
      outputFile << "\n\nThe Grid has stabilized\n====GAME OVER====\n\n" << endl;
      outputFile.close();
      return true;
    }
    else {
      cout << "\n\nThe Grid has stabilized\n====GAME OVER====\n\n" << endl;
      return true;
    }
  }
  else
    return false;
}

/* Base Class version of checking the cell for requirements of life or death
 * Use polymorphism to override this function if the gamemode is different
 * This function will use the rules required for the classic gamemode
 */
void Gamemode::checkGrid() {
  for (int i = 0; i < gRow; ++i) {
    for (int j = 0; j < gColumn; ++j) {
      //Counter for number of alive neighbors around each cell
      int neighborCounter = 0;

      /* Counts the num of alive neighbors that is around the current cell */
      //TOP LEFT
      if (i-1 >= 0 && j-1 >= 0) {
        if (curGrid[i-1][j-1] == 'X')
          neighborCounter++;
      }
      //TOP RIGHT
      if (i-1 >= 0 && j+1 < gColumn) {
        if (curGrid[i-1][j+1] == 'X')
          neighborCounter++;
      }
      //BOTTOM LEFT
      if (i+1 < gRow && j-1 >= 0) {
        if (curGrid[i+1][j-1] == 'X')
          neighborCounter++;
      }
      //BOTTOM RIGHT
      if (i+1 < gRow && j+1 < gColumn) {
        if (curGrid[i+1][j+1] == 'X')
          neighborCounter++;
      }
      //DIRECTLY ABOVE
      if (i-1 >= 0) {
        if (curGrid[i-1][j] == 'X')
          neighborCounter++;
      }
      //DIRECTLY BELOW
      if (i+1 < gRow) {
        if (curGrid[i+1][j] == 'X')
          neighborCounter++;
      }
      //DIRECTLY LEFT
      if (j-1 >= 0) {
        if (curGrid[i][j-1] == 'X')
          neighborCounter++;
      }
      //DIRECTLY RIGHT
      if (j+1 < gColumn) {
        if (curGrid[i][j+1] == 'X')
          neighborCounter++;
      }

      /*Check for Num of Neighbors*/
      //If neighborCounter = 0 or 1, then current cell dies
      if (neighborCounter <= 1)
        newGrid[i][j] = '-';
      //If neighborCounter = 2, then current cell remains the same
      else if (neighborCounter == 2)
        newGrid[i][j] = curGrid[i][j];
      //If neighborCounter = 3, then current cell comes to life
      else if (neighborCounter == 3)
        newGrid[i][j] = 'X';
      //If neighborCounter = 4, 5, 6, 7, or 8, then current cell dies
      else
        newGrid[i][j] = '-';
    }
  }
}
