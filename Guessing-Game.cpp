#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

string creator() {
    return "LeonDev";
}

int main() {
    char playAgain;
    do {
        cout << "Welcome to the Number Guessing Game!\n";
        cout << "Try to guess the secret number between 1 and 100.\n";

        srand(static_cast<unsigned int>(time(0)));
        int secretNumber = rand() % 100 + 1;
        int guess, attempts = 0;

        do {
            cout << "Guess the number (1-100): ";
            while (!(cin >> guess) || guess < 1 || guess > 100) {
                cout << "Please enter a valid number between 1 and 100: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            attempts++;

            if (guess > secretNumber) {
                cout << "Too high!\n";
            } else if (guess < secretNumber) {
                cout << "Too low!\n";
            } else {
                cout << "Congratulations! You guessed the number in " << attempts << " attempts!\n";
            }

            if (attempts >= 10) {
                cout << "You have reached the maximum number of attempts.\n";
                break;
            }

        } while (guess != secretNumber);

        cout << "Do you want to play again? (y/n): ";
        while (!(cin >> playAgain) || (tolower(playAgain) != 'y' && tolower(playAgain) != 'n')) {
            cout << "Please enter 'y' or 'n': ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (tolower(playAgain) == 'y');

    cout << "Thanks for playing the Number Guessing Game!\n";
    cout << "Code created by " << creator() << "\n";

    return 0;
}
