#include <iostream>
#include <limits>

using namespace std;

int main() {
    cout << "Welcome to the Calculator program!" << endl;

    char choice;
    do {
        float num1, num2;
        char operation;

        cout << "Enter the first number: ";
        while (!(cin >> num1)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter the operation (+, -, *, /): ";
        while (!(cin >> operation) || (operation != '+' && operation != '-' && operation != '*' && operation != '/')) {
            cout << "Invalid input. Please enter a valid operation (+, -, *, /): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter the second number: ";
        while (!(cin >> num2)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (operation) {
            case '+':
                cout << "Result: " << num1 + num2 << endl;
                break;
            case '-':
                cout << "Result: " << num1 - num2 << endl;
                break;
            case '*':
                cout << "Result: " << num1 * num2 << endl;
                break;
            case '/':
                if (num2 != 0) {
                    cout << "Result: " << num1 / num2 << endl;
                } else {
                    cout << "Division by zero is not allowed!" << endl;
                }
                break;
            default:
                cout << "Invalid operation!" << endl;
                break;
        }

        cout << "Do you want to perform another calculation? (Y/N): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (choice == 'Y' || choice == 'y');

    cout << "Thank you for using the Calculator program!" << endl;

    return 0;
}
