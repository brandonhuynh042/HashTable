#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "Node.h"
#include "Student.h"
#include <bits/stdc++.h>


bool addStudent(Student* newStudent, int &size, Node** &students);
void printStudents(Node** students, int size);
void deleteStudent(int targetID, int size, Node** &students);
void REHASH(Node** &students, Node** oldStudents, int size, int oldSize);


/* This program stores a list of students using a hash table with chaining;
   there are options to add students manually and randomly, along with the
   option to delete a student of a certain ID.

   Brandon Huynh, last updated 2/4/2025 */



// credit w3 schools for all random float functions. they take the random, generate an integer within one below the range, than add a 0-1 float.
// link: https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
float randomFloat()
{
    return (float)(rand()) / (float)(RAND_MAX);
}

int randomInt(int a, int b)
{
    if (a > b)
        return randomInt(b, a);
    if (a == b)
        return a;
    return a + (rand() % (b - a));
}

float randomFloat(int a, int b)
{
    if (a > b)
        return randomFloat(b, a);
    if (a == b)
        return a;

    return (float)randomInt(a, b) + randomFloat();
}


int main() {
  // initialize with size of 100
  int size = 100;
  Node** Students = new Node*[size];
  for (int i = 0; i < size; i++) {
    Students[i] = NULL;
  }
  bool quit = false;
  int incID = 1;
    while (quit == false) {
    // Take in user input, show commands
      char input[9];
    cout << "You can: \'ADD\' \'PRINT\' \'DELETE\' \'QUIT\'" << endl;
    cin >> input;
    // See what they entered...
    if (strcmp(input, "ADD") == 0) {
      // Do they want random or manual adding?
      cout << "RANDOM or MANUAL?" << endl;
      char addInput[8];
      cin >> addInput;
      bool rehash = false;
      if (strcmp(addInput, "MANUAL") == 0) {
	// take in student info
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
	//add info to student, add to list
	newStudent->setFName(firstName);
	newStudent->setLName(lastName);
	newStudent->setID(id);
	newStudent->setGpa(gpa);
	rehash = addStudent(newStudent, size, Students);
	// once everything is added, do we need to rehash?
	      if (rehash == true) {
		int oldSize = size; // double the size (-3 too)
		size = (size*2) - 3;
		// create a new blank list of that size
		Node** reStudents = new Node*[size];
		for (int i = 0; i < size; i++) {
		  reStudents[i] = NULL;
		}
		REHASH(reStudents, Students, size, oldSize); // rehash
		
		Students = reStudents; // change the student list to this with the new size
      }
      }
      if (strcmp(addInput, "RANDOM") == 0) {
	// how many students do they want to add?
	cout << "How many students would you like to add?" << endl;
	int studentNumber = 0;
	cin >> studentNumber;
	char firstName[20];
	char lastName[20];
	srand(time(0));
	// create the number of students
	for (int i = 0; i < studentNumber; i++) {
	  rehash = false;
	  // read in name files, choose random line to read in
	  ifstream FNames("FirstNames.txt");
          ifstream LNames("LastNames.txt");
	  int firstR = rand() % 99;
	  int lastR =  rand() % 99;
	  //read in the random line 
	  for (int j = 0; j < firstR; j++) {
	    FNames.getline(firstName, 100, '\n');
	  }
	  for (int j = 0; j < lastR; j++) {
	    LNames.getline(lastName, 100, '\n');
	 }
	  // add these random names to a new student
	  Student* newStudent = new Student();
	  newStudent->setFName(firstName);
	  newStudent->setLName(lastName);
	  // add the id, increment for the next one
	  newStudent->setID(incID);
	  incID++;
	  // add a random gpa
	  float newGPA = randomFloat(0,5);
	  newStudent->setGpa(newGPA);
	  rehash = false;
	  rehash = addStudent(newStudent, size, Students);
	  // same rehash as in manual
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

// this function returns a boolean of whether or not we need to rehash
bool addStudent(Student* newStudent, int &size, Node** &students) {
  // create a new node for the student
  Node* newNode = new Node(newStudent);
  // hashing based off their id
  int index = newStudent->getID() % size;
 // if the index is empty, it's the head of the list!
  if (students[index] == NULL) {
    students[index] = newNode;
    return false;
  }
  // if there's one.,.
  else if (students[index]->getNext() == NULL) {
    students[index]->setNext(newNode);
    return false;
  }
  // if there's two...
  else if (students[index]->getNext()->getNext() == NULL) {
    students[index]->getNext()->setNext(newNode);
    return false;
  }
  // if there's three, add it, but we will rehash now.
  else  {
    students[index]->getNext()->getNext()->setNext(newNode);
    cout << "finished." << endl;
    return true;
  }
}
//deletes student off id
void deleteStudent(int targetID, int size, Node** &students) {
  cout << size;
  int i = targetID % size; // find the index
  cout << i << endl;
  // if the entered value is invalid
  if (students[i] == NULL) {
    cout << "student not found..." << endl;
  }
  else {
    // first one is the target
    if (students[i]->getValue()->getID() == targetID) {
      // is there more in the list? if so, make the next one the new head.
      if (students[i]->getNext() != NULL) {
	Node* temp = students[i];
	students[i] = students[i]->getNext();
	delete temp;
	return;
      }
      // otherwise, it's empty now
      else {
	Node* temp = students[i];
	students[i] = NULL;
	delete temp;
	return;
      }
    }
    // scan through the list
    Node* current = students[i]->getNext();
    while (current != NULL) {
      // if the target is found
      if (current->getValue()->getID() == targetID) {
	// is it the last one? if not, the first now connects to the third (as size is lim to 3, no other cases)
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
    // right index, not right id
    cout << "Student not found!" << endl;
  }
}
void printStudents(Node** students, int size) {
  // traverse through the hash table, and when a spot is occupied, traverse through the list there.
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
  // traverse through the old hash table
  for (int i = 0; i < oldSize; i++) {
     if (oldStudents[i] != NULL) {
       Node* current = oldStudents[i];
       while (current != NULL) {
	 int index = current->getValue()->getID() % size; // rehashing with the new size
	 // add it to the new hash table; similar to add function, but assumes double rehashing will never happen
	 if (students[index] == NULL) {
	   students[index] = new Node(current->getValue());
	  }
	  else if (students[index]->getNext() == NULL) {
	    students[index]->setNext(new Node(current->getValue()));
	  }
	  else if (students[index]->getNext()->getNext() == NULL) {
	    students[index]->getNext()->setNext(new Node(current->getValue()));
	  }
	  current = current->getNext();
       }
     }
  }
}
