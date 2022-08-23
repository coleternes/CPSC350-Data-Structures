#include "Person.h"
using namespace std;

//Default Constructor
Person::Person() {
  m_id = -1;
  m_name = "";
  m_standing = "";
}

//Overloaded Constructor
Person::Person(int id, string name, string standing) {
  m_id = id;
  m_name = name;
  m_standing = standing;
}

//Copy Constructor
Person::Person(Person *per) {
  m_id = per->m_id;
  m_name = per->m_name;
  m_standing = per->m_standing;
}

int Person::getID() {
  return m_id;
}
