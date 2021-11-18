#include "messaghandler.hpp"
#include <iostream>

#define MAX_MESSAGES 12
const float min_persent = 1.0/MAX_MESSAGES;

bool MessageHandler::addMessage(int ammount, std::string msg) {
    // is ammount enough to display message
    if ((((float)ammount)/(sum_paid+ammount)) >= min_persent) {
        messages.push_back(Message(ammount, msg));
        sum_paid += ammount;
    } else {
        return false;
    }
    return true;
}

void MessageHandler::removeZeroTimeMessages() {
    std::cout << min_persent << std::endl;
    int sum_deleted = 0;
    for (int i = 0; i < messages.size(); i++) {
        int ammount = messages[i].getAmmount();
        if ((((float)ammount)/(sum_paid)) < min_persent) {
            sum_deleted += ammount;
            messages.erase(messages.begin()+i);
            i--;
        }
    }
    sum_paid -= sum_deleted;
}

std::vector<std::string> MessageHandler::serializeCommands() {
    std::vector<std::string> commands;
    removeZeroTimeMessages();
    for (Message m : messages) {
        // construct time:message
        int time = (((float)m.getAmmount())/(sum_paid)) * 60;
        std::string command = std::to_string(time) + ":" + m.getText();
        commands.push_back(command);
    }
    return commands;
}