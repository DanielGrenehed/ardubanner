#include "messagehandler.hpp"

#define MAX_MESSAGES 12
const float min_persent = 1.0/MAX_MESSAGES;

bool MessageHandler::addMessage(int ammount, std::string msg, std::string author) {
    return addMessage(Message(ammount, msg, author));
}

bool MessageHandler::addMessage(Message m) {
    if (m.getAmmount() <= 0) return false;
    if ((((float)m.getAmmount())/(sum_paid+m.getAmmount())) >= min_persent) {
        messages.push_back(m);
        sum_paid +=m.getAmmount();
    } else {
        return false;
    }
    return true;
}



void MessageHandler::removeZeroTimeMessages() {
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

void MessageHandler::clear() {
    messages.clear();
    sum_paid = 0;
}

std::vector<std::string> MessageHandler::serialize() {
    std::vector<std::string> commands;
    removeZeroTimeMessages();
    for(std::vector<Message>::iterator it = messages.begin(); it != messages.end(); ++it) {

        std::string command = std::to_string(it->getAmmount()) + ":" + it->getAuthor() + ":"+ it->getText();
        commands.push_back(command);
    }
    return commands;
}

std::vector<TimedMessage> MessageHandler::calculateTimedMessages() {
    std::vector<TimedMessage> msgs;
    removeZeroTimeMessages();
    for(std::vector<Message>::iterator it = messages.begin(); it != messages.end(); ++it) {
        int time = (((float)it->getAmmount())/(sum_paid)) * 60;
        TimedMessage tmsg = {it->getText(), time};
        //std::string command = std::to_string(time) + ":" + it->getText();
        msgs.push_back(tmsg);
    }
    return msgs;
}