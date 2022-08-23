#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "DB.h"
#include "GenBST.h"
#include "Student.h"
#include "Faculty.h"
using namespace std;

DB::DB() { //Constrcutor
  masterStudent = new GenBST<Student>();
  masterFaculty = new GenBST<Faculty>();
  editStack = new GenStack<DBEdits>();
}

DB::~DB() { //Destructor
  delete masterStudent;
  delete masterFaculty;
  delete editStack;
}

void DB::serializeTables() { //Stores the tables in two separate files
  ifstream stuTableFile;
  stuTableFile.open("masterStudentTable.txt", ios::app);
  ifstream facTableFile;
  facTableFile.open("masterFacultyTable.txt", ios::app);

  string currentLine = "";
  int lineNum = 0;
  int id = -1;
  string name = "";
  string standing = "";
  string major = "";
  double gpa = -1.0;
  int advisor = -1;
  string department = "";
  int advisee = -1;

  if (stuTableFile.is_open()) {
    while (getline(stuTableFile, currentLine)) { //Reads through the file and pulls in the student data
      if (lineNum % 6 == 0)
        id = stoi(currentLine); //Reads the id
      else if (lineNum % 6 == 1)
        name = currentLine; //Reads the name
      else if (lineNum % 6 == 2)
        standing = currentLine; //Reads the standing
      else if (lineNum % 6 == 3)
        major = currentLine; //Reads the major
      else if (lineNum % 6 == 4)
        gpa = stod(currentLine); //Reads the gpa
      else {
        advisor = stoi(currentLine); //Reads the advisor
        Student *tmpStu = new Student(id, name, standing, major, gpa, advisor);
        masterStudent->insert(tmpStu);
      }
      lineNum++; //Increases the lineNum
    }
    stuTableFile.close(); //Closes the file
  }
  else
    cout << "[ERROR!!!] Cannot open Student Table file" << endl;

  if (facTableFile.is_open()) {
    currentLine = "";
    bool gotID = false;
    bool gotName = false;
    bool gotStanding = false;
    bool gotDepartment = false;
    bool gotAdvisees = false;
    while (getline(facTableFile, currentLine)) { //Reads through the file and pulls in the faculty data
      if (!gotID && !gotName && !gotStanding && !gotDepartment && !gotAdvisees) {
        id = stoi(currentLine); //Reads the id
        gotID = true;
      }
      else if (!gotName && !gotStanding && !gotDepartment && !gotAdvisees) {
        name = currentLine; //Reads the name
        gotName = true;
      }
      else if (!gotStanding && !gotDepartment && !gotAdvisees) {
        standing = currentLine; //Reads the standing
        gotStanding = true;
      }
      else if (!gotDepartment && !gotAdvisees) {
        department = currentLine; //Reads the department
        gotDepartment = true;
        Faculty *tmpFac = new Faculty(id, name, standing, department);
        masterFaculty->insert(tmpFac);
      }
      else if (!gotAdvisees) {
        if (stoi(currentLine) < 1000 && stoi(currentLine) >= 0) {
          advisee = stoi(currentLine); //Reads the advisee
          masterFaculty->search(id)->key->m_advisees->insertBack(masterStudent->search(advisee)->key);
        }
        else
          gotAdvisees = true;
      }
      else {
        gotID = false;
        gotName = false;
        gotStanding = false;
        gotDepartment = false;
        gotAdvisees = false;
      }
    }
  }
  else
    cout << "[ERROR!!!] Cannot open Faculty Table file" << endl;
}

void DB::printAllStu() {
  if (!masterStudent->printTree())
    cout << "\n[ERROR!!!] The student table is empty" << endl;
}

int DB::checkInput(string testInput) {
  int value = -1;
  bool isNum = true;
  do { //Do-While-Loop to check if the testInput is valid
    isNum = true;
    for (int i = 0; i < testInput.size(); ++i) { //For-Loop to check if each char is an int
      if (!isdigit(testInput[i]))
        isNum = false;
    }
    if (isNum)
      value = stoi(testInput);
    else { //Database prompts user until an int is entered
      cout << "\n[ERROR!!!!] Please enter an integer" << endl;
      getline(cin, testInput);
    }
  } while (!isNum);
  return value;
}

void DB::printAllFac() {
  if (!masterFaculty->printTree())
    cout << "\n[ERROR!!!] The faculty table is empty" << endl;
}

void DB::printStu() {
  string userInput = "";
  int stuID = -1;
  cout << "\n[DATABASE] Please enter the Student's ID: " << endl;
  getline(cin, userInput);
  stuID = checkInput(userInput);

  if (masterStudent->search(stuID) != NULL) {
    Student *tmpStu = new Student(masterStudent->search(stuID)->key);
    tmpStu->toString();
  } else {
    cout << "\n[ERROR!!!] Student could not be found" << endl;
  }
}

void DB::printFac() {
  string userInput = "";
  int facID = -1;
  cout << "\n[DATABASE] Please enter the Faculty Member's ID: " << endl;
  getline(cin, userInput);
  facID = checkInput(userInput);

  if (masterFaculty->search(facID) != NULL) {
    Faculty *tmpFac = new Faculty(masterFaculty->search(facID)->key);
    tmpFac->toString();
  } else
    cout << "\n[ERROR!!!] Faculty Member could not be found" << endl;
}

void DB::printStuAdvisor() {
  string userInput = "";
  int stuID = -1;
  cout << "\n[DATABASE] Please enter the Student's ID: " << endl;
  getline(cin, userInput);
  stuID = checkInput(userInput);

  if (masterStudent->search(stuID) != NULL) {
    int facID = masterStudent->search(stuID)->key->m_advisor;
    masterFaculty->search(facID)->key->toString();
  }
  else
    cout << "\n[ERROR!!!] Student could not be found" << endl;
}

void DB::printFacAdvisees() {
  string userInput = "";
  int facID = -1;
  cout << "\n[DATABASE] Please enter the Faculty Member's ID: " << endl;
  getline(cin, userInput);
  facID = checkInput(userInput);

  if (masterFaculty->search(facID) != NULL) {
    int adviseesSize = masterFaculty->search(facID)->key->m_advisees->size;

    for (int i = 0; i < adviseesSize; ++i) {
      Student *tmpStu = new Student(masterFaculty->search(facID)->key->m_advisees->removeFront());
      tmpStu->toString();
      masterFaculty->search(facID)->key->m_advisees->insertBack(tmpStu);
    }
  }
  else
    cout << "\n[ERROR!!!] Faculty member could not be found" << endl;
}

void DB::addStu() {
  string userInput = "";
  bool isDec = true;
  int stuID = -1;
  for (int i = 0; i < 1000; ++i) { //For-Loop to take the next available id
    if (masterStudent->search(i) == NULL) {
      stuID = i;
      break;
    }
  }
  string name = "";
  cout << "[DATABASE] Please enter the Student's Name: " << endl;
  getline(cin, name);
  string standing = "";
  cout << "[DATABASE] Please enter the Student's Standing: " << endl;
  getline(cin, standing);
  string major = "";
  cout << "[DATABASE] Please enter the Student's Major: " << endl;
  getline(cin, major);
  double gpa = -1.0;
  cout << "[DATABASE] Please enter the Student's GPA: " << endl;
  getline(cin, userInput);
  do { //Do-While-Loop to check if the testInput is valid
    isDec = true;
    try {
      gpa = stod(userInput);
    } catch (...) {
      isDec = false;
    }
    if (isDec)
      gpa = stod(userInput);
    else { //Database prompts user until an int is entered
      cout << "\n[ERROR!!!!] Please enter a decimal value" << endl;
      getline(cin, userInput);
    }
  } while (!isDec);
  int advisor = -1;
  cout << "\n[DATABASE] Please enter the Student's Advisor ID: " << endl;
  cout << "[DATABASE] Remember Faculty IDs are 1000-1999" << endl;
  getline(cin, userInput);
  advisor = checkInput(userInput);
  do {
    if (advisor < 1000) {
      cout << "\n[ERROR!!!] Please enter an integer in the range 1000-1999" << endl;
      getline(cin, userInput);
      advisor = checkInput(userInput);
    }
  } while (advisor < 1000);

  bool advisorExists = false;
  if (masterFaculty->search(advisor) != NULL)
    advisorExists = true;

  if (advisorExists) { //Checks to make sure the advisor exists before adding the student
    Student *tmpStu = new Student(stuID, name, standing, major, gpa, advisor); //Creates the student
    masterStudent->insert(tmpStu); //Inserts the student into the tree

    masterFaculty->search(advisor)->key->m_advisees->insertBack(tmpStu);

    cout << "\n[DATABASE] Successfully added the Student" << endl;
    cout << "[DATABASE] " << name << "'s ID is " << stuID << endl;

    DBEdits *tmpDBE = new DBEdits('a', tmpStu); //Records the edit made
    editStack->push(tmpDBE); //Adds the edit to the stack
  } else
    cout << "\n[ERROR!!!] Student could not be added because advisor does not exist" << endl;
}

void DB::deleteStu() {
  string userInput = "";
  int stuID = -1;
  cout << "\n[DATABASE] Please enter the Student's ID: " << endl;
  getline(cin, userInput);
  stuID = checkInput(userInput);

  if (masterStudent->search(stuID) != NULL) {
    Student *tmpStu = new Student(masterStudent->search(stuID)->key); //Creates a temporary version of the student

    DBEdits *tmpDBE = new DBEdits('d', tmpStu); //Records the edit made
    editStack->push(tmpDBE); //Adds the edit to the stack

    bool isDel = masterStudent->deleteNode(tmpStu); //Deletes the student from the tree
    if (isDel)
      cout << "\n[DATABASE] Successfully deleted " << tmpStu->m_name << endl;
  } else {
    cout << "\n[ERROR!!!] Student could not be found" << endl;
  }
}

void DB::addFac() {
  int facID = -1;
  for (int i = 1000; i < 2000; ++i) { //For-Loop to take the next available id
    if (masterFaculty->search(i) == NULL) {
      facID = i;
      break;
    }
  }
  string name = "";
  cout << "[DATABASE] Please enter the Faculty Member's Name: " << endl;
  getline(cin, name);
  string standing = "";
  cout << "[DATABASE] Please enter the Faculty Member's Standing: " << endl;
  getline(cin, standing);
  string department = "";
  cout << "[DATABASE] Please enter the Faculty Member's Department: " << endl;
  getline(cin, department);

  Faculty *tmpFac = new Faculty(facID, name, standing, department); //Creates the faculty

  string cont1 = "";
  string cont2 = "";
  string userInput = "";
  int stuID = -1;
  bool adviseeExists = false;

  cout << "\n[DATABASE] Would you like to add an Advisee? (y/n)" << endl;
  getline(cin, cont1);
  if (cont1 == "y" || cont1 == "Y") {
    do { //Do-While to prompt the user to add advisees until done
      cout << "\n[DATABASE] Please enter the Student's ID: " << endl;
      getline(cin, userInput);
      stuID = checkInput(userInput);

      if (masterStudent->search(stuID) != NULL) {
        Student *tmpStu = new Student(masterStudent->search(stuID)->key);
        tmpFac->m_advisees->insertBack(tmpStu); //Inserts the student into the faculty's advisees list
        cout << "[DATABASE] Would you like to add another? (y/n)" << endl;
        getline(cin, cont2);
      } else {
        cout << "[ERROR!!!] Student does not exist\n[DATABASE] Would you like to try again? (y/n)" << endl;
        getline(cin, cont2);
      }
    } while (cont2 == "y" || cont2 == "Y");
  }

  cout << "\n[DATABASE] Successfully added the Faculty Member" << endl;
  cout << "[DATABASE] " << name << "'s ID is " << facID << endl;

  masterFaculty->insert(tmpFac); //Inserts the faculty into the tree

  DBEdits *tmpDBE = new DBEdits('a', tmpFac); //Records the edit made
  editStack->push(tmpDBE); //Adds the edit to the stack
}

void DB::deleteFac() {
  string userInput = "";
  int facID = -1;
  bool transferedAdvisees = false;
  cout << "\n[DATABASE] Please enter the Faculty Member's ID: " << endl;
  getline(cin, userInput);
  facID = checkInput(userInput);

  if (masterFaculty->search(facID) != NULL) {
    Faculty *tmpFac = new Faculty(masterFaculty->search(facID)->key); //Creates a temporary version of the faculty

    DBEdits *tmpDBE = new DBEdits('d', tmpFac); //Records the edit made
    editStack->push(tmpDBE);

    for (int i = facID + 1; i < 2000; ++i) {
      if (masterFaculty->search(i) != NULL) {
        while (!tmpFac->m_advisees->isEmpty()) {
          Student *tmpStu = new Student(tmpFac->m_advisees->removeFront());
          masterFaculty->search(i)->key->m_advisees->insertBack(tmpStu);
          transferedAdvisees = true;
        }
      }
    }

    if (!transferedAdvisees) {
      for (int i = 0; i < tmpFac->m_advisees->size; ++i) {

        masterStudent->search(tmpFac->m_advisees->removeFront()->m_id)->key->m_advisor = -1;
      }
    }

    bool isDel = masterFaculty->deleteNode(tmpFac); //Deletes the faculty from the tree
    if (isDel)
      cout << "\n[DATABASE] Successfully deleted " << tmpFac->m_name << endl;
  }
  else
    cout << "\n[ERROR!!!] Faculty Member could not be found" << endl;
}

void DB::changeStuAdvisor() {
  string userInput = "";
  int stuID = -1;
  cout << "\n[DATABASE] Please enter the Student's ID: " << endl;
  getline(cin, userInput);
  stuID = checkInput(userInput);

  if (masterStudent->search(stuID) != NULL) {
    int oldAdvisor = masterStudent->search(stuID)->key->m_advisor;

    int facID = -1;
    cout << "[DATABASE] Please enter the ID of the Faculty Member you wish to switch to: " << endl;
    getline(cin, userInput);
    facID = checkInput(userInput);

    if (masterFaculty->search(facID) != NULL) {
      masterStudent->search(stuID)->key->m_advisor = facID;
      masterFaculty->search(oldAdvisor)->key->m_advisees->remove(masterStudent->search(stuID)->key);
      cout << "[DATABASE] Successfully changed " << masterStudent->search(stuID)->key->m_name << "'s Advisor to " << masterFaculty->search(facID)->key->m_name << endl;
    }
    else
      cout << "\n[ERROR!!!] Faculty Member could not be found" << endl;
  }
  else
    cout << "\n[ERROR!!!] Student could not be found" << endl;
}

void DB::removeFacAdvisee() {
  string userInput = "";
  int facID = -1;
  cout << "\n[DATABASE] Please enter the new Faculty Member's ID: " << endl;
  getline(cin, userInput);
  facID = checkInput(userInput);

  if (masterFaculty->search(facID) != NULL) {
    int stuID = -1;
    cout << "[DATABASE] Please enter the ID of the Student you wish to remove: " << endl;
    getline(cin, userInput);
    stuID = checkInput(userInput);

    if (masterStudent->search(stuID) != NULL) {
      masterFaculty->search(facID)->key->m_advisees->remove(masterStudent->search(stuID)->key);
      masterStudent->search(stuID)->key->m_advisor = -1;
      cout << "[DATABASE] Successfully removed " << masterStudent->search(stuID)->key->m_name << " from " << masterFaculty->search(facID)->key->m_name << "'s advisee list" << endl;
    }
    else
      cout << "\n[ERROR!!!] Student could not be found" << endl;
  }
  else
    cout << "\n[ERROR!!!] Faculty Member could not be found" << endl;
}

void DB::rollback() {
  DBEdits *tmpDBE = new DBEdits(editStack->pop()); //Pops the last thing off of the stack
  if (tmpDBE->m_event_type == 'a') { //Checks to see if the edit was an "add"
    if (tmpDBE->m_tmp_stu->getID() != -1) {//Checks to see if a student was added
      bool isDel = masterStudent->deleteNode(tmpDBE->m_tmp_stu);
      cout << "\n[DATABASE] Successfully rollbacked\n[DATABASE] Deleted Student " << tmpDBE->m_tmp_stu->m_name << endl;
    }
    else if (tmpDBE->m_tmp_fac->getID() != -1) { //Checks to see if a faculty was added
      bool isDel = masterFaculty->deleteNode(tmpDBE->m_tmp_fac);
      cout << "\n[DATABASE] Successfully rollbacked\n[DATABASE] Deleted Faculty Member " << tmpDBE->m_tmp_fac->m_name << endl;
    }
  }
  else if (tmpDBE->m_event_type == 'd') { //Checks to see if the edit was a "delete"
    if (tmpDBE->m_tmp_stu->getID() != -1) { //Checks to see if a student was deleted
      Student *tmpStu = new Student(tmpDBE->m_tmp_stu);
      masterStudent->insert(tmpStu);
      cout << "\n[DATABASE] Successfully rollbacked\n[DATABASE] Added Student " << tmpDBE->m_tmp_stu->m_name << endl;
    } else if (tmpDBE->m_tmp_fac->getID() != -1) { //Checks to see if a faculty was deleted
      Faculty *tmpFac = new Faculty(tmpDBE->m_tmp_fac);
      masterFaculty->insert(tmpFac);
      cout << "\n[DATABASE] Successfully rollbacked\n[DATABASE] Added Faculty Member " << tmpDBE->m_tmp_fac->m_name << endl;
    }
  }
  else //The popped edit was neither an add nor a delete
    cout << "\n[ERROR!!!] There are no remaining rollbacks available" << endl;
}

void DB::exit() {
  fstream stuTableFile;
  stuTableFile.open("masterStudentTable.txt", ios::out);
  fstream facTableFile;
  facTableFile.open("masterFacultyTable.txt", ios::out);

  if (stuTableFile.is_open()) {
    for (int i = 0; i < 1000; ++i) {
      if (masterStudent->search(i) != NULL) {
        stuTableFile << masterStudent->search(i)->key->m_id << endl;
        stuTableFile << masterStudent->search(i)->key->m_name << endl;
        stuTableFile << masterStudent->search(i)->key->m_standing << endl;
        stuTableFile << masterStudent->search(i)->key->m_major << endl;
        stuTableFile << masterStudent->search(i)->key->m_gpa << endl;
        stuTableFile << masterStudent->search(i)->key->m_advisor << endl;
      }
    }
    stuTableFile.close(); //Closes the file
  }
  else
    cout << "[ERROR!!!] Cannot open Student Table file" << endl;

  if (facTableFile.is_open()) {
    for (int i = 1000; i < 2000; ++i) {
      if (masterFaculty->search(i) != NULL) {
        facTableFile << masterFaculty->search(i)->key->m_id << endl;
        facTableFile << masterFaculty->search(i)->key->m_name << endl;
        facTableFile << masterFaculty->search(i)->key->m_standing << endl;
        facTableFile << masterFaculty->search(i)->key->m_department << endl;
        while (!masterFaculty->search(i)->key->m_advisees->isEmpty()) {
          facTableFile << masterFaculty->search(i)->key->m_advisees->removeFront()->m_id << endl;
        }
      }
    }
    facTableFile.close(); //Closes the file
  }
  else
    cout << "[ERROR!!!] Cannot open Faculty Table file" << endl;
}
