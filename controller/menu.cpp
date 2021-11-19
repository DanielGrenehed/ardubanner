#include "menu.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib> 
#include <random>


Menu::Menu(std::vector<std::shared_ptr<Serial> > ports) : ports(ports) {
    for (int i=0; i < ports.size(); i++) {
        //std::shared_ptr<DisplayUpdater> updtr;
        updaters.push_back((std::shared_ptr<DisplayUpdater>)(new DisplayUpdater()));
        threads.push_back(std::thread(UpdateDisplay, updaters[i], ports[i]));
    }
}
Menu::~Menu() {
    for (int i = 0; i < updaters.size(); i++) {
        updaters[i]->stop();
    }
    for (int i  = 0; i < threads.size(); i++) {
        threads[i].join();
    }
    threads.clear();
    updaters.clear();
}

void Menu::printMenu() {
    std::cout << "1: Purchase ad\n";
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

    if(msghand.addMessage(ammount, text)){
       updateSerial(); 
       std::cout << "Ad succesfully added\n";

    } else{
        std::cout << "Ad was not succesfully added, minimum price not reached\n";
    }
    
    
}

void Menu::updateSerial() {
    std::vector<TimedMessage> messages = msghand.calculateTimedMessages();
    std::default_random_engine e(0);
    for (std::vector<std::shared_ptr<DisplayUpdater> >::iterator it = updaters.begin(); it != updaters.end(); ++it) {
        std::shuffle(messages.begin(), messages.end(), e);
        (*it)->setData(messages);
    }
    /* std::vector<std::string> commands = msghand.serializeCommands();
    std::string header = "U:"+ std::to_string(commands.size());
    std::default_random_engine e(0);
    for (std::vector<std::shared_ptr<Serial> >::iterator pit = ports.begin(); pit != ports.end(); ++pit) {
        //std::shuffle(commands.begin(), commands.end(), std::default_random_engine());
        std::shuffle(commands.begin(), commands.end(), e);

        char tmp[256];
        strcpy(tmp, header.c_str());
        tmp[header.size()] = '\n';
        tmp[header.size()+1] = 0;
        (*pit)->writeToPort(tmp, strlen(tmp));
        std::cout << tmp;
        
        for (std::vector<std::string>::iterator it = commands.begin(); it != commands.end(); ++it) {

            char temp[256];
            strcpy(temp, it->c_str());
            temp[it->size()] = '\n';
            temp[it->size()+1] = 0;
            (*pit)->writeToPort(temp, strlen(temp));
            std::cout << temp;
        }
    } */
}
