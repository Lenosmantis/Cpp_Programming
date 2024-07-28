#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// Function to generate a random word
string generateWord() {
    string words[] = {"apple", "banana", "cherry", "orange", "grape", "melon", "kiwi", "pear", "peach", "plum"};
    int index = rand() % 10;
    return words[index];
}

// Function to check if the guessed word matches the target word
bool checkWord(const string& target, const string& guess) {
    return target == guess;
}

// Function to validate if the input contains only letters
bool isValidInput(const string& input) {
    for (char c : input) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "Welcome to Wordle!" << endl;
    cout << "Guess The Word With Fruits!" << endl;

    char playAgain;

    do {
        string targetWord = generateWord();
        string guessWord;
        int attempts = 0;

        do {
            cout << "Attempt " << attempts + 1 << ": ";
            cin >> guessWord;

            // Validate input
            if (!isValidInput(guessWord)) {
                cout << "Invalid input. Please enter letters only." << endl;
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                continue;
            }

            if (checkWord(targetWord, guessWord)) {
                cout << "Congratulations! You guessed the word correctly." << endl;
                break;
            } else {
                cout << "Incorrect guess. Try again." << endl;
                attempts++;
            }

            if (attempts >= 10) {
                cout << "Sorry, you couldn't guess the word. The correct word was: " << targetWord << endl;
                break;
            }
        } while (true);

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        playAgain = tolower(playAgain);
    } while (playAgain == 'y');

    cout << "Thanks for playing Wordle!" << endl;

    return 0;
}
