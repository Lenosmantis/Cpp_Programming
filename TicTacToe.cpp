#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

vector<vector<char>> board(3, vector<char>(3, ' '));

void resetBoard() {
    board = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
}

void printBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}

bool isValidMove(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3)
        return false;
    if (board[row][col] != ' ')
        return false;
    return true;
}

bool checkWinner(char player) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;  // Row
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;  // Column
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;  // Diagonal
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;  // Diagonal
    return false;
}

int checkFreeSpaces() {
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ')
                count++;
        }
    }
    return count;
}

void printWinner(const string& winner) {
    if (winner == "X")
        cout << "Congratulations! You win!" << endl;
    else if (winner == "O")
        cout << "Sorry, the computer wins." << endl;
    else
        cout << "It's a draw!" << endl;
}

pair<int, int> getComputerMove() {
    // Check if the computer can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (isValidMove(i, j)) {
                board[i][j] = 'O';
                if (checkWinner('O')) {
                    board[i][j] = ' ';
                    return make_pair(i, j);
                }
                board[i][j] = ' ';
            }
        }
    }
    
    // Check if the player can win in the next move and block
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (isValidMove(i, j)) {
                board[i][j] = 'X';
                if (checkWinner('X')) {
                    board[i][j] = 'O';
                    return make_pair(i, j);
                }
                board[i][j] = ' ';
            }
        }
    }

    // If no winning moves, make a random move
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!isValidMove(row, col));
    return make_pair(row, col);
}

void computerMove() {
    cout << "Computer is thinking..." << endl;
    sleep(1); // Add a delay to simulate thinking time
    pair<int, int> move = getComputerMove();
    board[move.first][move.second] = 'O';
    cout << "Computer has made a move: " << move.first << ", " << move.second << endl;
}

int main() {
    string playerName;
    string response = "";

    cout << "Welcome to Tic Tac Toe game!" << endl;
    cout << "Enter your name: ";
    cin >> playerName;

    do {
        resetBoard();

        while (checkFreeSpaces() != 0) {
            printBoard();
            cout << endl;
            cout << playerName << "'s move." << endl;
            int row, col;
            cout << "Enter your move (row and column, 0 to 2): ";
            cin >> row >> col;

            // Validate user input
            while (cin.fail() || row < 0 || row > 2 || col < 0 || col > 2 || !isValidMove(row, col)) {
                cout << "Invalid move. Please enter valid row and column (0 to 2): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> row >> col;
            }
            board[row][col] = 'X';

            if (checkWinner('X')) {
                printBoard();
                printWinner("X");
                break;
            }
            if (checkFreeSpaces() == 0) {
                printBoard();
                cout << "It's a draw!" << endl;
                break;
            }

            computerMove(); // Make the computer move
            if (checkWinner('O')) {
                printBoard();
                printWinner("O");
                break;
            }
            // Delay before next move
            sleep(1);
        }

        // Validate user response for playing again
        do {
            cout << "Do you want to play again? (Y/N): ";
            cin >> response;
        } while (response != "Y" && response != "y" && response != "N" && response != "n");

    } while (response == "Y" || response == "y");

    cout << "Thank you for playing Tic Tac Toe, " << playerName << "!" << endl;

    return 0;
}
