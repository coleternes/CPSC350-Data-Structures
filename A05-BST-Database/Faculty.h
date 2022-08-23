#ifndef FACULTY_H
#define FACULTY_H
#include "Person.h"
#include "Student.h"
#include "DLinkedList.h"
using namespace std;

class Faculty : public Person {
  public:
    //Member Variables
    string m_department;
    DLinkedList<Student> *m_advisees; //DLinkedList of Students
    Faculty(); //Default Constrcutor
    Faculty(int id, string name, string standing, string department); //Overloaded Constrcutor
    Faculty(Faculty *fac);
    ~Faculty(); //Destructor
    //Helper Functions
    bool compareFac(Faculty *fac);
    void toString();
};

#endif
