#include "menu.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib> 
#include <random>
#include "save.hpp"


Menu::Menu(std::vector<std::shared_ptr<Serial> > ports) : ports(ports) {
    for (int i=0; i < ports.size(); i++) {
        //std::shared_ptr<DisplayUpdater> updtr;
        shared_data.push_back((std::shared_ptr<ThreadData>)(new ThreadData()));
        threads.push_back(std::thread(UpdateDisplay, shared_data[i], ports[i]));
    }
}
Menu::~Menu() {
    for (int i = 0; i < shared_data.size(); i++) {
        shared_data[i]->stop();
    }
    for (int i  = 0; i < threads.size(); i++) {
        threads[i].join();
    }
    threads.clear();
    shared_data.clear();
}

void Menu::printMenu() {
    std::cout << "1: Purchase ad\n";
    std::cout << "2: Load from file\n";
    std::cout << "3: Save to file\n";
    std::cout << "4: Print messages\n";
    std::cout << "0: Quit\n";
    std::cout << "Enter your choice:\n";
}

void Menu::show() {
    int choice = -1;
    while (choice != 0) {
        printMenu();
        std::cin >> choice;
        std::cin.clear();
        fflush(stdin);
        switch(choice) {
            case 1:
            addMessage();
            break;
            case 2:
            loadFromFile();
            break;
            case 3:
            saveToFile();
            break;
            case 4:
            printMessages();
            break;

        }
    }

}

static std::string getLine(bool &success) {
    std::string text;
    std::getline(std::cin, text);
    std::cin.clear();
    fflush(stdin);
    if (text.length() >= 90) success = false;
    return text;
}

void Menu::addMessage() {
    int ammount;
    std::cout << "Enter ammount paid: \n";
    std::cin >> ammount;
    std::cin.clear();
    fflush(stdin);
    std::string text;
    std::cout << "Enter first line:\n";
    bool success = true;
    text += getLine(success);
    if (!success) {
        std::cout << "Your text is exceeding the limits\n";
        return;
    }
    std::cout << "Enter second line:\n";
    text += '|' + getLine(success);
    if (!success) {
        std::cout << "Your text is exceeding the limits\n";
        return;
    }
    std::cout << "Enter your company name: \n";
    std::string author = getLine(success);
    if (!success) {
        std::cout << "That is not an acceptible company name!!\n";
        return;
    }

    if (!message_handler.addMessage({ammount, text, author})) {
        std::cout << "Failed to add message!\n";
        return;
    }
    updateSerial();
}

void Menu::updateSerial() {
    std::vector<TimedMessage> messages = message_handler.calculateTimedMessages();
    std::default_random_engine e(0);
    for (std::vector<std::shared_ptr<ThreadData> >::iterator it = shared_data.begin(); it != shared_data.end(); ++it) {
        std::shuffle(messages.begin(), messages.end(), e);
        (*it)->setData(messages);
    }
}

static Message messageFromLine(std::string line) {
    int i = line.find(':');
    if (i < 0) return Message(0, "", "");
      
    int amount = stoi(line.substr(0, i));
    line = line.substr(i+1);
    i = line.find(':');
    if (i < 0) return Message(0, "", "");
    
    std::string author = line.substr(0, i);
    std::string msg = line.substr(i+1);
    return Message(amount, msg, author);
}

void Menu::addMessagesFromLines(std::vector<std::string> lines) {
    for (int i = 0; i < lines.size(); i++) message_handler.addMessage(messageFromLine(lines[i]));
}

void Menu::loadFromFile() {
    bool success = true;
    std::cout << "Enter file to load from:\n";
    std::string filename = getLine(success);
    std::vector<std::string> lines = loadLinesFromFile(filename);
    if (!success || lines.size() == 0) {
        std::cout << "Failed to load from '" + filename + "'\n";
        return;
    }

    message_handler.clear();
    addMessagesFromLines(lines);

    updateSerial();
}

void Menu::saveToFile() {
    bool success = true;
    std::cout << "Enter file to save to:\n";
    std::string filename = getLine(success);
    if (!writeLinesToFile(message_handler.serialize(), filename)) {
        std::cout << "Could not write to file '" + filename + "'!\n";
    }
}

void Menu::printMessages() {
    std::vector<std::string> cerial = message_handler.serialize();
    for (int i = 0; i < cerial.size(); i++) std::cout << cerial[i] << std::endl;
}