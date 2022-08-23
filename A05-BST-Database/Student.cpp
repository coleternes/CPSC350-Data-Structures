#include "Student.h"
#include <iostream>
using namespace std;

//Default Constrcutor
Student::Student() : Person() {
  m_major = "";
  m_gpa = -1.0;
  m_advisor = -1;
}

//Overloaded Constrcutor
Student::Student(int id, string name, string standing, string major, double gpa, int advisor) : Person(id, name, standing) {
  m_major = major;
  m_gpa = gpa;
  m_advisor = advisor;
}

//Copy Constrctor
Student::Student(Student *stu) : Person(stu->m_id, stu->m_name, stu->m_standing) {
  m_major = stu->m_major;
  m_gpa = stu->m_gpa;
  m_advisor = stu->m_advisor;
}

//Helper Functions
bool Student::compareStu(Student *stu) { //This may cause an error >>> stu->Person()->m_id as possible fix?
  return (m_id == stu->m_id);
}
void Student::toString() {
  cout << "\nID: " << m_id << "\nName: " << m_name << "\nStanding: " << m_standing << "\nMajor: " << m_major << "\nGPA: " << m_gpa << "\nAdvisor ID: " << m_advisor <<  endl;
}
