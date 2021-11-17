#include "messaghandler.hpp"


bool MessageHandler::addMessage(int ammount, std::string msg) {
    // is ammount enough to display message
    if ((((float)ammount)/(sum_paid+ammount)) >= 0.05) {
        messages.push_back(Message(ammount, msg));
        sum_paid += ammount;
    } else {
        return false;
    }
    return true;
}

void MessageHandler::removeZeroTimeMessages() {
    int sum_deleted = 0;
    for (int i = 0; i < messages.size(); i++) {
        int ammount = messages[i].getAmmount();
        if ((((float)ammount)/(sum_paid)) < 0.05) {
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