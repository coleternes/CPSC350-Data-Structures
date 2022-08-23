#include "DBEdits.h"
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
using namespace std;

//Default Constructor
DBEdits::DBEdits() {
  m_event_type = 'z';
  m_tmp_stu = new Student();
  m_tmp_fac = new Faculty();
}

//Overloaded Constructor 1
DBEdits::DBEdits(char eventType, Student *tmpStu) {
  m_event_type = eventType;
  m_tmp_stu = new Student(tmpStu);
  m_tmp_fac = new Faculty();
}

//Overloaded Constructor 2
DBEdits::DBEdits(char eventType, Faculty *tmpFac) {
  m_event_type = eventType;
  m_tmp_stu = new Student();
  m_tmp_fac = new Faculty(tmpFac);
}

//Overloaded Constructor 3
DBEdits::DBEdits(char eventType, Student *tmpStu, Faculty *tmpFac) {
  m_event_type = eventType;
  m_tmp_stu = new Student(tmpStu);
  m_tmp_fac = new Faculty(tmpFac);
}
//Copy Constrcutor
DBEdits::DBEdits(DBEdits *dbe) {
  m_event_type = dbe->m_event_type;
  m_tmp_stu = dbe->m_tmp_stu;
  m_tmp_fac = dbe->m_tmp_fac;
}

//Destructor
DBEdits::~DBEdits() {
  delete m_tmp_stu;
  delete m_tmp_fac;
}
