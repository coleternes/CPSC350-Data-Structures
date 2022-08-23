#include "Gamemode.h"
#include "Classic.h"
#include "Doughnut.h"
#include "Mirror.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

int main() {
  Gamemode* game;
  //Variables used to control the initialization of the game board
  string cont = "";
  string outputStyle = "";
  string outputFileName = "";
  bool gameOver = false;
  bool fileOpen = true;
  int newDelayTime = -1;

  //The first greeting of the game
  cout << "\n\n==WELCOME TO GAME OF LIFE==" << endl;

  //Do-While that makes sure the user wants to continue with the board that is generated
  do {
    //User response variables must be strings in case the user inputs more than one char
    string paramStyle = "";
    string inputFileName = "";
    string userGame = "";
    //Variables that will be inputed into the game
    string row = "";
    string column = "";
    string cellProb = "";
    string delayTime = "";
    int newRow = -1;
    int newColumn = -1;
    float newCellProb = -1;
    bool rowOnlyInt = true;
    bool colOnlyInt = true;
    bool probOnlyInt = true;
    bool delayOnlyInt = true;

    //Ask the user how to input the gamemode parameters and prompts user to input their choice
    cout << "\nHow will you input the parameters for the gameboard?\nInput File [F]\tCommand Line [C]" << endl;
    cin >> paramStyle;
    //Do-While loop to continually prompt user until a correct response is inputed
    do {
      //Puts the user input to all lowercase
      for (int i = 0; i < paramStyle.size(); ++i)
        paramStyle[i] = tolower(paramStyle[i]);
      //Checks to see if the input is appropriate
      if (paramStyle == "f") {
        cout << "\nYou have selected File Input Mode\n\nPlease enter the File Name:" << endl;
        cin >> inputFileName;
        //Do-While Loop to check if the filename is valid
        do {
          fileOpen = true;
          ifstream inputFile (inputFileName + ".txt");
          if (!inputFile.is_open()) {
            cout << "\n\n!!!!ERROR!!!!\nPlease enter a valid File Name:" << endl;
            cin >> inputFileName;
            fileOpen = false;
          }
        } while (!fileOpen);
      }
      else if (paramStyle == "c") {
        //Prompts the user for the number of rows
        cout << "\nYou have selected Command Line Input Mode\n\n\nPlease enter the number of rows for the Grid:" << endl;
        cin >> row;
        //Do-While loop to continually prompt user until a correct response is inputed
        do {
          rowOnlyInt = true;
          //Checks to see if the input is a int
          for (int i = 0; i < row.size(); ++i) {
            if (!isdigit(row[i]))
              rowOnlyInt = false;
          }
          //Program continues to prompt the user
          if (rowOnlyInt) {
            newRow = stoi(row);
            //Prompts the user for the number of columns
            cout << "\nPlease enter the number of Columns for the Grid:" << endl;
            cin >> column;
            //Do-While loop to continually prompt user until a correct response is inputed
            do {
              colOnlyInt = true;
              //Checks to see if the input is a int
              for (int i = 0; i < column.size(); ++i) {
                if (!isdigit(column[i]))
                  colOnlyInt = false;
              }
              //Program continues to prompt the user
              if (colOnlyInt) {
                newColumn = stoi(column);
                cout << "\nPlease enter the Probability of Cell Life on the Grid (Between 0 & 1):" << endl;
                cin >> cellProb;
                //Do-While loop to continually prompt user until a correct response is inputed
                do {
                  probOnlyInt = true;
                  //Program tries to convert the user input to a float
                  try {
                    newCellProb = stof(cellProb);
                  }
                  //If it can't then it prompts the user to try again
                  catch (...) {
                    probOnlyInt = false;
                  }
                  //Program finishes and tests the prompts
                  if (probOnlyInt) {
                    //Succesfully converts cellProb to a float
                    newCellProb = stof(cellProb);
                    //If it't not within the bounds, then prompts user to enter it again
                    if (newCellProb < 0 || newCellProb > 1)
                      probOnlyInt = false;
                  }
                  //If cellProb is not a float or not within the bounds, prompts the user to enter it again
                  if (!probOnlyInt) {
                    cout << "\n!!!!ERROR!!!!\nPlease enter a value between 0 and 1" << endl;
                    cin >> cellProb;
                  }
                } while (!probOnlyInt);
              }
              //Prompts the user to enter col again
              else {
                cout << "\n!!!!ERROR!!!!\nPlease enter a valid column value" << endl;
                cin >> column;
              }
            } while (!colOnlyInt);
          }
          //Prompts the user to enter row again
          else {
            cout << "\n!!!!ERROR!!!!\nPlease enter a valid row value" << endl;
            cin >> row;
          }
        } while (!rowOnlyInt);
      }
      //Prompts the user to enter an appropriate input
      else {
        cout << "\n!!!!ERROR!!!!\nPlease enter the following:\nInput File [F]\tCommand Line [C]" << endl;
        cin >> paramStyle;
      }
    } while (paramStyle != "c" && paramStyle != "f");

    //Ask the user what kind of gamemode to play and prompts user to input their choice
    cout << "\n\nPlease select a Gamemode:\nClassic [C]\tDoughnut [D]\tMirror [M]" << endl;
    cin >> userGame;
    //Do-While loop to continually prompt user until a correct response is inputed
    do {
      //Puts the user input to all lowercase
      for (int i = 0; i < userGame.size(); ++i)
        userGame[i] = tolower(userGame[i]);
      //Checks to see if the input is appropriate
      if (userGame == "c")
        cout << "\nYou have selected the Classic Gamemode" << endl;
      else if (userGame == "d")
        cout << "\nYou have selected the Doughnut Gamemode" << endl;
      else if (userGame == "m")
        cout << "\nYou have selected the Mirror Gamemode" << endl;
      //If it's not, then the program will prompt the user again for a correct input
      else {
        cout << "\n!!!!ERROR!!!!\nPlease enter the following:\nClassic [C]\tDoughnut [D]\tMirror [M]" << endl;
        cin >> userGame;
      }
    } while (userGame != "c" && userGame != "d" && userGame != "m");

    //Based on what the user inputted, the game is generated
    if (userGame == "c" && paramStyle == "c")
      game = new Classic(newRow, newColumn, newCellProb);
    else if (userGame == "c" && paramStyle == "f")
      game = new Classic(inputFileName);
    else if (userGame == "d" && paramStyle == "c")
      game = new Doughnut(newRow, newColumn, newCellProb);
    else if (userGame == "d" && paramStyle == "f")
      game = new Doughnut(inputFileName);
    else if (userGame == "m" && paramStyle == "c")
      game = new Mirror(newRow, newColumn, newCellProb);
    else if (userGame == "m" && paramStyle == "f")
      game = new Mirror(inputFileName);

    //Ask the user how to the output should be displayed
    cout << "\n\nHow would you like the gameboard to be displayed?\nSystematic Pauses [S]\tManual Pauses [M]\tOutput File [F]" << endl;
    cin >> outputStyle;
    //Do-While loop to continually prompt user until a correct response is inputed
    do {
      //Puts the user input to all lowercase
      for (int i = 0; i < outputStyle.size(); ++i)
        outputStyle[i] = tolower(outputStyle[i]);
      if (outputStyle == "s") {
        cout << "\nPlease enter the number of milliseconds you want between each generation:" << endl;
        cin >> delayTime;
        //Makes sure delay time is an int
        do {
          delayOnlyInt = true;
          //Checks to see if the input is a int
          for (int i = 0; i < delayTime.size(); ++i) {
            if (!isdigit(delayTime[i]))
              delayOnlyInt = false;
          }
          //Program continues to prompt the user
          if (delayOnlyInt) {
            newDelayTime = stoi(delayTime);
          }
          //Prompts the user to enter delayTime again
          else {
            cout << "\n!!!!ERROR!!!!\nPlease enter a valid delay time value" << endl;
            cin >> delayTime;
          }
        } while (!delayOnlyInt);
      }
      else if (outputStyle == "m") { }
      else if (outputStyle == "f") {
        cout << "\nPlease enter the file name that you want the output to be put in:" << endl;
        cin >> outputFileName;
      }
      else {
        cout << "\n!!!!ERROR!!!!\nPlease enter the following:\nSystematic Pauses [S]\tManual Pauses [M]\tOutput File [F]" << endl;
        cin >> outputStyle;
      }
    } while (outputStyle != "s" && outputStyle != "m" && outputStyle != "f");

    //Initiates the grid and prints out the first board
    game->initiateGrid();
    cout << "\n\nHere is the initial board. Would you like to continue with it?\n[Y] Yes\t[N] No" << endl;
    game->printGrid();
    cin >> cont;
    //Puts the user input to all lowercase
    for (int i = 0; i < cont.size(); ++i)
      cont[i] = tolower(cont[i]);
  } while (cont != "y");

  //Clears out all the previous content within the file
  if (outputStyle == "f") {
    ofstream outputFile;
    outputFile.open(outputFileName + ".out", std::ofstream::out | std::ofstream::trunc);
    outputFile.close();
  }

  //There is a brief pause between each generation
  if (outputStyle == "s") {
    //Continues to run the program until the grid is empty or stabilizes
    while (!gameOver && fileOpen) {
      game->checkGrid();
      if (!gameOver)
        game->printGrid();
      gameOver = game->isEmpty(outputFileName);
      if (!gameOver)
        gameOver = game->isSame(outputFileName);
      game->flipGrids();
      sleep_for(milliseconds(newDelayTime));
    }
  }
  //User presses enter to continue through the program
  else if (outputStyle == "m") {
    //Continues to run the program until the grid is empty or stabilizes
    while (!gameOver && fileOpen) {
      game->checkGrid();
      if (!gameOver)
        game->printGrid();
      gameOver = game->isEmpty(outputFileName);
      if (!gameOver)
        gameOver = game->isSame(outputFileName);
      game->flipGrids();
      system("read -p 'Press Enter to continue' var");
    }
  }
  //Grid is output to a file
  else if (outputStyle == "f") {
    //Continues to run the program until the grid is empty or stabilizes
    while (!gameOver && fileOpen) {
      game->checkGrid();
      if (!gameOver)
        game->writeGrid(outputFileName);
      gameOver = game->isEmpty(outputFileName);
      if (!gameOver)
        gameOver = game->isSame(outputFileName);
      game->flipGrids();
    }
  }

  return 0;
}
