#include "Faculty.h"
#include "Student.h"
#include <iostream>
using namespace std;

//Default Constrcutor
Faculty::Faculty() : Person() {
  m_department = "";
  m_advisees = new DLinkedList<Student>();
}

//Overloaded Constructor
Faculty::Faculty(int id, string name, string standing, string department) : Person(id, name, standing) {
  m_department = department;
  m_advisees = new DLinkedList<Student>();
}

//Copy Constrcutor
Faculty::Faculty(Faculty *fac) : Person(fac->m_id, fac->m_name, fac->m_standing) {
  m_department = fac->m_department;
  m_advisees = new DLinkedList<Student>();
  while (!fac->m_advisees->isEmpty()) {
    m_advisees->insertFront(fac->m_advisees->removeBack());
  }
}

//Destructor
Faculty::~Faculty() {
  delete m_advisees;
}

//Helper Functions
bool Faculty::compareFac(Faculty *fac) { //This may cause an error >>> fac->Person()->m_id as possible fix?
  return (m_id == fac->m_id);
}

void Faculty::toString() {
  cout << "\nID: " << m_id << "\nName: " << m_name << "\nStanding: " << m_standing << "\nDepartment: " << m_department << endl;
}
