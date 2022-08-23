#ifndef DBEDITS_H
#define DBEDITS_H
#include "Student.h"
#include "Faculty.h"
using namespace std;

class DBEdits {
  public:
    //Member Variables
    char m_event_type; //Added (a), Deleted (d)
    Student *m_tmp_stu; //Student affected
    Faculty *m_tmp_fac; //Faculty affected
    DBEdits(); //Default Constructor
    DBEdits(char eventType, Student *tmpStu); //Overloaded Constructor 1
    DBEdits(char eventType, Faculty *tmpFac); //Overloaded Constrcutor 2
    DBEdits(char eventType, Student *tmpStu, Faculty *tmpFac); //Overloaded Constrcutor 3
    DBEdits(DBEdits *dbe); //Copy Constructor
    ~DBEdits(); //Destructor
};

#endif
