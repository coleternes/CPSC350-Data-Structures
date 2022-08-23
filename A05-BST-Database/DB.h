#ifndef DB_H
#define DB_H
#include "GenBST.h"
#include "Student.h"
#include "Faculty.h"
#include "GenStack.h"
#include "DBEdits.h"
using namespace std;

class DB {
  public:
    //Member Variables
    GenBST<Student> *masterStudent; //TODO: Serialize
    GenBST<Faculty> *masterFaculty; //TODO: Serialize
    GenStack<DBEdits> *editStack; //Tracks the last 5 edits to the DB
    DB(); //Constructor
    ~DB(); //Destructor
    void serializeTables();
    int checkInput(string testInput);
    void printAllStu(); //Ascending IDs
    void printAllFac(); //Ascending IDs
    void printStu(); //Accesses masterStudent - Stu ID
    void printFac(); //Accesses masterFaculty - Fac ID
    void printStuAdvisor(); //Stu ID
    void printFacAdvisees(); //Fac ID
    void addStu();
    void deleteStu(); //Removed from advisor's list - Stu ID
    void addFac();
    void deleteFac(); //Advisees dispersed amongst other fac - Fac ID
    void changeStuAdvisor(); //Use the given Stu ID to change their advisor to the given Fac ID
    void removeFacAdvisee(); //Use the given Fac ID to remove the advisee using the given Stu ID
    void rollback();
    void exit(); //Writes the tables back out
};

#endif
