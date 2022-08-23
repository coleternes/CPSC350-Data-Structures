#include "Mirror.h"
#include <iostream>
using namespace std;

//Command Line Constructor
Mirror::Mirror(int row, int column, float cellProb) : Gamemode(row, column, cellProb) { }
//File Constructor
Mirror::Mirror(string fileName) : Gamemode(fileName) { }

//checkCell Function
void Mirror::checkGrid() {
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
      //Mirrored Neighbor Along Top
      else if (i-1 < 0 && j-1 >= 0) {
        if (curGrid[i][j-1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Left
      else if (i-1 >= 0 && j-1 < 0) {
        if (curGrid[i-1][j] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Corner
      else if (i-1 < 0 && j-1 < 0) {
        if (curGrid[i][j] == 'X')
          neighborCounter++;
      }
      //TOP RIGHT
      //Normal Neighbor
      if (i-1 >= 0 && j+1 < gColumn) {
        if (curGrid[i-1][j+1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Top
      else if (i-1 < 0 && j+1 < gColumn) {
        if (curGrid[i][j+1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Right
      else if (i-1 >= 0 && j+1 >= gColumn) {
        if (curGrid[i-1][j] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Corner
      else if (i-1 < 0 && j+1 >= gColumn) {
        if (curGrid[i][j] == 'X')
          neighborCounter++;
      }
      //BOTTOM LEFT
      //Normal Neighbor
      if (i+1 < gRow && j-1 >= 0) {
        if (curGrid[i+1][j-1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Bottom
      else if (i+1 >= gRow && j-1 >= 0) {
        if (curGrid[i][j-1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Left
      else if (i+1 < gRow && j-1 < 0) {
        if (curGrid[i+1][j] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Corner
      else if (i+1 >= gRow && j-1 < 0) {
        if (curGrid[i][j] == 'X')
          neighborCounter++;
      }
      //BOTTOM RIGHT
      //Normal Neighbor
      if (i+1 < gRow && j+1 < gColumn) {
        if (curGrid[i+1][j+1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Bottom
      else if (i+1 >= gRow && j+1 < gColumn) {
        if (curGrid[i][j+1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Right
      else if (i+1 < gRow && j+1 >= gColumn) {
        if (curGrid[i+1][j] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Corner
      else if (i+1 >= gRow && j+1 >= gColumn) {
        if (curGrid[i][j] == 'X')
          neighborCounter++;
      }
      //DIRECTLY ABOVE
      //Normal Neighbor
      if (i-1 >= 0) {
        if (curGrid[i-1][j] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Top
      else {
        if (curGrid[i][j] == 'X')
          neighborCounter++;
      }
      //DIRECTLY BELOW
      //Normal Neighbor
      if (i+1 < gRow) {
        if (curGrid[i+1][j] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Bottom
      else {
        if (curGrid[i][j] == 'X')
          neighborCounter++;
      }
      //DIRECTLY LEFT
      //Normal Neighbor
      if (j-1 >= 0) {
        if (curGrid[i][j-1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Left
      else {
        if (curGrid[i][j] == 'X')
          neighborCounter++;
      }
      //DIRECTLY RIGHT
      //Normal Neighbor
      if (j+1 < gColumn) {
        if (curGrid[i][j+1] == 'X')
          neighborCounter++;
      }
      //Mirrored Neighbor Along Right
      else {
        if (curGrid[i][j] == 'X')
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
