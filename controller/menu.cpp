#include "menu.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib> 
#include <random>



void Menu::printMenu() {
    std::cout << "1: Purchase ad\n";
    std::cout << "2: Update displays\n";
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
            updateSerial();
            break;

        }
    }

}

void Menu::addMessage() {
    int ammount;
    std::cout << "Enter ammount paid: \n";
    std::cin >> ammount;
    std::cin.clear();
    fflush(stdin);
    std::string text;
    std::cout << "Enter message to be displayed, use '|' for newline:\n";
    std::getline(std::cin, text);
    std::cin.clear();
    fflush(stdin);

    msghand.addMessage(ammount, text);
}

void Menu::updateSerial() {
    std::vector<std::string> commands = msghand.serializeCommands();
    std::string header = "U:"+ std::to_string(commands.size());
    for (std::shared_ptr<Serial> s: ports) {
        std::shuffle(commands.begin(), commands.end(), std::default_random_engine());

        char tmp[256];
        strcpy(tmp, header.c_str());
        tmp[header.size()] = '\n';
        tmp[header.size()+1] = 0;
        s->writeToPort(tmp, strlen(tmp));
        std::cout << tmp;
        
        for (std::string msg: commands) {

            char temp[256];
            strcpy(temp, msg.c_str());
            temp[msg.size()] = '\n';
            temp[msg.size()+1] = 0;
            s->writeToPort(temp, strlen(temp));
            std::cout << temp;
        }
    }
}
