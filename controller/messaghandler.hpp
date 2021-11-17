#ifndef MESSAGEHANDER_HPP
#define MESSAGEHANDER_HPP

//keybr.com
#include "message.hpp"
#include <vector>

class MessageHandler {
private:
    std::vector<Message> messages;
    int sum_paid;
public:
    MessageHandler(): sum_paid(0) {}

    bool addMessage(int ammount, std::string msg);

    void removeZeroTimeMessages();
    
    std::vector<std::string> serializeCommands();
};

#endif /* ifndef MESSAGEMANDLER_HPP */