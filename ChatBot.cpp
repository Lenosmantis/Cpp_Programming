#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class ChatBot {
private:
    map<string, vector<string>> training_data;
    vector<string> memory;

public:
    ChatBot() {
        training_data = {
            {"hello", {"Hello! How are you?", "Good day!", "Hi there!"}},
            {"how are you?", {"Fine, thank you for asking.", "I'm doing well, thanks.", "Not too bad."}},
            {"what's your name?", {"My name is ChatBot.", "You can call me ChatBot.", "I'm ChatBot."}},
            {"goodbye", {"Goodbye! Have a nice day!", "See you later!", "Bye!"}},
            {"what's the weather like?", {"I don't have access to weather data.", "I'm not sure about the weather.", "I can't tell you the weather."}},
            {"what's up?", { "Many things", "Various things", "Not much" }},
            {"what time is it?", {"Now is the time to talk with ChatBot!", "Time for a chat!", "I don't have a watch!"}},
            {"what can you do?", { "I can answer your questions.", "I'm here to chat with you.", "I'm a simple ChatBot."}},
            {"tell me a joke;", { "The cat walks into a bar. The bartender says, 'What'll you have?' The cat says, 'A beer, please. And a saucer of milk for my friend here.'" }},
            {"help", { "The available questions for the ChatBot are:", "Here are the questions I can answer:", "You can ask me the following questions:"}},
        };
    }

    string getRandomResponse(const vector<string>& responses) {
        int index = rand() % responses.size();
        return responses[index];
    }

    string getResponse(const string& question) {
        string response;

        if (question == "what time is it?") {
            tellTime();
            return "";
        }

        auto it = training_data.find(question);
        if (it != training_data.end()) {
            memory.push_back(question);
            response = getRandomResponse(it->second);
        } else {
            memory.push_back(question);
            response =  "Sorry, I can't understand your question.";
        }
        return response;
    }

    void showHelp() {
        cout << "The available questions for the ChatBot are:" << endl;
        bool helpDisplayed = false;
        for (const auto& entry : training_data) {
            if (entry.first == "help" && !helpDisplayed) {
                cout <<  "- " << entry.first << endl;
                helpDisplayed = true;
            } else if (entry.first != "help") {
                cout <<  "- " << entry.first << endl;
            }
        }
    }

    bool playAgain() {
        string choice;
        cout << "Do you want to chat with me again? (y/n): ";
        getline(cin, choice);
        return choice == "y";
    }

    void tellTime() {
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        cout << "The current time is: " << asctime(timeinfo);
    }

    string creator() {
        return "LeonDev";
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    ChatBot chatbot;
    cout <<"Welcome to ChatBot! For more help, type 'help'." << endl;

    string question;
    do {
        cout << "> ";
        getline(cin, question);

        if (question == "goodbye") {
            cout <<"Goodbye! Have a nice day!" << endl;
            break;
        } else if (question == "help") {
            chatbot.showHelp();
            continue;
        } else if (question == "what time is it?") {
            chatbot.tellTime();
            continue;
        }

        cout << chatbot.getResponse(question) << endl;
    } while (chatbot.playAgain());

    cout << "My creator is " << chatbot.creator() << endl;

    return 0;
}
