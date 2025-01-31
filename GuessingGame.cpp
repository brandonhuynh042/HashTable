#include <iostream>
#include <ctime>

using namespace std;

/*
 * This program plays a guessing game with the user, with the user guessing
 * numbers between 0 and 100.
 * Brandon Huynh, last edited 8/28/2024
*/

/*
 * The three rules of C++:
 * 1. No global variables.
 * 2. No strings.
 * 3. Include <iostream>, not stdio; use "new" and "delete" instead of
 * "malloc" and "free"
*/

int main() {
  bool playing = true;
 while (playing == true) {
  // allows a different number to be chosen each time
  srand(time(NULL));
  // selecting random number, initializing place to hold atttempts and input
  int randomNumber = rand() % 101;
  int attempts = 0;
  int guess = -1;
  // while the user is trying to figure out the number...
  do {
    attempts++;
    cout << "Guess a number between 0 and 100." << endl;
    cin >> guess;
    // letting the user know why their guess is wrong
    if (guess > randomNumber) {
      cout << "Your guess was too high!" << endl;
    }
    else if (guess < randomNumber) {
      cout << "Your guess was too low!" << endl;
    }
 } while (guess != randomNumber);
  // user guessed correctly! let them know how many attempts it took
  cout << "Congrats! You guessed the number in " << attempts << " attempts!" << endl;
  cout << "Would you like to play again? Type \'y\' for yes, and \'n\' for no." << endl;
  // seeing if the user wants to play again - must be valid input
  bool validInput = false;
  while (validInput == false) {
    char playInput;
    cin >> playInput;
    if (playInput == 'y') {
      cout << "Restarting!" << endl;
      validInput = true;
    }
    else if (playInput == 'n') {
      cout << "Thanks for playing!" << endl;
      validInput = true;
      playing = false;
    }
    // incase of invalid input
    else {
      cout << "Please enter a valid input!" << endl;
    }
  }
 }
 return 0;
}
