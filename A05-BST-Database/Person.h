#ifndef PERSON_H
#define PERSON_H
#include <iostream>
using namespace std;

class Person {
  public:
    //Member Variables
    int m_id; //Auto-generate IDs: 0-999 = Stu, 1000-1999 = Fac
    string m_name;
    string m_standing;
    Person(); //Default Constructor
    Person(int id, string name, string standing); //Overloaded Constructor
    Person(Person *per); //Copy Constructor
    //Helper Functions
    int getID();
};

#endif
