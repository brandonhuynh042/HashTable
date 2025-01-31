#include <iostream>
#include <cstring>

struct Student {
  char firstName[20];
  char lastName[20];
  int studentID;
  float studentGPA;
};
int() main {
  vector<Student*> studentList;
  bool quit = false;
  char input[6];
  while (quit == false) {
    cout << "You can: \'ADD\' \'PRINT\' \'DELETE\' \'QUIT\'" << endl;
    cin >> input;
    if (strcmp(input, "ADD") == 0) {
      cout << "it works." << endl;
    }
  }
  return 0;
}
