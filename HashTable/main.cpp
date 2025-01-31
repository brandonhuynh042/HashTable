#include <iostream>
#include <cstring>
#include <iomanip>
#include "Node.h"
#include "Student.h"

bool addStudent(Student* newStudent, int &size, Node** &students);
void printStudents(Node** students, int size);
void deleteStudent(int targetID, int size, Node** &students);
void REHASH(Node** &students, Node** oldStudents, int size, int oldSize);
int main() {
  int size = 100;
  Node** Students = new Node*[size];
  for (int i = 0; i < size; i++) {
    Students[i] = NULL;
  }
  bool quit = false;
    while (quit == false) {
    // Take in user input, show commands
      char input[9];
    cout << "You can: \'ADD\'             \'PRINT\' \'DELETE\' \'QUIT\'" << endl;
    cin >> input;
    // See what they entered...
    if (strcmp(input, "ADD") == 0) {
         // take inputs for student info
      cout << "RANDOM or MANUAL?" << endl;
      char addInput[8];
      cin >> addInput;
      bool rehash = false;
      if (strcmp(addInput, "MANUAL") == 0) {
	Student* newStudent = new Student();
	cout << "What is the student's first name?" << endl;
	char firstName[20];
	cin >> firstName;
	cout << "What is the student's last name?" << endl;
	char lastName[20];
	cin >> lastName;
	cout << "What is the student's ID?" << endl;
	int id;
	cin >> id;
	cout << "What is the student's GPA?" << endl;
	float gpa;
	cin >> gpa;
	newStudent->setFName(firstName);
	newStudent->setLName(lastName);
	newStudent->setID(id);
	newStudent->setGpa(gpa);
	rehash = addStudent(newStudent, size, Students);
      }
      if (strcmp(addInput, "RANDOM") == 0) {
	cout << "How many students would you like to add?" << endl;
	int studentNumber = 0;
	cin >> studentNumber;
      }
      if (rehash == true) {
	int oldSize = size;
	size = (size*2) - 3;
	Node** reStudents = new Node*[size];
	for (int i = 0; i < size; i++) {
	  reStudents[i] = NULL;
	}
	REHASH(reStudents, Students, size, oldSize);
	Students = reStudents;
      }
    }
    else if (strcmp(input, "PRINT") == 0) {
      printStudents(Students, size);
    }
    else if (strcmp(input, "DELETE") == 0) {
        cout << "What is the ID of the student you'd like to delete?" << endl;
      int deleteInput;
      cin >> deleteInput;
      deleteStudent(deleteInput, size, Students);        // go to process of deleting student
    }
    else if (strcmp(input, "QUIT") == 0) {
      cout << "Quitting." << endl;
      quit = true;
    }
    else {
      cout << "Please enter a valid input!" << endl;
    }
  }
  return 0;
}

bool addStudent(Student* newStudent, int &size, Node** &students) {
  cout << "starting" << endl;
  Node* newNode = new Node(newStudent);
  int index = newStudent->getID() % size;
  cout << "Adding" << endl;
  if (students[index] == NULL) {
    cout << "adding one" << endl;
    students[index] = newNode;
    return false;
  }
  else if (students[index]->getNext() == NULL) {
    students[index]->setNext(newNode);
    return false;
  }
  else if (students[index]->getNext()->getNext() == NULL) {
    students[index]->getNext()->setNext(newNode);
    return false;
  }
  else  {
    students[index]->getNext()->getNext()->setNext(newNode);
    cout << "finished." << endl;
    return true;
  }
}
void deleteStudent(int targetID, int size, Node** &students) {
  int i = targetID % size;
  if (students[i] == NULL) {
    cout << "student not found..." << endl;
  }
  else {
    if (students[i]->getValue()->getID() == targetID) {
      if (students[i]->getNext() != NULL) {
	Node* temp = students[i];
	students[i] = students[i]->getNext();
	delete temp;
	return;
      }
      else {
	Node* temp = students[i];
	students[i] = NULL;
	delete temp;
	return;
      }
    }
    Node* current = students[i]->getNext();
    while (current != NULL) {
      if (current->getValue()->getID() == targetID) {
	if (current->getNext() != NULL) {
	  students[i]->setNext(current->getNext());
	  delete current;
	  return;
	}
	else {
	  students[i]->setNext(NULL);
	  delete current;
	  return;
	}
      }
      current = current->getNext();
    }
  }
}
void printStudents(Node** students, int size) {
  for (int i = 0; i < size; i++) {
    if (students[i] != NULL) {
      Node* current = students[i];
      while (current != NULL) {
	cout << current->getValue()->getID() << ", " << current->getValue()->getFName() << " " << current->getValue()->getLName() << " " << fixed << setprecision(2) << current->getValue()->getGpa() << endl;
	current = current->getNext();
      }
    }
  }
}

void REHASH(Node** &students, Node** oldStudents, int size, int oldSize) {
  for (int i = 0; i < oldSize; i++) {
     if (oldStudents[i] != NULL) {
       Node* current = oldStudents[i];
       while (current != NULL) {
	 int index = oldStudents[i]->getValue()->getID() % size;
	  if (students[index] == NULL) {
	    students[index] = current;
	  }
	  else if (students[index]->getNext() == NULL) {
	    students[index]->setNext(current);
	  }
	  else if (students[index]->getNext()->getNext() == NULL) {
	    students[index]->getNext()->setNext(current);
	  }
	  current = current->getNext();
       }
     }
  }
}
