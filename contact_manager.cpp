#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

vector<Contact> contacts;

bool is_valid_name(const string& name) {
    return all_of(name.begin(), name.end(), ::isalpha);
}

bool is_valid_phone(const string& phone) {
    return all_of(phone.begin(), phone.end(), ::isdigit);
}

bool is_valid_email(const string& email) {
    size_t at_pos = email.find('@');
    return at_pos != string::npos && email.find('.', at_pos) != string::npos;
}

void add_contact() {
    string name;
    string phone;
    string email;

    while (true) {
        cout << "Enter the name of the contact: ";
        getline(cin, name);
        if (!name.empty() && is_valid_name(name)) {
            break;
        } else {
            cout << "Name must contain only alphabetical characters and cannot be empty." << endl;
        }
    }

    while (true) {
        cout << "Enter the phone number of the contact: ";
        getline(cin, phone);
        if (is_valid_phone(phone)) {
            break;
        } else {
            cout << "Phone number must consist only of digits." << endl;
        }
    }

    while (true) {
        cout << "Enter the email of the contact: ";
        getline(cin, email);
        if (is_valid_email(email)) {
            break;
        } else {
            cout << "Email must have a valid format (e.g., example@example.com)." << endl;
        }
    }

    contacts.push_back({name, phone, email});
    cout << "Contact added successfully." << endl;
}

void display_contacts() {
    if (contacts.empty()) {
        cout << "No contacts available." << endl;
    } else {
        cout << "Your contacts:" << endl;
        for (size_t i = 0; i < contacts.size(); ++i) {
            cout << i + 1 << ". Name: " << contacts[i].name << ", Phone: " << contacts[i].phone << ", Email: " << contacts[i].email << endl;
        }
    }
}

void delete_contact() {
    display_contacts();
    if (contacts.empty()) {
        return;
    }

    while (true) {
        string choice;
        cout << "Select the number of the contact you want to delete: ";
        getline(cin, choice);
        if (all_of(choice.begin(), choice.end(), ::isdigit) && stoi(choice) >= 1 && stoi(choice) <= contacts.size()) {
            contacts.erase(contacts.begin() + stoi(choice) - 1);
            cout << "Contact deleted successfully." << endl;
            break;
        } else {
            cout << "Invalid choice. Please select a valid number." << endl;
        }
    }
}

void save_contacts(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& contact : contacts) {
            file << contact.name << "," << contact.phone << "," << contact.email << endl;
        }
        cout << "Contacts saved to " << filename << " successfully." << endl;
        file.close();
    } else {
        cout << "Unable to open file " << filename << " for saving contacts." << endl;
    }
}

void load_contacts(const string& filename) {
    contacts.clear();
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            string name = line.substr(0, pos1);
            string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string email = line.substr(pos2 + 1);
            contacts.push_back({name, phone, email});
        }
        cout << "Contacts loaded from " << filename << " successfully." << endl;
        file.close();
    } else {
        cout << "Unable to open file " << filename << " for loading contacts." << endl;
    }
}

int main() {
    load_contacts("contacts.txt");

    while (true) {
        cout << "\nWelcome to the contact manager!" << endl;
        cout << "Options:" << endl;
        cout << "1. Add contact" << endl;
        cout << "2. Display contacts" << endl;
        cout << "3. Delete contact" << endl;
        cout << "4. Save contacts" << endl;
        cout << "5. Exit" << endl;

        string choice;
        cout << "Select an option: ";
        getline(cin, choice);

        if (choice == "1") {
            add_contact();
        } else if (choice == "2") {
            display_contacts();
        } else if (choice == "3") {
            delete_contact();
        } else if (choice == "4") {
            save_contacts("contacts.txt");
        } else if (choice == "5") {
            cout << "Program ended. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

