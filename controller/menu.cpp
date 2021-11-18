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
    }
}
