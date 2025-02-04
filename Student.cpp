#include <iostream>
#include "Student.h"
#include <cstring>
using namespace std;

Student::Student() {
  id = 0;
  firstName = new char[20];
  lastName = new char[20];
  gpa = 0.00;
}

Student::~Student() {
  delete firstName;
  delete lastName;
}

void Student::setID(int newID) {
  id = newID;
}

int Student::getID() {
  return id;
}

void Student::setFName(char* newFName) {
  strcpy(firstName, newFName);
}

char* Student::getFName() {
  return firstName;
}

void Student::setLName(char* newLName) {
  strcpy(lastName, newLName);
}

char* Student::getLName() {
  return lastName;
}

void Student::setGpa(float newGpa) {
  gpa = newGpa;
}

float Student::getGpa() {
  return gpa;
}
