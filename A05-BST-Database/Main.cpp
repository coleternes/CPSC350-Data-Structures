#include <iostream>
#include <string>
#include "DB.h"
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
using namespace std;

int main(int argc, char **argv) {
  /* WORKING DB FUNCTIONS:
   * 1 - Y  8 - Y
   * 2 - Y  9 - Y
   * 3 - Y  10 - Y
   * 4 - Y  11 - Y
   * 5 - Y  12 - N
   * 6 - Y  13 - Y
   * 7 - Y  14 - N
   */

  DB *database = new DB();
  database->serializeTables();

  string userInput = ""; //Used to see what the user wants the program to perform
  string spacing = "";
  int funcSelect = -1;
  bool isNum = true;

  do {
    cout << "\n==============================DATABASE MAIN MENU==============================" << endl;
    cout << "1) Print all Students\t\t\t8) Delete a Student" << endl;
    cout << "2) Print all Faculty Members\t\t9) Add a Faculty Member" << endl;
    cout << "3) Print a Student\t\t\t10) Delete a Faculty Member" << endl;
    cout << "4) Print a Faculty Member\t\t11) Change a Student's Advisor" << endl;
    cout << "5) Print a Student's Advisor\t\t12) Remove a Faculty Member's Advisee" << endl;
    cout << "6) Print a Faculty Member's Advisees\t13) Rollback an Action" << endl;
    cout << "7) Add a Student\t\t\t14) Exit" << endl;
    getline(cin, userInput);
    do {
      if (userInput.size() == 0) {
        cout << "[ERROR!!!] Please enter an integer" << endl;
        getline(cin, userInput);
      }
    } while (userInput.size() == 0);
    funcSelect = database->checkInput(userInput);

    if (funcSelect == 1)
      database->printAllStu();
    else if (funcSelect == 2)
      database->printAllFac();
    else if (funcSelect == 3)
      database->printStu();
    else if (funcSelect == 4)
      database->printFac();
    else if (funcSelect == 5)
      database->printStuAdvisor();
    else if (funcSelect == 6)
      database->printFacAdvisees();
    else if (funcSelect == 7)
      database->addStu();
    else if (funcSelect == 8)
      database->deleteStu();
    else if (funcSelect == 9)
      database->addFac();
    else if (funcSelect == 10)
      database->deleteFac();
    else if (funcSelect == 11)
      database->changeStuAdvisor();
    else if (funcSelect == 12)
      database->removeFacAdvisee();
    else if (funcSelect == 13)
      database->rollback();
    else
      database->exit();
  } while (funcSelect < 14 && funcSelect >= 1);

  return 0;
}
