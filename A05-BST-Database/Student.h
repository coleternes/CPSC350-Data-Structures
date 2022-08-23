#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"
using namespace std;

class Student : public Person {
  public:
    //Member Variables
    string m_major;
    double m_gpa;
    int m_advisor; //Faculty ID
    Student(); //Default Constructor
    Student(int id, string name, string standing, string major, double gpa, int advisor); //Overloaded Constrcutor
    Student(Student *stu); //Copy Constructor
    //Helper Functions
    bool compareStu(Student *stu);
    void toString();
};

#endif
