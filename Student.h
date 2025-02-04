#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

using namespace std;

class Student {
 public:
  Student();
  ~Student();
  void setID(int newID);
  int getID();
  void setFName(char* newFName);
  void setLName(char* newLName);
  void setGpa(float newGpa);
  float getGpa();
  char* getFName();
  char* getLName();
 protected:
  int id;
  char* firstName;
  char* lastName;
  float gpa;
};

#endif
