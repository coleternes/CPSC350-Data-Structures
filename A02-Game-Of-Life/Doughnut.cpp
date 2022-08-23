#include "Doughnut.h"
#include <iostream>
using namespace std;

//Command Line Constructor
Doughnut::Doughnut(int row, int column, float cellProb) : Gamemode(row, column, cellProb) { }
//File Constructor
Doughnut::Doughnut(string fileName) : Gamemode(fileName) { }

//checkCell Function
void Doughnut::checkGrid() {
  for (int i = 0; i < gRow; ++i) {
    for (int j = 0; j < gColumn; ++j) {
      //Counter for number of alive neighbors around each cell
      int neighborCounter = 0;

      /* Counts the num of alive neighbors that is around the current cell */
      //TOP LEFT
      //Normal Neighbor
      if (i-1 >= 0 && j-1 >= 0) {
        if (curGrid[i-1][j-1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Top
      else if (i-1 < 0 && j-1 >= 0) {
        if (curGrid[gRow-1][j-1] == 'X') {
          neighborCounter++;
        }
      }
      //Wrap Around Neighbor Along Left
      else if (i-1 >= 0 && j-1 < 0) {
        if (curGrid[i-1][gColumn-1] == 'X') {
          neighborCounter++;
        }
      }
      //Wrap Around Neighbor Along Corner
      else if (i-1 < 0 && j-1 < 0) {
        if (curGrid[gRow-1][gColumn-1 == 'X'])
          neighborCounter++;
      }
      //TOP RIGHT
      //Normal Neighbor
      if (i-1 >= 0 && j+1 < gColumn) {
        if (curGrid[i-1][j+1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Top
      else if (i-1 < 0 && j+1 < gColumn) {
        if (curGrid[gRow-1][j+1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Right
      else if (i-1 >= 0 && j+1 >= gColumn) {
        if (curGrid[i-1][0] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Corner
      else if (i-1 < 0 && j+1 >= gColumn) {
        if (curGrid[gRow-1][0] == 'X')
          neighborCounter++;
      }
      //BOTTOM LEFT
      //Normal Neighbor
      if (i+1 < gRow && j-1 >= 0) {
        if (curGrid[i+1][j-1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Bottom
      else if (i+1 >= gRow && j-1 >= 0) {
        if (curGrid[0][j-1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Left
      else if (i+1 < gRow && j-1 < 0) {
        if (curGrid[i+1][gColumn-1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Corner
      else if (i+1 >= gRow && j-1 < 0) {
        if (curGrid[0][gColumn-1] == 'X')
          neighborCounter++;
      }
      //BOTTOM RIGHT
      //Normal Neighbor
      if (i+1 < gRow && j+1 < gColumn) {
        if (curGrid[i+1][j+1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Bottom
      else if (i+1 >= gRow && j+1 < gColumn) {
        if (curGrid[0][j+1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Right
      else if (i+1 < gRow && j+1 >= gColumn) {
        if (curGrid[i+1][0] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Corner
      else if (i+1 >= gRow && j+1 >= gColumn) {
        if (curGrid[0][0] == 'X')
          neighborCounter++;
      }
      //DIRECTLY ABOVE
      //Normal Neighbor
      if (i-1 >= 0) {
        if (curGrid[i-1][j] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Top
      else {
        if (curGrid[gRow-1][j] == 'X')
          neighborCounter++;
      }
      //DIRECTLY BELOW
      //Normal Neighbor
      if (i+1 < gRow) {
        if (curGrid[i+1][j] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Bottom
      else {
        if (curGrid[0][j] == 'X')
          neighborCounter++;
      }
      //DIRECTLY LEFT
      //Normal Neighbor
      if (j-1 >= 0) {
        if (curGrid[i][j-1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Left
      else {
        if (curGrid[i][gColumn-1] == 'X')
          neighborCounter++;
      }
      //DIRECTLY RIGHT
      //Normal Neighbor
      if (j+1 < gColumn) {
        if (curGrid[i][j+1] == 'X')
          neighborCounter++;
      }
      //Wrap Around Neighbor Along Right
      else {
        if (curGrid[i][0] == 'X')
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
